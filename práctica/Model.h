#pragma once
#include <vector>
#include<string>
#include<assimp/Importer.hpp>
#include<assimp/scene.h>
#include<assimp/postprocess.h>
// vec3
#include <glm.hpp>



#include "Mesh.h"
#include "Texture.h"

class Model
{
	public:
		Model();

		void LoadModel(const std::string& fileName);
		void RenderModel();
		void ClearModel();
		glm::vec3 GetModelPosition();
		void SetUniformModel(glm::vec3);
		~Model();

	private:
		glm::vec3 position;
		void LoadNode(aiNode* node, const aiScene* scene); //assimp
		void LoadMesh(aiMesh* mesh, const aiScene* scene);
		void LoadMaterials(const aiScene* scene);
		std::vector<Mesh*>MeshList;
		std::vector<Texture*>TextureList;
		std::vector<unsigned int>meshTotex;
};

