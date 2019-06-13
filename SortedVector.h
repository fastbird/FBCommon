#pragma once
// Fastbird Engine
// Written by Jungwan Byun
// https://fastbirddev.blogspot.com

#include <vector>
#include <algorithm>
namespace fb {

	template <class _Ty, class _Alloc = std::allocator<_Ty>>
	class SortedVector : public std::vector<_Ty, _Alloc> {
		using super = std::vector<_Ty, _Alloc>;
		using iterator = typename std::vector<_Ty, _Alloc>::iterator;
		
	public:
		iterator insert(const _Ty& v) {
			iterator it = std::lower_bound(super::begin(), super::end(), v);
			if (it != super::end() && *it == v) {
				*it = v;
			}
			else {
				it = super::insert(it, v);
			}
			return it;
		}

		bool contains(const _Ty& v) const {
			return std::binary_search(super::begin(), super::end(), v);
		}

		bool erase(const _Ty& v) {
			auto it = std::lower_bound(super::begin(), super::end(), v);
			if (it != super::end() && *it == v) {
				super::erase(it);
				return true;
			}
			return false;
		}

	private:
		void push_back(const _Ty& v) = delete;
	};
}
