#include <glew/GL/glew.h>
#include "Shader.h"


Shader::Shader(const char* vertexPath, const char* fragmentPath)
{
    GLenum err = glewInit();
    if (GLEW_OK != err)
    {
        std::cerr << "Error: " << glewGetErrorString(err) << std::endl;
    }
    std::cerr << "Status: Using GLEW " << glewGetString(GLEW_VERSION) << std::endl;
    //Variables to open the shader file
    std::string vertexShaderCode;
    std::string fragmentShaderCode;
    std::ifstream vShaderFile;
    std::ifstream fShaderFile;

    vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

    try
    {
        // open files
        vShaderFile.open(vertexPath);
        fShaderFile.open(fragmentPath);
        std::stringstream vShaderStream, fShaderStream;

        // read file's buffer contents into streams
        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();

        // close file handlers
        vShaderFile.close();
        fShaderFile.close();

        // convert stream into string
        vertexShaderCode = vShaderStream.str();
        fragmentShaderCode = fShaderStream.str();
   

        const char* vShaderCode = vertexShaderCode.c_str();
        const char* fShaderCode = fragmentShaderCode.c_str();

        unsigned int fragmentShader;
        unsigned int vertexShader;

        CreateShaders(vertexShader, &vShaderCode, 0);
        CreateShaders(fragmentShader, &fShaderCode, 1);
        ShaderLinking(vertexShader, fragmentShader);
    
    }
    
    catch (std::ifstream::failure e)
    {
        std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
    }
}

void Shader::CreateShaders(unsigned int& shadername, const GLchar* const* actualShader, int typeOfShader)
{
    int  success;
    char infoLog[512];

    //Determine the type of shader
    if (typeOfShader == 0)
        shadername = glCreateShader(GL_VERTEX_SHADER);
    else if (typeOfShader == 1)
        shadername = glCreateShader(GL_FRAGMENT_SHADER);

    glShaderSource(shadername, 1, actualShader, NULL);
    glCompileShader(shadername);
    glGetShaderiv(shadername, GL_COMPILE_STATUS, &success);

    if (!success)
    {
        glGetShaderInfoLog(shadername, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::" << typeOfShader << "::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
}

void Shader::ShaderLinking(unsigned int& vertexShader, unsigned int& fragmentShader)
{
    int  success;
    char infoLog[512];

    ID = glCreateProgram();

    glAttachShader(ID, vertexShader);
    glAttachShader(ID, fragmentShader);
    glLinkProgram(ID);
    glGetProgramiv(ID, GL_LINK_STATUS, &success);

    if (!success)
    {
        glGetShaderInfoLog(ID, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::LINKER::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
}

bool Shader::useShaderForLoop()
{
    if (ID == NULL)
        return false;
    else
    {
        glUseProgram(ID);
        return true;
    }


}



