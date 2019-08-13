#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Shader.h"
#include "stb_image.h"
#include "Camera.h"

using namespace std;

// �������� (x,y,z)
float verticesNew[] = {
	-0.5f, -0.5f, 0.0f, 0, 0,		//����
	0.5f, -0.5f, 0.0f, 1, 0,         //����
	0.5f, 0.5f, 0.0f, 1, 1,         //����
	-0.5f, 0.5f, 0.0f, 0, 1   	    //����
};
// 36 ���� �Լ� ��������
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
	glm::vec3(0.0f, 0.0f,  0.0f),
	glm::vec3(2.0f, 5.0f, -15.0f),
	glm::vec3(-2.0f, 3.0f, -7.5f)
};

unsigned int indices[] = {
	0,1,3,
	1,2,3
}; // EBO ��������

GLFWwindow* init();
void VAOSet();
void texture(Shader * myShader);
void processInput(GLFWwindow* windows); // ���̲��� ��ת
void mouse_callback(GLFWwindow* windows, double xpose, double ypose); // ������
void scroll_callback(GLFWwindow* windows, double xoffset, double yoffset); //������� 

Camera camera;
float deltaTime = 0.0f;
float lastFrameTime = 0.0f;
float currentFrameTime = glfwGetTime();

int main()
{
	// ��ʼ��
	GLFWwindow* windows = init();
	VAOSet();
	//Shader myShader;
	Shader myShader("4.0.shader.vs","4.0.shader.fs");
	texture(&myShader);
	glfwSetCursorPosCallback(windows, mouse_callback); // ���ù��ص�����
	glfwSetInputMode(windows, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetScrollCallback(windows, scroll_callback);
	glEnable(GL_DEPTH_TEST); // ���

	// ��Ⱦ����
	while (!glfwWindowShouldClose(windows))
	{
		currentFrameTime = glfwGetTime();
		deltaTime = currentFrameTime - lastFrameTime;
		lastFrameTime = currentFrameTime;

		processInput(windows); // wsad ���ƴ�����
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f); // ���ô��ڱ�����ɫ
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  //  �����ɫ

		for (size_t i = 0; i < 3; i++)
		{
			glm::mat4 trans = glm::mat4(1.0f);
			// ģ�;���
			glm::mat4 model = glm::mat4(1.0f);  
			model = glm::translate(trans, cubePositon[i]); //  ƽ��
			//model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f)); // ��x����ת 45��
			model = glm::rotate(model, (float)glfwGetTime(), glm::vec3(0.5f, 1.0f, 0.0f));   // ��ʱ����ת
			// ��ͼ����
			glm::mat4 view = glm::mat4(1.0f); // ��Ҫ��ʼ��
			view = camera.GetViewMatirx();
			//view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
			// ͶӰ����
			glm::mat4 projection = glm::mat4(1.0f);
			projection = glm::perspective(glm::radians(camera.Fov), 800.0f / 600.0f, 0.1f, 100.0f);
			trans = projection * view * model;

			myShader.userShader();
			glUniformMatrix4fv(glGetUniformLocation(myShader.ID, "transform"), 1, GL_FALSE, glm::value_ptr(trans));

			glDrawArrays(GL_TRIANGLES, 0, 36); // ��ȡ�����㣬���л��� ������
		}
		//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL); //ʹ����������
		glfwSwapBuffers(windows);
		glfwPollEvents(); // �����¼�
	}

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
		cout << "Failed to create GLFW window" << endl;
		glfwTerminate();
	}
	glfwMakeContextCurrent(windows); // �����Ĺ��� windows
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) { //  GLAD ��ʼ�� 
		// ��ʼ�� glad
		cout << "Failed to initialize GLAD" << endl;
	}
	return windows;
}

void VAOSet()
{
	unsigned int VBO, VAO, EBO; // ID ��

	// ���� VAO 
	glGenVertexArrays(1, &VAO);
	// �� VAO
	glBindVertexArray(VAO);

	glGenBuffers(1, &VBO); // �Դ�ռ�
	//glGenBuffers(1, &EBO); // �Դ�ռ�

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	
	// ��VBO����
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	// ���� ��ɫ�� VBO�Ľṹ - λ������ 0��VAO�ĵ�һ��λ�� ��3����xyz���� ֵ���ͣ� float��  �Ƿ��׼�� �� ��С-������ ƫ��VBO��λ��-- VBO����ǰ��ƫ����Ϊ0 
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	// ���� VAO �ĵ�0��λ��
	glEnableVertexAttribArray(0);

	// ��������
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	// ���� VAO �ĵ�1��λ��
	glEnableVertexAttribArray(1);
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
	data = stbi_load("1.jpg", &width, &height, &nrchannels, 0);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);
	stbi_image_free(data);

	// ���صڶ������� ����ͼƬ̫С ����ش���
	glBindTexture(GL_TEXTURE_2D, texture[1]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);// ����Ŵ�ʱ ʹ�� ���ԭ�����
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); // ������Сʱ ʹ�� ���ԭ�����
	data = stbi_load("temp.jpg", &width, &height, &nrchannels, 0);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
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

//���� ת�����λ�ã��ӽǣ�
void processInput(GLFWwindow* windows)
{
	if (glfwGetKey(windows, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(windows, true); // esc �˳�����
	}
	float cameraSpeed = 2.5f * deltaTime;
	if (glfwGetKey(windows, GLFW_KEY_W) == GLFW_PRESS) {
		camera.Positon += cameraSpeed * (camera.Front);
	}
	if (glfwGetKey(windows, GLFW_KEY_S) == GLFW_PRESS) {
		camera.Positon -= cameraSpeed * (camera.Front);
	}
	if (glfwGetKey(windows, GLFW_KEY_A) == GLFW_PRESS) {
		camera.Positon -= glm::normalize(glm::cross(camera.Front, camera.Up)) * cameraSpeed;
	}
	if (glfwGetKey(windows, GLFW_KEY_D) == GLFW_PRESS) {
		camera.Positon += glm::normalize(glm::cross(camera.Front, camera.Up)) * cameraSpeed;
	}
}

// ���ص�����
void mouse_callback(GLFWwindow* windows, double xpose, double ypose)
{
	static float lastX = 800.0f / 2, lastY = 600.0f / 2, xoffset = 0.0f, yoffset = 0.0f;
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