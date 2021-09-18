/*****************************************************************//**
 * \file   AScript.h
 * \brief
 *
 * \date   17 September 2021
 *********************************************************************/

#pragma once

#include <string>

/**
 * @brief An asset for a script storing game behaviour. can be shared among many components
*/
class AScript
{
public:
	/**
	 * @brief constructor
	 * @param newKey storage key in the asset factory
	*/
	AScript(const std::string &key, const std::string &sourceFilePath);

	/**
	 * get the factory key of this asset
	 *
	 * \return
	 */
	const std::string &Key() const;

	/**
	 * .
	 * \return get the source code of this script component
	 */
	const std::string &Source() const;

	void SetSource(const std::string &source);

private:
	std::string m_key;

	/**
	 * @brief the contents of the script
	*/
	std::string m_sourceCode;

	void LoadLua(const std::string &filePath);
};
