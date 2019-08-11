#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
using namespace std;

int shaderProgram;
GLFWwindow* windows;
// 顶点数据 (x,y,z)
float verticesNew[] = {
	0.0f, 0.0f, 0.0f,		//左下
	0.0f, 1.0f, 0.0f,   	//左上
	1.0f, 1.0f, 0.0f,       //右上
	1.0f, 0.0f, 0.0f       //右下  

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
void shaderSet();

int main()
{
	// 初始化
	init();
	VAOSet();
	shaderSet();

	// 绘制方式 用line方式 默认是gl_file
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	// 渲染引擎
	while (!glfwWindowShouldClose(windows))
	{
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f); // 设置窗口背景颜色
		glClear(GL_COLOR_BUFFER_BIT);  //  填充颜色

		glUseProgram(shaderProgram);   // 使用自定义渲染程序
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
	glBufferData(GL_ARRAY_BUFFER, sizeof(verticesNew), verticesNew, GL_STATIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// 告诉 着色器 VBO的结构 - 位置属性 0：VAO的第一个位置 ；3：（xyz）； 值类型： float；  是否标准化 ； 大小-步长； 偏移VBO的位置-- VBO中在前，偏移量为0 
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	// 启用 VAO 的第一个位置
	glEnableVertexAttribArray(0);


	glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
	// 数据存放
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// 告诉 着色器 VBO的结构 - 位置属性 0：VAO的第一个位置 ；3：（xyz）； 值类型： float；  是否标准化 ； 大小-步长； 偏移VBO的位置-- VBO中在前，偏移量为0 
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	// 启用 VAO 的第一个位置
	glEnableVertexAttribArray(1);

	// 告诉 着色器 VBO的结构 - 颜色属性 1：VAO的第二个位置   3：（xyz）； 值类型：  float；   是否标准化 ；  大小-步长； 偏移--在VBO中在后，偏移量为3个float大小
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	// 启用 VAO 的第二个位置
	glEnableVertexAttribArray(2);

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

void shaderSet()
{
	// 顶点着色器源码
	const char* vertexShaderSource = "#version 400 core\n"
		"layout (location=0) in vec3 aPos;\n"
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