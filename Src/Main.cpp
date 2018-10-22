/**
* @file Main.cpp
*/
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

/**
* GLFWからのエラー報告を処理する
*
*
* @param error	エラー番号
* @param desc	エラーの内容
*
*/
void  ErrorCallback(int error, const char* desc)
{
	//GLFWから渡されたエラーメッセージを標準エラー出力に表示するだけ
	std::cerr << "ERROR: " << desc << std::endl;
}





/**
* エントリーポート
*/
int main() 
{
	//ErrorCallback関数を呼び出す
	glfwSetErrorCallback(ErrorCallback);




	// GLFW






	return 0;
}