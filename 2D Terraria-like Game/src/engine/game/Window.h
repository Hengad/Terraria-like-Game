#pragma once
#include <GL\glew.h>

struct Window
{
private:
	static const GLuint m_width = 1280;
	static const GLuint m_height = 720;
public:
	static GLuint getWinWidth() { return m_width; }
	static GLuint getWinHeight() { return m_height; }
};