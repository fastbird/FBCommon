#pragma once

#define FBIteratingWeakContainer(container, it, var)\
	auto (var) = (it)->lock();\
	if (!(var)){\
		(it) = (container).erase((it));\
		continue;\
	}\
	++it;

#define FBIteratingWeakContainerNoErase(container, it, var)\
	auto (var) = (it)->lock();\
	++it;\
	if (!(var)){\
		continue;\
	}

#define FBValueExistsInVector(arr, v)	(std::find(arr.begin(), arr.end(), v) != arr.end())

#define FBDeleteValuesInVector_Size(arr, v) \
	unsigned arr ## SizeBefore = arr.size(); \
	arr.erase(std::remove(arr.begin(), arr.end(), v), arr.end()); \
	unsigned arr ## SizeAfter = arr.size();

#define FBDeleteValuesInVector(arr, v) \
	auto arr##It = std::remove(arr.begin(), arr.end(), v);\
	bool arr##DeletedAny = arr##It != arr.end();\
	arr.erase(arr##It, arr.end());	

#define FBDeleteValuesInVectorWeak(arr, v) \
	using FBElementType = typename std::decay<decltype(*arr.begin())>::type;\
	auto FBdeleteFrom = std::remove_if(arr.begin(), arr.end(), [&v](const FBElementType& p){return p.lock() == v;});\
	bool FBdeletedAny = FBdeleteFrom != arr.end();\
	arr.erase(FBdeleteFrom, arr.end());

#define FBDeleteValuesInList(arr, v) \
	unsigned arr ## SizeBefore = arr.size(); \
	for (auto it = arr.begin(); it != arr.end();)\
		{\
		if ((*it) == v)\
				{\
			it = mChildren.erase(it);\
				}\
				else\
				{\
			++it;\
				}\
		}\
	unsigned arr ## SizeAfter = arr.size();

template<typename T>
bool FBValidCString(T str) {
	return str && str[0] != 0;
}