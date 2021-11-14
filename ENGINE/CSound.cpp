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
		std::cout << soundName << " sound is not loaded!" << std::endl;
}

void CSound::ChangeVolume(std::string soundName, int volume)
{
	Mix_Volume(soundinfo[soundName].channel, volume);
}

void CSound::StopPlaying(std::string soundName)
{
	Mix_HaltChannel(soundinfo[soundName].channel);
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

			//std::cout << distance << std::endl;
			/*glm::vec3 checkPos = glm::vec3(playerTransform->GetPosition().GetX(), playerTransform->GetPosition().GetY(), playerTransform->GetPosition().GetZ()) - glm::vec3(thisTransform->GetPosition().GetX(), thisTransform->GetPosition().GetY(), thisTransform->GetPosition().GetZ());

			Quaternion rawRotation;
			rawRotation = playerTransform->GetRotation().GetInverse();
			bool zRotated = false;
			bool centred = false;


			int rotation = glm::degrees(rawRotation.GetEulerAnglesDegrees().GetY());

			if (rotation < 0)
				rotation += 360.0;*/

			if (!Mix_SetPosition(value.channel, 0, distance))
			{
				std::cout << "ERROR Mix_SetPosition: " << Mix_GetError() << std::endl;
			}
		}

		else
			Mix_SetPosition(value.channel, 0, 0);
	}
}
