#include "ChunkMeshManager.h"


ChunkMeshManager::ChunkMeshManager() {}


ChunkMeshManager::~ChunkMeshManager()
{
	Clean();
}


void ChunkMeshManager::Init()
{
	if (vertices.size() != 0) {
		glGenVertexArrays(1, &vao);
		glGenBuffers(1, &vbo);
		glGenBuffers(1, &ebo);

		//glBindVertexArray(vao);
		GL::bindVao(vao);

		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vertices.size(), (void*)&vertices[0], GL_STREAM_DRAW);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 2, GL_BYTE, GL_FALSE, sizeof(Vertex), (void*)(sizeof(glm::vec3)));
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 1, GL_BYTE, GL_FALSE, sizeof(Vertex), (void*)(sizeof(glm::vec3) + 2));

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int) * indices.size(), (void*)&indices[0], GL_STREAM_DRAW);

		glBindVertexArray(0);
	}
}


void ChunkMeshManager::Update()
{
	Clean();
	Init();
}


void ChunkMeshManager::Clean()
{
	glDeleteVertexArrays(1, &vao);

	glDeleteBuffers(1, &vbo);
	glDeleteBuffers(1, &ebo);
}


void ChunkMeshManager::Draw()
{
	if (needsToInit) {
		Update();
		needsToInit = false;
	}

	if (vertices.size() != 0) {
		//glBindVertexArray(vao);
		GL::bindVao(vao);
		GL::drawElements(indices.size());
		//glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);

		glBindVertexArray(0);
	}
}


void ChunkMeshManager::Clear()
{
	vertices.clear();
	indices.clear();
	infos.clear();
}

void ChunkMeshManager::AddFaceToMesh(const Face& face)
{
	for (int i = 0; i < 4; ++i) {
		vertices.push_back(face.vertices[i]);
	}

	int start = vertices.size() - 4;
	for (int i = 0; i < 6; ++i) {
		indices.push_back(start + face.indices[i]);
	}
	infos.push_back(face.info);
	needsToInit = true;
}
