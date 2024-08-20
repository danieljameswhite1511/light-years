#include "gameFramework/gameApplication.h"

ly::application* getApplication()
{
	return new ly::gameApplication{};
}