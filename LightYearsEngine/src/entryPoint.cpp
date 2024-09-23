#include "entryPoint.h"

#include "framework/Application.h"

int main()
{
	ly::Application* app = getApplication();

	app->Run();

	delete app;

	return 0;
}
