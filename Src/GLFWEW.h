/**
* @file GLFWEW.h
*/
#ifndef GLFWEW_H_INCLUDED
#define GLFWEW_H_INCLUDED
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/vec2.hpp>

namespace GLFWEW {

	/**
	* GLFWとGLEWのラッパークラス.
	*/
	class Window
	{
	public:
		static Window& Instance();
		bool Init(int w, int h, const char* title);
		bool ShouldClose() const;
		void SwapBuffers() const;

		void InitTimer();
		void UpdateTimer();
		double DeltaTime() const;

		bool IsKeyPressed(int key) const;
		glm::vec2 GetMousePosition() const;
		int GetMouseButton(int button) const;

	private:
		Window();
		~Window();
		Window(const Window&) = delete;
		Window& operator=(const Window&) = delete;

		bool isGLFWInitialized = false;
		bool isInitialized = false;
		GLFWwindow* window = nullptr;
		double previousTime = 0;
		double deltaTime = 0;
	};

} // namespace GLFWEW

#endif // GLFWEW_H_INCLUDED
