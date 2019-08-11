#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Shader.h"
#include "stb_image.h"
using namespace std;


GLFWwindow* windows;
// 顶点数据 (x,y,z)
float verticesNew[] = {
	-0.5f, -0.5f, 0.0f, 0, 0,		//左下
	0.5f, -0.5f, 0.0f, 1, 0,         //右下
	0.5f, 0.5f, 0.0f, 1, 1,         //右上
	-0.5f, 0.5f, 0.0f, 0, 1   	    //左上
};

float vertices[] = {
	-0.5f, -0.5f, 0.0f, 1, 0, 0,		//左下
	-0.5f, 0.5f, 0.0f, 0, 1, 0,		//左上
	0.5f, 0.5f, 0.0f, 0, 0, 1,      //右上
	0.5f, -0.5f, 0.0f, 1, 0, 0       //右下  

};

// EBO 索引数组
unsigned int indices[] = {
	0,1,3,
	1,2,3
};

void init();
void VAOSet();


int main()
{
	// 初始化
	init();
	VAOSet();

	Shader myShader;

	int width, height, nrchannels;
	unsigned char * data = stbi_load("1.jpg", &width, &height, &nrchannels, 0);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);
	stbi_image_free(data);

	// 绘制方式 用line方式 默认是gl_file
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	// 渲染引擎
	while (!glfwWindowShouldClose(windows))
	{
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f); // 设置窗口背景颜色
		glClear(GL_COLOR_BUFFER_BIT);  //  填充颜色

		myShader.userShader();
		//glUseProgram(shaderProgram);   // 使用自定义渲染程序
		//glDrawArrays(GL_TRIANGLES, 0, 3); // 读取三个点，进行绘制 画三角
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL);

		glfwPollEvents(); // 接受事件
		glfwSwapBuffers(windows);
	}
	// 退出 
	glfwTerminate();
	return 0;
}

void VAOSet()
{
	unsigned int VBO[2], VAO, EBO; // ID 号
	// 生成 VAO 
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(2, VBO); // 显存空间
	glGenBuffers(1, &EBO); // 显存空间
	glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glBufferData(GL_ARRAY_BUFFER, sizeof(verticesNew), verticesNew, GL_STATIC_DRAW);
	// 告诉 着色器 VBO的结构 - 位置属性 0：VAO的第一个位置 ；3：（xyz）； 值类型： float；  是否标准化 ； 大小-步长； 偏移VBO的位置-- VBO中在前，偏移量为0 
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	// 启用 VAO 的第一个位置
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*) (3 * sizeof(float)));
	// 启用 VAO 的第一个位置
	glEnableVertexAttribArray(1);


	//glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
	//// 数据存放
	//glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	//// 告诉 着色器 VBO的结构 - 位置属性  1：VAO的第二个位置 ；3：（xyz）； 值类型： float；  是否标准化 ； 大小-步长； 偏移VBO的位置-- VBO中在前，偏移量为0 
	//glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	//// 启用 VAO 的第一个位置
	//glEnableVertexAttribArray(1);

	//// 告诉 着色器 VBO的结构 - 颜色属性  2：VAO的第三个位置   3：（xyz）； 值类型：  float；   是否标准化 ；  大小-步长； 偏移--在VBO中在后，偏移量为3个float大小
	//glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	//// 启用 VAO 的第二个位置
	//glEnableVertexAttribArray(2);

}

void init()
{
	glfwInit(); // 初始化 窗口库
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);  // opengl的版本号
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // 设置核心模式

	windows = glfwCreateWindow(800, 600, "OPENGL - LEARN", NULL, NULL);
	if (windows == NULL) {
		cout << "Failed to create GLFW window" << endl;
		glfwTerminate();
		return;
	}
	glfwMakeContextCurrent(windows); // 上下文关联 windows

	//  GLAD 初始化 
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		// 初始化 glad
		cout << "Failed to initialize GLAD" << endl;
		return;
	}
}
