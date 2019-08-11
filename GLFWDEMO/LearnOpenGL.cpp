#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Shader.h"
#include "stb_image.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>  // 导入 glm 库

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
	 -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,
	  0.5f, -0.5f, -0.5f, 1.0f, 0.0f,
	  0.5f,  0.5f, -0.5f, 1.0f, 1.0f,
	  0.5f,  0.5f, -0.5f, 1.0f, 1.0f,
	 -0.5f,  0.5f, -0.5f, 0.0f, 1.0f,
	 -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,

	 -0.5f, -0.5f,  0.5f, 0.0f, 0.0f,
	  0.5f, -0.5f,  0.5f, 1.0f, 0.0f,
	  0.5f,  0.5f,  0.5f, 1.0f, 1.0f,
	  0.5f,  0.5f,  0.5f, 1.0f, 1.0f,
	 -0.5f,  0.5f,  0.5f, 0.0f, 1.0f,
	 -0.5f, -0.5f,  0.5f, 0.0f, 0.0f,

	 -0.5f,  0.5f,  0.5f, 1.0f, 0.0f,
	 -0.5f,  0.5f, -0.5f, 1.0f, 1.0f,
	 -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
	 -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
	 -0.5f, -0.5f,  0.5f, 0.0f, 0.0f,
	 -0.5f,  0.5f,  0.5f, 1.0f, 0.0f,

	  0.5f,  0.5f,  0.5f, 1.0f, 0.0f,
	  0.5f,  0.5f, -0.5f, 1.0f, 1.0f,
	  0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
	  0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
	  0.5f, -0.5f,  0.5f, 0.0f, 0.0f,
	  0.5f,  0.5f,  0.5f, 1.0f, 0.0f,

	 -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
	  0.5f, -0.5f, -0.5f, 1.0f, 1.0f,
	  0.5f, -0.5f,  0.5f, 1.0f, 0.0f,
	  0.5f, -0.5f,  0.5f, 1.0f, 0.0f,
	 -0.5f, -0.5f,  0.5f, 0.0f, 0.0f,
	 -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,

	 -0.5f,  0.5f, -0.5f, 0.0f, 1.0f,
	  0.5f,  0.5f, -0.5f, 1.0f, 1.0f,
	  0.5f,  0.5f,  0.5f, 1.0f, 0.0f,
	  0.5f,  0.5f,  0.5f, 1.0f, 0.0f,
	 -0.5f,  0.5f,  0.5f, 0.0f, 0.0f,
	 -0.5f,  0.5f, -0.5f, 0.0f, 1.0f,
};

glm::vec3 cubePositon[] =
{
	glm::vec3(0.0f, 0.0f,  0.0f),
	glm::vec3(2.0f, 5.0f, -15.0f),
	glm::vec3(-2.0f, 3.0f, -7.5f)
};

// EBO 索引数组
unsigned int indices[] = {
	0,1,3,
	1,2,3
};

void init();
void VAOSet();
void texture(Shader &myShader);

int main()
{
	//// 列向量 表示
	//glm::vec4 vec(1.0f, 0.0f, 0.0f, 1.0f);
	//glm::mat4 trans = glm::mat4(1.0f);
	//trans = glm::translate(trans, glm::vec3(1.0f, 1.0f, 0.0f));
	//vec = trans * vec;
	//cout << " x: " <<vec.x << vec.y << vec.z << endl;

	//glm::mat4 trans = glm::mat4(1.0f);
	//trans = glm::rotate(trans, glm::radians(90.0f),glm::vec3(0.0f,0.0f,1.0f)); // 度数 和 参考轴
	//trans = glm::scale(trans, glm::vec3(0.5f, 0.5f, 0.5f));

	// 初始化
	init();
	VAOSet();

	Shader myShader;
	texture(myShader);

	glEnable(GL_DEPTH_TEST); // 深度

	// 渲染引擎
	while (!glfwWindowShouldClose(windows))
	{
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f); // 设置窗口背景颜色
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  //  填充颜色

		for (size_t i = 0; i < 3; i++)
		{
			glm::mat4 trans = glm::mat4(1.0f);
			glm::mat4 model = glm::mat4(1.0f);  // 模型矩阵
			model = glm::translate(trans, cubePositon[i]); //  平移
			//model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f)); // 绕x轴旋转 45°
			model = glm::rotate(model, (float)glfwGetTime(), glm::vec3(0.5f, 1.0f, 0.0f));   // 随时间旋转

			glm::mat4 view = glm::mat4(1.0f); // 需要初始化
			view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));

			glm::mat4 projection = glm::mat4(1.0f);
			projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);
			trans = projection * view * model;

			myShader.userShader();
			glUniformMatrix4fv(glGetUniformLocation(myShader.ID, "transform"), 1, GL_FALSE, glm::value_ptr(trans));

			glDrawArrays(GL_TRIANGLES, 0, 36); // 读取三个点，进行绘制 画三角
		}
		//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL);

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

	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	// 告诉 着色器 VBO的结构 - 位置属性 0：VAO的第一个位置 ；3：（xyz）； 值类型： float；  是否标准化 ； 大小-步长； 偏移VBO的位置-- VBO中在前，偏移量为0 
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	// 启用 VAO 的第一个位置
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
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

void texture(Shader &myShader)
{
	int width, height, nrchannels;
	unsigned char * data = NULL;
	stbi_set_flip_vertically_on_load(true);  // 实现y轴的反转

	unsigned int texture[2];
	glGenTextures(2, texture);

	// 加载第一个纹理
	glBindTexture(GL_TEXTURE_2D, texture[0]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);// 纹理放大时 使用 最近原则过滤
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); // 纹理缩小时 使用 最近原则过滤
	data = stbi_load("1.jpg", &width, &height, &nrchannels, 0);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);
	stbi_image_free(data);

	// 加载第二个纹理 纹理图片太小 会加载错误
	glBindTexture(GL_TEXTURE_2D, texture[1]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);// 纹理放大时 使用 最近原则过滤
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); // 纹理缩小时 使用 最近原则过滤
	data = stbi_load("temp.jpg", &width, &height, &nrchannels, 0);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	// glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data); // png 格式  带有透明度参数
	glGenerateMipmap(GL_TEXTURE_2D);
	stbi_image_free(data);


	myShader.userShader();
	glUniform1i(glGetUniformLocation(myShader.ID, "ourTexture1"), 0);
	glUniform1i(glGetUniformLocation(myShader.ID, "ourTexture2"), 1);

	glActiveTexture(GL_TEXTURE0); // 先激活再绑定 纹理单元0 默认是激活的
	glBindTexture(GL_TEXTURE_2D, texture[0]);

	glActiveTexture(GL_TEXTURE1); // 纹理单元
	glBindTexture(GL_TEXTURE_2D, texture[1]);
}