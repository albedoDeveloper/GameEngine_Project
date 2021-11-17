#include "CSound.h"
#include "GameObjectFactory.h"
#include "GraphicsEngine.h"
#include <glm/glm/gtx/vector_angle.hpp>
#include "SoundManager.h"
CSound::CSound(Transform *parent, GameObject *parentObj)
	:CComponent{ parent, parentObj }
{

}


void CSound::PlaySound(std::string soundName, int length, bool positional)
{
	auto sound = SOUND->GetSound(soundName);

	if (sound != nullptr)
	{
		SoundInfo temp;
		temp.channel = Mix_PlayChannel(-1, sound, length);
		temp.soundName = soundName;
		temp.isPositional = positional;
		soundinfo.emplace(std::pair<std::string, SoundInfo>(soundName, temp));
	}
	else
		std::cout << soundName << "Sound is not loaded!" << std::endl;
}

void CSound::ChangeVolume(std::string soundName, int volume)
{
	if (soundinfo.count(soundName) > 0)
		Mix_Volume(soundinfo[soundName].channel, volume);
}

void CSound::StopPlaying(std::string soundName)
{
	if (soundinfo.count(soundName) > 0)
	{
		Mix_HaltChannel(soundinfo[soundName].channel);
		soundinfo.erase(soundName);
	}
}


void CSound::Update()
{
	for (auto &[key, value] : soundinfo)
	{
		if (value.isPositional && value.channel != -1)
		{
			auto playerTransform = GAMEOBJECT->GetGameObject("player")->GetTransform();
			auto thisTransform = this->GetParentObject()->GetTransform();

			float distanceF = glm::abs((glm::abs(thisTransform->GetRelativePosition().GetZ()) - glm::abs(playerTransform->GetRelativePosition().GetZ()))) + glm::abs(glm::abs((thisTransform->GetRelativePosition().GetX()) - glm::abs(playerTransform->GetRelativePosition().GetX()))) / 2 * 60;

			int distance = (int)distanceF;

			if (distance < 1)
				distance = 1;
			else if (distance > 255)
				distance = 255;

			if (!Mix_SetPosition(value.channel, 0, distance))
			{
				std::cout << "ERROR Mix_SetPosition: " << Mix_GetError() << std::endl;
			}
		}

		else
			Mix_SetPosition(value.channel, 0, 0);
	}
}
