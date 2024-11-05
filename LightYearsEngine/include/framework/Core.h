
#include <map>
#include <memory>
#include <set>
#include <stdio.h>
#include <unordered_map>
#include <vector>
#include <unordered_set>

namespace ly {

	template<typename T>
	using unique = std::unique_ptr<T>;

	template<typename T>
	using shared = std::shared_ptr<T>;

	template<typename T>
	using weak = std::weak_ptr<T>;

	template<typename T>
	using List = std::vector<T>;

	//the less predicate will order number ascending
	template<typename Tkey, typename Tvalue, typename pr = std::less<Tkey>>
	using map = std::map<Tkey, Tvalue, pr>;

	template<typename Tkey, typename Tvalue, typename hash = std::hash<Tkey>>
	using dictionary = std::unordered_map<Tkey, Tvalue, hash>;

	template<typename T>
	using set = std::unordered_set<T>;

	using uint8 = unsigned char;

//this is a macro, and how it is defined, the flush part is to refresh the console straight away
#define LOG(M, ...)  do { printf(M "\n", ##__VA_ARGS__); fflush(stdout); } while (0)


}
