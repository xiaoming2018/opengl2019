#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Shader.h"
#include "stb_image.h"
#include "Camera.h"

float vertices_light[] = {
	// positions          // normals           // texture coords
	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
	 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
	-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,

	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,

	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
	-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

	 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,

	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f
};

void texture(Shader *myShader);

GLFWwindow* init();
void light_VAO_init();
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* windows); // ���̲��� ��ת
void mouse_callback(GLFWwindow* windows, double xpose, double ypose); // ������
void scroll_callback(GLFWwindow* windows, double xoffset, double yoffset); //������� 

const unsigned int SCR_WIDTH = 1280;
const unsigned int SCR_HEIGHT = 720;
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
//glm::vec3 lightPos(1.2f, 1.0f, 2.0f);
glm::vec3 lightPos(2.0f, 0.0f, 0.0f);
//VBO VAO
unsigned int VBO, cubeVAO, lightVAO;
int main()
{
	// ��ʼ��
	GLFWwindow* windows = init();

	// configure global opengl state
	glEnable(GL_DEPTH_TEST); // ��Ȳ���
	glDepthFunc(GL_LESS); // ��Ƭ�����ֵС�ڻ�������ֵʱͨ������
	glEnable(GL_STENCIL_TEST);  // ģ�����
	glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
	glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);

	Shader lightingShader("1.cube.vs", "1.cube.fs");
	Shader lampShader("1.lamp.vs", "1.lamp.fs");
	light_VAO_init();
	texture(&lightingShader);

	while (!glfwWindowShouldClose(windows))
	{
		currentFrameTime = glfwGetTime();
		deltaTime = currentFrameTime - lastFrameTime;
		lastFrameTime = currentFrameTime;

		processInput(windows); // wsad ���ƴ�����
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f); // ���ô��ڱ�����ɫ
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  //  �����ɫ

		// be sure to activate shader when setting uniforms/drawing objects
		lightingShader.userShader();
		lightingShader.setVec3("objectColor", 1.0f, 0.5f, 0.31f);
		lightingShader.setVec3("lightColor", glm::vec3(1.0f, 1.0f, 1.0f));
		//lightingShader.setVec3("lightPos", 1.0f + sin(glfwGetTime()) * 2.0f, sin(glfwGetTime() / 2.0f) * 1.0f, sin(glfwGetTime()) * 1.3f);
		lightingShader.setVec4("lightPos", glm::vec4(lightPos,1));
		lightingShader.setVec3("viewPos", camera.Position);
		lightingShader.setVec3("front", camera.Front);

		// view/projection transformations
		glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
		glm::mat4 view = camera.GetViewMatirx();
		lightingShader.setMat4("projection", projection);
		lightingShader.setMat4("view", view);

		// world transformation
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
		model = glm::rotate(model, (float)glfwGetTime(), glm::vec3(1.0f, 1.0f, 0.0f));
		lightingShader.setMat4("model", model);

		// render the cube
		glBindVertexArray(cubeVAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);
        
		//�ڶ���cube
		glm::mat4 trans = glm::mat4(1.0f);
		model = glm::translate(trans, glm::vec3(-2.0f, 1.0f, 0.0f));
		//model = glm::rotate(model,glm::radians(-55.0f), glm::vec3(1.0f, 1.0f, 0.0f));
		lightingShader.setMat4("model", model);
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// also draw the lamp object
		lampShader.userShader();
		lampShader.setMat4("projection", projection);
		lampShader.setMat4("view", view);
		lampShader.setVec3("lightColor", glm::vec3(1.0f, 1.0f, 1.0f));
		model = glm::mat4(1.0f);
		model = glm::translate(model, lightPos);
		model = glm::scale(model, glm::vec3(0.2f)); // a smaller cube
		lampShader.setMat4("model", model);

		glBindVertexArray(lightVAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);

		//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL); //ʹ����������
		glfwSwapBuffers(windows);
		glfwPollEvents(); // �����¼�
	}
	// optional: de-allocate all resources once they've outlived their purpose:
	glDeleteVertexArrays(1, &cubeVAO);
	glDeleteVertexArrays(1, &lightVAO);
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
	windows = glfwCreateWindow(800, 600, "OPENGL - LEARN", NULL, NULL);
	if (windows == NULL) {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
	}
	glfwMakeContextCurrent(windows); // �����Ĺ��� windows
	glfwSetFramebufferSizeCallback(windows, framebuffer_size_callback);
	glfwSetScrollCallback(windows, scroll_callback);   // 
	glfwSetCursorPosCallback(windows, mouse_callback); // ���ù��ص�����

	// tell GLFW to capture our mouse
	glfwSetInputMode(windows, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) { //  GLAD ��ʼ�� 
		// ��ʼ�� glad
		std::cout << "Failed to initialize GLAD" << std::endl;
	}
	return windows;
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
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	
	// ����
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3*sizeof(float)));
	glEnableVertexAttribArray(1);
	
	// ��������
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	// second, configure the light's VAO (VBO stays the same; the vertices are the same for the light object which is also a 3D cube)
	glGenVertexArrays(1, &lightVAO);
	glBindVertexArray(lightVAO);
	// we only need to bind to the VBO (to link it with glVertexAttribPointer), no need to fill it; the VBO's data already contains all we need (it's already bound, but we do it again for educational purposes)
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
}

void texture(Shader *myShader)
{
	int width, height, nrchannels;
	unsigned char * data = NULL;
	stbi_set_flip_vertically_on_load(true);  // ʵ��y��ķ�ת

	unsigned int texture[2];
	glGenTextures(2, texture);

	// ���ص�һ������
	glBindTexture(GL_TEXTURE_2D, texture[0]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);// ����Ŵ�ʱ ʹ�� ���ԭ�����
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); // ������Сʱ ʹ�� ���ԭ�����
	data = stbi_load("container2.png", &width, &height, &nrchannels, 0);
	GLenum format;
	if (nrchannels == 1) {
		format = GL_RED;
	}
	else if (nrchannels == 3) {
		format = GL_RGB;
	}
	else if (nrchannels == 4) {
		format = GL_RGBA;
	}
	glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);
	stbi_image_free(data);

	// ���صڶ������� ����ͼƬ̫С ����ش���
	glBindTexture(GL_TEXTURE_2D, texture[1]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);// ����Ŵ�ʱ ʹ�� ���ԭ�����
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); // ������Сʱ ʹ�� ���ԭ�����
	data = stbi_load("container2_specular.png", &width, &height, &nrchannels, 0);
	if (nrchannels == 1) {
		format = GL_RED;
	}
	else if (nrchannels == 3) {
		format = GL_RGB;
	}
	else if (nrchannels == 4) {
		format = GL_RGBA;
	}
	glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
	// glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data); // png ��ʽ  ����͸���Ȳ���
	glGenerateMipmap(GL_TEXTURE_2D);
	stbi_image_free(data);

	myShader->userShader();
	glUniform1i(glGetUniformLocation(myShader->ID, "ourTexture1"), 0);
	glUniform1i(glGetUniformLocation(myShader->ID, "ourTexture2"), 1);

	glActiveTexture(GL_TEXTURE0); // �ȼ����ٰ� ����Ԫ0 Ĭ���Ǽ����
	glBindTexture(GL_TEXTURE_2D, texture[0]);

	glActiveTexture(GL_TEXTURE1); // ����Ԫ
	glBindTexture(GL_TEXTURE_2D, texture[1]);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}

//���� ת�����λ�ã��ӽǣ�
void processInput(GLFWwindow* windows)
{
	if (glfwGetKey(windows, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(windows, true); // esc �˳�����
	}

	// Camrea Proceckeyboard ����
	if (glfwGetKey(windows, GLFW_KEY_W) == GLFW_PRESS)
		camera.ProcessKeyboard(FORWARD, deltaTime);
	if (glfwGetKey(windows, GLFW_KEY_S) == GLFW_PRESS)
		camera.ProcessKeyboard(BACKWARD, deltaTime);
	if (glfwGetKey(windows, GLFW_KEY_A) == GLFW_PRESS)
		camera.ProcessKeyboard(LEFT, deltaTime);
	if (glfwGetKey(windows, GLFW_KEY_D) == GLFW_PRESS)
		camera.ProcessKeyboard(RIGHT, deltaTime);
}

// ���ص�����
void mouse_callback(GLFWwindow* windows, double xpose, double ypose)
{
	static float xoffset = 0.0f, yoffset = 0.0f;
	if (firstMouse) {
		lastX = xpose;
		lastY = ypose;
		firstMouse = false;
	}
	xoffset = xpose - lastX;
	yoffset = lastY - ypose;  // ��Ļ����ʱ ����Ϊԭ��
	lastX = xpose ;
	lastY = ypose;
	camera.ProcessMouseMovement(xoffset, yoffset);
}

// ����ص�����
void scroll_callback(GLFWwindow* windows, double xoffset, double yoffset) 
{
	camera.ProcessScrollMovement(yoffset);
}