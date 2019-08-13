#pragma once
#include <glad/glad.h>

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

class Shader
{
public:
	unsigned int ID;
	void userShader();
	void setBool(const std::string &name, bool value) const;
	void setInt(const std::string &name, int value) const;
	void setFloat(const std::string &name, float value) const;
	Shader();
	Shader(const char* vertexPath, const char* framentPath);
	~Shader();
private:
	void checkCompileErrors(unsigned int shader, std::string type);
};
