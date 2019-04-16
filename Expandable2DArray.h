#pragma once
#undef min
#undef max
#include <algorithm>
#include <vector>
#include <iterator>
#include <chrono>
namespace fb
{
	// (0, 0) ----- (width, 0)
	// |
	// |
	// |
	// |
	// (0, height)

	template<typename DataType>
	class Expandable2DArray
	{
		using RowType = std::vector<DataType>;
		int mLeft = -1;
		int mTop = -1;
		std::vector<RowType> mData;
		unsigned int mNextCheckCol = -1;
		unsigned int mNextCheckRow = -1;
	public:
		void Add(const int left, const int top, DataType* data, const int width, const int height)
		{
			if (width == 0 || height == 0)
				return;

			auto currentHeight = mData.size();
			auto currentWidth = currentHeight > 0 ? mData[0].size() : 0;

			int leftAdd = 0;
			int topAdd = 0;
			int rightAdd = 0;
			int bottomAdd = 0;
			if (mLeft == -1) {
				mLeft = left;
				mTop = top;
				rightAdd = width;
				bottomAdd = height;
			}
			else {				
				auto leftAdd = std::max(0, mLeft - left);
				auto topAdd = std::max(0, mTop - top);
				auto rightAdd = std::max(0, (left + width) - (mLeft + currentWidth));
				auto bottomAdd = std::max(0, (top + height) - (mTop + currentHeight));
				mLeft = std::min(mLeft, left);
				mTop = std::min(mTop, top);
				auto finalWidth = currentWidth + leftAdd + rightAdd;
				auto finalHeight = currentHeight + topAdd + bottomAdd;
				if (topAdd > 0) {
					std::fill_n(std::front_inserter(mData), topAdd, RowType(finalWidth, (DataType*)nullptr));
				}
				if (bottomAdd > 0) {
					std::fill_n(std::back_inserter(mData), topAdd, RowType(finalWidth, (DataType*)nullptr));
				}
				if (leftAdd > 0) {
					for (int r = topAdd; r < finalHeight - bottomAdd; ++r) {
						std::fill_n(std::front_inserter(mData[r]), leftAdd, (DataType*)nullptr);
					}
				}
				if (rightAdd > 0) {
					for (int r = topAdd; r < finalHeight - bottomAdd; ++r) {
						std::fill_n(std::back_inserter(mData[r]), rightAdd, (DataType*)nullptr);
					}
				}
			}

			// copy data
			for (int r = 0; r < height; ++r) {
				auto sourceIndexR = r * width;
				auto destR = (top + r) - mTop;
				assert(destR > 0);
				for (int c = 0; c < width; ++c) {
					auto destC = (left + c) - mLeft;
					assert(destC > 0);
					auto sourceIndex = sourceIndexR + c;
					mData[destR][destC] = data[sourceIndex];
				}
			}
		}

		void RemoveOld()
		{
			using namespace std::chrono;
			using namespace std::chrono_literals;
			if (mData.empty()) return;
			auto now = high_resolution_clock::now();
			// row
			if (mNextCheckRow >= mData.size()) mNextCheckRow = mData.size() - 1;
			auto allEmpty = true;
			auto& row = mData[mNextCheckRow];
			for (auto& c : row) {
				if (c.mData) {
					if (now - c.mTime > 10s) {
						c.mData = nullptr;
					}
					else {
						allEmpty = false;
					}
				}
			}
			if (allEmpty) {
				mData.erase(mData.begin() + mNextCheckRow);
			}
			--mNextCheckRow;

			if (mData.empty())
				return;

			// col
			auto height = mData.size();
			allEmpty = true;
			if (mNextCheckCol >= mData[0].size())
				mNextCheckCol = mData[0].size() - 1;
			for (int r = 0; r < height; ++r) {
				auto& c = mData[r][mNextCheckCol];
				if (c.mData) {
					if (now - c.mTime > 10s) {
						c.mData = nullptr;
					}
					else {
						allEmpty = false;
					}
				}
			}
			if (allEmpty) {
				for (int r = 0; r < height; ++r) {
					mData[r].erase(mData[r].begin() + mNextCheckCol);
				}
				if (mData[0].empty()) {
					mData.clear();
				}
			}
			--mNextCheckCol;
		}

		int GetLeft() const { return mLeft; }
		int GetTop() const { return mTop; }
		int GetRight() const { return mData.empty() ? mLeft : mLeft + mData[0].size(); }
		int GetBottom() const { return mData.empty() ? mTop : mTop + mData.size(); }
		void ShiftIndex(int shiftX, int shiftY) { mLeft += shiftX; mTop += shiftY; }
	};
}
