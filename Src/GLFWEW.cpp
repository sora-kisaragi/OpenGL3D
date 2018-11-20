/**
* @file GLFWE.cpp
*/
#include "GLFWEW.h"
#include <iostream>

/// GLFWとGLEWをラップするための名前空間.
namespace GLFWEW {

	void APIENTRY OutputGLDebugMessage(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar *message, GLvoid *userParam)
	{
		std::cerr << message << "\n";
	}

	/**
	* GLFWからのエラー報告を処理する.
	*
	* @param error エラー番号.
	* @param desc  エラーの内容.
	*/
	void ErrorCallback(int error, const char* desc)
	{
		std::cerr << "ERROR: " << desc << std::endl;
	}

	/**
	* シングルトンインスタンスを取得する.
	*
	* @return Windowのシングルトンインスタンス.
	*/
	Window& Window::Instance()
	{
		static Window instance;
		return instance;
	}

	/**
	* コンストラクタ.
	*/
	Window::Window()
	{
	}

	/**
	* デストラクタ.
	*/
	Window::~Window()
	{
		if (isGLFWInitialized) {
			glfwTerminate();
		}
	}

	/**
	* GLFW/GLEWの初期化.
	*
	* @param w ウィンドウの描画範囲の幅(ピクセル).
	* @param h ウィンドウの描画範囲の高さ(ピクセル).
	* @param title ウィンドウタイトル(UTF-8の0終端文字列).
	*
	* @retval true 初期化成功.
	* @retval false 初期化失敗.
	*/
	bool Window::Init(int w, int h, const char* title)
	{
		if (isInitialized) {
			std::cerr << "ERROR: GLFWEWは既に初期化されています." << std::endl;
			return false;
		}
		if (!isGLFWInitialized) {
			glfwSetErrorCallback(ErrorCallback);
			if (glfwInit() != GL_TRUE) {
				return false;
			}
			isGLFWInitialized = true;
		}

		if (!window) {
			glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);
			window = glfwCreateWindow(w, h, title, nullptr, nullptr);
			if (!window) {
				return false;
			}
			glfwMakeContextCurrent(window);
		}

		if (glewInit() != GLEW_OK) {
			std::cerr << "ERROR: GLEWの初期化に失敗しました." << std::endl;
			return false;
		}

		glDebugMessageCallback(OutputGLDebugMessage, nullptr);

		const GLubyte* renderer = glGetString(GL_RENDERER);
		std::cout << "Renderer: " << renderer << std::endl;
		const GLubyte* version = glGetString(GL_VERSION);
		std::cout << "Version: " << version << std::endl;

		isInitialized = true;
		return true;
	}

	/**
	* ウィンドウを閉じるべきか調べる.
	*
	* @retval true 閉じる.
	* @retval false 閉じない.
	*/
	bool Window::ShouldClose() const
	{
		return glfwWindowShouldClose(window) != 0;
	}

	/**
	* フロントバッファとバックバッファを切り替える.
	*/
	void Window::SwapBuffers() const
	{
		glfwPollEvents();
		glfwSwapBuffers(window);
	}

	/**
	* キーが押されているか調べる.
	*
	* @param key 調べるキーのID(GLFW_KEY_Aなど).
	*
	* @retval true  キーが押されている.
	* @retval false キーが押されていない.
	*/
	bool Window::IsKeyPressed(int key) const
	{
		return glfwGetKey(window, key) == GLFW_PRESS;
	}

	/**
	* タイマーを初期化する.
	*
	* @sa UpdateTimer, GetDeltaTime
	*/
	void Window::InitTimer()
	{
		glfwSetTime(0.0);
		previousTime = 0.0;
		deltaTime = 0.0;
	}

	/**
	* タイマーを更新する.
	*
	* @sa InitTimer, GetDeltaTime
	*/
	void Window::UpdateTimer()
	{
		// 経過時間を計測.
		const double currentTime = glfwGetTime();
		deltaTime = currentTime - previousTime;
		previousTime = currentTime;

		// 経過時間が長くなりすぎないように調整.
		const float upperLimit = 0.25f; // 経過時間として許容される上限.
		if (deltaTime > upperLimit) {
			deltaTime = 0.1f;
		}
	}

	/**
	* 経過時間を取得する.
	*
	* @return 直前の2回のUpdateTimer()呼び出しの間に経過した時間.
	*
	* @sa InitTimer, UpdateTimer
	*/
	double Window::DeltaTime() const
	{
		return deltaTime;
	}

	/**
	*
	*/
	glm::vec2 Window::GetMousePosition() const
	{
		double x, y;
		glfwGetCursorPos(window, &x, &y);
		return glm::vec2(x, y);
	}

	/**
	*
	*/
	int Window::GetMouseButton(int button) const
	{
		return glfwGetMouseButton(window, button);
	}

} // namespace GLFWEW





///**
//* @file GLFWEW.cpp
//*/
//#include "GLFWEW.h"
//#include <iostream>
//
////ラッパーとは関数やクラス、ライブラリを薄く包むようなコードを示す表現
////機能をまとめて扱いやすくする
//
///// GLFW とGLEWをラップするための名前空間
//namespace GLFWEW {
//
//
//	/**
//	* GLFWからのエラー報告を処理する
//	*
//	*
//	* @param error	エラー番号
//	* @param desc	エラーの内容
//	*
//	*/
//	void  ErrorCallback(int error, const char* desc)
//	{
//		//GLFWから渡されたエラーメッセージを標準エラー出力に表示するだけ
//		std::cerr << "ERROR: " << desc << std::endl;
//	}
//
//
//	/**
//	* シングルトンインスタンスを取得する
//	*
//	* @param Window のシングルトンインスタンス
//	*/
//	Window& Window::Instance()
//	{
//		//staticで Window をひとつだけ定義
//		static Window instance;
//		//その参照を返す
//		return instance;
//	}
//
//	/**
//	* コンストラクタ
//	* 何もしない
//	*/
//	Window::Window()
//	{
//
//	}
//
//	/**
//	* デストラクタ
//	*/
//	Window::~Window()
//	{
//		//GLFWが初期化されていた場合
//		if (isGLFWInitialized) {
//
//			//GLFWの終了
//			glfwTerminate();
//
//		}
//
//	}
//
//	/**
//	* GLFW/GLEW の初期化
//	*
//	* @param w ウィンドウの描画範囲の幅(ピクセル)
//	* @param h ウィンドウの描画範囲の高さ(ピクセル)
//	* @param title ウィンドウタイトル (UTF-8 の 0 終端文字)
//	*
//	* @retval true	初期化成功
//	* @retval false	初期化失敗
//	*/
//	bool Window::Init(int w, int h, const char* title)
//	{
//		//初期化されていた場合
//		if (isInitialized) {
//			std::cerr << "ERROR: GLFWEWはすでに初期化されています" << std::endl;
//			return false;
//		}
//
//		//GLFW の 初期化フラグがFalseの場合
//		if (!isGLFWInitialized) {
//
//			//ErrorCallback関数を呼び出す
//			glfwSetErrorCallback(ErrorCallback);
//
//			//GLFWの初期化.
//			if (glfwInit() != GL_TRUE) {
//				//失敗したらfalseを返す
//				return false;
//			}
//			//初期化フラグをTrueにする
//			isGLFWInitialized = true;
//		}
//
//		//windowがない場合
//		if (!window) {
//			window = glfwCreateWindow(w, h, title, nullptr, nullptr);
//			
//			//windowが創られなかった場合
//			if (!window) {
//				//アプリケーションを終了する
//				return false;
//			}
//			//指定したWindowに対応するOpenGLコンテキストを描画対象に設定
//			glfwMakeContextCurrent(window);
//		}
//
//		//GLEWを初期化.
//		if (glewInit() != GLEW_OK) {
//
//			//GLFWと関係ないために、コールバックが呼ばれないので明示的に出力
//			std::cerr << "ERROR: GLEWの初期化に失敗しました" << std::endl;
//
//			//falseを返す
//			return false;
//		}
//
//
//		//=========================課題2 [GL_EXTENSIONS, GL_VENDOR]などを同じ形で書き加える============================
//		//==============================================================================================
//		// OpenGLの情報をコンソールウィンドウへ出力する
//
//		//GPUの名前 もしくは ドライバ名
//		const GLubyte* renderer = glGetString(GL_RENDERER);
//		std::cout << "Renderer: " << renderer << std::endl;
//
//		//GPUが対応している最大のOpenGLのversion
//		const GLubyte* version = glGetString(GL_VERSION);
//		std::cout << "Version: " << version << std::endl;
//
//		//初期化フラグをTrueにする
//		isInitialized = true;
//
//		//trueを返す
//		return true;
//
//	}
//
//
//	/**
//	* ウィンドウを閉じるべきか調べる
//	*	(glfwWindowShouldClose関数 の ラッパー)
//	* @param true 閉じる
//	* @param false 閉じない
//	*/
//	bool Window::ShouldClose() const
//	{
//		//windowを閉じる
//		return glfwWindowShouldClose(window) != 0;
//	}
//
//
//	/**
//	* フロントバッファとバックバッファを切り替える
//	*	glfwPollEvents関数 と glfwSwapBuffers関数 の ラッパー
//	*/
//	void Window::SwapBuffers() const
//	{
//		//GLFW が OSから送られたイベントを処理する関数
//		glfwPollEvents();
//
//		//フレームバッファの表示側と描画側を入れ替える
//		//描画中の画面を隠すことで、ユーザーから見えないようにする。
//		glfwSwapBuffers(window);
//
//	}
//
//
//
//	//====================-ゲームパッド系========================================
//	/**
//	* ゲームパッドの状態を取得する
//	*	
//	* @return ゲームパッドの状態
//	*/
//	const GamePad& Window::GetGamePad() const
//	{	
//		//gamepadのメンバ変数の参照を返すだけ
//		return gamepad;
//	}
//
//
//	//=================IDの列挙型定義======================
//	/**
//	* アナログ入力装置ID
//	*
//	* @note Xinput基準
//	*/
//	enum GLFWAXESID {
//		GLFWAXESID_LeftX, ///< 左スティックのX軸
//		GLFWAXESID_LeftY, ///< 左スティックのY軸
//		
//		GLFWAXESID_BackX, ///< アナログトリガー
//		
//		GLFWAXESID_RightX, ///< 右スティックのX軸
//		GLFWAXESID_RightY, ///< 右スティックのY軸
//	};
//
//
//	/**
//	* デジタル入力装置ID
//	*
//	* @note Xinput基準
//	*/
//	enum GLFWBUTTONID {
//
//		GLFWBUTTONID_A, ///< Aボタン
//		GLFWBUTTONID_B, ///< Bボタン
//		GLFWBUTTONID_X, ///< Xボタン
//		GLFWBUTTONID_Y, ///< Yボタン
//
//		GLFWBUTTONID_L, ///< Lボタン
//		GLFWBUTTONID_R, ///< Rボタン
//
//		GLFWBUTTONID_Back, ///< Backボタン
//		GLFWBUTTONID_Start, ///< Startボタン
//
//		GLFWBUTTONID_LThumb, ///< 左スティック(LT)ボタン
//		GLFWBUTTONID_RThumb, ///< 右スティック(RT)ボタン
//
//		GLFWBUTTONID_Up, ///< 上ボタン
//		GLFWBUTTONID_Right, ///< 右ボタン
//		GLFWBUTTONID_Down, ///< 下ボタン
//		GLFWBUTTONID_Left, ///< 左ボタン
//
//	};
//
//
//	//==========更新関数====================
//
//	/**
//	* ゲームパッドの状態を更新する
//	*/
//	void Window::UpdateGamePad()
//	{
//		//ゲームパッドの入力（押されているかどうか）状態を格納する。
//		const uint32_t prevButtons = gamepad.buttons;
//		//?????
//		int axesCount, buttonCount;
//
//		//入力データを取得		引数は入力データ配列への戻り値
//		const float* axes = glfwGetJoystickAxes(GLFW_JOYSTICK_1, &axesCount);
//		//入力データを取得		引数は入力データ配列への戻り値
//		const uint8_t* buttons = glfwGetJoystickButtons(GLFW_JOYSTICK_1, &buttonCount);
//		//２つの軸と８つのボタンが取得できている場合ゲームパッドの入力を扱うようにする
//		if (axes && buttons && (axesCount >= 2) && (buttonCount >= 8))
//		{
//			// &=  ←ビットごとの AND 代入
//			gamepad.buttons &= ~(GamePad::DPAD_UP | GamePad::DPAD_DOWN | GamePad::DPAD_LEFT | GamePad::DPAD_RIGHT);
//
//			//アナログ入力の判定（Judgmentを越えたら入力されているとするための変数） ジャッジメント
//			static const float Judgment = 0.3f;
//
//			//左アナログスティックの入力を上下左右キーに割り当てる
//			if (axes[GLFWAXESID_LeftY] >= Judgment)
//			{
//				// |= ←ビットごとの OR代入
//				gamepad.buttons |= GamePad::DPAD_UP;
//			}
//			else if (axes[GLFWAXESID_LeftY] <= -Judgment)
//			{
//				// |= ←ビットごとの OR代入
//				gamepad.buttons |= GamePad::DPAD_DOWN;
//			}
//			if (axes[GLFWAXESID_LeftX] >= Judgment)
//			{
//				// |= ←ビットごとの OR代入
//				gamepad.buttons |= GamePad::DPAD_LEFT;
//			}
//			else if (axes[GLFWAXESID_LeftX] <= -Judgment)
//			{
//				// |= ←ビットごとの OR代入
//				gamepad.buttons |= GamePad::DPAD_RIGHT;
//			}
//
//			//ボタン入力
//			//対応する要素同士をペアにしたテーブルを使い
//			//ジョイスティック入力をゲームパッド入力に変換する
//			static const struct {
//				int glfwCode;
//				uint32_t gamepadCode;
//			} KeyMap[] = {
//				{ GLFWBUTTONID_A, GamePad::A},
//				{ GLFWBUTTONID_B, GamePad::B},
//				{ GLFWBUTTONID_X, GamePad::X},
//				{ GLFWBUTTONID_Y, GamePad::Y},
//				{ GLFWBUTTONID_L, GamePad::L},
//				{ GLFWBUTTONID_R, GamePad::R },
//				{ GLFWBUTTONID_LThumb, GamePad::LT },
//				{ GLFWBUTTONID_RThumb, GamePad::RT },
//				{ GLFWBUTTONID_Start, GamePad::START },
//				{ GLFWBUTTONID_Back, GamePad::Back},
//			};
//
//			
//			for (const auto& e : KeyMap)
//			{
//				if (buttons[e.glfwCode] == GLFW_PRESS)
//				{
//					gamepad.buttons |= e.gamepadCode;
//				}
//				else if (buttons[e.glfwCode] == GLFW_RELEASE)
//				{
//					gamepad.buttons &= ~e.gamepadCode;
//				}
//			}
//		}
//		else {
//			//ボタン入力
//			//対応する要素同士をペアにしたテーブルを使い
//			//キーボード入力をゲームパッド入力に変換する
//			static const struct {
//				int glfwCode;
//				uint32_t gamepadCode;
//			} KeyMap[] = {
//				{ GLFW_KEY_W, GamePad::DPAD_UP },
//				{ GLFW_KEY_S, GamePad::DPAD_DOWN },
//				{ GLFW_KEY_A, GamePad::DPAD_LEFT },
//				{ GLFW_KEY_D, GamePad::DPAD_RIGHT },
//				{ GLFW_KEY_ENTER, GamePad::START},
//				{ GLFW_KEY_ESCAPE, GamePad::Back},
//				{ GLFW_KEY_J, GamePad::X},
//				{ GLFW_KEY_I, GamePad::Y},
//				{ GLFW_KEY_K, GamePad::A},
//				{ GLFW_KEY_O, GamePad::B},
//			};
//			//押されているかどうかをglfwGetKeyで取得する
//			for (const auto& e : KeyMap)
//			{
//				const int key = glfwGetKey(window, e.glfwCode);
//				if (key == GLFW_PRESS) {
//					//押されているならば、対応するビットを格納する。
//					gamepad.buttons |= e.gamepadCode;
//				}
//				else if (key == GLFW_RELEASE) {
//					//離されてたら、対応するビットを格納する。
//					gamepad.buttons &= ~e.gamepadCode;
//				}
//			}
//		}
//		//今回の更新で押されたキーを格納する
//		gamepad.buttonDown = gamepad.buttons & ~prevButtons;
//	};
//
//	/**
//	* キーが押されているか調べる.
//	*
//	* @param key 調べたいキー・コード(GLFW_KEY_Aなど).
//	*
//	* @retval true  キーが押されている.
//	* @retval false キーが押されていない.
//	*
//	* 使用できるキー・コードの一覧はglfw3.hにあります(「keyboard」で検索).
//	*/
//	bool Window::IsKeyPressed(int key) const
//	{
//		return glfwGetKey(window, key) == GLFW_PRESS;
//	}
//
//}// namespace GLFWEW