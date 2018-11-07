/*
* @file Shader.cpp
*/
#include "Shader.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <stdint.h>


/**
* �V�F�[�_�[�Ɋւ���@�\���i�[���閼�O���
*/
namespace Shader {

/**
* �V�F�[�_�[��v���O�������R���p�C������
*
* @param type	�V�F�[�_�[�̎��
* @param string �V�F�[�_�[��v���O�����ւ̃|�C���^
*	
* @retval 0���傫��	�쐬�����V�F�[�_�[��I�u�W�F�N�g
* @retval 0				�V�F�[�_�[��I�u�W�F�N�g�̍쐬�Ɏ��s
*/
GLuint Compile(GLenum type, const GLchar* string)
{
	if (!string) {
		return 0;
	}


	
	//�V�F�[�_�[�I�u�W�F�N�g���쐬
	GLuint shader = glCreateShader(type);

	//�쐬�����V�F�[�_�[�I�u�W�F�N�g�ɃV�F�[�_�[�v���O�������֘A�t����
	glShaderSource(shader, 1, &string, nullptr);

	//�֘A�t�����V�F�[�_�[�v���O�������R���p�C��
	//�V�F�[�_�[�I�u�W�F�N�g�ɃZ�b�g
	glCompileShader(shader);

	// �R���p�C���Ɏ��s�����ꍇ�A�������R���\�[���ɏo�͂���0��Ԃ�.
	GLint compiled = 0;

	//�V�F�[�_�[�I�u�W�F�N�g�̏�Ԃ��擾����
	glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);

	//�����R���p�C���Ɏ��s������
	if (!compiled) {

		//���� 0
		GLint infoLen = 0;

		//GL_INFO_LENGTH���w�肷��ƁA�ڍ׏��̃o�C�g�����擾�B
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLen);

		
		if (infoLen) {
			//�ڍ׏����擾���邽�߂̃o�b�t�@
			std::vector<char> buf;

			//std::vector�̃T�C�Y��ύX����֐� std::vector::resize
			buf.resize(infoLen);

			//�T�C�Y�ύX�ɐ��������ꍇ
			if ((int)buf.size() >= infoLen) {

				//buf�ɏڍ׏�����荞��
				glGetShaderInfoLog(shader, infoLen, nullptr, buf.data());
				//buf�̓��e���G���[�\��
				std::cerr << "ERROR: �V�F�[�_�[�̃R���p�C���Ɏ��s.\n" << buf.data() << std::endl;
			}

		}
		//�V�F�[�_�[�I�u�G�N�Ƃ��폜
		glDeleteShader(shader);

		//�R���p�C�����s�łO��Ԃ�
		return 0;

	}
	//�R���p�C�������ŃV�F�[�_�[�I�u�W�F�N�g��Ԃ�
	return shader;
}


/**
* �v���O�����I�u�W�F�N�g���쐬����
*
* @param vsCode ���_�V�F�[�_�v���O�����ւ̃|�C���^
* @param fsCode �t���O�����g�V�F�[�_�v���O�����ւ̃|�C���^
*
* @retval 0���傫��	�쐬�����v���O�����I�u�W�F�N�g
* @retval 0				�v���O�����I�u�W�F�N�g�̍쐬�Ɏ��s
*/
GLuint Build(const GLchar* vsCode, const GLchar* fsCode)
{
	//�V�F�[�_�[�v���O��������V�F�[�_�[�I�u�W�F�N�g���쐬
	GLuint vs = Compile(GL_VERTEX_SHADER, vsCode);
	GLuint fs = Compile(GL_FRAGMENT_SHADER, fsCode);
	
	//���s������0��Ԃ�
	if (!vs || !fs) {
		return 0;
	}

	//�v���O�����I�u�W�F�N�g���쐬
	GLuint program = glCreateProgram();

	//�V�F�[�_�[�I�u�W�F�N�g���v���O�����I�u�W�F�N�g�Ɋ��蓖�Ă�
	glAttachShader(program, fs);

	//�폜�}�[�N�����č폜�ҋ@
	glDeleteShader(fs);

	//�V�F�[�_�[�I�u�W�F�N�g���v���O�����I�u�W�F�N�g�Ɋ��蓖�Ă�
	glAttachShader(program, vs);

	//�폜�}�[�N�����č폜�ҋ@
	glDeleteShader(vs);

	//���蓖�Ă��V�F�[�_�[�I�u�W�F�N�g���m�������N
	glLinkProgram(program);

	//�����N�Ɏ��s�����ꍇ,�������R���\�[���ɏo�͂���0��Ԃ�
	GLint linkStatus = GL_FALSE;

	//�V�F�[�_�[�v���O�����̏�Ԃ��擾����
	glGetProgramiv(program, GL_LINK_STATUS, &linkStatus);

	//���������N�o���Ă��Ȃ��ꍇ
	if (linkStatus != GL_TRUE) {
		//�ϐ���0��
		GLint infoLen = 0;

		//�ڍ׏����擾����
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &infoLen);
		
		if (infoLen) {

			//�ڍ׏����擾����o�b�t�@
			std::vector<char> buf;

			//buf�����T�C�Y
			buf.resize(infoLen);

			//���T�C�Y�ɐ���������
			if ((int)buf.size() >= infoLen) {
				
				//buf�ɏڍ׏��������
				glGetProgramInfoLog(program, infoLen, nullptr, buf.data());
				
				//�ڍ׏����G���[�o��
				std::cerr << "ERROR:�V�F�[�_�[�̃����N�Ɏ��s.\n" << buf.data() << std::endl;
			}
		}

		//�V�F�[�_�[�I�u�W�F�N�g���폜
		glDeleteProgram(program);

		//���s������0��Ԃ�
		return 0;
	}
	//����������program��Ԃ�
	return program;
}


/**
* �t�@�C����ǂݍ���
*
* @param path �ǂݍ��ރt�@�C����
*
* @return �ǂݍ��񂾃f�[�^
*/
std::vector<GLchar> ReadFile(const char* path)
{
	
	std::basic_ifstream<GLchar> ifs;

	//
	ifs.open(path, std::ios_base::binary);
	
	if (!ifs.is_open()) {
		std::cerr << "ERROR: " << path << " ���J���܂���.\n";
		return {};
		
	}

	
	//
	ifs.seekg(0, std::ios_base::end);
	
	//
	const size_t length = (size_t)ifs.tellg();
	
	ifs.seekg(0, std::ios_base::beg);

	std::vector<GLchar>buf(length);
	
	//
	ifs.read(buf.data(), length);
	
	//
	buf.push_back('\0');
	
	//
	return buf;
}

/**
* �t�@�C������v���O�����E�I�u�W�F�N�g���쐬����
*
* @param vsPath ���_�V�F�[�_�[�E�t�@�C����
* @param fsPath �t���O�����g�V�F�[�_�[�E�t�@�C����
*
* @return �쐬�����v���O�����I�u�W�F�N�g
*
*/
GLuint BuildFromFile(const char* vsPath, const char* fsPath)
{
	const std::vector<GLchar> vsCode = ReadFile(vsPath);
	const std::vector<GLchar> fsCode = ReadFile(fsPath);
	
	//���_�V�F�[�_�[�t�@�C���ƃt���O�����g�V�F�[�_�[�t�@�C����ǂݍ���
	//Build�֐��ɂ��ǂݍ��񂾃f�[�^��n���ăv���O�������쐬
	return Build(vsCode.data(), fsCode.data());
}


}//Shader namespace