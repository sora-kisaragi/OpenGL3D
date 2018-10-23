/**
* @file Main.cpp
*/
#include "GLFWEW.h"
#include <iostream>



/**
* �G���g���[�|�[�g
*/
int main() 
{
	//GLFW GLEW�̏������ƃE�B���h�E�̍쐬
	GLFWEW::Window& window = GLFWEW::Window::Instance();
	if (!window.Init(800, 600, "OpenGL3D")) {
		return 1;
	}


	//���C�����[�v
	while (!window.ShouldClose()) {

		//=========================�ۑ�P �F��ς���ꍇ�͂����̈�����ς���============================
		//==============================================================================================
		//�o�b�N�o�b�t�@��ߋ�����Ƃ��̐F�@RGBA
		glClearColor(.01f, 0.3f, 0.5f, 1.0f);
		
		//�o�b�N�o�b�t�@����������֐� �����͏�������o�b�t�@�̎��
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//�o�b�t�@�̐ؑ�
		window.SwapBuffers();

	}

	return 0;
}