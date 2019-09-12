#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Shader.h"

#include <iostream>

// �������� (x,y,z)
float points[] = {
	-0.5f,  0.5f, 1.0f, 0.0f, 0.0f, // top-left
	 0.5f,  0.5f, 0.0f, 1.0f, 0.0f, // top-right
	 0.5f, -0.5f, 0.0f, 0.0f, 1.0f, // bottom-right
	-0.5f, -0.5f, 1.0f, 1.0f, 0.0f  // bottom-left
};

GLFWwindow* init();
void VAOSet();

void framebuffer_size_callback(GLFWwindow* window, int width, int height);

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

//VBO VAO
unsigned int VBO, VAO;

int main()
{
	// ��ʼ��
	GLFWwindow* windows = init();
	glEnable(GL_DEPTH_TEST); // ���

	VAOSet();
	//light_VAO_init();
	Shader shader("geometry_shader.vs", "geometry_shader.fs", "geometry_shader.gs");

	// ��Ⱦ����
	while (!glfwWindowShouldClose(windows))
	{

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f); // ���ô��ڱ�����ɫ
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  //  �����ɫ

		shader.userShader();
		glBindVertexArray(VAO);
		glDrawArrays(GL_POINTS, 0, 4);

		//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL); //ʹ����������
		glfwSwapBuffers(windows);
		glfwPollEvents(); // �����¼�
	}
	// optional: de-allocate all resources once they've outlived their purpose:
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	// �˳� 
	glfwTerminate();
	return 0;
}

GLFWwindow* init()
{
	GLFWwindow* windows;
	glfwInit(); // ��ʼ�� ���ڿ�
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);  // opengl�İ汾��
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // ���ú���ģʽ
	windows = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "OPENGL - LEARN", NULL, NULL);
	if (windows == NULL) {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
	}
	glfwMakeContextCurrent(windows); // �����Ĺ��� windows
	glfwSetFramebufferSizeCallback(windows, framebuffer_size_callback);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) { //  GLAD ��ʼ�� 
		// ��ʼ�� glad
		std::cout << "Failed to initialize GLAD" << std::endl;
	}
	return windows;
}

void VAOSet()
{
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	glGenBuffers(1, &VBO); // �Դ�ռ�

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	// ��VBO����
	glBufferData(GL_ARRAY_BUFFER, sizeof(points), &points, GL_STATIC_DRAW);
	// ���� ��ɫ�� VBO�Ľṹ - λ������ 0��VAO�ĵ�һ��λ�� ��3����xyz���� ֵ���ͣ� float��  �Ƿ��׼�� �� ��С-������ ƫ��VBO��λ��-- VBO����ǰ��ƫ����Ϊ0 
	
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(2 * sizeof(float)));
	
	glBindVertexArray(0);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}
