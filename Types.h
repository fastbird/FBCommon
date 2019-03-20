#pragma once
#ifndef FBCommon_Types_h
#define FBCommon_Types_h

#include <vector>
#include <chrono>
#include <boost/thread/shared_mutex.hpp>
#include <boost/thread/lock_types.hpp>
#include <filesystem>

namespace fb {
	using byte = unsigned char;
	using uint8 = unsigned char;
	using ushort = unsigned short;
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
	using SharedMutex = boost::shared_mutex;
	using SharedLock = boost::shared_lock<SharedMutex>;
	using UniqueLock = boost::unique_lock<SharedMutex>;
	using UpgradableLock = boost::upgrade_lock<SharedMutex>;
	using UpgradeToUniqueLock = boost::upgrade_to_unique_lock<SharedMutex>;
	namespace FileSystem = std::filesystem;
	using Path = FileSystem::path;
	using Paths = std::vector<Path>;
	using DirectoryIterator = FileSystem::directory_iterator;

	struct Rect {
		int  left, top, right, bottom;
	};
	struct Rectf {
		Real left, top, right, bottom;
	};
	struct GameTime {
		Real DeltaTime;
		TimePoint Time;
	};
}
#define FBDeclarePointer(classname) class classname; typedef std::shared_ptr<classname> classname##Ptr; typedef std::weak_ptr<classname> classname##WeakPtr;

#endif //FBCommon_Types_h