#pragma once

#include <memory>
#include <GL/glew.h>
#include <SDL.h>
#include <SDL_opengl.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform2.hpp>
#include "includes/gCamera.h"
#include "includes/ProgramObject.h"
#include "includes/BufferObject.h"
#include "includes/VertexArrayObject.h"
#include "includes/TextureObject.h"
#include "includes/ObjParser_OGL3.h"
#include "GLFunctions.h"


#include "SimplexNoise.h"
#include "ChunkManager.h"


class CApplication
{
public:
	CApplication(void);
	~CApplication(void);

	bool Init();
	void Clean();

	void Update();
	void Render();
	void CoutTest(float deltaTime);

	void KeyboardDown(SDL_KeyboardEvent&);
	void KeyboardUp(SDL_KeyboardEvent&);
	void MouseMove(SDL_MouseMotionEvent&);
	void MouseDown(SDL_MouseButtonEvent&);
	void MouseUp(SDL_MouseButtonEvent&);
	void MouseWheel(SDL_MouseWheelEvent&);
	void Resize(int, int);

protected:
	float lastWriteTime = 0;
	int ticks = 0;


	//skybox
	ProgramObject		m_programSkybox;
	VertexArrayObject	m_SkyboxVao;
	IndexBuffer			m_SkyboxIndices;	
	ArrayBuffer			m_SkyboxPos;
	GLuint				m_skyboxTexture;
	void InitSkyBox();

	//chunks
	ProgramObject		m_programChunk;
	VertexArrayObject	m_ChunkVao;
	IndexBuffer			m_ChunkIndices;
	ArrayBuffer			m_ChunkPos;
	void InitChunks();
	
	//Text
	Texture2D			m_textAtlas;

	gCamera				m_camera;
	bool				visible = true;

	Block_t RenderDistance = 20;
	std::vector<std::vector<ChunkManager*>> activeChunks;
};

