#pragma once
#ifndef MODEL_H
#define MODEL_H
#include <glad/glad.h> 
#include "Shader.h"
#include "mesh.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>  // ���� glm ��
#include "stb_image.h"

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <map>
#include <vector>
using namespace std;


class Model
{
public:
	/*  ����   */
	Model(char *path)
	{
		loadModel(path);
	}
	void Draw(Shader shader);
private:
	/*  ģ������  */
	vector<Mesh> meshes;
	string directory;
	/*  ����   */
	void loadModel(string path);
	//void processNode(aiNode *node, const aiScene *scene);
	//Mesh processMesh(aiMesh *mesh, const aiScene *scene);
	//vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, string typeName);
};

#endif // !MODEL_H
