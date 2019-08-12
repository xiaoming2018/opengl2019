#pragma once
#ifndef CAMERA_H
#define CAMEAR_H
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>  // 导入 glm 库

class Camera
{
public:
	glm::vec3 Positon, Front, Up;
	float Pitch, Yaw, Fov;

public:
	Camera();
	glm::mat4 GetViewMatirx() 
	{
		return glm::lookAt(Positon, Positon + Front, Up);
	};
	void ProcessMouseMovement(float xoffset, float yoffset)
	{
		Yaw += xoffset * 0.1;
		Pitch += yoffset * 0.1;
		// 防止反转 
		if (Pitch > 89.0f)
		{
			Pitch = 89.0f;
		}
		if (Pitch < -89.0f)
		{
			Pitch = -89.0f;
		}

		glm::vec3 front(1.0f);
		front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
		front.y = sin(glm::radians(Pitch));
		front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
	    Front = glm::normalize(front);
	}

	void ProcessScrollMovement(float yoffset) {

		if (Fov >= 20.0f && Fov <= 85.0f) {
			Fov -= yoffset;
		}
		if (Fov <= 20.0f) {
			Fov = 20.0f;
		}
		if (Fov >= 85.0f) {
			Fov = 85.0f;
		}
	}
	~Camera();

private:
	
};

Camera::Camera()
{
	Positon = glm::vec3(0.0f, 0.0f, 3.0f);
	Front = glm::vec3(0.0f, 0.0f, -1.0f);
	Up = glm::vec3(0.0f, 1.0f, 0.0f);
	this->Yaw = -90.0f;
	this->Pitch = 0.0f;
	this->Fov = 45.0f;
}

Camera::~Camera()
{
}

#endif // !
