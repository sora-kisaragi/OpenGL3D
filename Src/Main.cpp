/**
* @file Main.cpp
*/
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

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
* �G���g���[�|�[�g
*/
int main() 
{
	//ErrorCallback�֐����Ăяo��
	glfwSetErrorCallback(ErrorCallback);




	// GLFW






	return 0;
}