#include "Shader.h"
void Shader::initShader(const char* _vertexPath, const char* _fragPath)
{
    std::string _vertexCode("");
    std::string _fragCode("");

    std::ifstream   _vShaderFile;
    std::ifstream   _fShaderFile;

    _vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    _fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

    try
    {
        _vShaderFile.open(_vertexPath);
        _fShaderFile.open(_fragPath);

        std::stringstream _vShaderStream, _fShaderStream;
        _vShaderStream << _vShaderFile.rdbuf();
        _fShaderStream << _fShaderFile.rdbuf();

        _vertexCode = _vShaderStream.str();
        _fragCode = _fShaderStream.str();
    }
    catch (std::ifstream::failure e)
    {
        std::string errStr = "read shader fail";
        std::cout << errStr << std::endl;
    }

    const char* _vShaderStr = _vertexCode.c_str();
    const char* _fShaderStr = _fragCode.c_str();

    //shaderµÄ±àÒëÁ´½Ó
    unsigned int   _vertexID = 0, _fragID = 0;
    char           _infoLog[512];
    int            _successFlag = 0;

    //±àÒë
    _vertexID = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(_vertexID, 1, &_vShaderStr, NULL);
    glCompileShader(_vertexID);

    glGetShaderiv(_vertexID, GL_COMPILE_STATUS, &_successFlag);
    if (!_successFlag)
    {
        glGetShaderInfoLog(_vertexID, 512, NULL, _infoLog);
        std::string errStr(_infoLog);
        std::cout << _infoLog << std::endl;
    }

    _fragID = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(_fragID, 1, &_fShaderStr, NULL);
    glCompileShader(_fragID);

    glGetShaderiv(_fragID, GL_COMPILE_STATUS, &_successFlag);
    if (!_successFlag)
    {
        glGetShaderInfoLog(_fragID, 512, NULL, _infoLog);
        std::string errStr(_infoLog);
        std::cout << _infoLog << std::endl;
    }

    //Á´½Ó
    m_shaderProgram = glCreateProgram();
    glAttachShader(m_shaderProgram, _vertexID);
    glAttachShader(m_shaderProgram, _fragID);
    glLinkProgram(m_shaderProgram);

    glGetProgramiv(m_shaderProgram, GL_LINK_STATUS, &_successFlag);
    if (!_successFlag)
    {
        glGetProgramInfoLog(m_shaderProgram, 512, NULL, _infoLog);
        std::string errStr(_infoLog);
        std::cout << _infoLog << std::endl;
    }
    glDeleteShader(_vertexID);
    glDeleteShader(_fragID);
}


void Shader::setMatrix(const std::string& _name, glm::mat4 _matrix)const
{
   glUniformMatrix4fv(glGetUniformLocation(m_shaderProgram, _name.c_str()) , 1 , GL_FALSE , glm::value_ptr(_matrix));
}