#include "Model.hpp"

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "glm/glm.hpp"

using namespace std;

vector<string> split(const string str, const char &delimiter)
{
	string::const_iterator iter;
	iter = str.begin();
	vector<string> token;

	while (iter != str.end())
	{
		string::const_iterator tmp_iter;
		tmp_iter = find(iter, str.end(), delimiter);
		token.push_back(string(iter, tmp_iter));
		iter = tmp_iter;
		if (iter != str.end())
			iter++;
	}
	return token;
}

int main()
{
	const char* objFile = "stall.obj";
	ifstream fr(objFile);
	if (!fr.is_open())
	{
		printf("[ERROR] Cannot read file %s!\r\n", objFile);
		fr.close();
		return false;
	}

	string currentLine;
	vector<string> token;
	vector<glm::vec3> vVertice;
	vector<glm::vec2> vTexture;
	vector<glm::vec3> vNormal;

	glm::vec3 vertex;
	glm::vec2 texture;
	glm::vec3 normal;
	
	unsigned int vertexIndex;
	unsigned int textureIndex;
	unsigned int normalIndex;

	vector<glm::vec3> vertices;
	vector<glm::vec2> textures;
	vector<glm::vec3> normals;

	vector<string> faceSplit;

	while(getline(fr, currentLine))
	{
		printf("%s\r\n", currentLine.c_str());

		token = split((const string)currentLine, ' ');
		const char* first = token.at(0).c_str();
		if (strcmp(first, "v") == 0)
		{
			vertex.x = stof(token.at(1).c_str());
			vertex.y = stof(token.at(2).c_str());
			vertex.z = stof(token.at(3).c_str());
			vVertice.push_back(vertex);
		}
		else if (strcmp(first, "vt") == 0)
		{
			texture.x = stof(token.at(1).c_str());
			texture.y = stof(token.at(2).c_str());
			vTexture.push_back(texture);
		}
		else if (strcmp(first, "vn") == 0)
		{
			normal.x = stof(token.at(1).c_str());
			normal.y = stof(token.at(2).c_str());
			normal.z = stof(token.at(3).c_str());
			vNormal.push_back(normal);
		}
		else if (strcmp(first, "f") == 0)
		{
			for (short numString = 1; numString <= 3; numString++)
			{
				faceSplit = split((const string)token.at(numString), '/');

				vertexIndex = stoi(faceSplit.at(0).c_str());
				glm::vec3 tmpVertex = vVertice.at(vertexIndex - 1);
				vertices.push_back(tmpVertex);
				printf("vertex: %f\t %f\t %f\r\n", vertices.at(vertices.size()-1).x, vertices.at(vertices.size() - 1).y, vertices.at(vertices.size() - 1).z);

				textureIndex = stoi(faceSplit.at(1).c_str());
				glm::vec2 tmpTexture = vTexture.at(textureIndex - 1);
				textures.push_back(tmpTexture);
				printf("texture: %f\t %f\t %f\r\n", textures.at(textures.size() - 1).x, textures.at(textures.size() - 1).y);

				normalIndex = stoi(faceSplit.at(2).c_str());
				glm::vec3 tmpNormal = vNormal.at(normalIndex - 1);
				normals.push_back(tmpNormal);
				printf("normal: %f\t %f\t %f\r\n", normals.at(normals.size() - 1).x, normals.at(normals.size() - 1).y, normals.at(normals.size() - 1).z);
			}
		}
	}
	
	fr.close();
	return true;
}

