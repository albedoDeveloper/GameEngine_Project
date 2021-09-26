#include "ShadowMapper.h"
#include "MiscMath.h"
#include <glad/glad.h>
#include "Utility.h"

ShadowMapper::ShadowMapper()
	:m_dirLightFBO{}, m_dirDepthMapTexObj{}, m_dirShadowRes{ 16384 }, m_dirLight{ nullptr }, m_initialised{ false },
	m_directionalProjection{}, m_pointShadowRes{ 2048 }, m_pointLightFBOs{}, m_pointLightFarPlane{ 30.f }
{
	m_directionalProjection = Ortho(-20.f, 20.f, -20.f, 20.f, 2.f, 30.f);
	m_pointProjection = Perspective(90, 1, 0.1f, m_pointLightFarPlane);
}

void ShadowMapper::Init()
{
	// directional depthmap
	glGenFramebuffers(1, &m_dirLightFBO); CHECK_GL_ERROR();
	glGenTextures(1, &m_dirDepthMapTexObj); CHECK_GL_ERROR();
	glBindTexture(GL_TEXTURE_2D, m_dirDepthMapTexObj); CHECK_GL_ERROR();
	glTexImage2D(
		GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT,
		m_dirShadowRes, m_dirShadowRes, 0, GL_DEPTH_COMPONENT,
		GL_FLOAT, nullptr
	); CHECK_GL_ERROR();
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); CHECK_GL_ERROR();
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST); CHECK_GL_ERROR();
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER); CHECK_GL_ERROR();
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER); CHECK_GL_ERROR();
	float borderColor[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor); CHECK_GL_ERROR();
	glBindFramebuffer(GL_FRAMEBUFFER, m_dirLightFBO); CHECK_GL_ERROR();
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, m_dirDepthMapTexObj, 0); CHECK_GL_ERROR();
	glDrawBuffer(GL_NONE); CHECK_GL_ERROR();
	glReadBuffer(GL_NONE); CHECK_GL_ERROR();
	glBindFramebuffer(GL_FRAMEBUFFER, 0); CHECK_GL_ERROR();
	glBindTexture(GL_TEXTURE_2D, 0); CHECK_GL_ERROR();

	m_initialised = true;
}

void ShadowMapper::SetupDirLightFBO()
{
	glViewport(0, 0, m_dirShadowRes, m_dirShadowRes); CHECK_GL_ERROR();
	glBindFramebuffer(GL_FRAMEBUFFER, m_dirLightFBO); CHECK_GL_ERROR();
	glClear(GL_DEPTH_BUFFER_BIT); CHECK_GL_ERROR();
}

void ShadowMapper::SetupPointLightFBO(unsigned lightIndex)
{
	assert(m_pointLightFBOs.size() > lightIndex);
	glViewport(0, 0, m_pointShadowRes, m_pointShadowRes); CHECK_GL_ERROR();
	glBindFramebuffer(GL_FRAMEBUFFER, m_pointLightFBOs[lightIndex]); CHECK_GL_ERROR();
	glClear(GL_DEPTH_BUFFER_BIT); CHECK_GL_ERROR();
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
	glGenTextures(1, &texObj); CHECK_GL_ERROR();
	m_pointDepthCubeMapTexObjs.push_back(texObj);
	glBindTexture(GL_TEXTURE_CUBE_MAP, m_pointDepthCubeMapTexObjs[lightVectorIndex]); CHECK_GL_ERROR();
	for (unsigned int i = 0; i < 6; i++)
	{
		glTexImage2D(
			GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_DEPTH_COMPONENT,
			m_pointShadowRes, m_pointShadowRes, 0, GL_DEPTH_COMPONENT,
			GL_FLOAT, NULL
		); CHECK_GL_ERROR();
	}
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_NEAREST); CHECK_GL_ERROR();
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_NEAREST); CHECK_GL_ERROR();
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); CHECK_GL_ERROR();
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE); CHECK_GL_ERROR();
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE); CHECK_GL_ERROR();

	// point depthcube FBO
	unsigned fbo;
	glGenFramebuffers(1, &fbo); CHECK_GL_ERROR();
	m_pointLightFBOs.push_back(fbo);
	glBindFramebuffer(GL_FRAMEBUFFER, m_pointLightFBOs[lightVectorIndex]); CHECK_GL_ERROR();
	glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, m_pointDepthCubeMapTexObjs[lightVectorIndex], 0); CHECK_GL_ERROR();
	glDrawBuffer(GL_NONE); CHECK_GL_ERROR();
	glReadBuffer(GL_NONE); CHECK_GL_ERROR();
	glBindFramebuffer(GL_FRAMEBUFFER, 0); CHECK_GL_ERROR();
}

bool ShadowMapper::IsInitialised() const
{
	return m_initialised;
}

void ShadowMapper::BindDirShadowDepthMapTexture() const
{
	glBindTexture(GL_TEXTURE_2D, m_dirDepthMapTexObj); CHECK_GL_ERROR();
}

void ShadowMapper::BindPointDepthCubeMapTexture(unsigned lightIndex) const
{
	assert(m_pointDepthCubeMapTexObjs.size() > lightIndex);
	glBindTexture(GL_TEXTURE_CUBE_MAP, m_pointDepthCubeMapTexObjs[lightIndex]); CHECK_GL_ERROR();
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

float ShadowMapper::GetPointLightFarPlane() const
{
	return m_pointLightFarPlane;
}

bool ShadowMapper::DirLightAcive() const
{
	return (m_dirLight != nullptr);
}
