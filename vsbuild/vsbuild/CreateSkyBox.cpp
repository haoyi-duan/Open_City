#include "CreateSkyBox.h"

GLuint createSkyBox(GLuint id)
{
	vector<string> faces;
	if (id == 0)
	{
		faces.push_back(string("resource/skybox/skybox3/left.jpg"));
		faces.push_back(string("resource/skybox/skybox3/right.jpg"));
		faces.push_back(string("resource/skybox/skybox3/top.jpg"));
		faces.push_back(string("resource/skybox/skybox3/bottom.jpg"));
		faces.push_back(string("resource/skybox/skybox3/front.jpg"));
		faces.push_back(string("resource/skybox/skybox3/back.jpg"));
		
		//faces.push_back(string("resource/skybox/bak9/left.jpg"));
		//faces.push_back(string("resource/skybox/bak9/right.jpg"));
		//faces.push_back(string("resource/skybox/bak9/top.jpg"));
		//faces.push_back(string("resource/skybox/bak9/down.jpg"));
		//faces.push_back(string("resource/skybox/bak9/front.jpg"));
		//faces.push_back(string("resource/skybox/bak9/back.jpg"));

		//faces.push_back(string("resource/skybox/lake/left.jpg"));
		//faces.push_back(string("resource/skybox/lake/right.jpg"));
		//faces.push_back(string("resource/skybox/lake/top.jpg"));
		//faces.push_back(string("resource/skybox/lake/down.jpg"));
		//faces.push_back(string("resource/skybox/lake/front.jpg"));
		//faces.push_back(string("resource/skybox/lake/back.jpg"));
	}
	else if (id == 1)
	{
		faces.push_back(string("resource/skybox/skybox1/right.jpg"));
		faces.push_back(string("resource/skybox/skybox1/left.jpg"));
		faces.push_back(string("resource/skybox/skybox1/top.jpg"));
		faces.push_back(string("resource/skybox/skybox1/bottom.jpg"));
		faces.push_back(string("resource/skybox/skybox1/front.jpg"));
		faces.push_back(string("resource/skybox/skybox1/back.jpg"));
	}

	GLuint textureID;
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);
	
	GLint width, height, nrChannels;
	for (unsigned int i = 0; i < faces.size(); i++)
	{
		stbi_uc * data = stbi_load(faces[i].c_str(), &width, &height, &nrChannels, 0);
		if (data)
		{
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			stbi_image_free(data);
		}
		else
		{
			cout << "CUBEMAP::LOAD::TEXTURE::FAILED" << endl;
			cout << "PATH::" << faces[i] << endl;
			stbi_image_free(data);
		}
	}

	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

	return textureID;
}