#pragma once

#include <GL/glew.h>

namespace GL {
	void drawElements(GLuint indicesCount) noexcept;
	void bindVao(GLuint vao) noexcept;

	namespace Enum {
		enum Texture
		{
			Tex2D = GL_TEXTURE_2D,
			TexCubeMap = GL_TEXTURE_CUBE_MAP
		};
	}
}