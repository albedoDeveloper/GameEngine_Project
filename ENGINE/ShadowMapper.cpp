#include "ShadowMapper.h"
#include "MiscMath.h"

ShadowMapper::ShadowMapper()
	:m_depthMapFBO{}, m_depthMapTexObj{}, m_dirShadowRes{ 16384 }, m_light{ nullptr }, m_initialised{ false },
	m_directionalProjection{}, m_depthCubemap{}, m_pointShadowRes{ 4096 }
{
	m_directionalProjection = Ortho(-20.f, 20.f, -20.f, 20.f, 2.f, 30.f);
	//m_pointProjection = Perspective(90, 1, )
}

void ShadowMapper::Init()
{
	// directional depthmap
	glGenFramebuffers(1, &m_depthMapFBO);
	glGenTextures(1, &m_depthMapTexObj);
	glBindTexture(GL_TEXTURE_2D, m_depthMapTexObj);
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
	glBindFramebuffer(GL_FRAMEBUFFER, m_depthMapFBO);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, m_depthMapTexObj, 0);
	glDrawBuffer(GL_NONE);
	glReadBuffer(GL_NONE);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glBindTexture(GL_TEXTURE_2D, 0);

	// point depthcube
	glGenTextures(1, &m_depthCubemap);
	glBindTexture(GL_TEXTURE_CUBE_MAP, m_depthCubemap);
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
	glGenFramebuffers(1, &m_depthCubeFBO);
	glBindFramebuffer(GL_FRAMEBUFFER, m_depthCubeFBO);
	glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, m_depthCubemap, 0);
	glDrawBuffer(GL_NONE);
	glReadBuffer(GL_NONE);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	m_initialised = true;
}

void ShadowMapper::SetupDirLightFBO()
{
	glViewport(0, 0, m_dirShadowRes, m_dirShadowRes);
	glBindFramebuffer(GL_FRAMEBUFFER, m_depthMapFBO);
	glClear(GL_DEPTH_BUFFER_BIT);
}

void ShadowMapper::SetupPointLightFBO()
{
	glViewport(0, 0, m_pointShadowRes, m_pointShadowRes);
	glBindFramebuffer(GL_FRAMEBUFFER, m_depthCubeFBO);
	glClear(GL_DEPTH_BUFFER_BIT);
}

void ShadowMapper::AssignLight(const CDirectionalLight *light)
{
	m_light = light;
}

bool ShadowMapper::IsInitialised() const
{
	return m_initialised;
}

void ShadowMapper::BindDepthMapTexture() const
{
	glBindTexture(GL_TEXTURE_2D, m_depthMapTexObj);
}

Matrix4f ShadowMapper::GetProjViewMat()
{
	ConfigureShaderAndMatrices();
	return m_directionalProjection * m_view;
}

void ShadowMapper::ConfigureShaderAndMatrices()
{
	if (m_light)
	{
		m_view = LookAt(
			m_light->GetTransformConst().GetWorldTransform().GetRelativePosition(),
			m_light->GetTransformConst().GetWorldTransform().GetRelativePosition() + m_light->GetTransformConst().GetWorldTransform().GetRelativeForward(),
			m_light->GetTransformConst().GetWorldTransform().GetRelativeUp()
		);
	}
}
