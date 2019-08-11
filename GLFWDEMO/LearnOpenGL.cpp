#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Shader.h"
#include "stb_image.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>  // ���� glm ��

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

// EBO ��������
unsigned int indices[] = {
	0,1,3,
	1,2,3
};

void init();
void VAOSet();
void texture(Shader &myShader);

int main()
{
	//// ������ ��ʾ
	//glm::vec4 vec(1.0f, 0.0f, 0.0f, 1.0f);
	//glm::mat4 trans = glm::mat4(1.0f);
	//trans = glm::translate(trans, glm::vec3(1.0f, 1.0f, 0.0f));
	//vec = trans * vec;
	//cout << " x: " <<vec.x << vec.y << vec.z << endl;

	//glm::mat4 trans = glm::mat4(1.0f);
	//trans = glm::rotate(trans, glm::radians(90.0f),glm::vec3(0.0f,0.0f,1.0f)); // ���� �� �ο���
	//trans = glm::scale(trans, glm::vec3(0.5f, 0.5f, 0.5f));

	// ��ʼ��
	init();
	VAOSet();

	Shader myShader;
	texture(myShader);

	glEnable(GL_DEPTH_TEST); // ���

	// ��Ⱦ����
	while (!glfwWindowShouldClose(windows))
	{
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f); // ���ô��ڱ�����ɫ
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  //  �����ɫ

		for (size_t i = 0; i < 3; i++)
		{
			glm::mat4 trans = glm::mat4(1.0f);
			glm::mat4 model = glm::mat4(1.0f);  // ģ�;���
			model = glm::translate(trans, cubePositon[i]); //  ƽ��
			//model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f)); // ��x����ת 45��
			model = glm::rotate(model, (float)glfwGetTime(), glm::vec3(0.5f, 1.0f, 0.0f));   // ��ʱ����ת

			glm::mat4 view = glm::mat4(1.0f); // ��Ҫ��ʼ��
			view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));

			glm::mat4 projection = glm::mat4(1.0f);
			projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);
			trans = projection * view * model;

			myShader.userShader();
			glUniformMatrix4fv(glGetUniformLocation(myShader.ID, "transform"), 1, GL_FALSE, glm::value_ptr(trans));

			glDrawArrays(GL_TRIANGLES, 0, 36); // ��ȡ�����㣬���л��� ������
		}
		//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL);

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

	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	// ���� ��ɫ�� VBO�Ľṹ - λ������ 0��VAO�ĵ�һ��λ�� ��3����xyz���� ֵ���ͣ� float��  �Ƿ��׼�� �� ��С-������ ƫ��VBO��λ��-- VBO����ǰ��ƫ����Ϊ0 
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	// ���� VAO �ĵ�һ��λ��
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
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

void texture(Shader &myShader)
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


	myShader.userShader();
	glUniform1i(glGetUniformLocation(myShader.ID, "ourTexture1"), 0);
	glUniform1i(glGetUniformLocation(myShader.ID, "ourTexture2"), 1);

	glActiveTexture(GL_TEXTURE0); // �ȼ����ٰ� ����Ԫ0 Ĭ���Ǽ����
	glBindTexture(GL_TEXTURE_2D, texture[0]);

	glActiveTexture(GL_TEXTURE1); // ����Ԫ
	glBindTexture(GL_TEXTURE_2D, texture[1]);
}