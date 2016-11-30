// 
// Boost.Process 
// ~~~~~~~~~~~~~ 
// 
// Copyright (c) 2006, 2007 Julio M. Merino Vidal 
// Copyright (c) 2008 Boris Schaeling 
// 
// Distributed under the Boost Software License, Version 1.0. (See accompanying 
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt) 
// 

#include <boost/process.hpp> 
#include <string> 
#include <vector> 
#include <iostream> 
#include <regex>

namespace bp = ::boost::process; 

bp::child start_child() 
{ 
    std::string exec = "./Examples"; 

    std::vector<std::string> args; 
    args.push_back("./Examples"); 
    args.push_back("1"); 
    args.push_back("0"); 

    bp::context ctx; 
    ctx.stdout_behavior = bp::capture_stream(); 

    return bp::launch(exec, args, ctx); 
} 

int count_words(const std::string& str, const std::string& word)
{
    const std::regex expression(word);

    return static_cast<int>(std::distance(
        std::sregex_iterator(str.begin(), str.end(), expression),
        std::sregex_iterator()));
}

int main(int argc, char** argv) 
{ 
    if(argc != 2)
    {
        std::cout << "usage: " << argv[0] << " {search_word}" << std::endl;
        return -1;
    }

    const std::string search_word = argv[1];
    bp::child c = start_child(); 

    bp::pistream &is = c.get_stdout(); 
    std::string line; 
    while (std::getline(is, line)) 
    {
        std::cout << line << std::endl; 
        std::cout << "count of word '" << search_word << "': " << count_words(line, search_word) << std::endl;
    }

    return 0;
} 