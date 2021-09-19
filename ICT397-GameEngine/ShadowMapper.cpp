#include "ShadowMapper.h"
#include <iostream> // debug
#include "MiscMath.h"

ShadowMapper::ShadowMapper()
	:m_depthMapFBO{}, m_depthMapTexObj{}, m_shadowWidth{ 16384 }, m_shadowHeight{ 16384 }, m_light{ nullptr }, m_initialised{ false }, m_projection{}
{
	m_projection = Ortho(-20.f, 20.f, -20.f, 20.f, 2.f, 30.f);
}

void ShadowMapper::Init()
{
	glGenFramebuffers(1, &m_depthMapFBO);
	glGenTextures(1, &m_depthMapTexObj);
	glActiveTexture(GL_TEXTURE3);
	glBindTexture(GL_TEXTURE_2D, m_depthMapTexObj);
	glTexImage2D(
		GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT,
		m_shadowWidth, m_shadowHeight, 0, GL_DEPTH_COMPONENT,
		GL_FLOAT, nullptr
	);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glBindFramebuffer(GL_FRAMEBUFFER, m_depthMapFBO);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, m_depthMapTexObj, 0);
	glDrawBuffer(GL_NONE);
	glReadBuffer(GL_NONE);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glBindTexture(GL_TEXTURE_2D, 0);

	m_initialised = true;
}

void ShadowMapper::Render()
{
	glViewport(0, 0, m_shadowWidth, m_shadowHeight);
	glBindFramebuffer(GL_FRAMEBUFFER, m_depthMapFBO);
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
	return m_projection * m_view;
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
