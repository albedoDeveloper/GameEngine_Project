#include "CSpotlight.h"
#include "GraphicsEngine.h"
#include "LightFactory.h"

CSpotlight::CSpotlight(Transform* parent, GameObject* parentObj) : Component(parent, parentObj)
{
	LIGHTS->AddSpotlight(this);

	colour = new Vector4f(1, 1, 1, 1);
	beamWidth = 30;
	beamLength = 10;
}

Vector4f* CSpotlight::GetColour() const
{
	return colour;
}

void CSpotlight::SetColour(Vector4f* colour)
{
	this->colour = colour;
}

int CSpotlight::GetBeamWidth()
{
	return beamWidth;
}

void CSpotlight::SetBeamWidth(int angle)
{
	beamWidth = angle;
}

void CSpotlight::Start()
{

}

void CSpotlight::Update()
{
	//GRAPHICS->UpdateSpotlight(this);
	//GRAPHICS->initLighting();
}

void CSpotlight::Render()
{
	GRAPHICS->initLighting();
}

void CSpotlight::LateRender()
{
}