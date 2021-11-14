#include "Mesh.h"

Mesh::Mesh(vector<vertexAddr> vertices, vector<textureAddr> textures, vector<GLuint> indices)
{
	this->vertices = vertices;
	this->textures = textures;
	this->indices = indices;

	// 获取到所有需要的数据以后，就可以传送到显示列表进行渲染的加速了
	// --------------------------------------------------------------
	setupMesh();
}

// 渲染网格
// ----------------------
GLvoid Mesh::draw(Shader &shader)
{
	// ************************* 绑定纹理 ************************* //
	// ************************************************************ //
	GLuint diffuseNr = 1;
	GLuint specularNr = 1;
	GLuint normalNr = 1;
	GLuint heightNr = 1;

	for (unsigned int i = 0; i < textures.size(); i++)
	{
		// 在绑定前激活相应编号的纹理
		// ------------------------------
		glActiveTexture(GL_TEXTURE0 + i);

		string number;
		string name = textures[i].type;
		if (name == "texture_diffuse")
			number = to_string(diffuseNr++);
		else if (name == "texture_specular")
			number = to_string(specularNr++);
		else if (name == "texture_normal")
			number = to_string(normalNr++);
		else if (name == "texture_height")
			number = to_string(heightNr++);

		glUniform1i(glGetUniformLocation(shader.ID, (name + number).c_str()), i);
		glBindTexture(GL_TEXTURE_2D, textures[i].id);
	}

	// ************************* 画出 mesh ************************* //
	// ************************************************************* //
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);

	// 
	//
	glActiveTexture(GL_TEXTURE0);
}

GLvoid Mesh::setupMesh()
{
	// 创建 buffers / arrays
	// ------------------------ 
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	// 把相关数据存储到 buffer 中
	// --------------------------
	glBindVertexArray(VAO);

	// 把相关数据存储到 buffer 中
	// --------------------------------
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(vertexAddr), &vertices[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), &indices[0], GL_STATIC_DRAW);

	// positions
	// --------------------------
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertexAddr), (GLvoid*)offsetof(vertexAddr, position));

	// normals
	// --------------------------
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(vertexAddr), (GLvoid*)offsetof(vertexAddr, normal));

	// texture coords
	// --------------------------
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(vertexAddr), (GLvoid*)offsetof(vertexAddr, texCoords));

	// tangent
	// --------------------------
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(vertexAddr), (GLvoid*)offsetof(vertexAddr, tangent));

	// bitangent
	// --------------------------
	glEnableVertexAttribArray(4);
	glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(vertexAddr), (GLvoid*)offsetof(vertexAddr, bitangent));

	glBindVertexArray(0);
}

GLuint loadTexture(GLchar const * path)
{
	// 获得纹理 ID
	// --------------
	GLuint textureID;
	glGenTextures(1, &textureID);

	// 用 stbi_load 函数去加载纹理贴图
	// -------------------------------
	GLint width, height, nrComponents;
	stbi_uc * data = stbi_load(path, &width, &height, &nrComponents, 0);
	if (data)
	{
		GLenum format;
		if (nrComponents == 1)
			format = GL_RED;
		else if (nrComponents == 3)
			format = GL_RGB;
		else if (nrComponents == 4)
			format = GL_RGBA;

		// 将纹理绑定到 buffer 中
		// -------------------------------------
		glBindTexture(GL_TEXTURE_2D, textureID);
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		
		// 为当前绑定的纹理自动生成所有需要的多级渐远纹理
		// -----------------------------
		glGenerateMipmap(GL_TEXTURE_2D);

		// Set the behavior when scaling
		// ----------------------------------------------------------
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		// 释放数据并解绑纹理对象
		// -------------------
		stbi_image_free(data);
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	else
	{
		cout << "TEXTURE::LOAD::FAILED" << endl;
		cout << "PATH::" << path << endl;
		stbi_image_free(data);
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	return textureID;
}