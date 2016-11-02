#include <map>
#include <string>

namespace Instagram {
	
	class InstagramClient 
	{

		 public:
			using dict_t = std::map<std::string, std::string>;

			InstagramClient() {};
			InstagramClient(dict_t settings) : settings_(settings) {};
			auto check_connection() -> bool;
		
    private:
			dict_t settings_;

	};
}
