#include "Map.h"
#include "Element.h"

// 根据地图文件构建游戏世界
// ----------------------------------
GLvoid createMap(const string filename)
{
	ifstream in(filename);
	string s, temp;
	GLint i = -1, length = 0, width = 0, count = 0;
	while (getline(in, s))
	{
		if (i == -1)
		{
			istringstream instr(s);
			instr >> length >> width;
		}
		else
		{
			GLint temp;
			istringstream instr(s);
			for (int k = 0; k < width; k++)
			{
				instr >> temp;
				if (temp == 1)
				{
					boxPosition.push_back(vec3(2 * i - 1, 0.0f, 2 * k - 1));
				}
				else if (temp == 2)
				{
					cupPosition = (vec3(2 * i - 1, -1.0f, 2 * k - 1));
				}
				else if (temp == 3)
				{
					elementVector[elementCount++] = new Element(1, 0.4f, vec3(4.5f, 9.6f, 1.3f), vec3(2 * i - 1, -1.0f, 2 * k - 1));
				}
				else if (temp == 4)
				{
					elementVector[elementCount++] = new Element(2, 0.3f, vec3(3.0f, 5.0f, 1.0f), vec3(2 * i - 1, -1.0f, 2 * k - 1));
				}
			}
		}
		i++;
		if (i == length) break;
	}
}

GLuint loadCubemap(vector<string> faces)
{
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
			cout << "CUBEMAP::TEXTURE::LOAD::FAILED" << endl;
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