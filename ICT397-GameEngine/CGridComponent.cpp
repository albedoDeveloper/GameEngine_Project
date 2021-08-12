#include "CGridComponent.h"
#include "GraphicsEngine.h"


CGridComponent::CGridComponent(Transform* parent, GameObject* parentObj)
    :Component{ parent, parentObj }
    {
    }

void CGridComponent::Start()
{
}

void CGridComponent::Update()
{
}

void CGridComponent::Render()
{
    GRAPHICS->DrawGrid(gridHeight, lineThickness, gridWidth, cellWidth);
}

void CGridComponent::LateRender()
{}

//depreciated:: Moved to graphics engine
//void GridComponent::DrawGrid() 
//{
//    for (float i = -gridWidth * 0.5f; i < gridWidth; i += cellWidth * 0.5f)
//    {
//        for (float j = -gridWidth * 0.5f; j < gridWidth; j += cellWidth * 0.5f)
//        {
//            glBegin(GL_LINE_LOOP);
//            glVertex3f(i - 1, gridHeight, j - 1);
//            glVertex3f(i - 1, gridHeight, j);
//            glVertex3f(i, gridHeight, j);
//            glVertex3f(i, gridHeight, j - 1);
//            glEnd();
//        }
//    }
//}