#include "Model.h"

// 绘制模型的所有网格
// ---------------------
GLvoid Model::draw(Shader & shader)
{
	for (unsigned int i = 0; i < meshes.size(); i++)
		meshes[i].draw(shader);
}

// 从文件中加载一个 ASSIMP 扩展支持的模型，把生成的网格存储在网格向量中
// --------------------------------------------------------------------
GLvoid Model::loadModel(string const & path)
{
	// 通过 Assimp 读取文件
	// -----------------------
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);

	// 检查错误并输出错误信息（如果有的话）
	// --------------------------------------------------------------------------
	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
	{
		cout << "ERROR::ASSIMP::FAILED" << endl;
		cout << importer.GetErrorString() << endl;
		exit(-1);
	}

	// 读取文件相对路径
	// ------------------------------------------------
	directory = path.substr(0, path.find_last_of('/'));

	// 生成 mesh
	// ----------------------------------
	processNode(scene->mRootNode, scene);
}


// 循环生成 mesh
// -------------------------------------------------
GLvoid Model::processNode(aiNode * node, const aiScene * scene)
{
	// 处理当前节点上的 mesh
	// ---------------------------------------
	for (unsigned int i = 0; i < node->mNumMeshes; i++)
	{
		// ----------------------------------------------------------- //
		// 节点对象仅包含对场景中实际对象进行索引的 indices; --------- //
		// scene 包含了所有的数据，使用节点只是为了更加的规整，------- //
		// 可以用节点之间的相互关系进行索引和查找 -------------------- //
		// ----------------------------------------------------------- //
		aiMesh * mesh = scene->mMeshes[node->mMeshes[i]];
		meshes.push_back(processMesh(mesh, scene));
	}

	// 当已经处理所有的 mesh (如果有的话)，我们之后将递归操作孩子节点
	// --------------------------------------------------------------
	for (unsigned int i = 0; i < node->mNumChildren; i++)
	{
		processNode(node->mChildren[i], scene);
	}
}

Mesh Model::processMesh(aiMesh * mesh, const aiScene * scene)
{
	// 需要填充的数据
	// ----------------------------
	vector<vertexAddr>    vertices;
	vector<GLuint>        indices;
	vector<textureAddr>   textures;

	// 遍历
	// --------------------------------------------------
	for (unsigned int i = 0; i < mesh->mNumVertices; i++)
	{
		// ---------------------------------------------------------------- //
		// 因为 assimp 使用自己的矢量类，不会直接转换为 glm 的 vec3 类，--- //
		// 因此首先将数据传输到此 vec3 vector ----------------------------- //
		// ---------------------------------------------------------------- //
		vertexAddr vertex;
		vec3 vector;

		// positions
		// -----------------------------
		vector.x = mesh->mVertices[i].x;
		vector.y = mesh->mVertices[i].y;
		vector.z = mesh->mVertices[i].z;
		vertex.position = vector;

		// normals
		// --------------------
		if (mesh->HasNormals())
		{
			vector.x = mesh->mNormals[i].x;
			vector.y = mesh->mNormals[i].y;
			vector.z = mesh->mNormals[i].z;
			vertex.normal = vector;
		}

		// texture coordinates
		// -------------------------
		if (mesh->mTextureCoords[0])
		{
			vec2 vec2;

			// ------------------------------------------------------------- //
			// 顶点可以包含多达 8 种不同的纹理坐标。------------------------ //
			// 因此，我们假设我们不会使用顶点可以具有多个纹理坐标的模型，--- //
			// 因此我们始终采用第一组 （0）。------------------------------- //
			// ------------------------------------------------------------- //
			vec2.x = mesh->mTextureCoords[0][i].x;
			vec2.y = mesh->mTextureCoords[0][i].y;
			vertex.texCoords = vec2;

			// tangent
			// -----------------------------
			vector.x = mesh->mTangents[i].x;
			vector.y = mesh->mTangents[i].y;
			vector.z = mesh->mTangents[i].z;
			vertex.tangent = vector;

			// bitangent
			// -------------------------------
			vector.x = mesh->mBitangents[i].x;
			vector.y = mesh->mBitangents[i].y;
			vector.z = mesh->mBitangents[i].z;
			vertex.bitangent = vector;
		}
		else
			vertex.texCoords = vec2(0.0f, 0.0f);

		vertices.push_back(vertex);
	}

	// 现在遍历网格的每一个面，并检索相应的顶点参数
	// -----------------------------------------------
	for (unsigned int i = 0; i < mesh->mNumFaces; i++)
	{
		aiFace face = mesh->mFaces[i];
		for (unsigned int j = 0; j < face.mNumIndices; j++)
			indices.push_back(face.mIndices[j]);
	}

	// 处理材质
	// ------------------------------------------------------------
	aiMaterial * material = scene->mMaterials[mesh->mMaterialIndex];

	// ------------------------------- //
	// 命名格式如下所示：------------- //
	// diffuse: texture_diffuseN ----- //
	// specular: texture_specularN --- //
	// normal: texture_normalN ------- //
	// ------------------------------- //

	// ************************* 1. diffuse maps ************************* //
	// ******************************************************************* //
	vector<textureAddr> diffuseMaps = loadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
	textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());

	// ************************* 2. specular maps ************************* //
	// ******************************************************************** //
	vector<textureAddr> specularMaps = loadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");
	textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());

	// ************************* 3. normal maps ************************* //
	// ****************************************************************** //
	vector<textureAddr> normalMaps = loadMaterialTextures(material, aiTextureType_HEIGHT, "texture_normal");
	textures.insert(textures.end(), normalMaps.begin(), normalMaps.end());
	
	// ************************* 4. height maps ************************* //
	// ****************************************************************** //
	vector<textureAddr> heightMaps = loadMaterialTextures(material, aiTextureType_AMBIENT, "texture_height");
	textures.insert(textures.end(), heightMaps.begin(), heightMaps.end());

	return Mesh(vertices, textures, indices);
}

// 检查给定类型的所有材料纹理，如果尚未加载，则加载纹理
// -------------------------------------------------------------------------------------------
vector<textureAddr> Model::loadMaterialTextures(aiMaterial * mat, aiTextureType type, string typeName)
{
	vector<textureAddr> textures;
	for (unsigned int i = 0; i < mat->GetTextureCount(type); i++)
	{
		aiString str;
		mat->GetTexture(type, i, &str);

		bool skip = false;
		for (unsigned int j = 0; j < texturesLoaded.size(); j++)
		{
			if (strcmp(texturesLoaded[j].path.data(), str.C_Str()) == 0)
			{
				textures.push_back(texturesLoaded[j]);
				skip = true;
				break;
			}
		}
		if (!skip)
		{
			textureAddr texture;
			texture.id = textureFromFile(str.C_Str(), this->directory);
			texture.type = typeName;
			texture.path = str.C_Str();
			textures.push_back(texture);
			
			texturesLoaded.push_back(texture);
		}
	}
	return textures;
}

GLuint textureFromFile(const GLchar * path, const string & directory, GLboolean gamma)
{
	string filename = string(path);
	filename = directory + '/' + filename;

	GLuint textureID;
	glGenTextures(1, &textureID);

	GLint width, height, nrComponents;
	stbi_uc * data = stbi_load(filename.c_str(), &width, &height, &nrComponents, 0);

	if (data)
	{
		GLenum format;
		if (nrComponents == 1)
			format = GL_RED;
		else if (nrComponents == 3)
			format = GL_RGB;
		else if (nrComponents == 4)
			format = GL_RGBA;

		glBindTexture(GL_TEXTURE_2D, textureID);
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		stbi_image_free(data);
	}
	else
	{
		cout << "TEXTURE::LOAD::FAILED" << endl;
		cout << "PATH::" << path << endl;
		stbi_image_free(data);
	}

	return textureID;
}
