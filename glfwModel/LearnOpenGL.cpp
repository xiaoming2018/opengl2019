#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Shader.h"
#include "stb_image.h"
#include "Camera.h"
#include "mesh.h"
#include "model.h"

//float vertices_light[] = {
//	// positions          // normals           // texture coords
//	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
//	 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f,
//	 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
//	 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
//	-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f,
//	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
//
//	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,
//	 0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 0.0f,
//	 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
//	 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
//	-0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 1.0f,
//	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,
//
//	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
//	-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
//	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
//	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
//	-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
//	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
//
//	 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
//	 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
//	 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
//	 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
//	 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
//	 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
//
//	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
//	 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f,
//	 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
//	 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
//	-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f,
//	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
//
//	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f,
//	 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 1.0f,
//	 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
//	 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
//	-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f,
//	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f
//};

GLFWwindow* init();


void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* windows); // ���̲��� ��ת
void mouse_callback(GLFWwindow* windows, double xpose, double ypose); // ������
void scroll_callback(GLFWwindow* windows, double xoffset, double yoffset); //������� 

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;
// camera
Camera camera(glm::vec3(0.0f, 5.0f, 20.0f));
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;
// timing
float deltaTime = 0.0f;
float lastFrameTime = 0.0f;
float currentFrameTime = glfwGetTime();

int main()
{
	// ��ʼ��
	GLFWwindow* windows = init();
	
	// config global opengl state
	glEnable(GL_DEPTH_TEST); // ��Ȼ���
	Shader lightingShader("1.cube.vs", "1.cube.fs");

	//Mesh mesh = processMesh();
	//char path[255] = "F:/Program/Visual Studio 2017/projects/GLFWDEMO/glfwModel/nanosuit/nanosuit.obj";
	Model ourModel("nanosuit/nanosuit.obj");

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
		lightingShader.setVec4("lightPos", glm::vec4(2.0f,0.0f,0.0f, 1));
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
		model = glm::rotate(model, (float)glfwGetTime(), glm::vec3(0.0f, 1.0f, 0.0f));
		lightingShader.setMat4("model", model);
		
		//mesh.Draw(lightingShader);
		ourModel.Draw(lightingShader);

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
	lastX = xpose;
	lastY = ypose;
	camera.ProcessMouseMovement(xoffset, yoffset);
}

// ����ص�����
void scroll_callback(GLFWwindow* windows, double xoffset, double yoffset)
{
	camera.ProcessScrollMovement(yoffset);
}

//Mesh processMesh()
//{
//	vector<Vertex> vertices;
//	vector<unsigned int> indices;
//	vector<Texture> textures;
//	for (int i = 0; i < 36; i++)
//	{
//		Vertex ver;
//		ver.Position[0] = vertices_light[i * 8 + 0];
//		ver.Position[1] = vertices_light[i * 8 + 1];
//		ver.Position[2] = vertices_light[i * 8 + 2];
//		ver.Normal[0] = vertices_light[i * 8 + 3];
//		ver.Normal[1] = vertices_light[i * 8 + 4];
//		ver.Normal[2] = vertices_light[i * 8 + 5];
//		ver.TexCoords[0] = vertices_light[i * 8 + 6];
//		ver.TexCoords[1] = vertices_light[i * 8 + 7];
//		vertices.push_back(ver);
//	}
//	for (int i = 0; i < 36; i++)
//	{
//		indices.push_back(i);
//	}
//	Texture texture;
//	texture.id = 1;
//	texture.type = "texture_diffuse";
//	texture.path = "container2.png";
//	textures.push_back(texture);
//
//	texture.id = 2;
//	texture.type = "texture_specular";
//	texture.path = "container2_specular.png";
//	textures.push_back(texture);
//
//	unsigned int texture_num[100];
//	for (unsigned int i = 0; i < textures.size(); i++)
//	{
//		glGenTextures(1, &texture_num[i]);
//		int width, height, nrchannels;
//		unsigned char * data = NULL;
//		stbi_set_flip_vertically_on_load(true);  // ʵ��y��ķ�ת
//		glBindTexture(GL_TEXTURE_2D, texture_num[i]);
//		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);// ����Ŵ�ʱ ʹ�� ���ԭ�����
//		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); // ������Сʱ ʹ�� ���ԭ�����
//		data = stbi_load(textures[i].path.c_str(), &width, &height, &nrchannels, 0);
//		GLenum format;
//		if (nrchannels == 1) {
//			format = GL_RED;
//		}
//		else if (nrchannels == 3) {
//			format = GL_RGB;
//		}
//		else if (nrchannels == 4) {
//			format = GL_RGBA;
//		}
//		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
//		glGenerateMipmap(GL_TEXTURE_2D);
//		stbi_image_free(data);
//	}
//
//	Mesh mesh(vertices, indices, textures);
//	return mesh;
//}