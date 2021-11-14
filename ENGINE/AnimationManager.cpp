#include "AnimationManager.h"
#include "GameObjectFactory.h"

AnimationManager::AnimationManager()
{

}

AnimationManager *AnimationManager::Instance()
{
	static AnimationManager instance;
	return &instance;
}

void AnimationManager::AddAnimation(std::string filePath, std::string modelName, std::string name)
{
	auto model = ASSET->GetModelAsset(modelName);

	animationList.emplace(std::pair<std::string, Animation *>(name, new Animation("../Assets/Models/" + filePath, model)));

}

Animation* AnimationManager::GetAnimation(std::string name)
{
	return animationList.at(name);
}