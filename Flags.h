#pragma once
#ifndef FBCommon_Flags_h
#define FBCommon_Flags_h
#include <inttypes.h>
namespace fb
{
	template <typename FlagBitsType> struct FlagTraits
	{
		enum { allFlags = 0 };
	};

	template <typename BitType, typename MaskType = uint32_t>
	class Flags
	{
	public:
		constexpr Flags()
			: m_mask(0)
		{
		}

		Flags(BitType bit)
			: m_mask(static_cast<MaskType>(bit))
		{
		}

		Flags(Flags<BitType> const& rhs)
			: m_mask(rhs.m_mask)
		{
		}

		explicit Flags(MaskType flags)
			: m_mask(flags)
		{
		}

		Flags<BitType> & operator=(Flags<BitType> const& rhs)
		{
			m_mask = rhs.m_mask;
			return *this;
		}

		Flags<BitType> & operator|=(Flags<BitType> const& rhs)
		{
			m_mask |= rhs.m_mask;
			return *this;
		}

		Flags<BitType> & operator&=(Flags<BitType> const& rhs)
		{
			m_mask &= rhs.m_mask;
			return *this;
		}

		Flags<BitType> & operator^=(Flags<BitType> const& rhs)
		{
			m_mask ^= rhs.m_mask;
			return *this;
		}

		Flags<BitType> operator|(Flags<BitType> const& rhs) const
		{
			Flags<BitType> result(*this);
			result |= rhs;
			return result;
		}

		Flags<BitType> operator&(Flags<BitType> const& rhs) const
		{
			Flags<BitType> result(*this);
			result &= rhs;
			return result;
		}

		Flags<BitType> operator^(Flags<BitType> const& rhs) const
		{
			Flags<BitType> result(*this);
			result ^= rhs;
			return result;
		}

		bool operator!() const
		{
			return !m_mask;
		}

		Flags<BitType> operator~() const
		{
			Flags<BitType> result(*this);
			result.m_mask ^= FlagTraits<BitType>::allFlags;
			return result;
		}

		bool operator==(Flags<BitType> const& rhs) const
		{
			return m_mask == rhs.m_mask;
		}

		bool operator!=(Flags<BitType> const& rhs) const
		{
			return m_mask != rhs.m_mask;
		}

		explicit operator bool() const
		{
			return !!m_mask;
		}

		explicit operator MaskType() const
		{
			return m_mask;
		}

	private:
		MaskType  m_mask;
	};

	template <typename BitType>
	Flags<BitType> operator|(BitType bit, Flags<BitType> const& flags)
	{
		return flags | bit;
	}

	template <typename BitType>
	Flags<BitType> operator&(BitType bit, Flags<BitType> const& flags)
	{
		return flags & bit;
	}

	template <typename BitType>
	Flags<BitType> operator^(BitType bit, Flags<BitType> const& flags)
	{
		return flags ^ bit;
	}
}
#endif //FBCommon_Flags_h
