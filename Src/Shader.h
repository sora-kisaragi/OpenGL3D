/**
* @file Shader.h
*/
#ifndef SHADER_H_INCLUDED
#define SHADER_H_INCLUDED
#include <GL/glew.h>




namespace Shader {

GLuint Build(const GLchar* vsCode, const GLchar* fsCode);

}// Shader namespace


#endif // SHADER_H_INCLUDED