#include "GLFunctions.h"

void GL::drawElements(GLuint indiceCount) noexcept
{
	glDrawElements(GL_TRIANGLES, indiceCount, GL_UNSIGNED_INT, nullptr);
}

void GL::bindVao(GLuint vao) noexcept
{
	glBindVertexArray(vao);
}