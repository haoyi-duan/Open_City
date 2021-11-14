#include "Shader.h"

Shader::Shader(const GLchar * vertexPath, const GLchar * fragmentPath)
{
	// ************************ 从文件路径中获取顶点/片段着色器 ************************** //
	// *********************************************************************************** //
	string vertexCode;
	string fragmentCode;
	ifstream vShaderFile;
	ifstream fShaderFile;

	// 保证ifstream对象可以抛出异常
	// ----------------------------
	vShaderFile.exceptions(ifstream::failbit | ifstream::badbit);
	fShaderFile.exceptions(ifstream::failbit | ifstream::badbit);

	try
	{
		// 打开文件
		// --------------------------
		vShaderFile.open(vertexPath);
		fShaderFile.open(fragmentPath);
		stringstream vShaderStream, fShaderStream;

		// 读取文件的缓冲内容到流中
		// ----------------------------------
		vShaderStream << vShaderFile.rdbuf();
		fShaderStream << fShaderFile.rdbuf();

		// 关闭文件
		// -----------------
		vShaderFile.close();
		fShaderFile.close();

		// 转换流到 GLchar 数组
		// --------------------------------
		vertexCode = vShaderStream.str();
		fragmentCode = fShaderStream.str();
	}
	catch (ifstream::failure & e)
	{
		cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << endl;
	}
	const GLchar * vShaderCode = vertexCode.c_str();
	const GLchar * fShaderCode = fragmentCode.c_str();

	// ************************* 编译着色器 ************************* //
	// ************************************************************** //

	GLuint vertex, fragment;
	GLint success;
	GLchar infoLog[512];

	// 顶点着色器
	// --------------------------------------
	vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vShaderCode, NULL);
	glCompileShader(vertex);

	// 打印编译错误（如果有的话）
	// 
	glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertex, 512, NULL, infoLog);
		cout << "ERROR::SHADER::VERTEX::COMPLATION_FAILED" << endl;
		cout << infoLog << endl;
	}

	// 片段着色器
	// ------------------------------------------- 
	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fShaderCode, NULL);
	glCompileShader(fragment);

	// 打印编译错误（如果有的话）
	// --------------------------------------------------
	glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragment, 512, NULL, infoLog);
		cout << "ERROR::SHADER::FRAGMENT::COMPLATION_FAILED" << endl;
		cout << fragmentPath << endl;
		cout << infoLog << endl;
	}

	// ************************* 着色器程序 ************************* //
	// ************************************************************** //

	this->ID = glCreateProgram();
	glAttachShader(this->ID, vertex);
	glAttachShader(this->ID, fragment);
	glLinkProgram(this->ID);

	// 打印连接错误（如果有的话）
	// ------------------------------------------ 
	glGetProgramiv(this->ID, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(this->ID, 512, NULL, infoLog);
		cout << "ERROR:SHADER::PROGRAM::LINKING_FAILED" << endl;
		cout << infoLog << endl;
	}

	// 删除着色器，它们已经连接到我们的程序中了，已经不再需要了
	// --------------------------------------------------------
	glDeleteShader(vertex);
	glDeleteShader(fragment);
}
