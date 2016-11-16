#include <map>
#include <string>

namespace Instagram {
	
	class InstagramClient 
	{

		 public:
			using dict_t = std::map<std::string, std::string>;
                         auto callback(char *ptr_, size_t size_, size_t nmemb_, string &userdata_);

			InstagramClient() {};
			InstagramClient(dict_t settings) : settings_(settings) {};
			auto check_connection() -> bool;
                        auto get_most_recent_media()->void;
                      //  auto liked_by_user()-> void;
		
    private:
			dict_t settings_;
                        //auto callback(char *ptr_, size_t size_, size_t nmemb_, string &userdata_);

	};
}
