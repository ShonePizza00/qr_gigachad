#include "qrGenerator.h"

qrGenerator::qrGenerator()
{
	images.resize(QRGENERATOR_BUFF_SIZE);
	for (size_t i = 0; i < QRGENERATOR_BUFF_SIZE; ++i)
		images[i] = nullptr;
}

qrGenerator::~qrGenerator()
{
	for (size_t i = 0; i < QRGENERATOR_BUFF_SIZE; ++i)
		if (!images[i])
			delete images[i];
}

qrGenerator* qrGenerator::getInstance()
{
	static qrGenerator instance;
	return &instance;
}

inline void qrGenerator::createNewQrClass(bool canBeCompressed)
{
	size_t workingIndex = newImagePosIndex % QRGENERATOR_BUFF_SIZE;
	if (!images[workingIndex])
		images[workingIndex] = new qrClass;
	else
	{
		delete images[workingIndex];
		images[workingIndex] = new qrClass;
	}
	images[newImagePosIndex % QRGENERATOR_BUFF_SIZE]->vCanBeCompressed = canBeCompressed;
	return;
}

size_t qrGenerator::createImage(std::string& path, bool canBeCompressed)
{
	createNewQrClass(canBeCompressed);
	return images[newImagePosIndex++ % QRGENERATOR_BUFF_SIZE]->open(path);
}

int qrGenerator::createImage(std::vector<char>& data, bool canBeCompressed)
{
	createNewQrClass(canBeCompressed);
	return images[newImagePosIndex++ % QRGENERATOR_BUFF_SIZE]->open(data);
}

size_t qrGenerator::saveLastImage(std::string& imageName, std::string& extension)
{
	if (!newImagePosIndex)
		return -1;
	return images[(newImagePosIndex - 1) % QRGENERATOR_BUFF_SIZE]->saveImage(imageName, extension);
}
