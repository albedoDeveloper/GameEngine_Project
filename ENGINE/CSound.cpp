#include "CSound.h"
#include "GameObjectFactory.h"
#include "GraphicsEngine.h"
#include <glm/glm/gtx/vector_angle.hpp>
CSound::CSound(Transform *parent, GameObject *parentObj)
	:CComponent{ parent, parentObj }
{
	int flags = MIX_INIT_MP3;
	int initted = Mix_Init(flags);

	if (initted & flags != flags)
		std::cout << "Mix_Init: Failed to intialize mp3" << std::endl;

	if (SDL_Init(SDL_INIT_AUDIO) == -1)
	{
		printf("SDL_Init: %s\n", SDL_GetError());
		exit(1);
	}

	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024) == -1)
	{
		printf("Mix_OpenAudio: %s\n", Mix_GetError());
		exit(2);
	}
}

void CSound::LoadSound(std::string soundName)
{
	auto soundNameFull = "../Assets/Sounds/" + soundName;

	Mix_Chunk *temp = Mix_LoadWAV(soundNameFull.data());

	if (!temp)
		std::cout << "ERROR Mix_LoadWAV: " << Mix_GetError() << std::endl;

	soundList.insert(std::make_pair(soundName, temp));
}

void CSound::PlaySound(std::string soundName, int length, bool positional)
{
	auto sound = soundList.find(soundName);

	if (sound != soundList.end())
	{
		SoundInfo temp;
		temp.channel = Mix_PlayChannel(-1, sound->second, length);
		temp.soundName = sound->first;
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

			if (!Mix_SetPosition(value.channel, 0, distance))
			{
				std::cout << "ERROR Mix_SetPosition: " << Mix_GetError() << std::endl;
			}
		}

		else
			Mix_SetPosition(value.channel, 0, 0);
	}
}
