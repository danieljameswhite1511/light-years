#include "entryPoint.h"

#include "framework/application.h"

void main()
{
	ly::application* app = getApplication();

	app->run();

	delete app;
}
