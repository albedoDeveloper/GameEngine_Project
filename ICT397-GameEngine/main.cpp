#include "Engine.h"
#include "GraphicsLibraryEnum.h"

int main(int argc, char* args[])
{
	Engine engine;
	int windowWidth = 700;
	int windowHeight = 700;

	return engine.OnExecute(GraphicsLibrary::OPENGL, windowWidth, windowHeight);
}
