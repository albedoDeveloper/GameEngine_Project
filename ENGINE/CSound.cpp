#include "CSound.h"
#include "GameObjectFactory.h"
#include "GraphicsEngine.h"
#include <glm/glm/gtx/vector_angle.hpp>


CSound::CSound(Transform *parent, GameObject *parentObj)
	:CComponent{ parent, parentObj }
{

}


void CSound::PlaySound(std::string soundName, int length, bool positional,float volume)
{
	auto sound = SOUND->GetSound(soundName);
	sound->setLooping(length);
	
	if (sound != nullptr)
	{
		SoundInfo temp;
		temp.soundName = soundName;
		temp.isPositional = positional;
		
		if (!temp.isPositional)
			temp.handler = SOUND->gSoloud.play(*sound, volume);
		else
		{
			auto soundPos = this->GetParentObject()->GetTransform()->GetRelativePosition();
			temp.handler = SOUND->gSoloud.play3d(*sound, soundPos.GetX(), soundPos.GetY(), soundPos.GetZ(),0.0f,0.0f,0.0f, volume);
			SOUND->gSoloud.set3dSourceAttenuation(temp.handler, 1, 0.2);
			//SOUND->gSoloud.set3dSourceMinMaxDistance(temp.handler, 1,2);
			SOUND->gSoloud.update3dAudio();
		}

		
		soundinfo.emplace(std::pair<std::string, SoundInfo>(soundName, temp));

		
	}
	else
		std::cout << soundName << "Sound is not loaded!" << std::endl;
}

void CSound::ChangeVolume(std::string soundName, float volume)
{
	if (soundinfo.count(soundName) > 0)
		SOUND->gSoloud.setVolume(soundinfo[soundName].handler, volume);
}

void CSound::StopPlaying(std::string soundName)
{
	if (soundinfo.count(soundName) > 0)
	{
		if (soundinfo.count(soundName) > 0)
			SOUND->gSoloud.stop(soundinfo[soundName].handler);
	}
}


void CSound::Update()
{
	for (auto &[key, value] : soundinfo)
	{
		if (value.isPositional && value.handler != NULL)
		{
			auto soundPos = this->GetParentObject()->GetTransform()->GetRelativePosition();
			SOUND->gSoloud.set3dSourceParameters(value.handler, soundPos.GetX(), soundPos.GetY(), soundPos.GetZ(), 0.0f, 0.0f, 0.0f);


		}
	}
}
