#pragma once
#include <string>

std::string GetResourceDir() {
#ifdef NDEBUG //if release mode
	return "assets/";
#else
	return "C:/Users/DanWhite/source/repos/danieljameswhite1511/light-years/LightYearsGame/assets/";
#endif

}
