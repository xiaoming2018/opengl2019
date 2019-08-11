#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Shader.h"
#include "stb_image.h"
using namespace std;


GLFWwindow* windows;
// �������� (x,y,z)
float verticesNew[] = {
	-0.5f, -0.5f, 0.0f, 0, 0,		//����
	0.5f, -0.5f, 0.0f, 1, 0,         //����
	0.5f, 0.5f, 0.0f, 1, 1,         //����
	-0.5f, 0.5f, 0.0f, 0, 1   	    //����
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


int main()
{
	// ��ʼ��
	init();
	VAOSet();

	Shader myShader;

	int width, height, nrchannels;
	unsigned char * data = stbi_load("1.jpg", &width, &height, &nrchannels, 0);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);
	stbi_image_free(data);

	// ���Ʒ�ʽ ��line��ʽ Ĭ����gl_file
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	// ��Ⱦ����
	while (!glfwWindowShouldClose(windows))
	{
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f); // ���ô��ڱ�����ɫ
		glClear(GL_COLOR_BUFFER_BIT);  //  �����ɫ

		myShader.userShader();
		//glUseProgram(shaderProgram);   // ʹ���Զ�����Ⱦ����
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
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glBufferData(GL_ARRAY_BUFFER, sizeof(verticesNew), verticesNew, GL_STATIC_DRAW);
	// ���� ��ɫ�� VBO�Ľṹ - λ������ 0��VAO�ĵ�һ��λ�� ��3����xyz���� ֵ���ͣ� float��  �Ƿ��׼�� �� ��С-������ ƫ��VBO��λ��-- VBO����ǰ��ƫ����Ϊ0 
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	// ���� VAO �ĵ�һ��λ��
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*) (3 * sizeof(float)));
	// ���� VAO �ĵ�һ��λ��
	glEnableVertexAttribArray(1);


	//glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
	//// ���ݴ��
	//glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	//// ���� ��ɫ�� VBO�Ľṹ - λ������  1��VAO�ĵڶ���λ�� ��3����xyz���� ֵ���ͣ� float��  �Ƿ��׼�� �� ��С-������ ƫ��VBO��λ��-- VBO����ǰ��ƫ����Ϊ0 
	//glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	//// ���� VAO �ĵ�һ��λ��
	//glEnableVertexAttribArray(1);

	//// ���� ��ɫ�� VBO�Ľṹ - ��ɫ����  2��VAO�ĵ�����λ��   3����xyz���� ֵ���ͣ�  float��   �Ƿ��׼�� ��  ��С-������ ƫ��--��VBO���ں�ƫ����Ϊ3��float��С
	//glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	//// ���� VAO �ĵڶ���λ��
	//glEnableVertexAttribArray(2);

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
