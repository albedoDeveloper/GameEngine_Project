#include "CGridComponent.h"
#include "GraphicsEngine.h"


CGridComponent::CGridComponent(Transform* parent, GameObject* parentObj)
    :Component{ parent, parentObj }
{
}

void CGridComponent::Render()
{
    GRAPHICS->DrawGrid(gridHeight, lineThickness, gridWidth, cellWidth);
}
