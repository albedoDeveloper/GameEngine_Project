#include "ShadowMapper.h"
#include <iostream> // debug
#include "MiscMath.h"

ShadowMapper::ShadowMapper()
	:m_depthMapFBO{}, m_depthMap{}, m_shadowWidth{ 1024 }, m_shadowHeight{ 1024 }, m_light{ nullptr }, m_initialised{ false }, m_projection{}
{
	m_projection = Ortho(-10.f, 10.f, 10.f, 10.f, 1.f, 7.5f);
}

void ShadowMapper::Init()
{
	glGenFramebuffers(1, &m_depthMapFBO);
	glGenTextures(1, &m_depthMap);
	glBindTexture(GL_TEXTURE_2D, m_depthMap);
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
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, m_depthMap, 0);
	glDrawBuffer(GL_NONE);
	glReadBuffer(GL_NONE);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	m_initialised = true;
}

void ShadowMapper::Render()
{
	//// 1. first render to depth map
	//glViewport(0, 0, m_shadowWidth, m_shadowHeight);
	//glBindFramebuffer(GL_FRAMEBUFFER, m_depthMapFBO);
	//glClear(GL_DEPTH_BUFFER_BIT);
	//ConfigureShaderAndMatrices();
	//RenderScene();
	//glBindFramebuffer(GL_FRAMEBUFFER, 0);
	//// 2. then render scene as normal with shadow mapping (using depth map)
	//glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);
	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//ConfigureShaderAndMatrices();
	//glBindTexture(GL_TEXTURE_2D, depthMap);
	//RenderScene();
}

void ShadowMapper::AssignLight(const CDirectionalLight *light)
{
	m_light = light;
}

bool ShadowMapper::IsInitialised() const
{
	return m_initialised;
}
