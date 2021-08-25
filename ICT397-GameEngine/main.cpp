#include "Engine.h"
#include "GraphicsLibraryEnum.h"

int main(int argc, char* args[])
{
	Engine engine;
	int windowWidth = 1000;
	int windowHeight = 700;

	return engine.OnExecute(GraphicsLibrary::OPENGL, windowWidth, windowHeight);
}
