
#include <map>
#include <memory>
#include <stdio.h>
#include <unordered_map>

namespace ly {

	template<typename T>
	using unique = std::unique_ptr<T>;

	template<typename T>
	using shared = std::shared_ptr<T>;

	template<typename T>
	using weak = std::weak_ptr<T>;

	template<typename T>
	using list = std::vector<T>;

	//the less predicate will order number ascending
	template<typename Tkey, typename Tvalue, typename pr = std::less<Tkey>>
	using map = std::map<Tkey, Tvalue, pr>;

	template<typename Tkey, typename Tvalue, typename hash = std::hash<Tkey>>
	using dictionary = std::unordered_map<Tkey, Tvalue, hash>;

//this is a macro, and how it is defined 
#define LOG(M, ...)  printf(M "\n", ##__VA_ARGS__)


}
