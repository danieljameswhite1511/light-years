#pragma once
#include <string>

std::string GetResourceDir() {
#ifdef NDEBUG //if release mode
	return "assets/";
#else
	return "C:/Users/danie/CLionProjects/light-years/LightYearsGame/assets/";
#endif

}
