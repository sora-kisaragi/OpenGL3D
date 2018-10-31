/**
* @file Texture.h
*/
#ifndef TEXTURE_H_INCLUDED
#define TEXTURE_H_INCLUDED
#include <GL/glew.h>

namespace Texture {

	//�e�N�X�`�����쐬����֐��@�����́@���@�����@�摜�f�[�^
	GLuint CreateImage2D(GLsizei width, GLsizei height, const GLvoid* data);
	//�e�N�X�`���ǂݍ��݊֐�
	GLuint LoadImage2D(const char* path);

}// namespace Texture


#endif // !TEXTURE_H_INCLUDE