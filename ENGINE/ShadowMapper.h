#pragma once

#include "CDirectionalLight.h"
#include "CPointLight.h"
#include "Matrix4f.h"
#include <vector>

class ShadowMapper
{
public:
	ShadowMapper();
	void Init();
	void SetupDirLightFBO();
	void SetupPointLightFBO(unsigned lightIndex);
	void AssignDirLight(const CDirectionalLight *light);
	void AddPointLight(CPointLight *light);
	bool IsInitialised() const;
	void BindDirShadowDepthMapTexture() const;
	void BindPointDepthCubeMapTexture(unsigned lightIndex) const;
	Matrix4f GetDirProjViewMat() const;
	std::vector<Matrix4f> GetPointProjViewMat(unsigned lightIndex) const;
	float GetPointLightFarPlane() const;
	bool DirLightAcive() const;

private:
	bool m_initialised;
	unsigned int m_dirLightFBO;
	std::vector<unsigned> m_pointLightFBOs;
	unsigned int m_dirDepthMapTexObj;
	std::vector<unsigned> m_pointDepthCubeMapTexObjs;
	unsigned int m_dirShadowRes;
	unsigned int m_pointShadowRes;
	const CDirectionalLight *m_dirLight;
	std::vector<CPointLight *> m_pointLights;
	Matrix4f m_directionalProjection;
	Matrix4f m_pointProjection;
	float m_pointLightFarPlane;
};
