#include "qrReader.h"

qrReader* qrReader::getInstance()
{
	static qrReader instance;
	return &instance;
}

qrReader::qrReader()
{

}

qrReader::~qrReader()
{
	if (!imageHolder)
		delete imageHolder;
}

bool qrReader::loadImage(std::string& path)
{
	if (!imageHolder)
		delete imageHolder;
	imageHolder = new qrClass(std::move(cv::imread(path)), compress);
	return true;
}

size_t qrReader::loadImages(std::string& path)
{
	if (!imageHolder)
		delete imageHolder;
	std::vector<std::string> filesPaths;
	getFilesPaths(path, filesPaths);
	std::vector<cv::Mat> images;
	for (std::string& fPath : filesPaths)
		images.push_back(std::move(cv::imread(fPath)));
	imageHolder = new qrClass(std::move(images), compress);
	return filesPaths.size();
}

void qrReader::setFileNameExt(std::string& filename)
{
	this->filename = filename;
	return;
}

int qrReader::saveImageIntoFile()
{
	return imageHolder->saveFromImage(filename);
}

int qrReader::saveImageIntoFile(std::string& path)
{
	return imageHolder->saveFromImage(path, filename);
}

size_t qrReader::saveImages()
{
	return imageHolder->saveFromImages();
}

size_t qrReader::saveImages(std::string& path)
{
	return imageHolder->saveFromImages(path);
}
