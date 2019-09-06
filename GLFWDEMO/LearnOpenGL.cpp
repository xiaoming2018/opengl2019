#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Shader.h"
#include "stb_image.h"
#include "Camera.h"

// 顶点数据 (x,y,z)
float verticesNew[] = {
	-0.5f, -0.5f, 0.0f, 0, 0,		//左下
	 0.5f, -0.5f, 0.0f, 1, 0,         //右下
	 0.5f,  0.5f, 0.0f, 1, 1,         //右上
	-0.5f,  0.5f, 0.0f, 0, 1   	    //左上
};
// 36 顶点 以及 纹理坐标
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

glm::vec3 cubePositon[] ={
	glm::vec3( 0.0f, 0.0f,   0.0f),
	glm::vec3( 2.0f, 5.0f, -15.0f),
	glm::vec3(-2.0f, 3.0f, -7.50f)
};

unsigned int indices[] = {
	0,1,3,
	1,2,3
}; // EBO 索引数组

float vertices_light[] = {
	   -0.5f, -0.5f, -0.5f,
		0.5f, -0.5f, -0.5f,
		0.5f,  0.5f, -0.5f,
		0.5f,  0.5f, -0.5f,
	   -0.5f,  0.5f, -0.5f,
	   -0.5f, -0.5f, -0.5f,

	   -0.5f, -0.5f,  0.5f,
		0.5f, -0.5f,  0.5f,
		0.5f,  0.5f,  0.5f,
		0.5f,  0.5f,  0.5f,
	   -0.5f,  0.5f,  0.5f,
	   -0.5f, -0.5f,  0.5f,

	   -0.5f,  0.5f,  0.5f,
	   -0.5f,  0.5f, -0.5f,
	   -0.5f, -0.5f, -0.5f,
	   -0.5f, -0.5f, -0.5f,
	   -0.5f, -0.5f,  0.5f,
	   -0.5f,  0.5f,  0.5f,

		0.5f,  0.5f,  0.5f,
		0.5f,  0.5f, -0.5f,
		0.5f, -0.5f, -0.5f,
		0.5f, -0.5f, -0.5f,
		0.5f, -0.5f,  0.5f,
		0.5f,  0.5f,  0.5f,

	   -0.5f, -0.5f, -0.5f,
		0.5f, -0.5f, -0.5f,
		0.5f, -0.5f,  0.5f,
		0.5f, -0.5f,  0.5f,
	   -0.5f, -0.5f,  0.5f,
	   -0.5f, -0.5f, -0.5f,

	   -0.5f,  0.5f, -0.5f,
		0.5f,  0.5f, -0.5f,
		0.5f,  0.5f,  0.5f,
		0.5f,  0.5f,  0.5f,
	   -0.5f,  0.5f,  0.5f,
	   -0.5f,  0.5f, -0.5f,
};

GLFWwindow* init();
void VAOSet();
void light_VAO_init();
void texture(Shader * myShader);

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* windows); // 键盘操作 旋转
void mouse_callback(GLFWwindow* windows, double xpose, double ypose); // 鼠标操作
void scroll_callback(GLFWwindow* windows, double xoffset, double yoffset); //滚轴操作 

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

// camera
Camera camera(glm::vec3(0.0f, 0.0f, 6.0f));
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

// timing
float deltaTime = 0.0f;
float lastFrameTime = 0.0f;
float currentFrameTime = glfwGetTime();

// lighting 
glm::vec3 lightPos(1.2f, 1.0f, 2.0f);

//VBO VAO
unsigned int VBO, cubeVAO, lightVAO;

int main()
{
	// 初始化
	GLFWwindow* windows = init();
	glEnable(GL_DEPTH_TEST); // 深度

	VAOSet();
	//light_VAO_init();
	Shader myShader("4.0.shader.vs","4.0.shader.fs");
	texture(&myShader);

	// 渲染引擎
	while (!glfwWindowShouldClose(windows))
	{
		currentFrameTime = glfwGetTime();
		deltaTime = currentFrameTime - lastFrameTime;
		lastFrameTime = currentFrameTime;

		processInput(windows); // wsad 控制处理函数
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f); // 设置窗口背景颜色
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  //  填充颜色

		for (size_t i = 0; i < 3; i++)
		{
			glm::mat4 trans = glm::mat4(1.0f);
			// 模型矩阵
			glm::mat4 model = glm::mat4(1.0f);
			model = glm::translate(trans, cubePositon[i]); //  平移
			//model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f)); // 绕x轴旋转 45°
			model = glm::rotate(model, (float)glfwGetTime(), glm::vec3(0.5f, 1.0f, 0.0f));   // 随时间旋转
			// 视图矩阵
			glm::mat4 view = glm::mat4(1.0f); // 需要初始化
			view = camera.GetViewMatirx();
			//view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
			// 投影矩阵
			glm::mat4 projection = glm::mat4(1.0f);
			projection = glm::perspective(glm::radians(camera.Zoom), 800.0f / 600.0f, 0.1f, 100.0f);
			trans = projection * view * model;

			myShader.userShader();
			glUniformMatrix4fv(glGetUniformLocation(myShader.ID, "transform"), 1, GL_FALSE, glm::value_ptr(trans));
			glDrawArrays(GL_TRIANGLES, 0, 36); // 读取三个点，进行绘制 画三角
		}

		//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL); //使用索引绘制
		glfwSwapBuffers(windows);
		glfwPollEvents(); // 接受事件
	}
	// optional: de-allocate all resources once they've outlived their purpose:
	glDeleteVertexArrays(1, &cubeVAO);
	glDeleteVertexArrays(1, &lightVAO);
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
	windows = glfwCreateWindow(800, 600, "OPENGL - LEARN", NULL, NULL);
	if (windows == NULL) {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
	}
	glfwMakeContextCurrent(windows); // 上下文关联 windows
	glfwSetFramebufferSizeCallback(windows, framebuffer_size_callback);
	glfwSetScrollCallback(windows, scroll_callback);   // 
	glfwSetCursorPosCallback(windows, mouse_callback); // 设置光标回调函数
	// tell GLFW to capture our mouse
	glfwSetInputMode(windows, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) { //  GLAD 初始化 
		// 初始化 glad
		std::cout << "Failed to initialize GLAD" << std::endl;
	}
	return windows;
}

void VAOSet()
{
	unsigned int VBO, VAO, EBO; // I顶点数组对象   顶点缓冲对象

	// 生成 VAO 
	glGenVertexArrays(1, &VAO);
	// 绑定 VAO
	glBindVertexArray(VAO);

	glGenBuffers(1, &VBO); // 显存空间
	//glGenBuffers(1, &EBO); // 显存空间

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	
	// 绑定VBO数据
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	// 告诉 着色器 VBO的结构 - 位置属性 0：VAO的第一个位置 ；3：（xyz）； 值类型： float；  是否标准化 ； 大小-步长； 偏移VBO的位置-- VBO中在前，偏移量为0 
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	// 启用 VAO 的第0个位置
	glEnableVertexAttribArray(0);

	// 纹理坐标
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	// 启用 VAO 的第1个位置
	glEnableVertexAttribArray(1);
}

void light_VAO_init()
{
	// first, configure the cube's VAO (and VBO)
	glGenVertexArrays(1, &cubeVAO);
	glGenBuffers(1, &VBO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_light), vertices_light, GL_STATIC_DRAW);
	glBindVertexArray(cubeVAO);
	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// second, configure the light's VAO (VBO stays the same; the vertices are the same for the light object which is also a 3D cube)
	glGenVertexArrays(1, &lightVAO);
	glBindVertexArray(lightVAO);
	// we only need to bind to the VBO (to link it with glVertexAttribPointer), no need to fill it; the VBO's data already contains all we need (it's already bound, but we do it again for educational purposes)
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
}

void texture(Shader *myShader)
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

	myShader->userShader();
	glUniform1i(glGetUniformLocation(myShader->ID, "ourTexture1"), 0); // 设置纹理单元
	glUniform1i(glGetUniformLocation(myShader->ID, "ourTexture2"), 1); 

	glActiveTexture(GL_TEXTURE0); // 先激活再绑定 纹理单元0 默认是激活的
	glBindTexture(GL_TEXTURE_2D, texture[0]);

	glActiveTexture(GL_TEXTURE1); // 纹理单元
	glBindTexture(GL_TEXTURE_2D, texture[1]);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}

//键盘 转换相机位置（视角）
void processInput(GLFWwindow* windows)
{
	if (glfwGetKey(windows, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(windows, true); // esc 退出窗口
	}

	// Camrea Proceckeyboard 函数
	if (glfwGetKey(windows, GLFW_KEY_W) == GLFW_PRESS)
		camera.ProcessKeyboard(FORWARD, deltaTime);
	if (glfwGetKey(windows, GLFW_KEY_S) == GLFW_PRESS)
		camera.ProcessKeyboard(BACKWARD, deltaTime);
	if (glfwGetKey(windows, GLFW_KEY_A) == GLFW_PRESS)
		camera.ProcessKeyboard(LEFT, deltaTime);
	if (glfwGetKey(windows, GLFW_KEY_D) == GLFW_PRESS)
		camera.ProcessKeyboard(RIGHT, deltaTime);
}

// 鼠标回调函数
void mouse_callback(GLFWwindow* windows, double xpose, double ypose)
{
	static float xoffset = 0.0f, yoffset = 0.0f;
	if (firstMouse) {
		lastX = xpose;
		lastY = ypose;
		firstMouse = false;
	}
	xoffset = xpose - lastX;
	yoffset = lastY - ypose;  // 屏幕坐标时 左上为原点
	lastX = xpose ;
	lastY = ypose;
	camera.ProcessMouseMovement(xoffset, yoffset);
}

// 滚轴回调函数
void scroll_callback(GLFWwindow* windows, double xoffset, double yoffset) 
{
	camera.ProcessScrollMovement(yoffset);
}