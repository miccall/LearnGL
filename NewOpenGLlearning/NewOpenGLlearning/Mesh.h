#pragma once
#include "MyGLLib.h"

namespace miccall {

	struct Vertex
	{
		// position
		glm::vec3 Position;
		// normal
		glm::vec3 Normal;
		// texCoords
		glm::vec2 TexCoords;
		// tangent
		glm::vec3 Tangent;
		// bitangent
		glm::vec3 Bitangent;
	};

	struct Texture
	{
		unsigned int id;
		string type;
		aiString path;
	};

	class Mesh
	{
	public:
		/*  网格数据  */
		
		vector<Vertex> vertices;
		vector<unsigned int> indices;
		vector<Texture> textures;
		/*  渲染数据  */
		unsigned int VAO, VBO, EBO;

		/*  函数  */
		Mesh(vector<Vertex> vertices, vector<unsigned int> indices, vector<Texture> textures);
		void Draw(Shader shader);
	private:

		/*  函数  */
		void setupMesh();

	};

	class Model
	{

		public:
			/*  Model Data */
			vector<Texture> textures_loaded;	// stores all the textures loaded so far, optimization to make sure textures aren't loaded more than once.
			vector<Mesh> meshes;
			string directory;
			bool gammaCorrection;

			/*  Functions   */
			// constructor, expects a filepath to a 3D model.
			Model(string const &path, bool gamma = false) : gammaCorrection(gamma)
			{
				loadModel(path);
			}

			void Draw(Shader shader);

		private:

			/*  函数   */
			void loadModel(string const &path);
			
			void processNode(aiNode *node, const aiScene *scene);
			Mesh processMesh(aiMesh *mesh, const aiScene *scene);
			vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type,
				string typeName);
	};


	//渲染一个mesh
	void RenderCube(Shader shader, Model mesh, glm::vec3 pos, glm::vec3 scale);
}


