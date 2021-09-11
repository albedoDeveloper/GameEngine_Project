#include "CPointLight.h"
#include "GraphicsEngine.h"

CPointLight::CPointLight(Transform* parent, GameObject* parentObj)
	:Component{ parent, parentObj },
	LightInfo{}
{
	LightInfo.ambientColour = Vector3f(0.2f, 0.2f, 0.2f);
	LightInfo.diffuseColour = Vector3f(0.8f, 0.8f, 0.8f);
	LightInfo.specularColour = Vector3f(1, 1, 1);
	LightInfo.constant = 1;
	LightInfo.linear = 0.09f;
	LightInfo.quadratic = 0.032f;
	GRAPHICS->AddPointLight(this);
}
