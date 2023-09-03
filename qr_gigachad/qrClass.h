#pragma once

#ifndef QRCLASS_H
#define QRCLASS_H
#define QRCLASS_VERSION 0 //[0, 255]

//#define MAX(a, b) (((a) > (b)) ? (a) : (b))
//#define MIN(a, b) (((a) < (b)) ? (a) : (b))

#define TRASH_PIXEL 228

#include "includes.h"

//finding all files from dir and subdirs
void getFilesPaths(std::string& path, std::vector<std::string>& dest);
std::string nameTempDir(std::string& imageName, std::string& ext);
std::string nameTempDir(std::string& fileNameExt);
std::string nameTempDir();

class qrClass
{
public:
	qrClass();
	qrClass(std::string& path);
	qrClass(std::vector<char>& data);
	qrClass(cv::Mat image, bool compress);
	qrClass(std::vector<cv::Mat> images, bool compress);
	~qrClass();
	inline cv::Mat* getImage();
	size_t viewImage();
	/*
	Saves readed data into image with name: "imageName.extension"
	if readed data contained more than 1 file it will ignore "imageName"
	and name files with specific names
	*/
	size_t saveImage(std::string& imageName, std::string& extension);

	// v returns num of saved files
	int saveFromImage(std::string& path, std::string& fileNameExt);
	int saveFromImage(cv::Mat& image, std::string& fileNameExt);
	int saveFromImage(std::string& fileNameExt);
	size_t saveFromImages(std::string& path);
	size_t saveFromImages(std::vector<cv::Mat>& images);
	size_t saveFromImages();

	size_t open(std::string& path);
	int open(std::vector<char>& data);
	int setPassword(std::vector<char>& data);
	int removePassword(std::vector<char>& data);

	bool vCanBeCompressed = true;
	bool emptyImage = true;
	bool isFile = true;

private:
	inline int saveIntoFile(cv::Mat& image, std::string& path);
	inline size_t putConfigImageToQueue(cv::Mat& image);
	int openFile(std::string& path);
	int openFile(std::vector<char>& data);

	size_t openDir(std::string& path);
	cv::Mat qr;
	std::vector<cv::Mat> qrs;
	std::queue<std::string> configTextFromImage;

};

#endif // !
