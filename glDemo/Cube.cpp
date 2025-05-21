#include "Cube.h"
//#include "TextureLoader.h"
//#include "Texture.h"


using namespace std;
using namespace glm;


// Example data for cube model


//original
/*

// Packed vertex buffer for cube
static float positionArray[] = {

	-1.0f, 1.0f, 1.0f, 1.0f,
	-1.0f, 1.0f, -1.0f, 1.0f,
	1.0f, 1.0f, -1.0f, 1.0f,
	1.0f, 1.0f, 1.0f, 1.0f,

	-1.0f, -1.0f, 1.0f, 1.0f,
	-1.0f, -1.0f, -1.0f, 1.0f,
	1.0f, -1.0f, -1.0f, 1.0f,
	1.0f, -1.0f, 1.0f, 1.0f
};

// Packed colour buffer for principle axes model
static float colourArray[] = {

	1.0f, 0.0f, 0.0f, 1.0f,
	1.0f, 0.0f, 1.0f, 1.0f,
	0.0f, 1.0f, 0.0f, 1.0f,
	1.0f, 1.0f, 0.0f, 1.0f,

	0.0f, 0.0f, 1.0f, 1.0f,
	0.0f, 1.0f, 1.0f, 1.0f,
	0.0f, 0.0f, 0.0f, 1.0f,
	0.0f, 0.0f, 0.0f, 1.0f
};


// Line list topology to render principle axes
static unsigned int indexArray[] = {

	// Top face
	2, 1, 0,
	3, 2, 0,

	// Bottom face
	5, 6, 4,
	6, 7, 4,

	// Right face
	3, 7, 2,
	7, 6, 2,

	// Front face
	0, 4, 3,
	4, 7, 3,

	// Left face
	0, 1, 5,
	4, 0, 5,

	// Back face
	2, 6, 1,
	6, 5, 1
};

*/



// Packed vertex buffer for cube
static float positionArray[] = {
	 0.0f,  0.0f, 0.0f, 1.0f,  
	 0.0f,  0.0f,  -10.0f, 1.0f,  
	 0.0f, 10.0f,  -10.0f, 1.0f,  
	 0.0f, 10.0f, 0.0f, 1.0f,  
};

// Packed colour buffer for principle axes model
static float colourArray[] = {
	0.62f, 0.46f, 0.28f, 1.0f, 
	0.75f, 0.55f, 0.33f, 1.0f, 
	0.54f, 0.29f, 0.02f, 1.0f, 
	0.98f, 0.54f, 0.02f, 1.0f, 
};

/*static float textureArray[] = {
	1.0f, 1.0f, //top right
	1.0f, 0.0f, //bottom right
	0.0f, 0.0f, //bottom left
	0.0f, 1.0f //top left
};*/


// Line list topology to render principle axes
static unsigned int indexArray[] = {
	0, 1, 2,  2, 3, 0,  
};



Cube::Cube() {

	m_numFaces = 1 * 2;
	
	//m_texture = loadTexture("Assets\\Textures\\mud.jpg", FIF_JPEG); 


	glGenVertexArrays(1, &m_vao);
	glBindVertexArray(m_vao);

	// setup vbo for position attribute
	glGenBuffers(1, &m_vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(positionArray), positionArray, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, (const GLvoid*)0);
	glEnableVertexAttribArray(0);

	// setup vbo for colour attribute
	glGenBuffers(1, &m_colourBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, m_colourBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(colourArray), colourArray, GL_STATIC_DRAW);
	glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, 0, (const GLvoid*)0);
	glEnableVertexAttribArray(4); 


	//https://learnopengl.com/code_viewer_gh.php?code=src/1.getting_started/4.1.textures/textures.cpp //https://learnopengl.com/Getting-started/Textures
	//setup vbo for texture
	/*glGenBuffers(1, &m_textureBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, m_textureBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(textureArray), textureArray, GL_STATIC_DRAW); 
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (const GLvoid*) 0); 
	glEnableVertexAttribArray(2); */


	// setup vbo for cube) index buffer
	glGenBuffers(1, &m_indexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indexArray), indexArray, GL_STATIC_DRAW);

	glBindVertexArray(0);
}


Cube::~Cube() {

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	glDeleteBuffers(1, &m_vertexBuffer);
	glDeleteBuffers(1, &m_colourBuffer);
	glDeleteBuffers(1, &m_indexBuffer);
	glDeleteBuffers(1, &m_textureBuffer);   
}


void Cube::render() 
{
	/*glEnable(GL_TEXTURE_2D);

	glActiveTexture(GL_TEXTURE0); 
	glBindTexture(GL_TEXTURE_2D, m_texture); */ 
	glBindVertexArray(m_vao);
	glDrawElements(GL_TRIANGLES, m_numFaces * 3, GL_UNSIGNED_INT, (const GLvoid*)0);
}
