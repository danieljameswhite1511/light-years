#include "entryPoint.h"

#include "framework/Application.h"

void main()
{
	ly::Application* app = getApplication();

	app->Run();

	delete app;
}
