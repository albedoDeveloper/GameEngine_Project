#include "Engine.h"
#include "GraphicsLibraryEnum.h"

int main(int argc, char* args[])
{
	Engine engine;
	int windowWidth = 1800;
	int windowHeight = 1000;

	return engine.OnExecute(GraphicsLibrary::OPENGL, windowWidth, windowHeight);
}
