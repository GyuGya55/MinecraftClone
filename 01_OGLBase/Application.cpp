#include "Application.h"

#include <math.h>
#include <vector>

#include <array>
#include <list>
#include <tuple>
#include <imgui/imgui.h>
#include "includes/GLUtils.hpp"

CApplication::CApplication(void)
{
	m_camera.SetView(glm::vec3(0, 69, 0), glm::vec3(5, 0, 5), glm::vec3(0, 1, 0));
}

CApplication::~CApplication(void)
{
	std::cout << "dtor!\n";
}

void CApplication::InitSkyBox()
{
	m_programSkybox.Init(
		{
			{ GL_VERTEX_SHADER, "skybox.vert" },
			{ GL_FRAGMENT_SHADER, "skybox.frag" }
		},
		{
			{ 0, "vs_in_pos" },				// VAO 0-as csatorna menjen a vs_in_pos-ba
		}
	);

	m_SkyboxPos.BufferData(
		std::vector<glm::vec3>{
		// hátsó lap
		glm::vec3(-1, -1, -1),
		glm::vec3(1, -1, -1),
		glm::vec3(1, 1, -1),
		glm::vec3(-1, 1, -1),
		// elülsõ lap
		glm::vec3(-1, -1, 1),
		glm::vec3(1, -1, 1),
		glm::vec3(1, 1, 1),
		glm::vec3(-1, 1, 1),
	}
	);

	// és a primitíveket alkotó csúcspontok indexei (az elõzõ tömbökbõl) - triangle list-el való kirajzolásra felkészülve
	m_SkyboxIndices.BufferData(
		std::vector<int>{
			// hátsó lap
			0, 1, 2,
			2, 3, 0,
			// elülsõ lap
			4, 6, 5,
			6, 4, 7,
			// bal
			0, 3, 4,
			4, 3, 7,
			// jobb
			1, 5, 2,
			5, 6, 2,
			// alsó
			1, 0, 4,
			1, 4, 5,
			// felsõ
			3, 2, 6,
			3, 6, 7,
	}
	);

	// geometria VAO-ban való regisztrálása
	m_SkyboxVao.Init(
		{
			{ CreateAttribute<0, glm::vec3, 0, sizeof(glm::vec3)>, m_SkyboxPos },
		}, m_SkyboxIndices
	);

	// skybox texture
	glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);

	glGenTextures(1, &m_skyboxTexture);
	glBindTexture(GL_TEXTURE_CUBE_MAP, m_skyboxTexture);

	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

	TextureFromFileAttach("assets/xpos.png", GL_TEXTURE_CUBE_MAP_POSITIVE_X);
	TextureFromFileAttach("assets/xneg.png", GL_TEXTURE_CUBE_MAP_NEGATIVE_X);
	TextureFromFileAttach("assets/ypos.png", GL_TEXTURE_CUBE_MAP_POSITIVE_Y);
	TextureFromFileAttach("assets/yneg.png", GL_TEXTURE_CUBE_MAP_NEGATIVE_Y);
	TextureFromFileAttach("assets/zpos.png", GL_TEXTURE_CUBE_MAP_POSITIVE_Z);
	TextureFromFileAttach("assets/zneg.png", GL_TEXTURE_CUBE_MAP_NEGATIVE_Z);

	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);

}

void CApplication::CoutTest(float deltaTime)
{

	lastWriteTime += deltaTime;
	++ticks;
	if (lastWriteTime >= 1.0f) {
		std::cout << ticks << " FPS\n";
		lastWriteTime = 0;
		ticks = 0;
	}


}


bool CApplication::Init()
{

	m_programChunk.AttachShaders
	(
		{
			{GL_VERTEX_SHADER, "BasicVertex.vert"},
			{GL_FRAGMENT_SHADER, "BasicFragment.frag"}
		}
	);

	m_programChunk.BindAttribLocations
	(
		{
			{ 0, "inVertexPosition" },
			{ 1, "inTextureCoordXY" },
			{ 2, "inNorm" }
		}
	);

	m_programChunk.LinkProgram();


	glClearColor(0.125f, 0.25f, 0.5f, 1.0f);
	SDL_GL_SetSwapInterval(0);

	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);

	InitSkyBox();
	InitChunks();

	m_textAtlas.FromFile("assets/atlas.png");
	m_programChunk.SetTexture("atlas", 0, m_textAtlas);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);

	m_camera.SetProj(45.0f, 640.0f / 480.0f, 0.01f, 1000.0f);
	//SDL_SetRelativeMouseMode(visible ? SDL_TRUE : SDL_FALSE);

	return true;


}

void CApplication::Clean()
{
	glDeleteTextures(1, &m_skyboxTexture);

	for (int i = 0; i < RenderDistance; ++i)
	{
		for (int j = 0; j < RenderDistance; ++j)
		{
			if (activeChunks[i][j] != nullptr)
			{
				delete activeChunks[i][j];
			}
		}
	}
}

void CApplication::Update()
{
	static Uint32 last_time = SDL_GetTicks();
	float delta_time = (SDL_GetTicks() - last_time) / 1000.0f;

	m_camera.Update(delta_time);
	CoutTest(delta_time);


	last_time = SDL_GetTicks();
}

void CApplication::Render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::mat4 viewProj = m_camera.GetViewProj();
	glm::mat4 world = glm::mat4(1.0f);
	m_programChunk.Use();
	m_programChunk.SetUniform("MVP", viewProj * world);
	m_programChunk.SetUniform("world", world);
	m_programChunk.SetUniform("worldIT", glm::inverse(glm::transpose(world)));

	for (int i = 0; i < activeChunks.size(); ++i) {
		for (int j = 0; j < activeChunks[i].size(); ++j) {
			activeChunks[i][j]->Render();
		}
	}

	m_programChunk.Unuse();



	GLint prevDepthFnc;
	glGetIntegerv(GL_DEPTH_FUNC, &prevDepthFnc);
	glDepthFunc(GL_LEQUAL);

	m_SkyboxVao.Bind();
	m_programSkybox.Use();
	m_programSkybox.SetUniform("MVP", viewProj * glm::translate(m_camera.GetEye()));

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, m_skyboxTexture);
	glUniform1i(m_programSkybox.GetLocation("skyboxTexture"), 0);

	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, nullptr);
	m_programSkybox.Unuse();

	glDepthFunc(prevDepthFnc);

}

void CApplication::KeyboardDown(SDL_KeyboardEvent& key)
{
	m_camera.KeyboardDown(key);
	if (key.keysym.sym == SDLK_f)
	{
		visible = !visible;
		SDL_SetRelativeMouseMode(visible ? SDL_TRUE : SDL_FALSE);
	}
}

void CApplication::KeyboardUp(SDL_KeyboardEvent& key)
{
	m_camera.KeyboardUp(key);
}

void CApplication::MouseMove(SDL_MouseMotionEvent& mouse)
{
	m_camera.MouseMove(mouse);
}

void CApplication::MouseDown(SDL_MouseButtonEvent& mouse)
{
}

void CApplication::MouseUp(SDL_MouseButtonEvent& mouse)
{
}

void CApplication::MouseWheel(SDL_MouseWheelEvent& wheel)
{
}

// a két paraméterbe az új ablakméret szélessége (_w) és magassága (_h) található
void CApplication::Resize(int _w, int _h)
{
	glViewport(0, 0, _w, _h );

	m_camera.Resize(_w, _h);
}







void CApplication::InitChunks()
{
	int start = SDL_GetTicks();

	for (int i = 0; i < RenderDistance; ++i) {
		activeChunks.push_back(std::vector<ChunkManager*>());
		for (int j = 0; j < RenderDistance; ++j) {
			activeChunks[i].push_back(new ChunkManager(glm::vec3(i * 16, 0, j * 16)));
		}
	}

	for (int i = 0; i < RenderDistance; ++i) {
		activeChunks.push_back(std::vector<ChunkManager*>());
		for (int j = 0; j < RenderDistance; ++j) {
			activeChunks[i][j]->ConnectChunkWithChunk
			(
				(j == 0) ? nullptr : activeChunks[i][j - 1],
				(i == RenderDistance - 1) ? nullptr : activeChunks[i + 1][j],
				(j == RenderDistance - 1) ? nullptr : activeChunks[i][j + 1],
				(i == 0) ? nullptr : activeChunks[i - 1][j]
			);
		}
	}
}
