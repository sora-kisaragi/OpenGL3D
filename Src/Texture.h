/**
* @file Texture.h
*/
#ifndef TEXTURE_H_INCLUDED
#define TEXTURE_H_INCLUDED
#include <GL/glew.h>

namespace Texture {

	//テクスチャを作成する関数　引数は　幅　高さ　画像データ フォーマット
	GLuint CreateImage2D(GLsizei width, GLsizei height, const GLvoid* data,GLenum format, GLenum type);

	//テクスチャ読み込み関数
	GLuint LoadImage2D(const char* path);

}// namespace Texture


#endif // !TEXTURE_H_INCLUDE