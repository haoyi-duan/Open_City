#ifndef _SHADER_H_
#define _SHADER_H_

#include "Const.h"

class Shader
{
public:
	// shader 的 ID
	// ----------------------------------------------------------------------
	GLuint ID;

	Shader(const GLchar * vertexPath, const GLchar * fragmentPath);
	
	// 激活 shader 着色器
	// ------------------
	GLvoid use()
	{
		glUseProgram(this->ID);
	}

	// utility uniform functions
	// -----------------------------------------------
	GLvoid setBool(const string & name, GLboolean value) const
	{
		glUniform1i(glGetUniformLocation(ID, name.c_str()), (GLuint)value);
	}
	// ------------------------------------------------------------------------
	GLvoid setInt(const string & name, GLuint value) const
	{
		glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
	}
	// ------------------------------------------------------------------------
	GLvoid setFloat(const string & name, GLfloat value) const
	{
		glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
	}
	// ------------------------------------------------------------------------
	GLvoid setVec2(const string & name, const vec2 & value) const
	{
		glUniform2fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
	}
	GLvoid setVec2(const string & name, GLfloat x, GLfloat y) const
	{
		glUniform2f(glGetUniformLocation(ID, name.c_str()), x, y);
	}
	// ------------------------------------------------------------------------
	GLvoid setVec3(const string & name, const vec3 & value) const
	{
		glUniform3fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
	}
	GLvoid setVec3(const string & name, GLfloat x, GLfloat y, GLfloat z) const
	{
		glUniform3f(glGetUniformLocation(ID, name.c_str()), x, y, z);
	}
	// ------------------------------------------------------------------------
	GLvoid setVec4(const string & name, const vec4 & value) const
	{
		glUniform4fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
	}
	GLvoid setVec4(const string & name, GLfloat x, GLfloat y, GLfloat z, GLfloat w)
	{
		glUniform4f(glGetUniformLocation(ID, name.c_str()), x, y, z, w);
	}
	// ------------------------------------------------------------------------
	GLvoid setMat2(const string & name, const mat2 & mat) const
	{
		glUniformMatrix2fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
	}
	// ------------------------------------------------------------------------
	GLvoid setMat3(const string & name, const mat3 & mat) const
	{
		glUniformMatrix3fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
	}
	// ------------------------------------------------------------------------
	GLvoid setMat4(const string & name, const mat4 & mat) const
	{
		glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
	}
};

#endif // !_SHADER_H_

