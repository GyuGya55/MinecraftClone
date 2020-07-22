#include "ChunkManager.h"
#include <iostream>


ChunkManager::ChunkManager(glm::vec3 _pos) : pos(_pos) 
{
	GenerateBlocks();
}

ChunkManager::~ChunkManager()
{

}

void ChunkManager::Render()
{
	chunkMesh.Draw();
}

void ChunkManager::GenerateBlocks()
{
	for (Block_t x = 0; x < 16; ++x)
	{
		for (Block_t z = 0; z < 16; z++)
		{
			float CoordHeight = getCoordHeight(x, z);

			Block_t y = 0;
			
			blocks[getBlocksPos(x, y, z)] = BlocksID::BEDROCK;
			++y;
			rand() % 20 > 7 ? blocks[getBlocksPos(x, y, z)] = BlocksID::BEDROCK : blocks[getBlocksPos(x, y, z)] = BlocksID::STONE;
			++y;
			rand() % 20 > 15 ? blocks[getBlocksPos(x, y, z)] = BlocksID::BEDROCK : blocks[getBlocksPos(x, y, z)] = BlocksID::STONE;
			++y;
			
			if (CoordHeight < 64)
			{
				for (; y < int(CoordHeight) - 4; ++y)
				{
					blocks[getBlocksPos(x, y, z)] = BlocksID::STONE;
				}
				for (; y < int(CoordHeight) - 2; ++y)
				{
					blocks[getBlocksPos(x, y, z)] = BlocksID::SAND_STONE;
				}
				for (; y < int(CoordHeight); ++y)
				{
					blocks[getBlocksPos(x, y, z)] = BlocksID::SAND;
				}
			}
			else
			{
				for (; y < int(CoordHeight) - 4; ++y)
				{
					blocks[getBlocksPos(x, y, z)] = BlocksID::STONE;
				}
				for (; y < int(CoordHeight) - 1; ++y)
				{
					blocks[getBlocksPos(x, y, z)] = BlocksID::DIRT;
				}
				blocks[getBlocksPos(x, y++, z)] = BlocksID::GRASS;
			}

			for (; y < 255; ++y)
			{
				blocks[getBlocksPos(x, y, z)] = BlocksID::AIR;
			}
		}
	}

	for (Block_t x = 2; x < 14; ++x)
	{
		for (Block_t z = 2; z < 14; z++)
		{
			float CoordHeight = getCoordHeight(x, z);
			int randNum = CoordHeight + rand() % 100 - 95;
			std::cout << CoordHeight << " -> " << randNum << std::endl;
			if ( CoordHeight < randNum && CoordHeight > 64)
			{
				for (Block_t y1 = CoordHeight + 4; y1 < CoordHeight + 6; ++y1)
				{
					for (Block_t x1 = x - 2; x1 < x + 3; ++x1)
					{
						for (Block_t z1 = z - 2; z1 < z + 3; ++z1)
						{
							if (blocks[getBlocksPos(x1, y1, z1)] == AIR)
							{
								blocks[getBlocksPos(x1, y1, z1)] = OAK_LEAVES;
							}
						}
					}
				}
				for (Block_t x1 = x - 1; x1 < x + 2; ++x1)
				{
					for (Block_t z1 = z - 1; z1 < z + 2; ++z1)
					{
						if (blocks[getBlocksPos(x1, CoordHeight + 6, z1)] == AIR)
						{
							blocks[getBlocksPos(x1, CoordHeight + 6, z1)] = OAK_LEAVES;
						}
					}
				}
				if (blocks[getBlocksPos(x-1, CoordHeight + 7, z)] == AIR)
				{
					blocks[getBlocksPos(x - 1, CoordHeight + 7, z)] = OAK_LEAVES;
				}
				if (blocks[getBlocksPos(x, CoordHeight + 7, z)] == AIR)
				{
					blocks[getBlocksPos(x, CoordHeight + 7, z)] = OAK_LEAVES;
				}
				if (blocks[getBlocksPos(x + 1, CoordHeight + 7, z)] == AIR)
				{
					blocks[getBlocksPos(x +1 , CoordHeight + 7, z)] = OAK_LEAVES;
				}
				if (blocks[getBlocksPos(x, CoordHeight + 7, z + 1)] == AIR)
				{
					blocks[getBlocksPos(x, CoordHeight + 7, z + 1)] = OAK_LEAVES;
				}
				if (blocks[getBlocksPos(x, CoordHeight + 7, z - 1)] == AIR)
				{
					blocks[getBlocksPos(x, CoordHeight + 7, z - 1)] = OAK_LEAVES;
				}

				for (Block_t y1 = CoordHeight; y1 < CoordHeight + 6; ++y1)
				{
					if (blocks[getBlocksPos(x, y1, z)] == AIR)
					{
						blocks[getBlocksPos(x, y1, z)] = OAK_WOOD;
					}
				}
			}
		}
	}

	CreateChunkMesh();
}

void ChunkManager::CreateChunkMesh()
{
	for (Block_t x = 0; x < 16; ++x) 
	{
		for (Block_t z = 0; z < 16; ++z) 
		{
			for (Block_t y = 0; y < 255; ++y) 
			{
				if (blocks[getBlocksPos(x,y,z)] != BlocksID::AIR) 
				{
					if (y < 255 && blocks[getBlocksPos(x, y + 1, z)] == BlocksID::AIR || y == 255)
					{
						InFaceFacingUp(x, y, z);
					}
					if (y > 0 && blocks[getBlocksPos(x, y - 1, z)] == BlocksID::AIR || y == 0)
					{
						InFaceFacingDown(x, y, z);
					}
					if (x < 15 && blocks[getBlocksPos(x + 1, y, z)] == BlocksID::AIR)
					{
						InFaceFacingRight(x, y, z);
					}
					if (x > 0 && blocks[getBlocksPos(x - 1, y, z)] == BlocksID::AIR)
					{
						InFaceFacingLeft(x, y, z);
					}
					if (z < 15 && blocks[getBlocksPos(x, y, z + 1)] == BlocksID::AIR)
					{
						InFaceFacingForwards(x, y, z);
					}
					if (z > 0 && blocks[getBlocksPos(x, y, z - 1)] == BlocksID::AIR)
					{
						InFaceFacingBackwards(x, y, z);
					}
				}
			}
		}
	}
}



void ChunkManager::InFaceFacingUp(Block_t x, Block_t y, Block_t z)
{
	chunkMesh.AddFaceToMesh
	(
		{
			{
				{ 
					pos + glm::vec3(x, y + 1, z),     
					{
						(Block_t)(ChunkManager::m_blocks[blocks[getBlocksPos(x, y, z)]].xTop * texStep),
						(Block_t)(ChunkManager::m_blocks[blocks[getBlocksPos(x, y, z)]].yTop * texStep)
					
					},
					1
				},
				{
					pos + glm::vec3(x, y + 1, z + 1),
					{
						(Block_t)(ChunkManager::m_blocks[blocks[getBlocksPos(x, y, z)]].xTop * texStep),
						(Block_t)(ChunkManager::m_blocks[blocks[getBlocksPos(x, y, z)]].yTop * texStep + 16)
					},
					1
				},
				{	
					pos + glm::vec3(x + 1, y + 1, z + 1),					   
					{	
						(Block_t)(ChunkManager::m_blocks[blocks[getBlocksPos(x, y, z)]].xTop * texStep + 16),
						(Block_t)(ChunkManager::m_blocks[blocks[getBlocksPos(x, y, z)]].yTop * texStep + 16)
					},
					1
				},															   
				{ 															   
					pos + glm::vec3(x + 1, y + 1, z),				
					{
						(Block_t)(ChunkManager::m_blocks[blocks[getBlocksPos(x, y, z)]].xTop * texStep + 16),
						(Block_t)(ChunkManager::m_blocks[blocks[getBlocksPos(x, y, z)]].yTop * texStep)
					},
					1
				}													   
			},
			{ 
				0, 1, 2, 2, 3, 0 
			},
			{ 
				(BlocksID)blocks[getBlocksPos(x, y, z)], 
				Facing::UP
			}
		}
	);
}


void ChunkManager::InFaceFacingDown(Block_t x, Block_t y, Block_t z)
{
	chunkMesh.AddFaceToMesh
	(
		{
			{
				{ 
					pos + glm::vec3(x, y, z),
					{
						(Block_t)(ChunkManager::m_blocks[blocks[getBlocksPos(x, y, z)]].xBot * texStep),
						(Block_t)(ChunkManager::m_blocks[blocks[getBlocksPos(x, y, z)]].yBot * texStep)
					},
					1
				},
				{ 
					pos + glm::vec3(x + 1, y, z),
					{
						(Block_t)(ChunkManager::m_blocks[blocks[getBlocksPos(x, y, z)]].xBot * texStep),
						(Block_t)(ChunkManager::m_blocks[blocks[getBlocksPos(x, y, z)]].yBot * texStep + 16)
					},
					1
				},
				{ 
					pos + glm::vec3(x + 1, y, z + 1),
					{
						(Block_t)(ChunkManager::m_blocks[blocks[getBlocksPos(x, y, z)]].xBot * texStep + 16),
						(Block_t)(ChunkManager::m_blocks[blocks[getBlocksPos(x, y, z)]].yBot * texStep + 16)
					},
					1
				},
				{ 
					pos + glm::vec3(x, y, z + 1),
					{
						(Block_t)(ChunkManager::m_blocks[blocks[getBlocksPos(x, y, z)]].xBot * texStep + 16),
						(Block_t)(ChunkManager::m_blocks[blocks[getBlocksPos(x, y, z)]].yBot * texStep)
					},
					1
				}
			},
			{ 
				0, 1, 2, 2, 3, 0 
			},
			{
				(BlocksID)blocks[getBlocksPos(x, y, z)],
				Facing::DOWN
			}
		}
	);
}


void ChunkManager::InFaceFacingRight(Block_t x, Block_t y, Block_t z)
{
	chunkMesh.AddFaceToMesh
	(
		{
			{
				{
					pos + glm::vec3(x + 1, y, z),
					{
						(Block_t)(ChunkManager::m_blocks[blocks[getBlocksPos(x, y, z)]].xSide * texStep + 16),
						(Block_t)(ChunkManager::m_blocks[blocks[getBlocksPos(x, y, z)]].ySide * texStep + 16)
					},
					1
				},
				{
					pos + glm::vec3(x + 1, y + 1, z),
					{
						(Block_t)(ChunkManager::m_blocks[blocks[getBlocksPos(x, y, z)]].xSide * texStep + 16),
						(Block_t)(ChunkManager::m_blocks[blocks[getBlocksPos(x, y, z)]].ySide * texStep)
					},
					1
				},
				{
					pos + glm::vec3(x + 1, y + 1, z + 1),
					{
						(Block_t)(ChunkManager::m_blocks[blocks[getBlocksPos(x, y, z)]].xSide * texStep),
						(Block_t)(ChunkManager::m_blocks[blocks[getBlocksPos(x, y, z)]].ySide * texStep)
					},
					1
				},
				{
					pos + glm::vec3(x + 1, y, z + 1),
					{
						(Block_t)(ChunkManager::m_blocks[blocks[getBlocksPos(x, y, z)]].xSide * texStep),
						(Block_t)(ChunkManager::m_blocks[blocks[getBlocksPos(x, y, z)]].ySide * texStep + 16)
					},
					1
				}
			},
			{
				0, 1, 2, 2, 3, 0
			},
			{
				(BlocksID)blocks[getBlocksPos(x, y, z)],
				Facing::RIGHT
			}
		}
	);
}


void ChunkManager::InFaceFacingLeft(Block_t x, Block_t y, Block_t z)
{
	chunkMesh.AddFaceToMesh
	(
		{
			{
				{ 
					pos + glm::vec3(x, y, z),
					{
						(Block_t)(ChunkManager::m_blocks[blocks[getBlocksPos(x, y, z)]].xSide * texStep + 16),
						(Block_t)(ChunkManager::m_blocks[blocks[getBlocksPos(x, y, z)]].ySide * texStep + 16)
					},
					1
				},
				{ 
					pos + glm::vec3(x, y, z + 1),
					{
						(Block_t)(ChunkManager::m_blocks[blocks[getBlocksPos(x, y, z)]].xSide * texStep),
						(Block_t)(ChunkManager::m_blocks[blocks[getBlocksPos(x, y, z)]].ySide * texStep + 16)
					},
					1
				},
				{ 
					pos + glm::vec3(x, y + 1, z + 1),		
					{
						(Block_t)(ChunkManager::m_blocks[blocks[getBlocksPos(x, y, z)]].xSide * texStep),
						(Block_t)(ChunkManager::m_blocks[blocks[getBlocksPos(x, y, z)]].ySide * texStep)
					},
					1
				},
				{ 
					pos + glm::vec3(x, y + 1, z),			
					{
						(Block_t)(ChunkManager::m_blocks[blocks[getBlocksPos(x, y, z)]].xSide * texStep + 16),
						(Block_t)(ChunkManager::m_blocks[blocks[getBlocksPos(x, y, z)]].ySide * texStep)
					},
					1
				}
			},
			{ 
				0, 1, 2, 2, 3, 0 
			},
			{
				(BlocksID)blocks[getBlocksPos(x, y, z)],
				Facing::LEFT
			}
		}
	);
}


void ChunkManager::InFaceFacingForwards(Block_t x, Block_t y, Block_t z)
{
	chunkMesh.AddFaceToMesh
	(
		{
			{
				{
					pos + glm::vec3(x, y, z + 1),
					{
						(Block_t)(ChunkManager::m_blocks[blocks[getBlocksPos(x, y, z)]].xSide * texStep + 16),
						(Block_t)(ChunkManager::m_blocks[blocks[getBlocksPos(x, y, z)]].ySide * texStep + 16)
					},
					1
				},
				{
					pos + glm::vec3(x + 1, y, z + 1),
					{
						(Block_t)(ChunkManager::m_blocks[blocks[getBlocksPos(x, y, z)]].xSide * texStep),
						(Block_t)(ChunkManager::m_blocks[blocks[getBlocksPos(x, y, z)]].ySide * texStep + 16)
					},
					1
				},
				{
					pos + glm::vec3(x + 1, y + 1, z + 1),
					{
						(Block_t)(ChunkManager::m_blocks[blocks[getBlocksPos(x, y, z)]].xSide * texStep),
						(Block_t)(ChunkManager::m_blocks[blocks[getBlocksPos(x, y, z)]].ySide * texStep)
					},
					1
				},
				{
					pos + glm::vec3(x, y + 1, z + 1),
					{
						(Block_t)(ChunkManager::m_blocks[blocks[getBlocksPos(x, y, z)]].xSide * texStep + 16),
						(Block_t)(ChunkManager::m_blocks[blocks[getBlocksPos(x, y, z)]].ySide * texStep)
					},
					1
				}
			},
			{
				0, 1, 2, 2, 3, 0
			},
			{
				(BlocksID)blocks[getBlocksPos(x, y, z)],
				Facing::FORWARD
			}
		}
	);
}


void ChunkManager::InFaceFacingBackwards(Block_t x, Block_t y, Block_t z)
{
	chunkMesh.AddFaceToMesh
	(
		{
			{
				{
					pos + glm::vec3(x, y, z),
					{
						(Block_t)(ChunkManager::m_blocks[blocks[getBlocksPos(x, y, z)]].xSide * texStep + 16),
						(Block_t)(ChunkManager::m_blocks[blocks[getBlocksPos(x, y, z)]].ySide * texStep + 16)
					},
					1
				},
				{
					pos + glm::vec3(x, y + 1, z),
					{
						(Block_t)(ChunkManager::m_blocks[blocks[getBlocksPos(x, y, z)]].xSide * texStep + 16),
						(Block_t)(ChunkManager::m_blocks[blocks[getBlocksPos(x, y, z)]].ySide * texStep)
					},
					1
				},
				{
					pos + glm::vec3(x + 1, y + 1, z),
					{
						(Block_t)(ChunkManager::m_blocks[blocks[getBlocksPos(x, y, z)]].xSide * texStep),
						(Block_t)(ChunkManager::m_blocks[blocks[getBlocksPos(x, y, z)]].ySide * texStep)
					},
					1
				},
				{
					pos + glm::vec3(x + 1, y, z),
					{
						(Block_t)(ChunkManager::m_blocks[blocks[getBlocksPos(x, y, z)]].xSide * texStep),
						(Block_t)(ChunkManager::m_blocks[blocks[getBlocksPos(x, y, z)]].ySide * texStep + 16)
					},
					1
				}
			},
			{
				0, 1, 2, 2, 3, 0
			},
			{
				
				(BlocksID)blocks[getBlocksPos(x, y, z)],
				Facing::BACKWARD
			}
		}
	);
}



void ChunkManager::ConnectChunkWithChunk(ChunkManager* otherChunkNorth, ChunkManager* otherChunkEast,
	ChunkManager* otherChunkSouth, ChunkManager* otherChunkWest)
{
	if (otherChunkNorth != nullptr)
	{
		for (int x = 0; x < 16; ++x)
			for (int y = 0; y < 255; ++y)
				if (blocks[getBlocksPos(x, y, 0)] != BlocksID::AIR && otherChunkNorth->blocks[getBlocksPos(x, y, 15)] == BlocksID::AIR)
				{
					InFaceFacingBackwards(x, y, 0);
				}
	}
	else
	{
		for (int x = 0; x < 16; ++x)
			for (int y = 0; y < 255; ++y)
				if (blocks[getBlocksPos(x, y, 0)] != AIR)
				{
					InFaceFacingBackwards(x, y, 0);
				}
	}

	if (otherChunkEast != nullptr)
	{
		for (int z = 0; z < 16; ++z)
			for (int y = 0; y < 255; ++y)
				if (blocks[getBlocksPos(15, y, z)] != BlocksID::AIR && otherChunkEast->blocks[getBlocksPos(0, y, z)] == BlocksID::AIR)
				{
					InFaceFacingRight(15, y, z);
				}
	}
	else
	{
		for (int z = 0; z < 16; ++z)
			for (int y = 0; y < 255; ++y) 
				if (blocks[getBlocksPos(15, y, z)] != AIR)
				{
					InFaceFacingRight(15, y, z);
				}
	}


	if (otherChunkSouth != nullptr)
	{
		for (int x = 0; x < 16; ++x)
			for (int y = 0; y < 255; ++y)
				if (blocks[getBlocksPos(x, y, 15)] != BlocksID::AIR && otherChunkSouth->blocks[getBlocksPos(x, y, 0)] == BlocksID::AIR)
				{
					InFaceFacingForwards(x, y, 15);
				}
	}
	else
	{
		for (int x = 0; x < 16; ++x) {
			for (int y = 0; y < 255; ++y) {
				if (blocks[getBlocksPos(x, y, 15)] != AIR)
				{
					InFaceFacingForwards(x, y, 15);
				}
			}
		}
	}

	if (otherChunkWest != nullptr)
	{
		for (int z = 0; z < 16; ++z)
			for (int y = 0; y < 255; ++y)
				if (blocks[getBlocksPos(0, y, z)] != BlocksID::AIR && otherChunkWest->blocks[getBlocksPos(15, y, z)] == BlocksID::AIR)
				{
					InFaceFacingLeft(0, y, z);
				}
	}
	else
	{
		for (int z = 0; z < 16; ++z)
			for (int y = 0; y < 255; ++y)
				if (blocks[getBlocksPos(0, y, z)] != AIR)
				{
					InFaceFacingLeft(0, y, z);
				}
	}
}