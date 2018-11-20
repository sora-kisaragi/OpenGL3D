/**
* @file Geometry.h
*/
#ifndef GEOMETRY_H_INCLUDED
#define GEOMETRY_H_INCLUDED
#include <GL\glew.h>

/// 2D�x�N�g���^.
struct Vector2
{
	float x, y;
};

/// 3D�x�N�g���^.
struct Vector3
{
	float x, y, z;
};

/// RGBA�J���[�^.
struct Color
{
	float r, g, b, a;
};

/// ���_�f�[�^�^.
struct Vertex
{
	Vector3 position; ///< ���W
	Color color; ///< �F
	Vector2 texCoord; ///< �e�N�X�`�����W.
	Vector3 normal; ///< �@��.
};

/**
* �|���S���\���P��.
*/
struct Mesh
{
	GLenum mode; ///< �v���~�e�B�u�̎��.
	GLsizei count; ///< �`�悷��C���f�b�N�X��.
	const GLvoid* indices; ///< �`��J�n�C���f�b�N�X�̃o�C�g�I�t�Z�b�g.
	GLint baseVertex; ///< �C���f�b�N�X0�Ƃ݂Ȃ���钸�_�z����̈ʒu.
};

#endif // GEOMETRY_H_INCLUDED