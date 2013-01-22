#include <iostream>
#include <exception>
#include "system/exploredir/ExploreDir.hh"
#include "system/log/Log.hh"
#include "AnimationManager.hh"

using namespace Sprite;

AnimationManager::AnimationManager(void)
{}

AnimationManager::~AnimationManager(void)
{}

AnimationManager::AnimationManager(const AnimationManager &other)
{
	_animations = other._animations;
}

AnimationManager& AnimationManager::operator=(const AnimationManager &other)
{
	if (this != &other) {
		_animations = other._animations;
	}
	return (*this);
}

bool AnimationManager::addSource(const std::string& spriteFile, const std::string &cfgFile)
{
	try {
		_animations.insert(std::make_pair(spriteFile,
							new Board(spriteFile, cfgFile)));
	} catch (std::exception &e) {
		std::cout << e.what() << std::endl;
		return (false);
	}
	return (true);
}

Board *AnimationManager::operator[](const std::string &spriteFile)
{
	if (_animations.find(spriteFile) != _animations.end()) {
		return (_animations.find(spriteFile)->second);
	} else {
		throw std::invalid_argument("Can not find " + spriteFile + ".");
	}
}

bool AnimationManager::addSourceFolder(const std::string &path)
{
	std::vector<std::string> fileList;
	
	fileList = TBSystem::ExploreDir::run(path);
	std::sort(fileList.begin(), fileList.end());
	return (findAssociatedFile(fileList));
}

bool AnimationManager::findAssociatedFile(std::vector<std::string> &files)
{
	bool success = true;
	std::vector<std::string>::iterator cfgFile;

	while ((cfgFile = findCfgFile(files)) != files.end()) {
		std::vector<std::string>::iterator imgFile = findAssociatedImg(files, *cfgFile);
	
		if (imgFile != files.end()) {
			try {
				if (!addSource(*imgFile, *cfgFile)) {
					success = false;
				}
			} catch (std::invalid_argument(&e)) {
				TBSystem::log::warn << e.what() << TBSystem::log::endl;
				success = false;
			}
		}
		if (cfgFile != files.end())
			files.erase(cfgFile);


	}
	return success;
}

std::vector<std::string>::iterator AnimationManager::findCfgFile(std::vector<std::string> &files)
{
	return (std::find_if(files.begin(), files.end(), [](std::string &file)
			{
				if (!file.compare(file.find_last_of('.'), file.length(),
								std::string(".cfg"))) {
					return (true);
				}
				return (false);
			}));
}

std::vector<std::string>::iterator AnimationManager::findAssociatedImg(std::vector<std::string> &files,
												const std::string &cfgFile)
{
	return (std::find_if(files.begin(), files.end(), [cfgFile](std::string &file)
			{
				if (file.compare(file.find_last_of('.'), file.length(),
								std::string(".cfg")) &&
					!cfgFile.compare(0, cfgFile.find_last_of('.'), file, 0, file.find_last_of('.'))) {
					return (true);
				}
				return (false);
			}));
}