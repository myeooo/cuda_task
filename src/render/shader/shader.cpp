#include "shader.h"
#include <GL/glew.h>
#include <fstream>
#include <sstream>
#include <iostream>
using namespace std;

static std::string ReadFile(const std::string& path)
{
    std::ifstream file(path);
    if (!file.is_open()) {
        std::cerr << "[Shader] Failed to open file: " << path << std::endl;
        return "";
    }

    std::stringstream ss;
    ss << file.rdbuf();
    return ss.str();
}

static void CheckCompileErrors(GLuint shader, const std::string& type)
{
    GLint success;
    GLchar infoLog[1024];

    if (type != "PROGRAM") {
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success) {
            glGetShaderInfoLog(shader, 1024, nullptr, infoLog);
            std::cerr << "[Shader] Compile error (" << type << "):\n"
                      << infoLog << std::endl;
        }
    } else {
        glGetProgramiv(shader, GL_LINK_STATUS, &success);
        if (!success) {
            glGetProgramInfoLog(shader, 1024, nullptr, infoLog);
            std::cerr << "[Shader] Link error:\n"
                      << infoLog << std::endl;
        }
    }
}

unsigned int LoadShader(
    const std::string& vertexPath,
    const std::string& fragmentPath
)
{
    std::string vertCode = ReadFile(vertexPath);
    std::string fragCode = ReadFile(fragmentPath);

    if (vertCode.empty() || fragCode.empty()) {
        std::cerr << "[Shader] Empty shader source\n";
        return 0;
    }
    cout << "[Shader] Vertex Shader Source:\n" << vertCode << std::endl;
    cout << "[Shader] Fragment Shader Source:\n" << fragCode << std::endl;
    const char* vSrc = vertCode.c_str();
    const char* fSrc = fragCode.c_str();

    GLuint vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vSrc, nullptr);
    glCompileShader(vertex);
    CheckCompileErrors(vertex, "VERTEX");

    GLuint fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fSrc, nullptr);
    glCompileShader(fragment);
    CheckCompileErrors(fragment, "FRAGMENT");

    GLuint program = glCreateProgram();
    glAttachShader(program, vertex);
    glAttachShader(program, fragment);
    glLinkProgram(program);
    CheckCompileErrors(program, "PROGRAM");

    glDeleteShader(vertex);
    glDeleteShader(fragment);

    return program;
}
