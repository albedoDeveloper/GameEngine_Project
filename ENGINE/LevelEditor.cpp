#include "LevelEditor.h"
#include "GameObjectFactory.h"
#include "Quaternion.h"

LevelEditor::LevelEditor()
{

}

void LevelEditor::DrawEditor()
{
	ImGui::SetNextWindowSize(ImVec2(520, 600), ImGuiCond_FirstUseEver);

	if (ImGui::CollapsingHeader("Level Editor"))
	{
		ObjectList();
	}
}

void LevelEditor::ObjectList()
{
	//retrieval
	std::map<std::string, GameObject *> *m_objects;

	m_objects = GAMEOBJECT->GetObjectMap();

	//iteration
	std::map<std::string, GameObject *>::iterator it;
	for (it = m_objects->begin(); it != m_objects->end(); it++)
	{
		//population
		ObjectHeader(it->second);
	}
}

void LevelEditor::ObjectHeader(GameObject *g)
{
	ImGui::AlignTextToFramePadding();

	if (ImGui::TreeNode((char *)g->GetFactoryKey().c_str()))
	{
		ImGui::AlignTextToFramePadding();

		TransformHeader(g);

		ComponentTree(g);

		ImGui::TreePop();
	}
}

void LevelEditor::TransformHeader(GameObject *g)
{
	if (ImGui::CollapsingHeader("Transform"))
	{

		ImGui::Indent(); ImGui::Indent(); ImGui::Indent();
		ImGui::Text("X"); ImGui::SameLine(150); ImGui::Text("Y"); ImGui::SameLine(210); ImGui::Text("Z");
		ImGui::Unindent(); ImGui::Unindent(); ImGui::Unindent();

		//<<<<<<<<<<<<<<<<<<POSITION>>>>>>>>>>>>>>>>>>>//

		PositionManipulators(g);

		//<<<<<<<<<<<<<<<<<<ROTATION>>>>>>>>>>>>>>>>>>>//
		RotationManipulators(g);

		//<<<<<<<<<<<<<<<<<<SCALE>>>>>>>>>>>>>>>>>>>//
		ScaleManipulators(g);

	}


}

void LevelEditor::PositionManipulators(GameObject *g)
{
	ImGuiSliderFlags flagPosX = ImGuiSliderFlags_None;
	ImGuiSliderFlags flagPosY = ImGuiSliderFlags_None;
	ImGuiSliderFlags flagPosZ = ImGuiSliderFlags_None;
	// Drags
	float drag_x_pos = g->GetTransform()->GetRelativePosition().GetX();
	float drag_y_pos = g->GetTransform()->GetRelativePosition().GetY();
	float drag_z_pos = g->GetTransform()->GetRelativePosition().GetZ();

	ImGui::PushItemWidth(50);

	ImGui::Text("Pos  "); ImGui::SameLine();
	ImGui::DragFloat("##PosX", &drag_x_pos, 0.005f, -FLT_MAX, +FLT_MAX, "%.3f", flagPosX);

	ImGui::SameLine();
	ImGui::DragFloat("##PosY", &drag_y_pos, 0.005f, -FLT_MAX, +FLT_MAX, "%.3f", flagPosY);

	ImGui::SameLine();
	ImGui::DragFloat("##PosZ", &drag_z_pos, 0.005f, -FLT_MAX, +FLT_MAX, "%.3f", flagPosZ);

	g->GetTransform()->SetRelativePosition(drag_x_pos, drag_y_pos, drag_z_pos);
}

void LevelEditor::RotationManipulators(GameObject *g)
{

	ImGuiSliderFlags flagRotX = ImGuiSliderFlags_None;
	ImGuiSliderFlags flagRotY = ImGuiSliderFlags_None;
	ImGuiSliderFlags flagRotZ = ImGuiSliderFlags_None;
	// Drags
	Vector3f eulerRot = g->GetTransform()->GetRelativeOrientation().GetEulerAnglesDegrees();
	float drag_x_rot = eulerRot.GetX();
	float drag_y_rot = eulerRot.GetY();
	float drag_z_rot = eulerRot.GetZ();

	ImGui::Text("Rot  "); ImGui::SameLine();
	ImGui::DragFloat("##RotX", &drag_x_rot, 0.005f, -FLT_MAX, +FLT_MAX, "%.3f", flagRotX);

	ImGui::SameLine();
	ImGui::DragFloat("##RotY", &drag_y_rot, 0.005f, -FLT_MAX, +FLT_MAX, "%.3f", flagRotY);

	ImGui::SameLine();
	ImGui::DragFloat("##RotZ", &drag_z_rot, 0.005f, -FLT_MAX, +FLT_MAX, "%.3f", flagRotZ);

	Quaternion newQuat;
	newQuat.SetEulerAnglesDegrees(drag_x_rot, drag_y_rot, drag_z_rot);

	g->GetTransform()->SetRelativeOrientation(newQuat);
}

void LevelEditor::ScaleManipulators(GameObject *g)
{

	ImGuiSliderFlags flagScaleX = ImGuiSliderFlags_None;
	ImGuiSliderFlags flagScaleY = ImGuiSliderFlags_None;
	ImGuiSliderFlags flagScaleZ = ImGuiSliderFlags_None;
	// Drags
	float drag_x_scale = g->GetTransform()->GetRelativeScale().GetX();
	float drag_y_scale = g->GetTransform()->GetRelativeScale().GetY();
	float drag_z_scale = g->GetTransform()->GetRelativeScale().GetZ();

	ImGui::Text("Scale"); ImGui::SameLine(); ImGui::SameLine();
	ImGui::DragFloat("##ScaleX", &drag_x_scale, 0.005f, -FLT_MAX, +FLT_MAX, "%.3f", flagScaleX);

	ImGui::SameLine();
	ImGui::DragFloat("##ScaleY", &drag_y_scale, 0.005f, -FLT_MAX, +FLT_MAX, "%.3f", flagScaleY);

	ImGui::SameLine();
	ImGui::DragFloat("##ScaleZ", &drag_z_scale, 0.005f, -FLT_MAX, +FLT_MAX, "%.3f", flagScaleZ);

	Vector3f newVec(drag_x_scale, drag_y_scale, drag_z_scale);

	g->GetTransform()->SetRelativeScale(newVec);

}

void LevelEditor::ComponentTree(GameObject *g)
{
	if (ImGui::CollapsingHeader("Components"))
	{
		std::unordered_map<std::type_index, std::list<CComponent *> *> compMap = g->GetComponentMap();

		// iterate through all component lists
		for (std::unordered_map<std::type_index, std::list<CComponent *> *>::iterator mapIterator = compMap.begin(); mapIterator != compMap.end(); ++mapIterator)
		{
			// iterate through all components in list
			for (std::list<CComponent *>::iterator listIterator = (*mapIterator).second->begin(); listIterator != (*mapIterator).second->end(); ++listIterator)
			{
				(*listIterator)->DrawToImGui();
			}
		}
	}
}