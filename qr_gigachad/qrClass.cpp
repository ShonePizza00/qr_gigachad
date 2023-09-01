#include "qrClass.h"

void getFilesPaths(std::string& path, std::vector<std::string>& dest)
{
	for (const auto& entry : std::filesystem::directory_iterator(path))
	{
		std::string t2 = entry.path().string();
		std::ifstream t1(t2);
		if (t1.is_open())
		{
			t1.close();
			dest.push_back(t2);
		}
		else
		{
			t1.close();
			getFilesPaths(t2, dest);
		}
	}
	return;
}

std::string createTempDir(std::string& imageName, std::string& ext)
{
	SHA256 sha;
	time_t t1 = time(NULL);
	sha.update(imageName + ext + (char)t1);
	return SHA256::toString(sha.digest()).substr(0, 8);
}

qrClass::qrClass()
{
	
}

qrClass::qrClass(std::string& path)
{
	open(path);
}

qrClass::qrClass(std::vector<char>& data)
{
	open(data);
}

qrClass::qrClass(cv::Mat image, bool compress)
{
	qr = std::move(image);
	vCanBeCompressed = compress;
}

qrClass::qrClass(std::vector<cv::Mat> images, bool compress)
{
	qrs = std::move(images);
	vCanBeCompressed = compress;
}

qrClass::~qrClass()
{

}

size_t qrClass::open(std::string& path)
{
	std::ifstream sourceFile(path, std::ios::binary);
	if (sourceFile.is_open())
	{
		sourceFile.close();
		return openFile(path);
	}
	isFile = false;
	return openDir(path);
}

int qrClass::open(std::vector<char>& data)
{
	return openFile(data);
}

int qrClass::openFile(std::string& path)
{
	std::ifstream sourceFile(path, std::ios::binary);
	size_t fileSize = std::filesystem::file_size(path);
	if (fileSize > 0xffffffffff)
	{
		throw std::exception("Source file's size is greater than 1 TB");
		return -1;
	}
	switch (vCanBeCompressed)
	{
	case (false):
	{
		int nx = (int)sqrt((long double)fileSize);
		nx += ((nx * nx == fileSize) ? 0 : 1);
		int ny = nx + 1;
		qr = cv::Mat(ny, nx, CV_8UC1, cv::Scalar(0));
		char* data = new char[nx];
		for (int y = 0; y < nx; ++y)
		{
			sourceFile.read(data, nx);
			for (int x = 0; x < nx; ++x)
			{
				qr.at<char>(y, x) = data[x]; ///////// this is for not compressed
			}
		}
		delete[] data;
		int y = int(fileSize / nx);
		int x = fileSize % nx;
		while (x < nx)
			qr.at<char>(y, x++) = (char)TRASH_PIXEL; //not NULL but some trash
		for (int xx = 0; xx < nx; ++xx)
			qr.at<char>(ny - 1, xx) = (char)TRASH_PIXEL; //not NULL but some trash
		x = fileSize % nx;
		qr.at<char>(ny - 1, x) = NULL;
		break;
	}
	case(true):
		break;
	}
	return 1;
}

int qrClass::openFile(std::vector<char>& data)
{
	size_t fileSize = data.size();
	if (fileSize > 0xffffffffff)
	{
		throw std::exception("Source file's size is greater than 1 TB");
		return -1;
	}
	switch (vCanBeCompressed)
	{
	case (false):
	{
		int nx = (int)sqrt((long double)fileSize);
		nx += ((nx * nx == fileSize) ? 0 : 1);
		int ny = nx + 1;
		qr = cv::Mat(ny, nx, CV_8UC1, cv::Scalar(0));
		bool f = false;
		for (int y = 0; y < nx; ++y)
		{
			size_t t1 = y * nx;
			for (int x = 0; x < nx; ++x)
			{
				if ((t1 + x) - fileSize)
					qr.at<char>(y, x) = data[t1 + x]; ///////// this is for not compressed
				else
				{
					f = true;
					break;
				}
			}
			if (f)
				break;
		}
		int y = int(fileSize / nx);
		int x = fileSize % nx;
		while (x < nx)
			qr.at<char>(y, x++) = (char)TRASH_PIXEL;
		for (int xx = 0; xx < nx; ++xx)
			qr.at<char>(ny - 1, xx) = (char)TRASH_PIXEL;
		x = fileSize % nx;
		qr.at<char>(ny - 1, x) = NULL;
		break;
	}

	case(true):
		break;
	}
	return 0;
}

size_t qrClass::openDir(std::string& path)
{
	std::vector<std::string> files;
	std::vector<char> configText;
	getFilesPaths(path, files);
	for (std::string& filePath : files)
	{
		open(filePath);
		qrs.push_back(std::move(qr));
		std::copy(filePath.begin() + path.length(), filePath.end(), std::back_inserter(configText));
		configText.push_back('\0');
	}
	open(configText);
	qrs.push_back(std::move(qr));
	return qrs.size();
}

cv::Mat* qrClass::getImage()
{
	return &qr;
}

size_t qrClass::viewImage()
{
	if (isFile)
		cv::imshow("Image preview", qr);
	else
		return qrs.size();
	return 0;
}

size_t qrClass::saveImage(std::string& imageName, std::string& extension)
{
	if (isFile)
		cv::imwrite(std::format("./pics/{}.{}", imageName, extension), qr);
	else
	{
		std::string dirName = createTempDir(imageName, extension);
		std::filesystem::create_directory(std::format("./pics/{}", dirName));
		for (size_t i = 0; i < qrs.size(); ++i)
		{
			std::string path = std::format("./pics/{}/{}.{}", dirName, i, extension);
			cv::imwrite(path, qrs[i]);
		}
		return qrs.size();
	}
	return 1;
}

int qrClass::saveFromImage(std::string& path, std::string& fileNameExt)
{
	if (!configTextFromImage.empty())
	{
		throw std::exception("The queue is not empty");
		return -1;
	}
	configTextFromImage.push(fileNameExt);
	std::ifstream file(path);
	if (file.is_open())
	{
		file.close();
		cv::Mat image = cv::imread(path);
		return saveIntoFile(image);
	}
	file.close();
	throw std::invalid_argument("The path points to a dir, not a file");
	return -1;
}

int qrClass::saveFromImage(cv::Mat& image, std::string& fileNameExt)
{
	if (!configTextFromImage.empty())
	{
		throw std::exception("The queue is not empty");
		return -1;
	}
	configTextFromImage.push(fileNameExt);
	return saveIntoFile(image);
}

int qrClass::saveFromImage(std::string& fileNameExt)
{
	if (!configTextFromImage.empty())
	{
		throw std::exception("The queue is not empty");
		return -1;
	}
	configTextFromImage.push(fileNameExt);
	return saveIntoFile(qr);
}

size_t qrClass::saveFromImages(std::string& path)
{
	std::ifstream file(path);
	if (file.is_open())
	{
		file.close();
		throw std::invalid_argument("The path points to a file, not a dir");
		return -1;
	}
	std::vector<std::string> filesPaths;
	getFilesPaths(path, filesPaths);
	cv::Mat t1 = cv::imread(filesPaths.back());
	putConfigImageToQueue(t1);
	int ret = 0;
	for (size_t i = 0; i < (filesPaths.size() - 1); ++i)
	{
		std::string& fPath = filesPaths[i];
		cv::Mat image = cv::imread(fPath);
		if (!(ret = saveIntoFile(image)))
			return ret;
	}
	return filesPaths.size();
}

size_t qrClass::saveFromImages(std::vector<cv::Mat>& images)
{
	int ret = 0;
	cv::Mat t1 = images.back();
	putConfigImageToQueue(t1);
	for (size_t i = 0; i < (images.size() - 1); ++i)
	{
		cv::Mat& image = images[i];
		if (!(ret = saveIntoFile(image)))
			return ret;
	}
	return images.size();
}

size_t qrClass::saveFromImages()
{
	int ret = 0;
	cv::Mat t1 = qrs.back();
	putConfigImageToQueue(t1);
	for (size_t i = 0; i < (qrs.size() - 1); ++i)
	{
		cv::Mat& image = qrs[i];
		if (!(ret = saveIntoFile(image)))
			return ret;
	}
	return qrs.size();
}

size_t qrClass::putConfigImageToQueue(cv::Mat& image)
{
	if (!configTextFromImage.empty())
	{
		throw std::exception("The queue is not empty");
		return -1;
	}
	uchar* configImageData = image.data;
	size_t configImageDataLen = image.total();
	for (size_t i = 0; i < configImageDataLen; ++i)
	{
		std::string t1 = "";
		while (configImageData[i])
			t1 += (char)configImageData[i++];
		configTextFromImage.push(move(t1));
	}
	return configTextFromImage.size();
}

int qrClass::saveIntoFile(cv::Mat& image)
{
	std::ofstream oFile(configTextFromImage.front(), std::ios::binary);
	if (!oFile.is_open())
		return 0;
	configTextFromImage.pop();
	oFile.write((char*)image.data, image.total());
	oFile.close();
	return 1;
}
