/**
* @file GLFWE.cpp
*/
#include "GLFWEW.h"
#include <iostream>

/// GLFW��GLEW�����b�v���邽�߂̖��O���.
namespace GLFWEW {

	void APIENTRY OutputGLDebugMessage(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar *message, GLvoid *userParam)
	{
		std::cerr << message << "\n";
	}

	/**
	* GLFW����̃G���[�񍐂���������.
	*
	* @param error �G���[�ԍ�.
	* @param desc  �G���[�̓��e.
	*/
	void ErrorCallback(int error, const char* desc)
	{
		std::cerr << "ERROR: " << desc << std::endl;
	}

	/**
	* �V���O���g���C���X�^���X���擾����.
	*
	* @return Window�̃V���O���g���C���X�^���X.
	*/
	Window& Window::Instance()
	{
		static Window instance;
		return instance;
	}

	/**
	* �R���X�g���N�^.
	*/
	Window::Window()
	{
	}

	/**
	* �f�X�g���N�^.
	*/
	Window::~Window()
	{
		if (isGLFWInitialized) {
			glfwTerminate();
		}
	}

	/**
	* GLFW/GLEW�̏�����.
	*
	* @param w �E�B���h�E�̕`��͈͂̕�(�s�N�Z��).
	* @param h �E�B���h�E�̕`��͈͂̍���(�s�N�Z��).
	* @param title �E�B���h�E�^�C�g��(UTF-8��0�I�[������).
	*
	* @retval true ����������.
	* @retval false ���������s.
	*/
	bool Window::Init(int w, int h, const char* title)
	{
		if (isInitialized) {
			std::cerr << "ERROR: GLFWEW�͊��ɏ���������Ă��܂�." << std::endl;
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
			std::cerr << "ERROR: GLEW�̏������Ɏ��s���܂���." << std::endl;
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
	* �E�B���h�E�����ׂ������ׂ�.
	*
	* @retval true ����.
	* @retval false ���Ȃ�.
	*/
	bool Window::ShouldClose() const
	{
		return glfwWindowShouldClose(window) != 0;
	}

	/**
	* �t�����g�o�b�t�@�ƃo�b�N�o�b�t�@��؂�ւ���.
	*/
	void Window::SwapBuffers() const
	{
		glfwPollEvents();
		glfwSwapBuffers(window);
	}

	/**
	* �L�[��������Ă��邩���ׂ�.
	*
	* @param key ���ׂ�L�[��ID(GLFW_KEY_A�Ȃ�).
	*
	* @retval true  �L�[��������Ă���.
	* @retval false �L�[��������Ă��Ȃ�.
	*/
	bool Window::IsKeyPressed(int key) const
	{
		return glfwGetKey(window, key) == GLFW_PRESS;
	}

	/**
	* �^�C�}�[������������.
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
	* �^�C�}�[���X�V����.
	*
	* @sa InitTimer, GetDeltaTime
	*/
	void Window::UpdateTimer()
	{
		// �o�ߎ��Ԃ��v��.
		const double currentTime = glfwGetTime();
		deltaTime = currentTime - previousTime;
		previousTime = currentTime;

		// �o�ߎ��Ԃ������Ȃ肷���Ȃ��悤�ɒ���.
		const float upperLimit = 0.25f; // �o�ߎ��ԂƂ��ċ��e�������.
		if (deltaTime > upperLimit) {
			deltaTime = 0.1f;
		}
	}

	/**
	* �o�ߎ��Ԃ��擾����.
	*
	* @return ���O��2���UpdateTimer()�Ăяo���̊ԂɌo�߂�������.
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
////���b�p�[�Ƃ͊֐���N���X�A���C�u�����𔖂���ނ悤�ȃR�[�h�������\��
////�@�\���܂Ƃ߂Ĉ����₷������
//
///// GLFW ��GLEW�����b�v���邽�߂̖��O���
//namespace GLFWEW {
//
//
//	/**
//	* GLFW����̃G���[�񍐂���������
//	*
//	*
//	* @param error	�G���[�ԍ�
//	* @param desc	�G���[�̓��e
//	*
//	*/
//	void  ErrorCallback(int error, const char* desc)
//	{
//		//GLFW����n���ꂽ�G���[���b�Z�[�W��W���G���[�o�͂ɕ\�����邾��
//		std::cerr << "ERROR: " << desc << std::endl;
//	}
//
//
//	/**
//	* �V���O���g���C���X�^���X���擾����
//	*
//	* @param Window �̃V���O���g���C���X�^���X
//	*/
//	Window& Window::Instance()
//	{
//		//static�� Window ���ЂƂ�����`
//		static Window instance;
//		//���̎Q�Ƃ�Ԃ�
//		return instance;
//	}
//
//	/**
//	* �R���X�g���N�^
//	* �������Ȃ�
//	*/
//	Window::Window()
//	{
//
//	}
//
//	/**
//	* �f�X�g���N�^
//	*/
//	Window::~Window()
//	{
//		//GLFW������������Ă����ꍇ
//		if (isGLFWInitialized) {
//
//			//GLFW�̏I��
//			glfwTerminate();
//
//		}
//
//	}
//
//	/**
//	* GLFW/GLEW �̏�����
//	*
//	* @param w �E�B���h�E�̕`��͈͂̕�(�s�N�Z��)
//	* @param h �E�B���h�E�̕`��͈͂̍���(�s�N�Z��)
//	* @param title �E�B���h�E�^�C�g�� (UTF-8 �� 0 �I�[����)
//	*
//	* @retval true	����������
//	* @retval false	���������s
//	*/
//	bool Window::Init(int w, int h, const char* title)
//	{
//		//����������Ă����ꍇ
//		if (isInitialized) {
//			std::cerr << "ERROR: GLFWEW�͂��łɏ���������Ă��܂�" << std::endl;
//			return false;
//		}
//
//		//GLFW �� �������t���O��False�̏ꍇ
//		if (!isGLFWInitialized) {
//
//			//ErrorCallback�֐����Ăяo��
//			glfwSetErrorCallback(ErrorCallback);
//
//			//GLFW�̏�����.
//			if (glfwInit() != GL_TRUE) {
//				//���s������false��Ԃ�
//				return false;
//			}
//			//�������t���O��True�ɂ���
//			isGLFWInitialized = true;
//		}
//
//		//window���Ȃ��ꍇ
//		if (!window) {
//			window = glfwCreateWindow(w, h, title, nullptr, nullptr);
//			
//			//window���n���Ȃ������ꍇ
//			if (!window) {
//				//�A�v���P�[�V�������I������
//				return false;
//			}
//			//�w�肵��Window�ɑΉ�����OpenGL�R���e�L�X�g��`��Ώۂɐݒ�
//			glfwMakeContextCurrent(window);
//		}
//
//		//GLEW��������.
//		if (glewInit() != GLEW_OK) {
//
//			//GLFW�Ɗ֌W�Ȃ����߂ɁA�R�[���o�b�N���Ă΂�Ȃ��̂Ŗ����I�ɏo��
//			std::cerr << "ERROR: GLEW�̏������Ɏ��s���܂���" << std::endl;
//
//			//false��Ԃ�
//			return false;
//		}
//
//
//		//=========================�ۑ�2 [GL_EXTENSIONS, GL_VENDOR]�Ȃǂ𓯂��`�ŏ���������============================
//		//==============================================================================================
//		// OpenGL�̏����R���\�[���E�B���h�E�֏o�͂���
//
//		//GPU�̖��O �������� �h���C�o��
//		const GLubyte* renderer = glGetString(GL_RENDERER);
//		std::cout << "Renderer: " << renderer << std::endl;
//
//		//GPU���Ή����Ă���ő��OpenGL��version
//		const GLubyte* version = glGetString(GL_VERSION);
//		std::cout << "Version: " << version << std::endl;
//
//		//�������t���O��True�ɂ���
//		isInitialized = true;
//
//		//true��Ԃ�
//		return true;
//
//	}
//
//
//	/**
//	* �E�B���h�E�����ׂ������ׂ�
//	*	(glfwWindowShouldClose�֐� �� ���b�p�[)
//	* @param true ����
//	* @param false ���Ȃ�
//	*/
//	bool Window::ShouldClose() const
//	{
//		//window�����
//		return glfwWindowShouldClose(window) != 0;
//	}
//
//
//	/**
//	* �t�����g�o�b�t�@�ƃo�b�N�o�b�t�@��؂�ւ���
//	*	glfwPollEvents�֐� �� glfwSwapBuffers�֐� �� ���b�p�[
//	*/
//	void Window::SwapBuffers() const
//	{
//		//GLFW �� OS���瑗��ꂽ�C�x���g����������֐�
//		glfwPollEvents();
//
//		//�t���[���o�b�t�@�̕\�����ƕ`�摤�����ւ���
//		//�`�撆�̉�ʂ��B�����ƂŁA���[�U�[���猩���Ȃ��悤�ɂ���B
//		glfwSwapBuffers(window);
//
//	}
//
//
//
//	//====================-�Q�[���p�b�h�n========================================
//	/**
//	* �Q�[���p�b�h�̏�Ԃ��擾����
//	*	
//	* @return �Q�[���p�b�h�̏��
//	*/
//	const GamePad& Window::GetGamePad() const
//	{	
//		//gamepad�̃����o�ϐ��̎Q�Ƃ�Ԃ�����
//		return gamepad;
//	}
//
//
//	//=================ID�̗񋓌^��`======================
//	/**
//	* �A�i���O���͑��uID
//	*
//	* @note Xinput�
//	*/
//	enum GLFWAXESID {
//		GLFWAXESID_LeftX, ///< ���X�e�B�b�N��X��
//		GLFWAXESID_LeftY, ///< ���X�e�B�b�N��Y��
//		
//		GLFWAXESID_BackX, ///< �A�i���O�g���K�[
//		
//		GLFWAXESID_RightX, ///< �E�X�e�B�b�N��X��
//		GLFWAXESID_RightY, ///< �E�X�e�B�b�N��Y��
//	};
//
//
//	/**
//	* �f�W�^�����͑��uID
//	*
//	* @note Xinput�
//	*/
//	enum GLFWBUTTONID {
//
//		GLFWBUTTONID_A, ///< A�{�^��
//		GLFWBUTTONID_B, ///< B�{�^��
//		GLFWBUTTONID_X, ///< X�{�^��
//		GLFWBUTTONID_Y, ///< Y�{�^��
//
//		GLFWBUTTONID_L, ///< L�{�^��
//		GLFWBUTTONID_R, ///< R�{�^��
//
//		GLFWBUTTONID_Back, ///< Back�{�^��
//		GLFWBUTTONID_Start, ///< Start�{�^��
//
//		GLFWBUTTONID_LThumb, ///< ���X�e�B�b�N(LT)�{�^��
//		GLFWBUTTONID_RThumb, ///< �E�X�e�B�b�N(RT)�{�^��
//
//		GLFWBUTTONID_Up, ///< ��{�^��
//		GLFWBUTTONID_Right, ///< �E�{�^��
//		GLFWBUTTONID_Down, ///< ���{�^��
//		GLFWBUTTONID_Left, ///< ���{�^��
//
//	};
//
//
//	//==========�X�V�֐�====================
//
//	/**
//	* �Q�[���p�b�h�̏�Ԃ��X�V����
//	*/
//	void Window::UpdateGamePad()
//	{
//		//�Q�[���p�b�h�̓��́i������Ă��邩�ǂ����j��Ԃ��i�[����B
//		const uint32_t prevButtons = gamepad.buttons;
//		//?????
//		int axesCount, buttonCount;
//
//		//���̓f�[�^���擾		�����͓��̓f�[�^�z��ւ̖߂�l
//		const float* axes = glfwGetJoystickAxes(GLFW_JOYSTICK_1, &axesCount);
//		//���̓f�[�^���擾		�����͓��̓f�[�^�z��ւ̖߂�l
//		const uint8_t* buttons = glfwGetJoystickButtons(GLFW_JOYSTICK_1, &buttonCount);
//		//�Q�̎��ƂW�̃{�^�����擾�ł��Ă���ꍇ�Q�[���p�b�h�̓��͂������悤�ɂ���
//		if (axes && buttons && (axesCount >= 2) && (buttonCount >= 8))
//		{
//			// &=  ���r�b�g���Ƃ� AND ���
//			gamepad.buttons &= ~(GamePad::DPAD_UP | GamePad::DPAD_DOWN | GamePad::DPAD_LEFT | GamePad::DPAD_RIGHT);
//
//			//�A�i���O���͂̔���iJudgment���z��������͂���Ă���Ƃ��邽�߂̕ϐ��j �W���b�W�����g
//			static const float Judgment = 0.3f;
//
//			//���A�i���O�X�e�B�b�N�̓��͂��㉺���E�L�[�Ɋ��蓖�Ă�
//			if (axes[GLFWAXESID_LeftY] >= Judgment)
//			{
//				// |= ���r�b�g���Ƃ� OR���
//				gamepad.buttons |= GamePad::DPAD_UP;
//			}
//			else if (axes[GLFWAXESID_LeftY] <= -Judgment)
//			{
//				// |= ���r�b�g���Ƃ� OR���
//				gamepad.buttons |= GamePad::DPAD_DOWN;
//			}
//			if (axes[GLFWAXESID_LeftX] >= Judgment)
//			{
//				// |= ���r�b�g���Ƃ� OR���
//				gamepad.buttons |= GamePad::DPAD_LEFT;
//			}
//			else if (axes[GLFWAXESID_LeftX] <= -Judgment)
//			{
//				// |= ���r�b�g���Ƃ� OR���
//				gamepad.buttons |= GamePad::DPAD_RIGHT;
//			}
//
//			//�{�^������
//			//�Ή�����v�f���m���y�A�ɂ����e�[�u�����g��
//			//�W���C�X�e�B�b�N���͂��Q�[���p�b�h���͂ɕϊ�����
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
//			//�{�^������
//			//�Ή�����v�f���m���y�A�ɂ����e�[�u�����g��
//			//�L�[�{�[�h���͂��Q�[���p�b�h���͂ɕϊ�����
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
//			//������Ă��邩�ǂ�����glfwGetKey�Ŏ擾����
//			for (const auto& e : KeyMap)
//			{
//				const int key = glfwGetKey(window, e.glfwCode);
//				if (key == GLFW_PRESS) {
//					//������Ă���Ȃ�΁A�Ή�����r�b�g���i�[����B
//					gamepad.buttons |= e.gamepadCode;
//				}
//				else if (key == GLFW_RELEASE) {
//					//������Ă���A�Ή�����r�b�g���i�[����B
//					gamepad.buttons &= ~e.gamepadCode;
//				}
//			}
//		}
//		//����̍X�V�ŉ����ꂽ�L�[���i�[����
//		gamepad.buttonDown = gamepad.buttons & ~prevButtons;
//	};
//
//	/**
//	* �L�[��������Ă��邩���ׂ�.
//	*
//	* @param key ���ׂ����L�[�E�R�[�h(GLFW_KEY_A�Ȃ�).
//	*
//	* @retval true  �L�[��������Ă���.
//	* @retval false �L�[��������Ă��Ȃ�.
//	*
//	* �g�p�ł���L�[�E�R�[�h�̈ꗗ��glfw3.h�ɂ���܂�(�ukeyboard�v�Ō���).
//	*/
//	bool Window::IsKeyPressed(int key) const
//	{
//		return glfwGetKey(window, key) == GLFW_PRESS;
//	}
//
//}// namespace GLFWEW