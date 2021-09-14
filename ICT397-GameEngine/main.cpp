#include "Engine.h"
#include "GraphicsLibraryEnum.h"

int main(int argc, char* args[])
{
	const int WINDOW_WIDTH = 500;
	const int WINDOW_HEIGHT = 500;

	return ENGINE->Execute(GraphicsLibrary::OPENGL, WINDOW_WIDTH, WINDOW_HEIGHT);
}
