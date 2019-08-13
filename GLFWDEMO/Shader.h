#pragma once
#include <glad/glad.h>
#include <iostream>

class Shader
{
public:
	int ID;
	void userShader();
	Shader();
	~Shader();
};
