#include "ResourceManager.h"

#include <iostream>
#include <sstream>
#include <fstream>


// Instantiate static variables
std::map<std::string, Shader>       ResourceManager::Shaders;
std::map<std::string, Texture>       ResourceManager::Textures;
std::map<std::string, unsigned char*> ResourceManager::Images;

Shader ResourceManager::loadShader(const GLchar *vShaderFile, const GLchar *fShaderFile, std::string name)
{
	Shaders[name] = loadShaderFromFile(vShaderFile, fShaderFile);
	return Shaders[name];
}

Shader ResourceManager::getShader(std::string name)
{
	return Shaders[name];
}

Texture ResourceManager::loadTexture(const GLchar * file, GLboolean alpha, std::string name)
{
	Textures[name] = loadTextureFromFile(file, alpha);
	return Textures[name];
}

Texture* ResourceManager::getTexture(std::string name)
{
	return &(Textures[name]);
}

void ResourceManager::clear()
{
	// (Properly) delete all shaders	
	for (auto iter : Shaders)
		glDeleteProgram(iter.second.ID);
}

Shader ResourceManager::loadShaderFromFile(const GLchar *vShaderFile, const GLchar *fShaderFile, const GLchar *gShaderFile)
{
	// 1. Retrieve the vertex/fragment source code from filePath
	std::string vertexCode;
	std::string fragmentCode;
	std::string geometryCode;
	try
	{
		// Open files
		std::ifstream vertexShaderFile(vShaderFile);
		std::ifstream fragmentShaderFile(fShaderFile);
		std::stringstream vShaderStream, fShaderStream;
		// Read file's buffer contents into streams
		vShaderStream << vertexShaderFile.rdbuf();
		fShaderStream << fragmentShaderFile.rdbuf();
		// close file handlers
		vertexShaderFile.close();
		fragmentShaderFile.close();
		// Convert stream into string
		vertexCode = vShaderStream.str();
		fragmentCode = fShaderStream.str();
		// If geometry shader path is present, also load a geometry shader
		if (gShaderFile != nullptr)
		{
			std::ifstream geometryShaderFile(gShaderFile);
			std::stringstream gShaderStream;
			gShaderStream << geometryShaderFile.rdbuf();
			geometryShaderFile.close();
			geometryCode = gShaderStream.str();
		}
	}
	catch (std::exception e)
	{
		std::cout << "ERROR::SHADER: Failed to read shader files" << std::endl;
	}
	const GLchar *vShaderCode = vertexCode.c_str();
	const GLchar *fShaderCode = fragmentCode.c_str();
	const GLchar *gShaderCode = geometryCode.c_str();
	// 2. Now create shader object from source code
	Shader shader;
	shader.compile(vShaderCode, fShaderCode, gShaderFile != nullptr ? gShaderCode : nullptr);
	return shader;
}

Texture ResourceManager::loadTextureFromFile(const GLchar * file, GLboolean alpha)
{
	Texture texture;
	if (alpha)
	{
		texture.Internal_Format = GL_RGBA;
		texture.Image_Format = GL_RGBA;
	}
	// Load image
	int width, height, nrChannels;
	//unsigned char* image = SOIL_load_image(file, &width, &height, 0, texture.Image_Format == GL_RGBA ? SOIL_LOAD_RGBA : SOIL_LOAD_RGB);
	unsigned char* image = stbi_load(file, &width, &height, &nrChannels, 0);
	// Now generate texture
	texture.generate(width, height, image);
	// And finally free image data
	stbi_image_free(image);
	return texture;
}

unsigned char* ResourceManager::loadImage(const GLchar* file, std::string name)
{
	int width, height, nrChannels;
	Images[name] = stbi_load(file, &width, &height, &nrChannels, 0);
	std::cout << "width: " << width << " height: " << height << "nrChannels: " << nrChannels << std::endl;
	return Images[name];
}

unsigned char* ResourceManager::getImage(std::string name)
{
	return (Images[name]);
}
