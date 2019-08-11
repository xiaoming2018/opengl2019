#include "Shader.h"

Shader::Shader()
{
	// 顶点着色器源码
	const char* vertexShaderSource = "#version 400 core\n"
		"layout (location=1) in vec3 aPos;\n"
		"layout (location=2) in vec3 aColor;\n"
		"out vec4 ourColor;\n"
		"void main()\n"
		"{\n"
		"	gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
		"	ourColor = vec4(aColor.x, aColor.y, aColor.z, 1.0);\n"
		"}\0";

	// 创建片段字符串  着色器源码
	const char * fragmentShaderSource = "#version 400 core\n"
		"out vec4 FragColor;\n"
		"in vec4 ourColor;\n"
		"void main()\n"
		"{\n"
		"FragColor = ourColor;\n"
		"}\n\0";

	// 创建顶点色器对象
	int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	// 对象与源码绑定
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	// 编译片元着色器
	glCompileShader(vertexShader);

	// 创建片元着色器对象
	int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	// 对象与源码绑定
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	// 编译片元着色器
	glCompileShader(fragmentShader);

	// 创建着色器程序
	shaderProgram = glCreateProgram();
	// 着色器附加到程序对象上
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	// 链接编译着色器程序
	glLinkProgram(shaderProgram);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	// 获取位置值
	int vertexColorLocation = glGetUniformLocation(shaderProgram, "myColor");
	glUseProgram(shaderProgram);   // 使用自定义渲染程序
	glUniform4f(vertexColorLocation, 1.0f, 0.0f, 0.0f, 1.0f);
}

void Shader::userShader()
{
	glUseProgram(shaderProgram);
}

Shader::~Shader()
{
}
