#pragma once
#include <map>
#include <string>

#include <GL/glew.h>

#include "Texture\Texture.h"
#include "Shader\Shader.h"
#include "stb_image\stb_image.h"


// A static singleton ResourceManager class that hosts several
// functions to load Textures and Shaders. Each loaded texture
// and/or shader is also stored for future reference by string
// handles. All functions and resources are static and no 
// public constructor is defined.
class ResourceManager
{
public:
	// Resource storage
	static std::map<std::string, Shader>    Shaders;
	static std::map<std::string, Texture> Textures;
	static std::map<std::string, unsigned char*> Images;
	static Shader   loadShader(const GLchar *vShaderFile, const GLchar *fShaderFile, std::string name);
	static Shader   getShader(std::string name);
	static Texture loadTexture(const GLchar *file, GLboolean alpha, std::string name);
	static Texture* getTexture(std::string name);
	static unsigned char* loadImage(const GLchar *file, std::string name);
	static unsigned char* getImage(std::string name);
	static void      clear();
private:
	// Private constructor, that is we do not want any actual resource manager objects. Its members and functions should be publicly available (static).
	ResourceManager() { }
	// Loads and generates a shader from file
	static Shader    loadShaderFromFile(const GLchar *vShaderFile, const GLchar *fShaderFile, const GLchar *gShaderFile = nullptr);
	static Texture loadTextureFromFile(const GLchar *file, GLboolean alpha);
};