#include "Shader.h"

Shader::Shader()
{
	// ������ɫ��Դ��
	const char* vertexShaderSource = "#version 400 core\n"
		"layout (location=0) in vec3 aPos;\n"
		"layout (location=1) in vec2 aTexCoord;\n"
		"out vec2 TexCoord;\n"
		"uniform mat4 transform;\n"
		"void main()\n"
		"{\n"
		"	gl_Position = transform * vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
		"	TexCoord = aTexCoord ;\n"
		"}\0";

	// ����Ƭ���ַ���  ��ɫ��Դ��
	const char * fragmentShaderSource = "#version 400 core\n"
		"out vec4 FragColor;\n"
		"in vec2 TexCoord;\n"
		"uniform sampler2D ourTexture1;\n"
		"uniform sampler2D ourTexture2;\n"
		"void main()\n"
		"{\n"
		"FragColor = mix(texture(ourTexture1,TexCoord),texture(ourTexture2,TexCoord),0.5);\n"
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
	ID = glCreateProgram();
	// ��ɫ�����ӵ����������
	glAttachShader(ID, vertexShader);
	glAttachShader(ID, fragmentShader);
	// ���ӱ�����ɫ������
	glLinkProgram(ID);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	// ��ȡλ��ֵ
	//int vertexColorLocation = glGetUniformLocation(shaderProgram, "myColor");
	//glUseProgram(shaderProgram);   // ʹ���Զ�����Ⱦ����
	//glUniform4f(vertexColorLocation, 1.0f, 0.0f, 0.0f, 1.0f);
}

void Shader::userShader()
{
	glUseProgram(ID);
}

Shader::~Shader()
{
}
