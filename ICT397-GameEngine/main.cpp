#include "Engine.h"
#include "GraphicsLibraryEnum.h"

int main(int argc, char* args[])
{
	Engine engine;
	const int WINDOW_WIDTH = 1700;
	const int WINDOW_HEIGHT = 900;

	return engine.OnExecute(GraphicsLibrary::OPENGL, WINDOW_WIDTH, WINDOW_HEIGHT);
}
