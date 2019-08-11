#include "Shader.h"

Shader::Shader()
{
	// ������ɫ��Դ��
	const char* vertexShaderSource = "#version 400 core\n"
		"layout (location=1) in vec3 aPos;\n"
		"layout (location=2) in vec3 aColor;\n"
		"out vec4 ourColor;\n"
		"void main()\n"
		"{\n"
		"	gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
		"	ourColor = vec4(aColor.x, aColor.y, aColor.z, 1.0);\n"
		"}\0";

	// ����Ƭ���ַ���  ��ɫ��Դ��
	const char * fragmentShaderSource = "#version 400 core\n"
		"out vec4 FragColor;\n"
		"in vec4 ourColor;\n"
		"void main()\n"
		"{\n"
		"FragColor = ourColor;\n"
		"}\n\0";

	// ��������ɫ������
	int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	// ������Դ���
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	// ����ƬԪ��ɫ��
	glCompileShader(vertexShader);

	// ����ƬԪ��ɫ������
	int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	// ������Դ���
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	// ����ƬԪ��ɫ��
	glCompileShader(fragmentShader);

	// ������ɫ������
	shaderProgram = glCreateProgram();
	// ��ɫ�����ӵ����������
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	// ���ӱ�����ɫ������
	glLinkProgram(shaderProgram);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	// ��ȡλ��ֵ
	int vertexColorLocation = glGetUniformLocation(shaderProgram, "myColor");
	glUseProgram(shaderProgram);   // ʹ���Զ�����Ⱦ����
	glUniform4f(vertexColorLocation, 1.0f, 0.0f, 0.0f, 1.0f);
}

void Shader::userShader()
{
	glUseProgram(shaderProgram);
}

Shader::~Shader()
{
}
