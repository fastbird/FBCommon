#pragma once
// Fastbird Engine
// Written by Jungwan Byun
// https://fastbirddev.blogspot.com

#include <map>
#include <vector>
#include <iostream>
#include <memory>
#include "Types.h"
namespace fb 
{
	template <typename Observer>
	class Observable {
	public:
		typedef int ObserverEventType;
		typedef std::shared_ptr<Observer> ObserverPtr;
		typedef std::weak_ptr<Observer> ObserverWeakPtr;
	protected:
		std::map< ObserverEventType, std::vector<ObserverWeakPtr> > mObservers_;

	public:

		void AddObserver(ObserverEventType type, ObserverPtr observer) {
			if (!observer) {
				return;
			}
			auto& observers = mObservers_[type];
			if (!ValueExistsInVector(observers, observer)) {
				observers.push_back(observer);
				OnObserverAdded(observer);
			}
		}

		bool RemoveObserver(ObserverEventType type, ObserverPtr observer) {
			auto& observers = mObservers_[type];
			DeleteValuesInVector(observers, observer);
			return observersDeletedAny;
		}

		virtual void OnObserverAdded(ObserverPtr observer) {}
	};
}