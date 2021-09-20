#pragma once

#include <glew/GL/glew.h>
#include "CDirectionalLight.h"
#include "Matrix4f.h"

class ShadowMapper
{
public:
	ShadowMapper();
	void Init();
	void SetupDirLightFBO();
	void SetupPointLightFBO();
	void AssignLight(const CDirectionalLight *light);
	bool IsInitialised() const;
	void BindDepthMapTexture() const;
	Matrix4f GetProjViewMat();

private:
	void ConfigureShaderAndMatrices();

	bool m_initialised;
	unsigned int m_depthMapFBO;
	unsigned int m_depthCubeFBO;
	unsigned int m_depthMapTexObj;
	unsigned int m_depthCubemap;
	unsigned int m_dirShadowRes;
	unsigned int m_pointShadowRes;
	const CDirectionalLight *m_light;
	Matrix4f m_directionalProjection;
	Matrix4f m_pointProjection;
	Matrix4f m_view;
};
