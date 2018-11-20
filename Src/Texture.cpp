/**
* @file Texture.cpp
*/
#include "Texture.h"
#include <cstdint>
#include <vector>
#include <fstream>
#include <iostream>

/// �e�N�X�`���֘A�̊֐���N���X���i�[���閼�O���.
namespace Texture {

	/**
	* 2D�e�N�X�`�����쐬����.
	*
	* @param width   �e�N�X�`���̕�(�s�N�Z����).
	* @param height  �e�N�X�`���̍���(�s�N�Z����).
	* @param data    �e�N�X�`���f�[�^�ւ̃|�C���^.
	* @param format  �]�����摜�̃f�[�^�`��.
	* @param type    �]�����摜�̃f�[�^�i�[�`��.
	*
	* @retval 0�ȊO  �쐬�����e�N�X�`���E�I�u�W�F�N�g��ID.
	* @retval 0      �e�N�X�`���̍쐬�Ɏ��s.
	*/
	GLuint CreateImage2D(GLsizei width, GLsizei height, const GLvoid* data, GLenum format, GLenum type)
	{
		GLuint id;
		glGenTextures(1, &id);
		glBindTexture(GL_TEXTURE_2D, id);
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, format, type, data);
		glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
		const GLenum result = glGetError();
		if (result != GL_NO_ERROR) {
			std::cerr << "ERROR: �e�N�X�`���̍쐬�Ɏ��s(0x" << std::hex << result << ").";
			glBindTexture(GL_TEXTURE_2D, 0);
			glDeleteTextures(1, &id);
			return 0;
		}

		// �e�N�X�`���̃p�����[�^��ݒ肷��.
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, 0);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		if (format == GL_RED) {
			const GLint swizzle[] = { GL_RED, GL_RED, GL_RED, GL_ONE };
			glTexParameteriv(GL_TEXTURE_2D, GL_TEXTURE_SWIZZLE_RGBA, swizzle);
		}

		glBindTexture(GL_TEXTURE_2D, 0);

		return id;
	}

	/**
	* �t�@�C������2D�e�N�X�`����ǂݍ���.
	*
	* @param path 2D�e�N�X�`���Ƃ��ēǂݍ��ރt�@�C���̃p�X.
	*
	* @retval 0�ȊO  �쐬�����e�N�X�`���E�I�u�W�F�N�g��ID.
	* @retval 0      �e�N�X�`���̍쐬�Ɏ��s.
	*/
	GLuint LoadImage2D(const char* path)
	{
		// TGA�w�b�_��ǂݍ���.
		std::basic_ifstream<uint8_t> ifs;
		ifs.open(path, std::ios_base::binary);
		uint8_t tgaHeader[18];
		ifs.read(tgaHeader, 18);

		// �C���[�WID���΂�.
		ifs.ignore(tgaHeader[0]);

		// �J���[�}�b�v���΂�.
		if (tgaHeader[1]) {
			const int colorMapLength = tgaHeader[5] | (tgaHeader[6] << 8);
			const int colorMapEntrySize = tgaHeader[7];
			const int colorMapSize = colorMapLength * colorMapEntrySize / 8;
			ifs.ignore(colorMapSize);
		}

		// �摜�f�[�^��ǂݍ���.
		const int width = tgaHeader[12] | (tgaHeader[13] << 8);
		const int height = tgaHeader[14] | (tgaHeader[15] << 8);
		const int pixelDepth = tgaHeader[16];
		const int imageSize = width * height * pixelDepth / 8;
		std::vector<uint8_t> buf(imageSize);
		ifs.read(buf.data(), imageSize);

		// �摜�f�[�^���u�ォ�牺�v�Ŋi�[����Ă���ꍇ�A�㉺�����ւ���.
		if (tgaHeader[17] & 0x20) {
			const int lineSize = width * pixelDepth / 8;
			std::vector<uint8_t> tmp(imageSize);
			std::vector<uint8_t>::iterator source = buf.begin();
			std::vector<uint8_t>::iterator destination = tmp.end();
			for (int i = 0; i < height; ++i) {
				destination -= lineSize;
				std::copy(source, source + lineSize, destination);
				source += lineSize;
			}
			buf.swap(tmp);
		}

		GLenum type = GL_UNSIGNED_BYTE;
		GLenum format = GL_BGRA;
		if (tgaHeader[2] == 3) {
			format = GL_RED;
		}
		if (tgaHeader[16] == 24) {
			format = GL_BGR;
		}
		else if (tgaHeader[16] == 16) {
			type = GL_UNSIGNED_SHORT_1_5_5_5_REV;
		}

		// �ǂݍ��񂾉摜�f�[�^����e�N�X�`�����쐬����.
		return CreateImage2D(width, height, buf.data(), format, type);
	}

} // namespace Texture