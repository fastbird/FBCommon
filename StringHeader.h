#pragma once
#include <string>
#include <vector>
#include <string_view>
namespace fb
{
#if FB_USE_BOOST
	std::vector<std::string> Split( char* str, const char* delim)
	{
		std::string_view view(str);
		std::vector<std::string> ret;

		boost::split(ret, str, boost::is_any_of(delim));
		return ret;
	}
#else
	std::vector<std::string_view> Split(std::string_view str, std::string_view delim)
	{
		std::vector<std::string_view> ret;
		size_t startPos = 0;
		size_t pos = 0;
		std::string_view token;
		while ((pos = str.find(delim, startPos)) != std::string::npos) {
			token = str.substr(startPos, pos - startPos);
			ret.push_back(token);
			startPos = pos + 1;
		}
		if (startPos < str.size()) {
			ret.push_back(str.substr(startPos));
		}
		return ret;
	}
#endif
}
