#include "GameObject.h"
#include "CCameraComponent.h"
#include "GraphicsEngine.h"

#if _DEBUG
#include <iostream>
#endif

CCamera::CCamera(Transform* parent, GameObject* parentObj)
    :Component{ parent, parentObj }
    ,m_camera {}
{
}

void CCamera::Start()
{
    m_camera = Camera();
    //SetAsCurrentCamera();
}

void CCamera::Update()
{

    //m_camera.Transf.SetPositionV( m_parent->GetTransform()->GetPosition());
    //m_camera.Transf.SetRotation(m_parent->GetTransform()->GetRotation());
}

void CCamera::Render()
{
}

void CCamera::LateRender()
{
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