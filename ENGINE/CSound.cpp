#include "CSound.h"
#include "GameObjectFactory.h"
#include "GraphicsEngine.h"
#include <glm/glm/gtx/vector_angle.hpp>


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
		temp.soundName = soundName;
		temp.isPositional = positional;
		if (!temp.isPositional)
			temp.handler = SOUND->gSoloud.play(*sound, -1.0);
		else
		{
			temp.handler = SOUND->gSoloud.play3d(*sound, this->GetParentObject()->GetTransform()->GetRelativePosition().GetX(), this->GetParentObject()->GetTransform()->GetRelativePosition().GetY(), this->GetParentObject()->GetTransform()->GetRelativePosition().GetZ(),0.0f,0.0f,0.0f,1.0f);
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

			SOUND->gSoloud.set3dSourceParameters(value.handler, this->GetParentObject()->GetTransform()->GetRelativePosition().GetX(), this->GetParentObject()->GetTransform()->GetRelativePosition().GetY(), this->GetParentObject()->GetTransform()->GetRelativePosition().GetZ(), 0.0f, 0.0f, 0.0f);


		}
	}
}
