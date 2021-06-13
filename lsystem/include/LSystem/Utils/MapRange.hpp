#pragma once


namespace LSystem
{
	
	template<typename T>
	T MapRange(const T& value, const T& from_range_min, const T& from_range_max, const T& to_range_min, const T& to_range_max)
	{
		return to_range_min + (value - from_range_min) * (to_range_max - to_range_min) / (from_range_max - from_range_min);
	}

}
