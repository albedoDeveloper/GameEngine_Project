#include "Engine.h"
#include "GraphicsLibraryEnum.h"

int main(int argc, char* args[])
{
	Engine engine;

	return engine.OnExecute(GraphicsLibrary::OPENGL);
}
