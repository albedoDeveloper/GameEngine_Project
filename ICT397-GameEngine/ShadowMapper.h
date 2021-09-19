#pragma once

#include <glew/GL/glew.h>
#include "CDirectionalLight.h"
#include "Matrix4f.h"

class ShadowMapper
{
	friend class Mesh;
public:
	ShadowMapper();
	void Init();
	void Render();
	void AssignLight(const CDirectionalLight *light);
	bool IsInitialised() const;
	void BindDepthMapTexture() const;
	Matrix4f GetProjViewMat();

private:
	void ConfigureShaderAndMatrices();

	bool m_initialised;
	unsigned int m_depthMapFBO;
	unsigned int m_depthMapTexObj;
	unsigned int m_shadowWidth;
	unsigned int m_shadowHeight;
	const CDirectionalLight *m_light;
	Matrix4f m_projection;
	Matrix4f m_view;
};
