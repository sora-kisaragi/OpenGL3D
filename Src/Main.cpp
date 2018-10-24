/**
* @file Main.cpp
*/
#include "GLFWEW.h"
#include "Shader.h"
#include <iostream>

/// 3D�x�N�g���^
struct Vector3
{
	float x, y, z;
};

/// RGBA�J���[�^
struct Color
{
	float r, g, b, a;
};

/// ���_�f�[�^�^ [Vertex = ���_]
struct Vertex
{
	Vector3 position;///< ���W
	Color color;///< �F
};

/// ���_�f�[�^
const Vertex vertices[] = {
	{ { -0.5f, -0.43f, 0.5f },{ 0.0f, 0.0f, 1.0f, 1.0f } },
	{ { 0.5f, -0.43f, 0.5f },{ 0.0f, 1.0f, 0.0f, 1.0f } },
	{ { 0.0f,  0.43f, 0.5f },{ 1.0f, 0.0f, 0.0f, 1.0f } },
};


/// ���_�V�F�[�_�[.
static const char* vsCode =
"#version 410 \n"
"layout(location=0) in vec3 vPosition; \n"
"layout(location=1) in vec4 vColor; \n"
"layout(location=0) out vec4 outColor; \n"
"void main() { \n"
"  outColor = vColor; \n"
"  gl_Position = vec4(vPosition, 1.0); \n"
"}";



/// �t���O�����g�V�F�[�_�[.
static const char* fsCode =
"#version 410 \n"
"layout(location=0) in vec4 inColor; \n"
"out vec4 fragColor; \n"
"void main() { \n"
"  fragColor = inColor; \n"
"}";







/**
* Vertex Buffer Object���쐬����.
*
* @param size ���_�f�[�^�̃T�C�Y.
* @param data ���_�f�[�^�ւ̃|�C���^.
*
* GLsizeiptr = int
* GLvoid = void
*
* @return �쐬����VBO.
*/
GLuint CreateVBO(GLsizeiptr size, const GLvoid* data)
{
	//unsigined int = GLuint
	GLuint vbo = 0;

	//�������̈���Ǘ�����I�u�W�F�N�g���쐬����֐�
	//�����̓o�b�t�@�I�u�W�F�N�g�̌��ƕϐ��ւ̃|�C���^
	glGenBuffers(1, &vbo);
	
	//�o�b�t�@�I�u�W�F�N�g�����̗p�r�Ɋ��蓖�Ă�
	//GL_ARRAY_BUFFER�@�́@���_�f�[�^�������萔
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	/**�o�b�t�@�I�u�W�F���ƂɃf�[�^��]������֐�
	*   ������
	* 1 �]����̃o�b�t�@�p�r
	* 2 �]���o�C�g��
	* 3 �]������f�[�^�ւ̃|�C���^
	* 4 �]����̃o�b�t�@�ɂǂ̂悤�ɃA�N�Z�X���邩�Ɋւ���q���g��n��
	*
	*	GL_STATIC_DRAW	= �A�v���P�[�V��������X�V����A�`�揈���̃\�[�X�Ƃ��Ďg����B
	*					  �o�b�t�@�͈�x�����]������A���x�����p����܂��B
	*/
	glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
	
	//0�Ŋ��蓖�Ă�����
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// vbo��Ԃ�
	return vbo;
}



/**
* Vertex Array Object���쐬����.
*
* @param vbo VAO�Ɋ֘A�t������VBO.
*
* @return �쐬����VAO.
*/
GLuint CreateVAO(GLuint vbo)
{
	GLuint vao = 0;
	
	//vao���쐬����
	glGenVertexArrays(1, &vao);

	//�w�肳�ꂽVAO��OpenGL�� ���݂̏����Ώ� �ɐݒ肷��֐�
	glBindVertexArray(vao);

	//���_�A�g���r���[�g��ݒ肷��ɂ͎��O�ɑΉ�����VBO�����蓖�Ă�K�v������
	//vbo��OpenGL�Ɋ��蓖�Ă�
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	//�w�肵���o�C���f�B���O�|�C���g��L���ɂ���
	//glDisableVertexAttribArray�Ŗ������ɂ���܂ł͗L��
	glEnableVertexAttribArray(0);

	/*
	*���_�A�g���r���[�g���o�C���f�B���O�|�C���^�Ɋ��蓖�Ă�֐�
	*���W�ƐF�f�[�^���̃A�g���r���[�g���쐬���A���ꂼ���0,1�ԂƂ���
	*������
	* 1 �o�C���f�B���O�|�C���g�̃C���f�b�N�X(0�`15) | 2 ���̗v�f�� sizeof�̓N���X��\���̂̃o�C�g�������߂�C/C++�̉��Z�q
	* 3 ���̌^ ���W��3��float�Ȃ̂�GL_FLOAT		| 4 ���𐳋K�����邩�ǂ��� GL_FALSE�Ȃ炵�Ȃ�
	* 5 ���_�f�[�^�̃o�C�g�� sizeof���g��			| 6 ��񂪒��_�f�[�^�̐擪���牽�o�C�g�ڂɂ��邩 ��ݒ肵�܂� C++�̋@�\ offsetof�}�N�����d�v �ڍׂ�Doc��2��
	*/
	glVertexAttribPointer(0, sizeof(Vertex::position) / sizeof(float),
		GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*)(offsetof(Vertex, position)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, sizeof(Vertex::color) / sizeof(float),
		GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*)(offsetof(Vertex, color)));

	//0�Ŋ��蓖�Ă�����
	glBindVertexArray(0);

	//VBO���폜����@VAO�Ɋ��蓖�Ă��Ă���ꍇ�폜�}�[�N��t���č폜�ҋ@����
	glDeleteBuffers(1, &vbo);

	return vao;

}








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

	//Shader.h
	//���������֐����Ăяo���A�쐬�����I�u�W�F�N�g��ϐ��Ɋi�[
	const GLuint vbo = CreateVBO(sizeof(vertices), vertices);
	const GLuint vao = CreateVAO(vbo);
	const GLuint shaderProgram = Shader::Build(vsCode, fsCode);

	//���s������1��Ԃ��ăv���O�������I��
	if (!vbo || !vao || !shaderProgram) {
		return 1;
	}








	//���C�����[�v
	while (!window.ShouldClose()) {


		//�o�b�N�o�b�t�@��ߋ�����Ƃ��̐F�@RGBA
		glClearColor(.01f, 0.3f, 0.5f, 1.0f);
		
		//�o�b�N�o�b�t�@����������֐� �����͏�������o�b�t�@�̎��
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//�`��Ɏg�p����v���O������ݒ�
		glUseProgram(shaderProgram);

		//�w�肳�ꂽVAO��OpenGL�̌��݂̏����Ώ��ɐݒ肷��
		glBindVertexArray(vao);

		//�w�肳�ꂽ�I�u�W�F�N�g��f�[�^���g���Đ}�`��`��
		glDrawArrays(GL_TRIANGLES, 0, sizeof(vertices) / sizeof(vertices[0]));

		//sizeof(�z��)/sizeof(�z��[0])�̐���
		/*
		*	[�⑫] �usizeof(�z��)/sizeof(�z��[0])�v�Ƃ����̂�
		*	C/C++�Ŕz��̑傫�����擾���銵�p�I�ȃv���O�����ł��B
		*	�����ł͒��ڏ����Ă��܂����A��ʓI�ɂ�
		*	#define ARRAY_SIZE(a) (sizeof(a)/sizeof((a)[0]))
		*	�̂悤�ȃ}�N�����`���Ă�����g���܂��B
		*/



		//�o�b�t�@�̐ؑ�
		window.SwapBuffers();
	}

	//���Ƃ�����ꂽ�I�u�W�F�N�g���ɍ폜
	glDeleteProgram(shaderProgram);
	glDeleteVertexArrays(1, &vao);

	//�폜���Ԃ̕⑫
	/*
	*�u�쐬�����Ƃ��Ƃ͋t�̏��ԂŃI�u�W�F�N�g���폜����v���Ƃ́A
	* �v���O�������쐬�����ň�ʓI�ȃ��[���ł��B
	* �ˑ��֌W�̗L���ɂ�����炸�A���̃��[���ɏ]�����Ƃ����E�߂��܂��B
	*/


	return 0;
}