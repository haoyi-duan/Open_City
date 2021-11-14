#ifndef _MESH_H_
#define _MESH_H_

#include "Const.h"
#include "Shader.h"

// 表示一个顶点属性
// ------------------------------
struct vertexAddr
{
	vec3 position;
	vec3 normal;
	vec2 texCoords;
	vec3 tangent;
	vec3 bitangent;
};

// 用于表示每一个纹理的数据结构
// --------------------------------
struct textureAddr {
	GLuint  id;
	string type;
	string path;
};

GLuint loadTexture(GLchar const * path);

class Mesh {
public:
	vector<vertexAddr>   vertices;
	vector<textureAddr>  textures;
	vector<GLuint>       indices;
	GLuint               VAO;

	Mesh(vector<vertexAddr> vertices, vector<textureAddr> textures, vector<GLuint> indices);

	// 渲染网格
	// --------------------------
	GLvoid draw(Shader & shader);

private:
	// 渲染参数
	// ------------
	GLuint VBO, EBO;

	GLvoid setupMesh();
};

#endif // !_MESH_H_
