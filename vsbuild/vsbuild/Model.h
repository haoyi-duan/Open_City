#ifndef _MODEL_H_
#define _MODEL_H_


#include "Const.h"
#include "Mesh.h"
#include "Shader.h"

GLuint textureFromFile(const GLchar * path, const string & directory, GLboolean gamma = false);

class Model
{
public:
	// ************************* model 的数据类型 ************************* //
	// ******************************************************************** //

	// 存储当前所有已经加载的纹理，优化以确保纹理不会加载超过一次
	// ----------------------------------------------------------
	vector<textureAddr> texturesLoaded;	
	vector<Mesh>        meshes;
	string              directory;
	GLboolean           gammaCorrection;

	// 构造函数，接收一个 3D model 的文件路径
	// ------------------------------------------------------------------------
	Model(string const & path, GLboolean gamma = false) : gammaCorrection(gamma) { loadModel(path); };

	// 绘制模型的所有网格
	// ---------------------
	void draw(Shader &shader);

private:
	// 从文件中加载一个 ASSIMP 扩展支持的模型，把生成的网格存储在网格向量中
	// --------------------------------------------------------------------
	GLvoid loadModel(string const & path);

	// 循环生成 mesh
	// --------------------------------------------------
	GLvoid processNode(aiNode * node, const aiScene * scene);

	Mesh processMesh(aiMesh * mesh, const aiScene * scene);

	// 检查给定类型的所有材料纹理，如果尚未加载，则加载纹理
	// --------------------------------------------------------------------------------------------
	vector<textureAddr> loadMaterialTextures(aiMaterial * mat, aiTextureType type, string typeName);
};

#endif // !_MODEL_H_

