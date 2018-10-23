/**
* @file Main.cpp
*/
#include "GLFWEW.h"
#include <iostream>



/**
* エントリーポート
*/
int main() 
{
	//GLFW GLEWの初期化とウィンドウの作成
	GLFWEW::Window& window = GLFWEW::Window::Instance();
	if (!window.Init(800, 600, "OpenGL3D")) {
		return 1;
	}


	//メインループ
	while (!window.ShouldClose()) {

		//=========================課題１ 色を変える場合はここの引数を変える============================
		//==============================================================================================
		//バックバッファを憑拠するときの色　RGBA
		glClearColor(.01f, 0.3f, 0.5f, 1.0f);
		
		//バックバッファを消去する関数 引数は消去するバッファの種類
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//バッファの切替
		window.SwapBuffers();

	}

	return 0;
}