#pragma once

#ifndef TEXTS_H
#define TEXTS_H

#pragma warning(disable:4129)

#include "includes.h"

namespace texts
{

	void printStrGetChoice(const std::string& str, int& dest);
	void printStrGetChoice(const std::string& str, std::string& dest);
	
	const std::string entryStr =
		"Choose what to do:\n \
	1: generate QR image from file/dir\n \
	2: read and create file/dir from QR image\n \
	other: exit from app";

	const std::string choiceStr = "Choice: ";

	const std::string imagesGeneraterStr = "Images generated: ";
	const std::string imagesSavedStr = "Images saved: ";

	const std::string generatorStr =
		"Choose what to do:\n \
	1: create image/images\n \
	2: set password on the image/images (does not work)\n \
	3: remove password from the image/images (does not work)\n \
	4: save last created image/images\n \
	other: exit from the generator";

	const std::string getFPathStr = "Enter source file's path";
	const std::string getFPathsStr = "Enter source files' paths";
	const std::string getFNameStr = "Enter file name";

	const std::string imagesLoadedStr = "Images loaded: ";
	const std::string filesSavedStr = "Files saved: ";

	const std::string getFNameExtStr = "Enter file's name and extension (name.ext)";

	const std::string readerStr =
		"Choose what to do:\n \
	1: load image\n \
	2: load images\n \
	3: remove password from image\images (does not work)\n \
	4: save image into file\n \
	5: save images into files\n \
	6: save image into file without loading\n \
	7: save images into files without loading\n \
	other: exit from reader";
}

#endif // !TEXTS_H
