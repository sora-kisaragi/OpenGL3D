/**
* @file Shader.h
*/
#ifndef SHADER_H_INCLUDED
#define SHADER_H_INCLUDED
#include <GL/glew.h>

namespace Shader {

GLuint Build(const GLchar* vsCode, const GLchar* fsCode);
GLuint BuildFromFile(const char* vsPath, const char* fsPath);

}// Shader namespace


#endif // SHADER_H_INCLUDED