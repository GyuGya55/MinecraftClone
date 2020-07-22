//#pragma once
//
//void Init()
//{
//	if (vertices.size() != 0) {
//		glGenVertexArrays(1, &vao);
//		glGenBuffers(1, &vbo);
//		glGenBuffers(1, &ib);
//
//		glBindVertexArray(vao);
//
//		glBindBuffer(GL_ARRAY_BUFFER, vbo);
//		glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vertices.size(), (void*)&vertices[0], GL_STREAM_DRAW);
//
//		glEnableVertexAttribArray(0);
//		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
//		glEnableVertexAttribArray(1);
//		glVertexAttribPointer(1, 1, GL_BYTE, GL_FALSE, sizeof(Vertex), (void*)(sizeof(glm::vec3)));
//		glEnableVertexAttribArray(2);
//		glVertexAttribPointer(2, 1, GL_BYTE, GL_FALSE, sizeof(Vertex), (void*)(sizeof(glm::vec3) + 1));
//		glEnableVertexAttribArray(3);
//		glVertexAttribPointer(3, 1, GL_BYTE, GL_FALSE, sizeof(Vertex), (void*)(sizeof(glm::vec3) + 2));
//
//		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ib);
//		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * indices.size(), (void*)&indices[0], GL_STREAM_DRAW);
//
//		glBindVertexArray(0);
//	}
//}