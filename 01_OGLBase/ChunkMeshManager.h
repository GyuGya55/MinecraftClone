#pragma once

#include <GL\glew.h>
#include "Vertex.h"
#include <vector>
#include "GLFunctions.h"
#include "BlockData.h"


class ChunkMeshManager
{
public:
	struct FaceData {
		BlocksID block;
		Block_t facing;

		bool operator==(const FaceData& other) {
			return block == other.block && facing == other.facing;
		}
	};

	struct Face {
		Vertex vertices[4];
		int indices[6];
		FaceData info;
	};

	ChunkMeshManager();
	~ChunkMeshManager();

	// For rendering
	void Init();
	void Update();
	void Clean();
	void Draw();
	void Clear();

	void AddFaceToMesh(const Face& face);
	/*// For updating
	void AddSurface(const Surface& surf);
	int FindSurface(const SurfaceInfo& info);
	void DeleteSurface(int);*/

protected:
	std::vector<Vertex> vertices;
	std::vector<int> indices;
	std::vector<FaceData> infos;

	GLuint vao;
	GLuint vbo;
	GLuint ebo;

	bool needsToInit = true;
};

