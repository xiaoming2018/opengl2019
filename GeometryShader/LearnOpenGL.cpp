#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Shader.h"

#include <iostream>

// 顶点数据 (x,y,z)
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
	// 初始化
	GLFWwindow* windows = init();
	glEnable(GL_DEPTH_TEST); // 深度

	VAOSet();
	//light_VAO_init();
	Shader shader("geometry_shader.vs", "geometry_shader.fs", "geometry_shader.gs");

	// 渲染引擎
	while (!glfwWindowShouldClose(windows))
	{

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f); // 设置窗口背景颜色
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  //  填充颜色

		shader.userShader();
		glBindVertexArray(VAO);
		glDrawArrays(GL_POINTS, 0, 4);

		//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL); //使用索引绘制
		glfwSwapBuffers(windows);
		glfwPollEvents(); // 接受事件
	}
	// optional: de-allocate all resources once they've outlived their purpose:
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	// 退出 
	glfwTerminate();
	return 0;
}

GLFWwindow* init()
{
	GLFWwindow* windows;
	glfwInit(); // 初始化 窗口库
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);  // opengl的版本号
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // 设置核心模式
	windows = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "OPENGL - LEARN", NULL, NULL);
	if (windows == NULL) {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
	}
	glfwMakeContextCurrent(windows); // 上下文关联 windows
	glfwSetFramebufferSizeCallback(windows, framebuffer_size_callback);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) { //  GLAD 初始化 
		// 初始化 glad
		std::cout << "Failed to initialize GLAD" << std::endl;
	}
	return windows;
}

void VAOSet()
{
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	glGenBuffers(1, &VBO); // 显存空间

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	// 绑定VBO数据
	glBufferData(GL_ARRAY_BUFFER, sizeof(points), &points, GL_STATIC_DRAW);
	// 告诉 着色器 VBO的结构 - 位置属性 0：VAO的第一个位置 ；3：（xyz）； 值类型： float；  是否标准化 ； 大小-步长； 偏移VBO的位置-- VBO中在前，偏移量为0 
	
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
