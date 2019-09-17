#include "ObjFile.h"
#include <fstream>
#include <string>



ObjFile::ObjFile()
{
}


ObjFile::~ObjFile()
{
}

void loadObjFile(char* path)
{
	std::ifstream file(path);
	std::string str;
	while (std::getline(file, str))
	{
		switch (str[0])
		{
		case 'v':
			printf("%s\n", str);
			break;
		case 'f':
			printf("%s\n", str);
			break;
		}
	}
}
