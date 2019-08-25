#pragma once
#include <string>
#include <vector>
#include <string_view>
namespace fb
{
	std::vector<std::string> Split( char* str, const char* delim)
	{
		std::string_view view(str);
		std::vector<std::string> ret;

		boost::split(ret, str, boost::is_any_of(delim));
		return ret;
	}
}
