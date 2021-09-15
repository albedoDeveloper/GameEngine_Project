#pragma once

#include "AAsset.h"
#include <string>

/**
 * @brief An asset for a script storing game behaviour
*/
struct AScript : public AAsset
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
        :AAsset{ newKey }
    {
    }
};
