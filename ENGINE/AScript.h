/*****************************************************************//**
 * \file   AScript.h
 *
 * \date   18 September 2021
 *********************************************************************/
#pragma once

#include <string>

	/**
	 * An asset for a script storing game behaviour. can be shared among many components
	 */
class AScript
{
public:
		/**
		 * constructs a script asset and loads in a script source file
		 *
		 * \param key asset factory reference to this asset
		 * \param sourceFilePath file path of script to load in
		 */
	AScript(const std::string &key, const std::string &sourceFilePath);

		/**
		 * get the asset factory key of this asset
		 *
		 * \return
		 */
	const std::string &Key() const;

		/**
		 * get the source code of this script asset
		 * \return get the source code of this script component
		 */
	const std::string &Source() const;

		/**
		 * set the source code this script will use
		 *
		 * \param source source code
		 */
	void SetSource(const std::string &source);

private:
		/// @brief unique identifier
	std::string m_key;

		/// @brief lua source code
	std::string m_sourceCode;

		/**
		 * load a lua file and store its source code.
		 *
		 * \param filePath
		 */
	void LoadLua(const std::string &filePath);
};
