/**
* @file GLFWEW.cpp
*/
#include "GLFWEW.h"
#include <iostream>

//���b�p�[�Ƃ͊֐���N���X�A���C�u�����𔖂���ނ悤�ȃR�[�h�������\��
//�@�\���܂Ƃ߂Ĉ����₷������

/// GLFW ��GLEW�����b�v���邽�߂̖��O���
namespace GLFWEW {


	/**
	* GLFW����̃G���[�񍐂���������
	*
	*
	* @param error	�G���[�ԍ�
	* @param desc	�G���[�̓��e
	*
	*/
	void  ErrorCallback(int error, const char* desc)
	{
		//GLFW����n���ꂽ�G���[���b�Z�[�W��W���G���[�o�͂ɕ\�����邾��
		std::cerr << "ERROR: " << desc << std::endl;
	}


	/**
	* �V���O���g���C���X�^���X���擾����
	*
	* @param Window �̃V���O���g���C���X�^���X
	*/
	Window& Window::Instance()
	{
		//static�� Window ���ЂƂ�����`
		static Window instance;
		//���̎Q�Ƃ�Ԃ�
		return instance;
	}

	/**
	* �R���X�g���N�^
	* �������Ȃ�
	*/
	Window::Window()
	{

	}

	/**
	* �f�X�g���N�^
	*/
	Window::~Window()
	{
		//GLFW������������Ă����ꍇ
		if (isGLFWInitialized) {

			//GLFW�̏I��
			glfwTerminate();

		}

	}

	/**
	* GLFW/GLEW �̏�����
	*
	* @param w �E�B���h�E�̕`��͈͂̕�(�s�N�Z��)
	* @param h �E�B���h�E�̕`��͈͂̍���(�s�N�Z��)
	* @param title �E�B���h�E�^�C�g�� (UTF-8 �� 0 �I�[����)
	*
	* @retval true	����������
	* @retval false	���������s
	*/
	bool Window::Init(int w, int h, const char* title)
	{
		//����������Ă����ꍇ
		if (isInitialized) {
			std::cerr << "ERROR: GLFWEW�͂��łɏ���������Ă��܂�" << std::endl;
			return false;
		}

		//GLFW �� �������t���O��False�̏ꍇ
		if (!isGLFWInitialized) {

			//ErrorCallback�֐����Ăяo��
			glfwSetErrorCallback(ErrorCallback);

			//GLFW�̏�����.
			if (glfwInit() != GL_TRUE) {
				//���s������false��Ԃ�
				return false;
			}
			//�������t���O��True�ɂ���
			isGLFWInitialized = true;
		}

		//window���Ȃ��ꍇ
		if (!window) {
			window = glfwCreateWindow(w, h, title, nullptr, nullptr);
			
			//window���n���Ȃ������ꍇ
			if (!window) {
				//�A�v���P�[�V�������I������
				return false;
			}
			//�w�肵��Window�ɑΉ�����OpenGL�R���e�L�X�g��`��Ώۂɐݒ�
			glfwMakeContextCurrent(window);
		}

		//GLEW��������.
		if (glewInit() != GLEW_OK) {

			//GLFW�Ɗ֌W�Ȃ����߂ɁA�R�[���o�b�N���Ă΂�Ȃ��̂Ŗ����I�ɏo��
			std::cerr << "ERROR: GLEW�̏������Ɏ��s���܂���" << std::endl;

			//false��Ԃ�
			return false;
		}


		//=========================�ۑ�2 [GL_EXTENSIONS, GL_VENDOR]�Ȃǂ𓯂��`�ŏ���������============================
		//==============================================================================================
		// OpenGL�̏����R���\�[���E�B���h�E�֏o�͂���

		//GPU�̖��O �������� �h���C�o��
		const GLubyte* renderer = glGetString(GL_RENDERER);
		std::cout << "Renderer: " << renderer << std::endl;

		//GPU���Ή����Ă���ő��OpenGL��version
		const GLubyte* version = glGetString(GL_VERSION);
		std::cout << "Version: " << version << std::endl;

		//�������t���O��True�ɂ���
		isInitialized = true;

		//true��Ԃ�
		return true;

	}


	/**
	* �E�B���h�E�����ׂ������ׂ�
	*	(glfwWindowShouldClose�֐� �� ���b�p�[)
	* @param true ����
	* @param false ���Ȃ�
	*/
	bool Window::ShouldClose() const
	{
		//window�����
		return glfwWindowShouldClose(window) != 0;
	}


	/**
	* �t�����g�o�b�t�@�ƃo�b�N�o�b�t�@��؂�ւ���
	*	glfwPollEvents�֐� �� glfwSwapBuffers�֐� �� ���b�p�[
	*/
	void Window::SwapBuffers() const
	{
		//GLFW �� OS���瑗��ꂽ�C�x���g����������֐�
		glfwPollEvents();

		//�t���[���o�b�t�@�̕\�����ƕ`�摤�����ւ���
		//�`�撆�̉�ʂ��B�����ƂŁA���[�U�[���猩���Ȃ��悤�ɂ���B
		glfwSwapBuffers(window);

	}



}// namespace GLFWEW