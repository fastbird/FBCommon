#pragma once
#include "Types.h"
namespace fb
{

// Not thread safe
class DLL_EXPORT IInterface {
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
	virtual ~IInterface(){}
};

}
