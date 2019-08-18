#pragma once
#ifndef FBCommon_Types_h
#define FBCommon_Types_h
// Fastbird Engine
// Written by Jungwan Byun
// https://fastbirddev.blogspot.com

// Configuretions
// FB_USE_BOOST, FB_USE_FILESYSTEM

#if FB_USE_BOOST
#include <boost/predef.h>
#include <boost/thread/shared_mutex.hpp>
#include <boost/thread/lock_types.hpp>
#endif
#include <vector>
#include <chrono>
#include "IntrusivePtr.h"
#include <filesystem>

namespace fb {
	using byte = unsigned char;
	using uint8 = unsigned char;
	using ushort = unsigned short;
	using uint16 = unsigned short;
	using uint32 = unsigned int;	
	using DWORD = unsigned long;
	using uint64 = unsigned __int64;
	using int64 = __int64;
	using Real = double;
	using IndexType = uint64;
	using FRAME_PRECISION = unsigned int;
	using TIME_PRECISION = Real;
	using CWSTR = const wchar_t*;
	using CSTR = const char*;

	using ByteArray = std::vector<unsigned char>;
	using RealArray = std::vector<Real>;
	using StringArray = std::vector<std::string>;
	using ClockType = std::chrono::high_resolution_clock;
	using TimePoint = std::chrono::time_point<ClockType>;
#if FB_USE_BOOST
	using SharedMutex = boost::shared_mutex;
	using SharedLock = boost::shared_lock<SharedMutex>;
	using UniqueLock = boost::unique_lock<SharedMutex>;
	using UpgradableLock = boost::upgrade_lock<SharedMutex>;
	using UpgradeToUniqueLock = boost::upgrade_to_unique_lock<SharedMutex>;
#endif
#if FB_USE_FILESYSTEM
	namespace FileSystem = std::filesystem;
	using Path = FileSystem::path;
	using Paths = std::vector<Path>;
	using DirectoryIterator = FileSystem::directory_iterator;
#endif

	struct Rect {
		int  left, top, right, bottom;
	};
	struct Rectf {
		Real left, top, right, bottom;
	};
	struct GameTime {
		TIME_PRECISION DeltaTime;
		TimePoint Time;
	};
	constexpr uint64_t InvalidIndex = (uint64_t)-1;
}
#define FBDeclarePointer(classname) class classname; typedef std::shared_ptr<classname> classname##Ptr; typedef std::weak_ptr<classname> classname##WeakPtr
#define FBDeclareIntrusivePointer(classname) class classname; typedef fb::intrusive_ptr<classname> classname##IPtr

#ifdef BOOST_OS_WINDOWS
#	ifdef _WINDLL
#		define DLL_EXPORT __declspec(dllexport)
#	else
#		define DLL_EXPORT __declspec(dllimport)
#	endif //_WINDLL
#else
#	define DLL_EXPORT 
#endif // BOOST_OS_WINDOWS

#define OVERRIDE override

#include "IRefCounted.h"

#endif //FBCommon_Types_h