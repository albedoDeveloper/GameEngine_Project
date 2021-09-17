/*****************************************************************//**
 * \file   AScript.h
 * \brief  
 * 
 * \date   17 September 2021
 *********************************************************************/

#pragma once

#include <string>

/**
 * @brief An asset for a script storing game behaviour
*/
struct AScript
{
public:
    /**
     * @brief constructor
     * @param newKey storage key in the asset factory
    */
    AScript(std::string newKey)
        :m_key{ newKey }
    {
    }

    /**
     * .
     * \return get the source code of this script component
     */
    const std::string& Source() const;

private:
    std::string m_key;

    /**
     * @brief the contents of the script
    */
    std::string m_sourceCode;
};
