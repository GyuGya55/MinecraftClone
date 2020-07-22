#pragma once
#include "Directions.h"
#include "BlockData.h"
#include <glm/glm.hpp>
#include "SimplexNoise.h"
#include "ChunkMeshManager.h"
#include <glm/gtc/noise.hpp>

using Block_t = uint8_t;


class ChunkManager
{
public:
	ChunkManager(glm::vec3 position);
	~ChunkManager();

	void Render();


	void GenerateBlocks();
	void CreateChunkMesh();
	void ConnectChunkWithChunk(ChunkManager* otherChunkNorth, ChunkManager* otherChunkEast, ChunkManager* otherChunkSouth, ChunkManager* otherChunkWest);

protected:
	ChunkMeshManager chunkMesh;

	std::array<coords, (int)BlocksID::NUM_TYPES> m_blocks{
		m_blocks[(int)BlocksID::DIRT] = { 2, 0, 2, 0, 2, 0 },
		m_blocks[(int)BlocksID::GRASS] = { 0, 0, 3, 0, 2, 0 },
		m_blocks[(int)BlocksID::STONE] = { 1, 0, 1, 0, 1, 0 },
		m_blocks[(int)BlocksID::COBBLESTONE] = { 0, 1, 0, 1, 0, 1 },
		m_blocks[(int)BlocksID::BEDROCK] = { 1, 1, 1, 1, 1, 1 },
		m_blocks[(int)BlocksID::OAK_WOOD] = { 5, 1, 4, 1, 5, 1 },
		m_blocks[(int)BlocksID::OAK_LEAVES] = { 4, 3, 4, 3, 4, 3 },
		m_blocks[(int)BlocksID::SAND] = { 2, 1, 2, 1, 2, 1 },
		m_blocks[(int)BlocksID::SAND_STONE] = { 0, 11, 0, 12, 0, 13 }
	};

	Block_t getCoordHeight(Block_t x, Block_t z)
	{
		return glm::simplex(glm::vec2((pos.x + x) / 1024, (pos.z + z) / 1024.f)) * 32 +
			glm::simplex(glm::vec2((pos.x + x) / 256.f, (pos.z + z) / 256.f)) * 8 +
			glm::simplex(glm::vec2((pos.x + x) / 64.f, (pos.z + z) / 64.f)) * 4 +
			glm::simplex(glm::vec2((pos.x + x) / 16.f, (pos.z + z) / 16.f)) * 1 + 60;
	}

	glm::vec3 pos;
	BlocksID blocks[65536] = { };

	inline int getBlocksPos(Block_t x, Block_t y, Block_t z) { return (16 * x + 256 * y + z); }

	Block_t texStep = 16;
	void InFaceFacingUp(Block_t x, Block_t y, Block_t z);
	void InFaceFacingDown(Block_t x, Block_t y, Block_t z);
	void InFaceFacingRight(Block_t x, Block_t y, Block_t z);
	void InFaceFacingLeft(Block_t x, Block_t y, Block_t z);
	void InFaceFacingForwards(Block_t x, Block_t y, Block_t z);
	void InFaceFacingBackwards(Block_t x, Block_t y, Block_t z);

};