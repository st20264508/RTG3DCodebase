#pragma once

#include "core.h"

class Cube {

private:

	GLuint				m_numFaces = 0;
	GLuint				m_vao = 0;

	GLuint				m_vertexBuffer;
	GLuint				m_colourBuffer;
	GLuint				m_indexBuffer;
	GLuint				m_textureBuffer; 

	GLuint				m_texture;

public:

	Cube();
	~Cube();

	void render();
};