#include "CWater.h"
#include "DeltaTime.h"
#include "GraphicsEngine.h"
#include "GameAssetFactory.h"

CWater::CWater(Transform* parent, GameObject* parentObj)
	:CStaticMesh{ parent, parentObj }
{
	texOffset = 0;
}

void CWater::Start()
{
}

void CWater::Update()
{

	if (directionForward) 
	{
		texOffset = texOffset + 0.05 * TIME->GetDeltaTime() ;
		if(texOffset >= 0.5)
			directionForward = !directionForward;
	}
	else if (!directionForward)
	{	
		texOffset = texOffset - 0.05f * TIME->GetDeltaTime();
		if (texOffset < 0.0)
			directionForward = !directionForward;
	}

}

void CWater::Render()
{
	GRAPHICS->DrawModelMovingTexture(m_model, m_transform.GetWorldTransform(), texOffset);
}

void CWater::LateRender()
{
}
