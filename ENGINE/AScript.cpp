#include "AScript.h"
#include <fstream>
#include <iostream>

AScript::AScript(const std::string& key, const std::string& sourceFilePath)
    :m_key{ key }, m_sourceCode{""}
{
    LoadLua(sourceFilePath);
}

const std::string& AScript::Key() const
{
	return m_key;
}

const std::string& AScript::Source() const
{
	return m_sourceCode;
}

void AScript::SetSource(const std::string& source)
{
	m_sourceCode = source;
}

void AScript::LoadLua(const std::string& filePath)
{
    std::ifstream inFile(filePath);
    if (!inFile.is_open())
    {
        std::cout << "Could not open the file: '" << filePath << "'" << std::endl;
        return;
    }

    m_sourceCode = std::string((std::istreambuf_iterator<char>(inFile)), std::istreambuf_iterator<char>());
}
