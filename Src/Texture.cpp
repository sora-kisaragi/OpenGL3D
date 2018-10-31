/**
* @file Texture.cpp
*/
#include "Texture.h"
#include <iostream>

/// �e�N�X�`���֘A�̊֐���N���X���i�[���閼�O���
namespace Texture {


	/**
	* 2D�e�N�X�`�����쐬����.
	*
	* @param width   �e�N�X�`���̕�(�s�N�Z����).
	* @param height  �e�N�X�`���̍���(�s�N�Z����).
	* @param data    �e�N�X�`���f�[�^�ւ̃|�C���^.
	*
	* @retval 0�ȊO  �쐬�����e�N�X�`���E�I�u�W�F�N�g��ID.
	* @retval 0      �e�N�X�`���̍쐬�Ɏ��s.
	*/
	GLuint CreateImage2D(GLsizei width, GLsizei height, const GLvoid* data)
	{
		GLuint id;
		
		//�e�N�X�`���̍쐬
		//����
		//�쐬���鐔
		//�I�u�W�F�N�g��ID���i�[�����ϐ��ւ̃|�C���^
		glGenTextures(1, &id);

		//����p�̃o�C���f�B���O�|�C���g�Ɋ��蓖�Ă�
		//������̃o�C���f�B���O�|�C���g
		//���蓖�Ă�I�u�W�F�N�g��ID 0�̏ꍇ������������
		glBindTexture(GL_TEXTURE_2D, id);

		//GPU�փe�N�X�`���̃p�����[�^�Ɖ摜�f�[�^��]��
		/**
		*	GLuint CreateImage2D(GLsizei width, GLsizei height, const GLvoid* date);
		*	target	�]����ɂȂ�o�C���f�B���O�|�C���g
		*	level	�ݒ肷��~�j�}�b�v���x���@�~�j�}�b�v�Ƃ̓I�u�W�F�N�g�ƃJ�����̋����ɉ����đ傫���̈Ⴄ�e�N�X�`�����g��������@�\
		*	internalFormat	�摜���ǂ̗l��GPU�������ɕۑ�����邩���w��
		*	width	�e�N�X�`���̕����s�N�Z���Ŏw��
		*	height	�e�N�X�`���̍������s�N�Z���Ŏw��
		*	border	��ɂO���w��iOpenGL3.0�ȍ~�͎g�p�֎~�j
		*	format	�]�����̉摜�̃f�[�^�`�����w�肷�� GL_RGBA�Ȃǂ��悭������
		*	type	�]�����v�̂����}���ǂ̂悤�ɐF���i�[���Ă��邩���w�肷��
		*	data	�]�����f�[�^�ւ̃|�C���^ nullptr�Ōォ�珑������Ŏg�p����ꍇ�Ɏg����i����������Ă��邩�킩��Ȃ���ԁj
		*/
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);

		//�e�N�X�`���쐬�̐������s���擾
		const GLenum result = glGetError();

		//�������s���Ă�����
		if (result != GL_NO_ERROR) {
			//�G���[��\��
			std::cerr << "ERROR: �e�N�X�`���̍쐬�Ɏ��s(0x" << std::hex << result << ").";
			//Bind������
			glBindTexture(GL_TEXTURE_2D, 0);
			//�I�u�W�F�N�g���폜 ������glGettextures�Ɠ���
			glDeleteTextures(1, &id);

			return 0;

		}
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, 0);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);



		//Bind������
		glBindTexture(GL_TEXTURE_2D, 0);

		return id;
	}




}// namespace Texture