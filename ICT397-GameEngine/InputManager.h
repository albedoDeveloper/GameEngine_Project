#pragma once
#include <SDL2/SDL.h>
#include <string>
#include "GraphicsEngine.h"

class Engine;

/**
 * @brief represents a key on the keyboard
*/
struct Key
{
    bool down = false;
    bool held = false;
    bool up = false;
};
/**
 * @brief represents a button on the mouse
*/
struct MouseButton
{
    bool down = false;
    bool held = false;
    bool up = false;
};
/**
 * @brief the letter represented by a key
*/
enum class KeyCode
{
    W,
    A,
    S,
    D,
    Z,
    X,
    Q,
    K,
    T,
    M,
    SPACE
};

/**
 * @brief singleton managing user input
*/
class InputManager
{
private:
    
    Engine* m_engine;

    bool m_cursorLocked;

    /**
     * @brief the SDL event taking place
    */
    SDL_Event* m_Event;

    /**
     * @brief the current x coordinate of the mouse
    */
    int mouseX = false;
    /**
     * @brief the current y coordinate of the mouse
    */
    int mouseY = false;

    int mouseXAbsolute;

    int mouseYAbsolute;

    /**
     * @brief the previous x coordinate of the mouse
    */
    int prevMouseX = 0;
    /**
     * @brief the previous y coordinate of the mouse
    */
    int prevMouseY = 0;

    /**
     * @brief the W key
    */
    Key w_Key;
    /**
     * @brief the A key
    */
    Key a_Key;
    /**
     * @brief the S key
    */
    Key s_Key;
    /**
     * @brief the D key
    */
    Key d_Key;
    /**
     * @brief the Z key
    */
    Key z_Key;
    /**
     * @brief the X key
    */
    Key x_Key;
    /**
     * @brief the Q key
    */
    Key q_Key;
    /**
     * @brief the K key
    */
    Key k_Key;    
    /**
     * @brief the t key
    */
    Key t_Key;
    Key m_Key;
    Key c_Key;
    Key space_Key;
    Key tilde_Key;

    /**
     * @brief the primary mouse button
    */
    MouseButton leftMouseButton;
    /**
     * @brief the secondary mouse button
    */
    MouseButton rightMouseButton;
    /**
     * @brief the tertiary mouse button
    */
    MouseButton middleMouseButton;

    /**
     * @brief whether key presses should be logged for debugging
    */
    bool debugKeyPresses = false;
    /**
     * @brief whether mouse buttons should be logged for debugging
    */
    bool debugMouseButtons = false;
    /**
     * @brief whether mouse movement should be logged for debugging
    */
    bool debugMouseMovement = false;

public:
    /**
     * @brief default constructor
    */
    InputManager();
    /**
     * @brief singleton instance generator
     * @return a pointer to the instance of the input manager
    */
    static InputManager* Instance();

    void Initialise(Engine* e);

    /**
     * @brief checks whether a key is being pressed and stores the resulting data
     * @param e the current SDL event
    */
    void CheckKey(SDL_Event* e);
    /**
     * @brief checks whether a key is moving down and stores the resulting data
     * @param e the current SDL event
    */
    void CheckKeyDown(SDL_Event* e);
    /**
     * @brief checks whether a key is being released and stores the resulting data
     * @param e the current SDL event
    */
    void CheckKeyUp(SDL_Event* e);

    /**
     * @brief checks whether a mouse button is being help and stores the resulting data
     * @param e the current SDL event
    */
    void CheckMouseButtonDown(SDL_Event* e);
    /**
     * @brief checks whether a mouse button is being released and stores the resulting data
     * @param e the current SDL event
    */
    void CheckMouseButtonUp(SDL_Event* e);

    /**
     * @brief checks whether the mouse is being moved and stores the resulting data
     * @param e the current SDL event
    */
    void CheckMouseMovement(SDL_Event* e);

    /**
     * @brief resets all input values to their original data
    */
    void ResetInputValues();
    /**
     * @brief resets key values to their original data
    */
    void ResetKeyValues();
    /**
     * @brief resets mouse button values to their original data
    */
    void ResetMouseButtonValues();
    /**
     * @brief resets mouse movement values to their original data
    */
    void ResetAxisValues();

    /**
     * @brief checks whether a key is held or down
     * @param keyCode the key's code
     * @return whether the key is held or down
    */
    bool GetKeyByCode(KeyCode keyCode);
    /**
     * @brief checks whether a key is held or down
     * @param c the key's character
     * @return whether the key is held or down
    */
    bool GetKey(char c);

    /**
     * @brief checks whether a key is down
     * @param keyCode the key's code
     * @return whether the key is down
    */
    bool GetKeyDownByCode(KeyCode keyCode);
    /**
     * @brief checks whether a key is down
     * @param c the key's character
     * @return whether the key is down
    */
    bool GetKeyDown(char c);

    /**
     * @brief checks whether a key is up
     * @param keyCode the key's code
     * @return whether the key is up
    */
    bool GetKeyUpByCode(KeyCode keyCode);
    /**
     * @brief checks whether a key is up
     * @param c the key's character
     * @return whether the key is up
    */
    bool GetKeyUp(char c);

    /**
     * @brief checks whether a mouse button is being held
     * @param mouseButton which button to check
     * @return whether the button is being held
    */
    bool GetMouseButton(int mouseButton);
    /**
     * @brief checks whether a mouse button is down
     * @param mouseButton which button to check
     * @return whether the button is down
    */
    bool GetMouseButtonDown(int mouseButton);
    /**
     * @brief checks whether a mouse button is up
     * @param mouseButton which button to check
     * @return whether the button is up
    */
    bool GetMouseButtonUp(int mouseButton);

    /**
     * @brief gets the value of a mouse movement axis
     * @param axisName whether to check Mouse X or Mouse Y
     * @return the value of the axis
    */
    int GetAxis(std::string axisName);

    /**
     * @brief prevents the cursor from moving
     * @param state the current state of the cursor
    */
    void LockCursor(bool state);
    bool CheckCursorLock();

    int GetMouseXPos() const;
    int GetMouseYPos() const;

    /**
     * @brief quits the game
    */
    void QuitGame();
    /**
     * @brief restarts the game
    */
    void RestartGame();
    /**
     * @brief saves the game
    */
    void SaveGame();
    /**
     * @brief loads the game from saved state
    */
    void LoadGame();
};

#define INPUT InputManager::Instance()

