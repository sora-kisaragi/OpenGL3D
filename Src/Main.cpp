/**
* @file Main.cpp
*/
#include "GLFWEW.h"
#include "Shader.h"
#include "Texture.h"
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>


/// 2d�x�N�g���^
struct Vector2
{
	float x, y;
};


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
	Vector2 texCoord;///< �e�N�X�`�����W�@Texture Coordinates�̗�
};



/// ���_�f�[�^
const Vertex vertices[] = {
	//��
	{ { 0.00f, 5.0f, 0.00f},{ 0.5f, 0.8f, 0.3f, 1.0f }, {0.0f,0.4f}},
	{ { 0.00f, 1.5f,-1.10f},{ 0.1f, 0.3f, 0.0f, 1.0f }, {0.0f,1.0f}},
	{ {-0.75f, 1.5f, 0.40f},{ 0.1f, 0.3f, 0.0f, 1.0f }, {-0.5f,0.0f}},
	{ { 0.75f, 1.5f, 0.40f},{ 0.1f, 0.3f, 0.0f, 1.0f }, {0.0f,0.0f}},
	{ { 0.00f, 4.0f, 0.00f},{ 0.2f, 0.1f, 0.0f, 1.0f }, {0.5f,0.1f}},
	{ { 0.00f, 0.0f,-0.37f},{ 0.5f, 0.3f, 0.2f, 1.0f }, {-0.5f,0.1f}},
	{ {-0.25f, 0.0f, 0.13f},{ 0.5f, 0.3f, 0.2f, 1.0f }, {-0.25f,0.0f}},
	{ { 0.25f, 0.0f, 0.13f},{ 0.5f, 0.3f, 0.2f, 1.0f }, {0.25f,0.0f}},

	//��

	{ { 2.8f, 0.0f, 3.0f},{ 0.4f, 0.3f, 0.2f, 1.0f },{ 1.000f, 1.00f } },
	{ { 3.0f, 4.0f, 3.0f},{ 0.6f, 0.5f, 0.3f, 1.0f },{ 1.000f, 0.31f } },
	{ { 0.0f, 6.0f, 3.0f},{ 0.5f, 0.4f, 0.2f, 1.0f },{ 0.875f, 0.00f } },
	{ {-3.0f, 4.0f, 3.0f},{ 0.6f, 0.5f, 0.3f, 1.0f },{ 0.750f, 0.31f } },
	{ {-2.8f, 0.0f, 3.0f},{ 0.4f, 0.3f, 0.2f, 1.0f },{ 0.750f, 1.00f } },
	
	{ {-2.8f, 0.0f,-3.0f},{ 0.4f, 0.3f, 0.2f, 1.0f },{ 0.500f, 1.00f } },
	{ {-3.0f, 4.0f,-3.0f},{ 0.6f, 0.5f, 0.3f, 1.0f },{ 0.500f, 0.31f } },
	{ { 0.0f, 6.0f,-3.0f},{ 0.5f, 0.4f, 0.2f, 1.0f },{ 0.375f, 0.00f } },
	{ { 3.0f, 4.0f,-3.0f},{ 0.6f, 0.5f, 0.3f, 1.0f },{ 0.250f, 0.31f } },
	{ { 2.8f, 0.0f,-3.0f},{ 0.4f, 0.3f, 0.2f, 1.0f },{ 0.250f, 1.00f } },
	
	{ { 2.8f, 0.0f, 3.0f},{ 0.4f, 0.3f, 0.2f, 1.0f },{ 0.000f, 1.00f } },
	{ { 3.0f, 4.0f, 3.0f},{ 0.6f, 0.5f, 0.3f, 1.0f },{ 0.000f, 0.31f } },
	{ { 0.0f, 6.0f, 3.0f},{ 1.0f, 1.0f, 1.0f, 1.0f },{ 0.750f, 0.00f } },
	{ { 0.0f, 6.0f,-3.0f},{ 1.0f, 1.0f, 1.0f, 1.0f },{ 0.500f, 0.00f } },
	{ { 0.0f, 6.0f,-3.0f},{ 1.0f, 1.0f, 1.0f, 1.0f },{ 0.250f, 0.00f } },
	{ { 0.0f, 6.0f, 3.0f},{ 1.0f, 1.0f, 1.0f, 1.0f },{ 0.000f, 0.00f } },

	//��
	//���
	{ { 5.0f,0.0f,0.0f },{ 1.0f,1.0f,1.0f,1.0f } },
	{ { 5.0f,0.0f,0.0f },{ 1.0f,1.0f,1.0f,1.0f } },
	{ { 5.0f,0.0f,0.0f },{ 1.0f,1.0f,1.0f,1.0f } },
	{ { 5.0f,0.0f,0.0f },{ 1.0f,1.0f,1.0f,1.0f } },
	{ { 5.0f,0.0f,0.0f },{ 1.0f,1.0f,1.0f,1.0f } },
	{ { 5.0f,0.0f,0.0f },{ 1.0f,1.0f,1.0f,1.0f } },
	//����(�O)
	{ { 5.0f,0.0f,0.0f },{ 1.0f,1.0f,1.0f,1.0f } },
	{ { 5.0f,0.0f,0.0f },{ 1.0f,1.0f,1.0f,1.0f } },
	{ { 5.0f,0.0f,0.0f },{ 1.0f,1.0f,1.0f,1.0f } },
	{ { 5.0f,0.0f,0.0f },{ 1.0f,1.0f,1.0f,1.0f } },
	{ { 5.0f,0.0f,0.0f },{ 1.0f,1.0f,1.0f,1.0f } },
	{ { 5.0f,0.0f,0.0f },{ 1.0f,1.0f,1.0f,1.0f } },
	//����(�E)
	{ { 5.0f,0.0f,0.0f },{ 1.0f,1.0f,1.0f,1.0f } },
	{ { 5.0f,0.0f,0.0f },{ 1.0f,1.0f,1.0f,1.0f } },
	{ { 5.0f,0.0f,0.0f },{ 1.0f,1.0f,1.0f,1.0f } },
	{ { 5.0f,0.0f,0.0f },{ 1.0f,1.0f,1.0f,1.0f } },
	{ { 5.0f,0.0f,0.0f },{ 1.0f,1.0f,1.0f,1.0f } },
	{ { 5.0f,0.0f,0.0f },{ 1.0f,1.0f,1.0f,1.0f } },
	//����(��)
	{ { 5.0f,0.0f,0.0f },{ 1.0f,1.0f,1.0f,1.0f } },
	{ { 5.0f,0.0f,0.0f },{ 1.0f,1.0f,1.0f,1.0f } },
	{ { 5.0f,0.0f,0.0f },{ 1.0f,1.0f,1.0f,1.0f } },
	{ { 5.0f,0.0f,0.0f },{ 1.0f,1.0f,1.0f,1.0f } },
	{ { 5.0f,0.0f,0.0f },{ 1.0f,1.0f,1.0f,1.0f } },
	{ { 5.0f,0.0f,0.0f },{ 1.0f,1.0f,1.0f,1.0f } },
	//����(��)
	{ { 5.0f,0.0f,0.0f },{ 1.0f,1.0f,1.0f,1.0f } },
	{ { 5.0f,0.0f,0.0f },{ 1.0f,1.0f,1.0f,1.0f } },
	{ { 5.0f,0.0f,0.0f },{ 1.0f,1.0f,1.0f,1.0f } },
	{ { 5.0f,0.0f,0.0f },{ 1.0f,1.0f,1.0f,1.0f } },
	{ { 5.0f,0.0f,0.0f },{ 1.0f,1.0f,1.0f,1.0f } },
	{ { 5.0f,0.0f,0.0f },{ 1.0f,1.0f,1.0f,1.0f } },
	//���
	{ { 5.0f,0.0f,0.0f },{ 1.0f,1.0f,1.0f,1.0f } },
	{ { 5.0f,0.0f,0.0f },{ 1.0f,1.0f,1.0f,1.0f } },
	{ { 5.0f,0.0f,0.0f },{ 1.0f,1.0f,1.0f,1.0f } },
	{ { 5.0f,0.0f,0.0f },{ 1.0f,1.0f,1.0f,1.0f } },
	{ { 5.0f,0.0f,0.0f },{ 1.0f,1.0f,1.0f,1.0f } },
	{ { 5.0f,0.0f,0.0f },{ 1.0f,1.0f,1.0f,1.0f } },


	//�l�p�`
	{ { -0.5f, -0.3f, 0.5f },{ 0.0f, 1.0f, 0.0f, 1.0f } },
	{ { 0.3f, -0.3f, 0.5f },{ 0.0f, 0.0f, 1.0f, 1.0f } },
	{ { 0.3f,  0.5f, 0.5f },{ 1.0f, 0.0f, 0.0f, 1.0f } },
	{ { -0.5f,  0.5f, 0.5f },{ 0.0f, 0.0f, 1.0f, 1.0f } },

	{ {-0.3f,  0.3f, 0.1f},{ 0.0f, 0.0f, 1.0f, 1.0f } },
	{ {-0.3f, -0.5f, 0.1f},{ 0.0f, 1.0f, 1.0f, 1.0f } },
	{ { 0.5f, -0.5f, 0.1f},{ 0.0f, 0.0f, 1.0f, 1.0f } },
	{ { 0.5f, -0.5f, 0.1f},{ 1.0f, 0.0f, 0.0f, 1.0f } },
	{ { 0.5f,  0.3f, 0.1f},{ 1.0f, 1.0f, 0.0f, 1.0f } },
	{ {-0.3f,  0.3f, 0.1f},{ 1.0f, 0.0f, 0.0f, 1.0f } },




	{ { -0.5f, -0.43f, 0.5f },{ 0.0f, 0.0f, 1.0f, 1.0f } },
	{ { 0.5f, -0.43f, 0.5f },{ 0.0f, 1.0f, 0.0f, 1.0f } },
	{ { 0.0f,  0.43f, 0.5f },{ 1.0f, 0.0f, 0.0f, 1.0f } },
};

// �C���f�b�N�X�f�[�^
const GLushort indices[] = {
	//��
	0, 1, 2, 0, 2, 3, 0, 3, 1, 1, 2, 3,
	4, 5, 6, 4, 6, 7, 4, 7, 5,

	//��
	0, 1, 3, 3, 4, 0, 1, 2, 3,
	5, 6, 8, 8, 9, 5, 6, 7, 8,
	9, 8, 11, 11, 10, 9,
	4, 3, 6, 6, 5, 4,
	3, 12, 13, 13, 6, 3,
	8, 14, 15, 15, 11, 8,


	//��	



	0,1,2,2,3,0,
	4,5,6,7,8,9,
};

/*
*�`��f�[�^
*/
struct Mesh
{
	GLenum mode;			///< �v���~�e�B�u�̎��
	GLsizei count;			///< �`�悷��C���f�b�N�X��
	const GLvoid* indices;	///< �`��J�n�C���f�b�N�X�̃o�C�g�I�t�Z�b�g
	GLint baseVertex;		///< �C���f�b�N�X0�ԂƂ݂Ȃ���钸�_�z����̈ʒu
};

/*
*�`��f�[�^���X�g
*/
const Mesh meshList[] = {
	{GL_TRIANGLES, 21,(const GLvoid*)0,0 }, //��
	{GL_TRIANGLES,42,(const GLvoid*)(21 * sizeof(GLshort)),8},//��
};



/// ���_�V�F�[�_�[.
static const char* vsCode =
"#version 410 \n"
"layout(location=0) in vec3 vPosition; \n"
"layout(location=1) in vec4 vColor; \n"
"layout(location=2) in vec2 vTexCoord; \n"
"layout(location=0) out vec4 outColor;"
"layout(location=1) out vec2 outTexCoord; \n"
"uniform mat4x4 matMVP; \n"
"void main() { \n"
"  outColor = vColor; \n"
"  outTexCoord = vTexCoord; \n"
"  gl_Position = matMVP * vec4(vPosition, 1.0); \n"
"}";



/// �t���O�����g�V�F�[�_�[.
static const char* fsCode =
"#version 410 \n"
"layout(location=0) in vec4 inColor; \n"
"layout(location=1) in vec2 inTexCoord; \n"
"uniform sampler2D texColor; \n"
"out vec4 fragColor; \n"
"void main() { \n"
"  fragColor = inColor * texture(texColor, inTexCoord); \n"
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
* Index Buffer Object���쐬����
*
* @param size �C���f�b�N�X�f�[�^�̃T�C�Y
* @param data �C���f�b�N�X�f�[�^�ւ̃|�C���^
*
* GL_ELEMENT_ARRAY_BUFFER�̓C���f�b�N�X�f�[�^�𑀍삷�邽�߂̃}�N��
*
* @return �쐬����IBO
*/
GLuint CreateIBO(GLsizeiptr size, const GLvoid* data)
{
	GLuint ibo = 0;

	//�������̈���Ǘ�����I�u�W�F�N�g���쐬����
	glGenBuffers(1, &ibo);

	//�o�b�t�@�I�u�W�F�N�g�����̗p�r�Ɋ��蓖�Ă�
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);

	//�o�b�t�@�I�u�W�F���ƂɃf�[�^��]������֐�
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);

	//0�Ŋ��蓖�Ă�����
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	//ibo��Ԃ�
	return ibo;
}





/**
* Vertex Array Object���쐬����.
*
* @param vbo VAO�Ɋ֘A�t������VBO.
* @param ibo VAO�Ɋ֘A�t������IBO.
*
* @return �쐬����VAO.
*/
GLuint CreateVAO(GLuint vbo, GLuint ibo)
{
	GLuint vao = 0;

	//vao���쐬����
	glGenVertexArrays(1, &vao);

	//�w�肳�ꂽVAO��OpenGL�� ���݂̏����Ώ� �ɐݒ肷��֐�
	glBindVertexArray(vao);

	//���_�A�g���r���[�g��ݒ肷��ɂ͎��O�ɑΉ�����VBO�����蓖�Ă�K�v������
	//vbo��OpenGL�Ɋ��蓖�Ă�
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	//ibo��OpenGL�Ɋ��蓖�Ă�
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);

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
	
	//�w�肵���o�C���f�B���O�|�C���g�����蓖�Ă�
	glEnableVertexAttribArray(1);

	//���_�A�g���r���[�g���o�C���f�B���O�|�C���^�֊��蓖�Ă�
	glVertexAttribPointer(1, sizeof(Vertex::color) / sizeof(float),
		GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*)(offsetof(Vertex, color)));

	//�w�肵���o�C���f�B���O�|�C���g��L���ɂ���
	glEnableVertexAttribArray(2);

	//���_�A�g���r���[�g���o�C���f�B���O�|�C���^�֊��蓖�Ă�
	glVertexAttribPointer(2, sizeof(Vertex::texCoord) / sizeof(float),
		GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*)(offsetof(Vertex, texCoord)));



	//0�Ŋ��蓖�Ă�����
	glBindVertexArray(0);

	//VBO���폜����@VAO�Ɋ��蓖�Ă��Ă���ꍇ�폜�}�[�N��t���č폜�ҋ@����
	glDeleteBuffers(1, &vbo);

	//IBO���폜����@IBO�Ɋ��蓖�Ă��Ă���ꍇ�폜�}�[�N��t���č폜�ҋ@����
	glDeleteBuffers(1, &ibo);

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
	const GLuint ibo = CreateIBO(sizeof(indices), indices);
	const GLuint vao = CreateVAO(vbo, ibo);
	const GLuint shaderProgram = Shader::Build(vsCode, fsCode);

	//���s������1��Ԃ��ăv���O�������I��
	if (!vbo || !ibo || !vao || !shaderProgram) {
		return 1;
	}

	//uniform�ϐ��̈ʒu���擾����
	const GLint matMVPLoc = glGetUniformLocation(shaderProgram, "matMVP");
	//������Ȃ������ꍇ
	if (matMVPLoc < 0) {
		//�G���[���o��
		std::cerr << "ERROR: uniform�ϐ�'matMVP'��������܂���.\n";
		//1��Ԃ�
		return 1;
	}

	glUseProgram(shaderProgram);
	const GLint texColorLoc = glGetUniformLocation(shaderProgram, "texColor");
	if (texColorLoc >= 0) {
		//1��int�^�̒l��uniform�ϐ��ɐݒ肷��֐�
		glUniform1i(texColorLoc, 0);
	}
	glUseProgram(0);


	//�e�N�X�`�����쐬����
	const int tw = 8; //�摜�̕�
	const int th = 8; //�摜�̍���
	const uint32_t B = 0xff'00'00'00; //��
	const uint32_t W = 0xff'ff'ff'ff; //��
	const uint32_t imageData[tw * th] = {
		W, W, B, W, W, W, W, W,
		W, W, B, W, W, W, W, W,
		W, W, B, W, W, W, W, W,
		B, B, B, B, B, B, B, B,
		W, W, W, W, W, W, B, W,
		W, W, W, W, W, W, B, W,
		W, W, W, W, W, W, B, W,
		B, B, B, B, B, B, B, B,
	};
	//�e�N�X�`�����쐬 ���ꂼ��Ɉ�����ݒ肷�邾��
	GLuint texId = Texture::CreateImage2D(tw, th, imageData, GL_RGBA, GL_UNSIGNED_BYTE);
	GLuint texHouse = Texture::LoadImage2D("Res/House.tga");
	
	//�쐬�Ɏ��s�����ꍇ��1��Ԃ��ďI��
	if (!texId) {
		return 1;
	}








	//���C�����[�v
	while (!window.ShouldClose()) {

		//glEnable�͋@�\��L���ɂ���֐�
		//GL_DEPTH_TEST�́@�[�x�o�b�t�@�ɂ�鉜�s���̔�r������
		glEnable(GL_DEPTH_TEST);


		//==========================�ۑ�2================================
		//�J�����O���I���ɂ���
		glEnable(GL_CULL_FACE);

		//�o�b�N�o�b�t�@��ߋ�����Ƃ��̐F�@RGBA
		glClearColor(0.1f, 0.3f, 0.5f, 1.0f);

		//�o�b�N�o�b�t�@����������֐� �����͏�������o�b�t�@�̎��
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	


		//���_����]�ړ�������
		static float degree = 0.0f;
		//���t���[��+0.0�P��
		degree += 0.01f;
		//����360�����z������360�������Ƃœ����p�x�ɂ���
		if (degree >= 360.0f) { degree -= 360.0f; }
		//�J�����̃|�W�V���������߂�
		const glm::vec3 viewPos = glm::rotate(
			glm::mat4(1), glm::radians(degree), glm::vec3(0, 1, 0)) * glm::vec4(20, 20, 30, 1);


		

		//�`��Ɏg�p����v���O������ݒ�
		glUseProgram(shaderProgram);


		//���W�ϊ��s����쐬���ăV�F�[�_�[�ɓ]������
		//glm::perspective
		//�������e���s�����W�ϊ��s��
		//�߂��ɂ�����̂قǑ傫���A�����ɂ�����̂قǏ���������\��
		const glm::mat4x4 matProj =
			glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 500.0f);
		
		//glm::lookAt
		//���[���h���W����r���[���W�ւ̕ϊ��s��
		//�����̏���
		//���_���W �����_���W ���_�̏�����̃x�N�g��
		const glm::mat4x4 matView =
			glm::lookAt(viewPos, glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));



		//���[�J�����W���烏�[���h���W�ւ̍s��ϊ�
		//mat4x4(1)�ŒP�ʍs��
		//translate�͕��s�ړ��s����쐬����֐�
		//�ŏ��̈�����������̍s�� �������s�ړ������鋗��
		
		//3�̍s����������킹�čs�������
		/*
		*�s��ǂ����̐ς����߂闝�R
		*�s��̐�����
		*�u�s��̐ς����W�Ɋ|�������ʂ́A�ς̂��ƂɂȂ����Q�̍s������Ԃɍ��W�Ɋ|�����ꍇ�Ɠ������v
		*���� ���������s��Ȃ�s��ƍ��W�̐Ȃ̌v�Z�͈��ōςނ��߂ɖ��x�v�Z�����葁���y��
		*/
		
		//�V�F�[�_�[�ɕϊ��s���]��
		//����
		//�]�����uniform�ϐ��̈ʒu	�]������f�[�^�̐�
		//�s����ǂ��]�u���邩���w��	�]������f�[�^�ւ̃|�C���^
		//&vp[0][0]�ōs��̍ŏ��̗v�f�ւ̃|�C���^��n���Ă���
		//���ݐݒ肳��Ă���v���O�����I�u�W�F�N�g�ɑ΂��ē]�����邽�߁AglUseProgram�̌�ɏ����B

		//�w�肳�ꂽVAO��OpenGL�̌��݂̏����Ώ��ɐݒ肷��

		////�w�肳�ꂽ�I�u�W�F�N�g��f�[�^���g���Đ}�`��`��

		//glDrawElements�֐��̌Z��̂悤�Ȃ���
		//�ǉ��̈����Ƃ��ăC���f�b�N�X�̂O�ԂƂ݂Ȃ����_�f�[�^�̈ʒu��ݒ肷�邱�Ƃ��ł���
		//���_�f�[�^�����������Ƃ��ɂ�����ς��邾���ŗǂ�



		


		//�w�肳�ꂽVAO��OpenGL�̌��݂̏����Ώ��ɐݒ肷��
		glBindVertexArray(vao);

		//�w�肵���e�N�X�`��Image���j�b�g���e�N�X�`���֐��̏����ΏۂƂ��Đݒ�
		glActiveTexture(GL_TEXTURE0);

		//�w�肵���e�N�X�`�����I�����ꂽ�e�N�X�`���C���[�W���j�b�g�Ɋ��蓖�Ă���
		glBindTexture(GL_TEXTURE_2D, texId);

		const float treeCount = 10;//�؂̖{��
		const float radius = 8;		//�؂�A����~�̔��a

		//�؂̖{�������
		for (float i = 0; i < treeCount; ++i) {
			//x���W
			const float x = std::cos(3.14f * 2 / treeCount * i) * radius;
			//y���W
			const float z = std::sin(3.14f * 2 / treeCount * i) * radius;
			//���[�J�����W���烏�[���h���W�ւ̍s��ϊ�
			const glm::mat4x4 matModel = glm::translate(glm::mat4(1), glm::vec3(x, 0, z));
			//3�̍s����������킹�čs�������
			const glm::mat4x4 matMVP = matProj * matView * matModel;
			//�V�F�[�_�[�ɕϊ��s���]��
			glUniformMatrix4fv(matMVPLoc, 1, GL_FALSE, &matMVP[0][0]);
			//�C���f�b�N�X��0�ԂƂ݂Ȃ����_�f�[�^�̈ʒu��ݒ�
			glDrawElementsBaseVertex(meshList[0].mode, meshList[0].count,
				GL_UNSIGNED_SHORT, meshList[0].indices, meshList[0].baseVertex);
		}

		//�Ƃ����

		{
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, texHouse);

			//���[�J�����W���烏�[���h���W�ւ̍s��ϊ�
			const glm::mat4x4 matModel = glm::translate(glm::mat4(1), glm::vec3(0, 0, 0));
			//3�̍s����������킹�čs�������
			const glm::mat4x4 matMVP = matProj * matView * matModel;
			//�V�F�[�_�[�ɕϊ��s���]��
			glUniformMatrix4fv(matMVPLoc, 1, GL_FALSE, &matMVP[0][0]);
			//�C���f�b�N�X��0�ԂƂ݂Ȃ����_�f�[�^�̈ʒu��ݒ�
			glDrawElementsBaseVertex(meshList[1].mode, meshList[1].count,
				GL_UNSIGNED_SHORT, meshList[1].indices, meshList[1].baseVertex);
		}






		//glDrawElements ����
		/**
		* 1 �v���~�e�B�u�̎��	|| 2 �`�悷��C���f�b�N�X��
		* 3 �C���f�b�N�X�̌^	|| 4 �C���f�b�N�X�f�[�^�̕`��I�t�Z�b�g���A�C���f�b�N�X�f�[�^�̐擪�f�[�^����̃o�C�g���Ŏw��
		*/


		//sizeof(�z��)/sizeof(�z��[0])�̐���
		/*
		*	[�⑫] �usizeof(�z��)/sizeof(�z��[0])�v�Ƃ����̂�
		*	C/C++�Ŕz��̑傫�����擾���銵�p�I�ȃv���O�����ł��B
		*	�����ł͒��ڏ����Ă��܂����A��ʓI�ɂ�
		*	#define ARRAY_SIZE(a) (sizeof(a)/sizeof((a)[0]))
		*	�̂悤�ȃ}�N�����`���Ă�����g���܂�
		*/

		//���蓖�Ă������i�f�t�H���g�����蓖�Ă�j
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, 0);


		//�o�b�t�@�̐ؑ�
		window.SwapBuffers();
	}

	//���Ƃ�����ꂽ�I�u�W�F�N�g���ɍ폜
	glDeleteTextures(1, &texHouse);
	glDeleteTextures(1, &texId);
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