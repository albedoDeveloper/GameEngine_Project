#include "Engine.h"
#include "GraphicsLibraryEnum.h"

int main(int argc, char *args[])
{
	const int WINDOW_WIDTH = 1700;
	const int WINDOW_HEIGHT = 800;

	return ENGINE->Execute(GraphicsLibrary::OPENGL, WINDOW_WIDTH, WINDOW_HEIGHT);
}
