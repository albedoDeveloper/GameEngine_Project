#include "CSound.h"
#include "GameObjectFactory.h"
CSound::CSound(Transform* parent, GameObject* parentObj)
	:Component{ parent, parentObj }
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

void CSound::LoadSound(std::string soundName, bool positional)
{
	isPositional = positional;
	auto soundNameFull = "../Assets/Sounds/" + soundName;

	Mix_Chunk* temp = Mix_LoadWAV(soundNameFull.data());
	
	if (!temp) 
		std::cout << "ERROR Mix_LoadWAV: "<<  Mix_GetError() << std::endl;
	
	soundList.insert(std::make_pair(soundName, temp));
}

void CSound::PlaySound(std::string soundName, int length)
{
	if (soundList.find(soundName) != soundList.end())
		channel = Mix_PlayChannel(-1, soundList.find(soundName)->second, length);
	else
		std::cout << soundName << " sound is not loaded!" << std::endl;

}

void CSound::Start()
{
}

void CSound::Update()
{
	auto playerTransform = GAMEOBJECT->GetGameObject("player")->GetTransform();
	auto thisTransform = this->GetParentObject()->GetTransform();

	int distance = (glm::distance(playerTransform->GetPosition().GetZ(), thisTransform->GetPosition().GetZ()) + glm::distance(playerTransform->GetPosition().GetX(), thisTransform->GetPosition().GetX()))/2 * 40;
	if (distance < 1)
		distance = 1;
	else if (distance > 235)
		distance = 235;

	if (isPositional && channel != -1)
	{
		auto rawRotation = playerTransform->GetRotation().GetInverse();
		
		int rotation = glm::degrees(rawRotation.GetEulerAngles().GetY());
		if (rotation < 0)
			rotation += 360.0;

		if (!Mix_SetPosition(channel,rotation, distance))
		{
			std::cout << "ERROR Mix_SetPosition: " << Mix_GetError() << std::endl;
		}
	}

}

void CSound::Render()
{
}

void CSound::LateRender()
{
}
