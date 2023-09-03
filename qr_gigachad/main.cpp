#include "includes.h"

#include "QR.h"
#include "texts.h"

int main()
{
	qrGenerator* generator = generator->getInstance();
	qrReader* reader = reader->getInstance();
	bool f1 = true;
	while (f1)
	{
		system("cls");
		int choiceVar = 0;
		texts::printStrGetChoice(texts::entryStr, choiceVar);
		bool f2 = true;
		switch (choiceVar)
		{
		case 1:
		{
			system("cls");
			while (f2)
			{
				texts::printStrGetChoice(texts::generatorStr, choiceVar);
				switch (choiceVar)
				{
				case 1:
				{
					std::string fPath = "";
					texts::printStrGetChoice(texts::getFPathStr, fPath);
					std::cout << texts::imagesGeneraterStr;
					std::cout << generator->createImage(fPath, false) << std::endl;
					break;
				}
				case 2:
				{
					break;
				}
				case 3:
				{
					break;
				}
				case 4:
				{
					std::string fName = "";
					std::string fExtension = "png";
					texts::printStrGetChoice(texts::getFNameStr, fName);
					std::cout << texts::imagesSavedStr;
					std::cout << generator->saveLastImage(fName, fExtension) << std::endl;
					break;
				}
				default:
					f2 = false;
				}
			}
			break;
		}
		case 2:
		{
			system("cls");
			while (f2)
			{
				texts::printStrGetChoice(texts::readerStr, choiceVar);
				switch (choiceVar)
				{
				case 1:
				{
					std::string fPath = "";
					texts::printStrGetChoice(texts::getFPathStr, fPath);
					std::cout << texts::imagesLoadedStr;
					std::cout << reader->loadImage(fPath) << std::endl;
					break;
				}
				case 2:
				{
					std::string fPaths = "";
					texts::printStrGetChoice(texts::getFPathsStr, fPaths);
					std::cout << texts::imagesLoadedStr;
					std::cout << reader->loadImages(fPaths) << std::endl;
					break;
				}
				case 3:
				{
					break;
				}
				case 4:
				{
					std::string fNameExt = "";
					texts::printStrGetChoice(texts::getFNameExtStr, fNameExt);
					reader->setFileNameExt(fNameExt);
					std::cout << texts::filesSavedStr;
					std::cout << reader->saveImageIntoFile() << std::endl;
					break;
				}
				case 5:
				{
					/*std::string fPaths = "";
					texts::printStrGetChoice(texts::getFPathsStr, fPaths);*/
					std::cout << texts::filesSavedStr;
					std::cout << reader->saveImages() << std::endl;
					break;
				}
				case 6:
				{
					std::string fPath = "";
					std::string fNameExt = "";
					texts::printStrGetChoice(texts::getFPathStr, fPath);
					texts::printStrGetChoice(texts::getFNameExtStr, fNameExt);
					reader->setFileNameExt(fNameExt);
					std::cout << texts::filesSavedStr;
					std::cout << reader->saveImageIntoFile(fPath) << std::endl;
					break;
				}
				case 7:
				{
					std::string fPaths = "";
					texts::printStrGetChoice(texts::getFPathsStr, fPaths);
					std::cout << texts::filesSavedStr;
					std::cout << reader->saveImages(fPaths) << std::endl;
					break;
				}
				default:
					f2 = false;
				}
			}
			break;
		}
		default:
			f1 = false;
		}
	}
	return 0;
}