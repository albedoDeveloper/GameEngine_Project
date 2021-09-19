#pragma once

#include <glew/GL/glew.h>
#include "CDirectionalLight.h"
#include "Matrix4f.h"

class ShadowMapper
{
public:
	ShadowMapper();
	void Init();
	void Render();
	void AssignLight(const CDirectionalLight *light);
	bool IsInitialised() const;

private:
	bool m_initialised;
	unsigned int m_depthMapFBO;
	unsigned int m_depthMap;
	unsigned int m_shadowWidth;
	unsigned int m_shadowHeight;
	const CDirectionalLight *m_light;
	Matrix4f m_projection;
};
