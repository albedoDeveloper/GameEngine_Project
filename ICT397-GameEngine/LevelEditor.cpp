#include "LevelEditor.h"
#include "GameObjectFactory.h"





LevelEditor::LevelEditor() 
{

}

void LevelEditor::DrawEditor()
{

	std::map<std::string, GameObject*>* objectList;

	objectList = GAMEOBJECT->GetObjectMap();

	ImGui::SetNextWindowSize(ImVec2(520, 600), ImGuiCond_FirstUseEver);
	
	ImGui::Begin("TEST");

	if (ImGui::CollapsingHeader("Window options"))
	{
		

		std::map<std::string, GameObject*>::iterator it;
		for (it = objectList->begin(); it != objectList->end(); it++)
		{
			ObjectHeader(it->second);
		}
	}

	ImGui::End();
}

void LevelEditor::ObjectHeader(GameObject* g)
{

	ImGui::AlignTextToFramePadding();

	
	std::string s{ "foo" };

	if (ImGui::TreeNode((char*)g->getFactoryKey().c_str()))
	{
		ImGui::AlignTextToFramePadding();

		TransformHeader(g);

		ImGui::TreePop();
	}
	
}

void LevelEditor::TransformHeader(GameObject* g)
{
	if (ImGui::CollapsingHeader("Transform") )
	{

		if (ImGui::TreeNode("Position"))
		{
			ImGuiSliderFlags flagx = ImGuiSliderFlags_None;
			ImGuiSliderFlags flagy = ImGuiSliderFlags_None;
			ImGuiSliderFlags flagz = ImGuiSliderFlags_None;
			// Drags
			float drag_x = g->GetTransform()->GetPosition().GetX();
			float drag_y = g->GetTransform()->GetPosition().GetY();
			float drag_z = g->GetTransform()->GetPosition().GetZ();

			ImGui::Text("X"); ImGui::SameLine(); ImGui::SameLine();
			ImGui::DragFloat("Drag X Pos", &drag_x, 0.005f, -FLT_MAX, +FLT_MAX, "%.3f",flagx);

			ImGui::Text("Y"); ImGui::SameLine(); ImGui::SameLine();
			ImGui::DragFloat("Drag Y Pos", &drag_y, 0.005f, -FLT_MAX, +FLT_MAX, "%.3f", flagy);

			ImGui::Text("Z"); ImGui::SameLine(); ImGui::SameLine();
			ImGui::DragFloat("Drag Z Pos", &drag_z, 0.005f, -FLT_MAX, +FLT_MAX, "%.3f", flagz);

			g->GetTransform()->SetPosition(drag_x, drag_y, drag_z);


			//ImGui::LabelText("label", "Value");
			ImGui::TreePop();

			
		}
		

		if (ImGui::TreeNode("Rotate"))
		{

			ImGuiSliderFlags flagx = ImGuiSliderFlags_None;
			ImGuiSliderFlags flagy = ImGuiSliderFlags_None;
			ImGuiSliderFlags flagz = ImGuiSliderFlags_None;
			// Drags
			Vector3f eulerRot = g->GetTransform()->GetRotation().GetEulerAngles();
			float drag_x = eulerRot.GetX();
			float drag_y = eulerRot.GetY();
			float drag_z = eulerRot.GetZ();

			ImGui::Text("X"); ImGui::SameLine(); ImGui::SameLine();
			ImGui::DragFloat("Drag X Rot", &drag_x, 0.005f, -FLT_MAX, +FLT_MAX, "%.3f", flagx);

			ImGui::Text("Y"); ImGui::SameLine(); ImGui::SameLine();
			ImGui::DragFloat("Drag Y Rot", &drag_y, 0.005f, -FLT_MAX, +FLT_MAX, "%.3f", flagy);

			ImGui::Text("Z"); ImGui::SameLine(); ImGui::SameLine();
			ImGui::DragFloat("Drag Z Rot", &drag_z, 0.005f, -FLT_MAX, +FLT_MAX, "%.3f", flagz);

			Quaternion newQuat;
			newQuat.SetEulerAngles(drag_x, drag_y, drag_z);

			g->GetTransform()->SetRotation(newQuat);

			ImGui::TreePop();
		}

		if (ImGui::TreeNode("Scale"))
		{

			ImGuiSliderFlags flagx = ImGuiSliderFlags_None;
			ImGuiSliderFlags flagy = ImGuiSliderFlags_None;
			ImGuiSliderFlags flagz = ImGuiSliderFlags_None;
			// Drags
			float drag_x = g->GetTransform()->GetScale().GetX();
			float drag_y = g->GetTransform()->GetScale().GetY();
			float drag_z = g->GetTransform()->GetScale().GetZ();

			ImGui::Text("X"); ImGui::SameLine(); ImGui::SameLine();
			ImGui::DragFloat("Drag X Scale", &drag_x, 0.005f, -FLT_MAX, +FLT_MAX, "%.3f", flagx);

			ImGui::Text("Y"); ImGui::SameLine(); ImGui::SameLine();
			ImGui::DragFloat("Drag Y Scale", &drag_y, 0.005f, -FLT_MAX, +FLT_MAX, "%.3f", flagy);

			ImGui::Text("Z"); ImGui::SameLine(); ImGui::SameLine();
			ImGui::DragFloat("Drag Z Scale", &drag_z, 0.005f, -FLT_MAX, +FLT_MAX, "%.3f", flagz);

			Vector3f newVec(drag_x,drag_y,drag_z);

			g->GetTransform()->SetScale(newVec);

			ImGui::TreePop();
		}


		//ImGui::TreePop();
	}
}