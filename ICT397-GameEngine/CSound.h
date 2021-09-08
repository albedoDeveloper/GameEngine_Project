#pragma once
#include <SDL2/SDL_mixer.h>
#include <iostream>
#include <SDL2/SDL_audio.h>
#include <SDL2/SDL.h>
#include <unordered_map>
#include <memory>
#include <vector>
#include "Component.h"



class CSound : public Component
{
public:
	CSound(Transform* parent, GameObject* parentObj);
	void LoadSound(std::string soundName);
	void PlaySound(std::string soundName, int length,bool positional);

    /**
    * @brief initialises component at program start
   */
    virtual void Start();
    /**
     * @brief updates ongoing behaviour each frame
    */
    virtual void Update();
    /**
     * @brief renders the component to the screen if visible
    */
    virtual void Render();
    /**
     * @brief renders the component after others have been rendered
    */
    virtual void LateRender();


private:
    struct SoundInfo
    {
        std::string soundName;
        bool isPositional = false;
        int channel = -1;
    };

    std::unordered_map<std::string, Mix_Chunk*> soundList;
    std::vector<SoundInfo> soundinfo;


};

