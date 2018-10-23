/**
* @file GLFWEW.h
*/
#ifndef GLFWEW_H_INCLUDED
#define GLFWEW_H_INCLUDED
#include <GL/glew.h>
#include <GLFW/glfw3.h>


namespace GLFWEW {

	/**
	* GLFW��GLEW�̃��b�p�[�N���X.
	*/
	class Window
	{
	public:

		//Window�̃V���O���g��
		static Window& Instance();

		bool Init(int x, int h, const char* title);
		
		bool ShouldClose() const;
		
		void SwapBuffers() const;

	private:
		//�f�t�H���g�R���X�g���N�^ �� �f�X�g���N�^
		Window();
		~Window();
		
		//�R�s�[�R���X�g���N�^�ƃR�s�[������Z�q���폜�w��
		//�R�s�[���֎~
		Window(const Window&) = delete;
		Window& operator=(const Window&) = delete;


		bool isGLFWInitialized = false;
		bool isInitialized = false;
		GLFWwindow* window = nullptr;

	};

} //namespace GLFWEW

#endif // GLFWEW_H_INCLUDED