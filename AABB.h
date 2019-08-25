#pragma once
namespace fb
{
	struct AABB
	{
		static const size_t CORNER_COUNT = 8;

		float Center[3];            // Center of the box.
		float Extents[3];           // Distance from the center to each side.
	};
}