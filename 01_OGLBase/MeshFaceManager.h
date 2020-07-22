#pragma once
#include "ChunkMeshManager.h"

class MeshFaceManager : public ChunkMeshManager
{
protected:

	void AddSurfaceTop(Block_t x, Block_t y, Block_t z);
	void AddSurfaceBottom(Block_t x, Block_t y, Block_t z);
	void AddSurfaceLeft(Block_t x, Block_t y, Block_t z);
	void AddSurfaceRight(Block_t x, Block_t y, Block_t z);
	void AddSurfaceFront(Block_t x, Block_t y, Block_t z);
	void AddSurfaceBack(Block_t x, Block_t y, Block_t z);
};

