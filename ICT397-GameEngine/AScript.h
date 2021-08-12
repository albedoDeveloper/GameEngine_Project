#pragma once

#include "Asset.h"
#include <string>

/**
 * @brief An asset for a script storing game behaviour
*/
struct AScript : public Asset
{
    /**
     * @brief the contents of the script
    */
    std::string Script;

    /**
     * @brief constructor
     * @param newKey storage key in the asset factory
    */
    AScript(std::string newKey)
        :Asset{ newKey }
    {
    }
};
