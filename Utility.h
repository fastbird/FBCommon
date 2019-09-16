#pragma once
// Fastbird Engine
// Written by Jungwan Byun
// https://fastbirddev.blogspot.com

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

#define FBDeleteOneValueInVector(arr, v)\
	auto it = std::find(arr.begin(), arr.end(), v);\
	arr.erase(it);

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

#define FBSafeRelease(p) if ((p)) {(p)->Release(); (p) = nullptr;}

namespace fb {
	template <class T>
	void ClearWithSwap(T& m)
	{
		T empty;
		std::swap(m, empty);
	}

	template<typename T>
	bool ValidCString(T str) {
		return str && str[0] != 0;
	}

	template<class T>
	unsigned RemoveInvalidWeakPtr(std::vector<T>& v) {
		unsigned numDeleted = 0;
		for (auto it = v.begin(); it != v.end(); /**/) {
			auto data = it->lock();
			if (!data) {
				it = v.erase(it);
				++numDeleted;
				continue;
			}
			++it;
		}
		return numDeleted;
	}

	inline unsigned int CalcAligned(unsigned int value, unsigned int alignment)
	{
		// Example: Suppose value = 300, alignment = 256.
		// (300 + 255) & ~255
		// 555 & ~255
		// 0x022B & ~0x00ff
		// 0x022B & 0xff00
		// 0x0200
		// aligned value = 512
		return (value + (alignment-1)) & ~(alignment-1);
	}

	inline int Rand(int a, int b)
	{
		return a + rand() % ((b - a) + 1);
	}

	inline float RandF()
	{
		return (float)(rand()) / (float)RAND_MAX;
	}

	inline float RandF(float a, float b)
	{
		return a + RandF() * (b - a);
	}
}