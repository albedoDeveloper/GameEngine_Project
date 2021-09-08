#include "Engine.h"
#include "GraphicsLibraryEnum.h"

int main(int argc, char* args[])
{
	Engine engine;
	int windowWidth = 1700;
	int windowHeight = 900;

	return engine.OnExecute(GraphicsLibrary::OPENGL, windowWidth, windowHeight);
}
