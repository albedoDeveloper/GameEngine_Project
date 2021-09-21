#include "ShadowMapper.h"
#include "MiscMath.h"
#include <glad/glad.h>

ShadowMapper::ShadowMapper()
	:m_dirLightFBO{}, m_dirDepthMapTexObj{}, m_dirShadowRes{ 16384 }, m_dirLight{ nullptr }, m_initialised{ false },
	m_directionalProjection{}, m_pointShadowRes{ 4096 }, m_pointLightFBOs{}
{
	m_directionalProjection = Ortho(-20.f, 20.f, -20.f, 20.f, 2.f, 30.f);
	m_pointProjection = Perspective(90, 1, 0.1f, 50.f);
}

void ShadowMapper::Init()
{
	// directional depthmap
	glGenFramebuffers(1, &m_dirLightFBO);
	glGenTextures(1, &m_dirDepthMapTexObj);
	glBindTexture(GL_TEXTURE_2D, m_dirDepthMapTexObj);
	glTexImage2D(
		GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT,
		m_dirShadowRes, m_dirShadowRes, 0, GL_DEPTH_COMPONENT,
		GL_FLOAT, nullptr
	);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
	float borderColor[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);
	glBindFramebuffer(GL_FRAMEBUFFER, m_dirLightFBO);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, m_dirDepthMapTexObj, 0);
	glDrawBuffer(GL_NONE);
	glReadBuffer(GL_NONE);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glBindTexture(GL_TEXTURE_2D, 0);

	m_initialised = true;
}

void ShadowMapper::SetupDirLightFBO()
{
	glViewport(0, 0, m_dirShadowRes, m_dirShadowRes);
	glBindFramebuffer(GL_FRAMEBUFFER, m_dirLightFBO);
	glClear(GL_DEPTH_BUFFER_BIT);
}

void ShadowMapper::SetupPointLightFBO(unsigned lightIndex)
{
	glViewport(0, 0, m_pointShadowRes, m_pointShadowRes);
	glBindFramebuffer(GL_FRAMEBUFFER, m_pointLightFBOs[lightIndex]);
	glClear(GL_DEPTH_BUFFER_BIT);
}

void ShadowMapper::AssignDirLight(const CDirectionalLight *light)
{
	m_dirLight = light;
}

void ShadowMapper::AddPointLight(CPointLight *light)
{
	m_pointLights.push_back(light);

	const unsigned lightVectorIndex = m_pointLights.size() - 1;
	unsigned texObj;
	glGenTextures(1, &texObj);
	m_pointDepthCubeMapTexObjs.push_back(texObj);
	glBindTexture(GL_TEXTURE_CUBE_MAP, m_pointDepthCubeMapTexObjs[lightVectorIndex]);
	for (unsigned int i = 0; i < 6; ++i)
	{
		glTexImage2D(
			GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_DEPTH_COMPONENT,
			m_pointShadowRes, m_pointShadowRes, 0, GL_DEPTH_COMPONENT,
			GL_FLOAT, NULL
		);
	}
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

	// point depthcube
	unsigned fbo;
	glGenFramebuffers(1, &fbo);
	m_pointLightFBOs.push_back(fbo);
	glBindFramebuffer(GL_FRAMEBUFFER, m_pointLightFBOs[lightVectorIndex]);
	glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, m_pointDepthCubeMapTexObjs[lightVectorIndex], 0);
	glDrawBuffer(GL_NONE);
	glReadBuffer(GL_NONE);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

bool ShadowMapper::IsInitialised() const
{
	return m_initialised;
}

void ShadowMapper::BindDirShadowDepthMapTexture() const
{
	glBindTexture(GL_TEXTURE_2D, m_dirDepthMapTexObj);
}

void ShadowMapper::BindPointDepthCubeMapTexture(unsigned lightIndex) const
{
	assert(m_pointDepthCubeMapTexObjs.size() > lightIndex);
	glBindTexture(GL_TEXTURE_CUBE_MAP, m_pointDepthCubeMapTexObjs[lightIndex]);
}

Matrix4f ShadowMapper::GetDirProjViewMat() const
{
	Matrix4f view;
	if (m_dirLight)
	{
		view = LookAt(
			m_dirLight->GetTransformConst().GetWorldTransform().GetRelativePosition(),
			m_dirLight->GetTransformConst().GetWorldTransform().GetRelativePosition() + m_dirLight->GetTransformConst().GetWorldTransform().GetRelativeForward(),
			m_dirLight->GetTransformConst().GetWorldTransform().GetRelativeUp()
		);
	}
	return m_directionalProjection * view;
}

std::vector<Matrix4f> ShadowMapper::GetPointProjViewMat(unsigned lightIndex) const
{
	assert(m_pointLights.size() > lightIndex);

	std::vector<Matrix4f> views;

	views.push_back(m_pointProjection * LookAt(
		m_pointLights[lightIndex]->GetTransformConst().GetWorldTransform().GetRelativePosition(),
		m_pointLights[lightIndex]->GetTransformConst().GetWorldTransform().GetRelativePosition() + Vector3f(1.0f, 0.0f, 0.0f),
		Vector3f(0.0f, -1.0f, 0.0f)
	));
	views.push_back(m_pointProjection * LookAt(
		m_pointLights[lightIndex]->GetTransformConst().GetWorldTransform().GetRelativePosition(),
		m_pointLights[lightIndex]->GetTransformConst().GetWorldTransform().GetRelativePosition() + Vector3f(-1.0f, 0.0f, 0.0f),
		Vector3f(0.0f, -1.0f, 0.0f)
	));
	views.push_back(m_pointProjection * LookAt(
		m_pointLights[lightIndex]->GetTransformConst().GetWorldTransform().GetRelativePosition(),
		m_pointLights[lightIndex]->GetTransformConst().GetWorldTransform().GetRelativePosition() + Vector3f(0.0f, 1.0f, 0.0f),
		Vector3f(0.0f, 0.0f, 1.0f)
	));
	views.push_back(m_pointProjection * LookAt(
		m_pointLights[lightIndex]->GetTransformConst().GetWorldTransform().GetRelativePosition(),
		m_pointLights[lightIndex]->GetTransformConst().GetWorldTransform().GetRelativePosition() + Vector3f(0.0f, -1.0f, 0.0f),
		Vector3f(0.0f, 0.0f, -1.0f)
	));
	views.push_back(m_pointProjection * LookAt(
		m_pointLights[lightIndex]->GetTransformConst().GetWorldTransform().GetRelativePosition(),
		m_pointLights[lightIndex]->GetTransformConst().GetWorldTransform().GetRelativePosition() + Vector3f(0.0f, 0.0f, 1.0f),
		Vector3f(0.0f, -1.0f, 0.0f)
	));
	views.push_back(m_pointProjection * LookAt(
		m_pointLights[lightIndex]->GetTransformConst().GetWorldTransform().GetRelativePosition(),
		m_pointLights[lightIndex]->GetTransformConst().GetWorldTransform().GetRelativePosition() + Vector3f(0.0f, 0.0f, -1.0f),
		Vector3f(0.0f, -1.0f, 0.0f)
	));

	return views;
}
