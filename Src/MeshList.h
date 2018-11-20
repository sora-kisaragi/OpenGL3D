#pragma once
/**
* @file MeshList.h
*/
#ifndef MESHLIST_H_INCLUDED
#define MESHLIST_H_INCLUDED
#include <GL/glew.h>
#include "Geometry.h"
#include <vector>

/**
* メッシュ管理クラス.
*/
class MeshList
{
public:
	MeshList();
	~MeshList();
	MeshList(const MeshList&) = default;
	MeshList& operator=(const MeshList&) = default;

	bool Allocate();
	void Free();
	void Add(const Vertex* vBegin, const Vertex* vEnd, const GLushort* iBegin, const GLushort* iEnd);
	bool AddFromObjFile(const char* filename);

	void BindVertexArray();
	const Mesh& operator[](size_t index) const;

private:
	GLuint vao = 0;
	std::vector<Mesh> meshes;

	std::vector<Vertex> tmpVertices;
	std::vector<GLushort> tmpIndices;
};

#endif // MESHLIST_H_INCLUDED