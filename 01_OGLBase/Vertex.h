#pragma once
#include <glm\glm.hpp>
#include <cstdint>
#include "Vector2.h"

using Block_t = uint8_t;


struct Vertex {
	glm::vec3 pos;
	Vector2 coords;
	char data; 
};