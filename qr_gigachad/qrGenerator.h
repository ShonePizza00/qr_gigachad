#pragma once

#ifndef QRGENERATOR_H
#define QRGENERATOR_H

#define QRGENERATOR_BUFF_SIZE 5

#include "qrClass.h"

class qrGenerator
{
public:
	static qrGenerator* getInstance();
	size_t createImage(std::string& path, bool canBeCompressed);
	int createImage(std::vector<char>& data, bool canBeCompressed);
	size_t saveLastImage(std::string& imageName, std::string& extension);
	void setPasswordOnLastImage(std::vector<char>& password);
	void removePasswordFromLastImage(std::vector<char> & password);

private:
	qrGenerator();
	~qrGenerator();
	inline void createNewQrClass(bool canBeCompressed);
	std::vector<qrClass*> images;
	size_t newImagePosIndex = 0;
};

#endif // !QRGENERATOR_H
