/**
* @file GLFWEW.cpp
*/
#include "GLFWEW.h"
#include <iostream>

//ラッパーとは関数やクラス、ライブラリを薄く包むようなコードを示す表現
//機能をまとめて扱いやすくする

/// GLFW とGLEWをラップするための名前空間
namespace GLFWEW {


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
	* シングルトンインスタンスを取得する
	*
	* @param Window のシングルトンインスタンス
	*/
	Window& Window::Instance()
	{
		//staticで Window をひとつだけ定義
		static Window instance;
		//その参照を返す
		return instance;
	}

	/**
	* コンストラクタ
	* 何もしない
	*/
	Window::Window()
	{

	}

	/**
	* デストラクタ
	*/
	Window::~Window()
	{
		//GLFWが初期化されていた場合
		if (isGLFWInitialized) {

			//GLFWの終了
			glfwTerminate();

		}

	}

	/**
	* GLFW/GLEW の初期化
	*
	* @param w ウィンドウの描画範囲の幅(ピクセル)
	* @param h ウィンドウの描画範囲の高さ(ピクセル)
	* @param title ウィンドウタイトル (UTF-8 の 0 終端文字)
	*
	* @retval true	初期化成功
	* @retval false	初期化失敗
	*/
	bool Window::Init(int w, int h, const char* title)
	{
		//初期化されていた場合
		if (isInitialized) {
			std::cerr << "ERROR: GLFWEWはすでに初期化されています" << std::endl;
			return false;
		}

		//GLFW の 初期化フラグがFalseの場合
		if (!isGLFWInitialized) {

			//ErrorCallback関数を呼び出す
			glfwSetErrorCallback(ErrorCallback);

			//GLFWの初期化.
			if (glfwInit() != GL_TRUE) {
				//失敗したらfalseを返す
				return false;
			}
			//初期化フラグをTrueにする
			isGLFWInitialized = true;
		}

		//windowがない場合
		if (!window) {
			window = glfwCreateWindow(w, h, title, nullptr, nullptr);
			
			//windowが創られなかった場合
			if (!window) {
				//アプリケーションを終了する
				return false;
			}
			//指定したWindowに対応するOpenGLコンテキストを描画対象に設定
			glfwMakeContextCurrent(window);
		}

		//GLEWを初期化.
		if (glewInit() != GLEW_OK) {

			//GLFWと関係ないために、コールバックが呼ばれないので明示的に出力
			std::cerr << "ERROR: GLEWの初期化に失敗しました" << std::endl;

			//falseを返す
			return false;
		}


		//=========================課題2 [GL_EXTENSIONS, GL_VENDOR]などを同じ形で書き加える============================
		//==============================================================================================
		// OpenGLの情報をコンソールウィンドウへ出力する

		//GPUの名前 もしくは ドライバ名
		const GLubyte* renderer = glGetString(GL_RENDERER);
		std::cout << "Renderer: " << renderer << std::endl;

		//GPUが対応している最大のOpenGLのversion
		const GLubyte* version = glGetString(GL_VERSION);
		std::cout << "Version: " << version << std::endl;

		//初期化フラグをTrueにする
		isInitialized = true;

		//trueを返す
		return true;

	}


	/**
	* ウィンドウを閉じるべきか調べる
	*	(glfwWindowShouldClose関数 の ラッパー)
	* @param true 閉じる
	* @param false 閉じない
	*/
	bool Window::ShouldClose() const
	{
		//windowを閉じる
		return glfwWindowShouldClose(window) != 0;
	}


	/**
	* フロントバッファとバックバッファを切り替える
	*	glfwPollEvents関数 と glfwSwapBuffers関数 の ラッパー
	*/
	void Window::SwapBuffers() const
	{
		//GLFW が OSから送られたイベントを処理する関数
		glfwPollEvents();

		//フレームバッファの表示側と描画側を入れ替える
		//描画中の画面を隠すことで、ユーザーから見えないようにする。
		glfwSwapBuffers(window);

	}



}// namespace GLFWEW