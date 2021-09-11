#pragma once

#include "Component.h"

/**
 * @brief Component for a displayed grid
*/
class CGridComponent : public Component
{
    private:
        /**
         * @brief the height of the grid
        */
        float gridHeight = 0.02f;
        /**
         * @brief the thickness of the lines making it up
        */
        float lineThickness = 1.0f;

        /**
         * @brief the width of the grid
        */
        float gridWidth = 50;
        /**
         * @brief the width of each cell in the world
        */
        float cellWidth = 1;

    public:
        /**
         * @brief constructor using parent
         * @param parent The parent transform for this component's transform
         * @param parentObj The parent object for this component
        */
        CGridComponent(Transform* parent, GameObject* parentObj);
        /**
         * @brief displays the component on the screen, if visible
        */
        void Render();
};
