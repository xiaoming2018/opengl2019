#pragma once
#include <glad/glad.h>
#include <iostream>


class Shader
{
public:
	int shaderProgram;
	void userShader();
	Shader();
	~Shader();
};

