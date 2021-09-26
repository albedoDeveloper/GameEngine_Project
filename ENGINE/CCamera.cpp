#include "GameObject.h"
#include "CCamera.h"
#include "GraphicsEngine.h"

CCamera::CCamera(Transform *parent, GameObject *parentObj)
	:CComponent{ parent, parentObj }
	, m_camera{}
{
}

void CCamera::Start()
{
	m_camera = Camera();
}

void CCamera::DrawToImGui()
{
	//ImGui::Text("staticMesh TREE");
	if (ImGui::TreeNode("Camera Component"))
	{
		ImGui::Text("Camera info : ");
		ImGui::TreePop();

	}
}

void CCamera::SetCamera(Camera camera)
{
	m_camera = camera;
}

Camera CCamera::GetCamera()
{
	return m_camera;
}

void CCamera::SetAsCurrentCamera()
{
	GRAPHICS->SetDisplayCamera(this);
}