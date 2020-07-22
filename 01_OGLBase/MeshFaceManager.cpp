#include "MeshFaceManager.h"


void MeshFaceManager::AddSurfaceTop(Block_t x, Block_t y, Block_t z)
{
	Block_t texStep = 256 / 16;
	AddFaceToMesh({
		{
			{
				pos + glm::vec3(x, y + 1, z),
				ChunkManager::m_blocks[blocks[getBlocksPos(x, y, z)]].xTop * texStep,
				ChunkManager::m_blocks[blocks[getBlocksPos(x, y, z)]].yTop * texStep
			},
			{
				pos + glm::vec3(x, y + 1, z + 1),
				ChunkManager::m_blocks[blocks[getBlocksPos(x, y, z)]].xTop * texStep,
				ChunkManager::m_blocks[blocks[getBlocksPos(x, y, z)]].yTop * texStep + 15
			},
			{
				pos + glm::vec3(x + 1, y + 1, z + 1),
				ChunkManager::m_blocks[blocks[getBlocksPos(x, y, z)]].xTop * texStep + 15,
				ChunkManager::m_blocks[blocks[getBlocksPos(x, y, z)]].yTop * texStep + 15
			},
			{
				pos + glm::vec3(x + 1, y + 1, z),
				ChunkManager::m_blocks[blocks[getBlocksPos(x, y, z)]].xTop * texStep + 15,
				ChunkManager::m_blocks[blocks[getBlocksPos(x, y, z)]].yTop * texStep
			},
		},
		{
			0, 1, 2, 2, 3, 0
		},
		{
			(BlocksID)blocks[getBlocksPos(x, y, z)], (Block_t)Facing::UP }
		}
	);
}