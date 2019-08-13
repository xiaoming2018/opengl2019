#include "Shader.h"

Shader::Shader()
{
	// 顶点着色器源码
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

	// 创建片段字符串  着色器源码
	const char * fragmentShaderSource = "#version 400 core\n"
		"out vec4 FragColor;\n"
		"in vec2 TexCoord;\n"
		"uniform sampler2D ourTexture1;\n"
		"uniform sampler2D ourTexture2;\n"
		"void main()\n"
		"{\n"
		"FragColor = mix(texture(ourTexture1,TexCoord),texture(ourTexture2,TexCoord),0.5);\n"
		"}\n\0";

	// 创建顶点色器对象
	int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	// 对象与源码绑定
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	// 编译顶元着色器
	glCompileShader(vertexShader);

	// check for shader compiler errors
	int success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	// 创建片元着色器对象
	int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	// 对象与源码绑定
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	// 编译片元着色器
	glCompileShader(fragmentShader);

	// check for shader compile errors
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}


	// 创建着色器程序
	ID = glCreateProgram();
	// 着色器附加到程序对象上
	glAttachShader(ID, vertexShader);
	glAttachShader(ID, fragmentShader);
	// 链接编译着色器程序
	glLinkProgram(ID);

	// check for linking errors
	glGetProgramiv(ID, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(ID, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINGKING_FAILED\n" << infoLog << std::endl;
	}
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	// 获取位置值
	//int vertexColorLocation = glGetUniformLocation(shaderProgram, "myColor");
	//glUseProgram(shaderProgram);   // 使用自定义渲染程序
	//glUniform4f(vertexColorLocation, 1.0f, 0.0f, 0.0f, 1.0f);
}

Shader::Shader(const char * vertexPath, const char * fragmentPath)
{
	// 1, retrive the vertex/fragment source code from filepath
	std::string vertexCode;
	std::string fragmentCode;
	std::ifstream vShaderFile;
	std::ifstream fShaderFile;
	// ensure ifstream objects can throw exception
	vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	try
	{
		// open files
		vShaderFile.open(vertexPath);
		fShaderFile.open(fragmentPath);
		std::stringstream vShaderStream, fShaderStream;
		// read file's buffer contents into stram
		vShaderStream << vShaderFile.rdbuf();
		fShaderStream << fShaderFile.rdbuf();
		vShaderFile.close();
		fShaderFile.close();
		// convert stream into string
		vertexCode = vShaderStream.str();
		fragmentCode = fShaderStream.str();
	}
	catch (const std::ifstream::failure e)
	{
		std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
	}
	const char* vShaderCode = vertexCode.c_str();
	const char* fShaderCode = fragmentCode.c_str();

	// 2, compile shaders
	unsigned int vertex, fragment;
	// vertex shader
	vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vShaderCode, NULL);
	glCompileShader(vertex);
	checkCompileErrors(vertex, "VERTEX");

	// fragment shader
	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fShaderCode, NULL);
	glCompileShader(fragment);
	checkCompileErrors(fragment, "FRAGMENT");

	// shader program
	ID = glCreateProgram();
	glAttachShader(ID, vertex);
	glAttachShader(ID, fragment);
	glLinkProgram(ID);
	checkCompileErrors(ID, "PROGRAM");

	glDeleteShader(vertex);
	glDeleteShader(fragment);	
}

// active the shader
void Shader::userShader()
{
	glUseProgram(ID);
}

void Shader::setBool(const std::string &name, bool value) const
{
	glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
}

void Shader::setInt(const std::string & name, int value) const
{
	glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::setFloat(const std::string & name, float value) const
{
	glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}

Shader::~Shader()
{
}

void Shader::checkCompileErrors(unsigned int shader, std::string type)
{
	int success;
	char infoLog[1024];
	if (type != "PROGRAM")
	{
		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(shader, 1024, NULL, infoLog);
			std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
		}
	}
	else
	{
		glGetProgramiv(shader, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetProgramInfoLog(shader, 1024, NULL, infoLog);
			std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
		}
	}
}
