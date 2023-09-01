#pragma once

#ifndef QRREADER_H
#define QRREADER_H

#include "qrClass.h"

class qrReader
{
public:
	static qrReader* getInstance();

	// loads image into memory
	bool loadImage(std::string& path);

	// loads a dir of images into memory
	size_t loadImages(std::string& path);

	// removes password from image/images
	void removePassword(std::vector<char>& password);

	// saves image from memory to disk
	int saveImageIntoFile();

	// saves image from disk to disk
	int saveImageIntoFile(std::string& path);

	// saves images from memory to disk
	size_t saveImages();

	// saves images from disk to disk
	size_t saveImages(std::string& path);

	// sets file's name and extension
	void setFileNameExt(std::string& filename);

private:
	bool compress = false;

	std::string filename = "";
	qrReader();
	~qrReader();
	qrClass* imageHolder = nullptr;
};

#endif // !QRREADER_H
