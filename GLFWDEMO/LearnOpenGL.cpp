#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
using namespace std;

int shaderProgram;
GLFWwindow* windows;
// �������� (x,y,z)
float verticesNew[] = {
	0.0f, 0.0f, 0.0f,		//����
	0.0f, 1.0f, 0.0f,   	//����
	1.0f, 1.0f, 0.0f,       //����
	1.0f, 0.0f, 0.0f       //����  

};

float vertices[] = {
	-0.5f, -0.5f, 0.0f, 1, 0, 0,		//����
	-0.5f, 0.5f, 0.0f, 0, 1, 0,		//����
	0.5f, 0.5f, 0.0f, 0, 0, 1,      //����
	0.5f, -0.5f, 0.0f, 1, 0, 0       //����  

};

// EBO ��������
unsigned int indices[] = {
	0,1,3,
	1,2,3
};

void init();
void VAOSet();
void shaderSet();

int main()
{
	// ��ʼ��
	init();
	VAOSet();
	shaderSet();

	// ���Ʒ�ʽ ��line��ʽ Ĭ����gl_file
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	// ��Ⱦ����
	while (!glfwWindowShouldClose(windows))
	{
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f); // ���ô��ڱ�����ɫ
		glClear(GL_COLOR_BUFFER_BIT);  //  �����ɫ

		glUseProgram(shaderProgram);   // ʹ���Զ�����Ⱦ����
		//glDrawArrays(GL_TRIANGLES, 0, 3); // ��ȡ�����㣬���л��� ������
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL);

		glfwPollEvents(); // �����¼�
		glfwSwapBuffers(windows);
	}
	// �˳� 
	glfwTerminate();
	return 0;
}

void VAOSet()
{
	unsigned int VBO[2], VAO, EBO; // ID ��
	// ���� VAO 
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(2, VBO); // �Դ�ռ�
	glGenBuffers(1, &EBO); // �Դ�ռ�
	glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verticesNew), verticesNew, GL_STATIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// ���� ��ɫ�� VBO�Ľṹ - λ������ 0��VAO�ĵ�һ��λ�� ��3����xyz���� ֵ���ͣ� float��  �Ƿ��׼�� �� ��С-������ ƫ��VBO��λ��-- VBO����ǰ��ƫ����Ϊ0 
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	// ���� VAO �ĵ�һ��λ��
	glEnableVertexAttribArray(0);


	glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
	// ���ݴ��
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// ���� ��ɫ�� VBO�Ľṹ - λ������ 0��VAO�ĵ�һ��λ�� ��3����xyz���� ֵ���ͣ� float��  �Ƿ��׼�� �� ��С-������ ƫ��VBO��λ��-- VBO����ǰ��ƫ����Ϊ0 
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	// ���� VAO �ĵ�һ��λ��
	glEnableVertexAttribArray(1);

	// ���� ��ɫ�� VBO�Ľṹ - ��ɫ���� 1��VAO�ĵڶ���λ��   3����xyz���� ֵ���ͣ�  float��   �Ƿ��׼�� ��  ��С-������ ƫ��--��VBO���ں�ƫ����Ϊ3��float��С
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	// ���� VAO �ĵڶ���λ��
	glEnableVertexAttribArray(2);

}

void init()
{
	glfwInit(); // ��ʼ�� ���ڿ�
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);  // opengl�İ汾��
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // ���ú���ģʽ

	windows = glfwCreateWindow(800, 600, "OPENGL - LEARN", NULL, NULL);
	if (windows == NULL) {
		cout << "Failed to create GLFW window" << endl;
		glfwTerminate();
		return;
	}
	glfwMakeContextCurrent(windows); // �����Ĺ��� windows

	//  GLAD ��ʼ�� 
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		// ��ʼ�� glad
		cout << "Failed to initialize GLAD" << endl;
		return;
	}
}

void shaderSet()
{
	// ������ɫ��Դ��
	const char* vertexShaderSource = "#version 400 core\n"
		"layout (location=0) in vec3 aPos;\n"
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