#pragma once
// Fastbird Engine
// Written by Jungwan Byun
// https://fastbirddev.blogspot.com

#include "Types.h"
namespace fb
{

// Not thread safe
class DLL_EXPORT IRefCounted {
	uint32_t FBReferenceCount = 1;

public: // functions
	void AddRef() {
		++FBReferenceCount;
	}
	void Release() {
		--FBReferenceCount;
		if (FBReferenceCount == 0) {
			delete this;
		}
	}

protected: // functions
	virtual ~IRefCounted(){}
};

}
