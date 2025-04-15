#ifndef FCP_ALGODS_BITMAP
#define FCP_ALGODS_BITMAP

#include "algo_ds/common/common.hpp"

#include <iostream>
#include <climits>
#include <array>
#include <limits>

#ifdef FCP_ALGODS_BITMAP_DEBUG
#include <stdexcept>
#endif

FCP_NAMESPACE_BEGIN
FCP_NAMESPACE_ALGODS_BEGIN

namespace internal
{
	// Bitmap of `CHAR_BIT` bits
	class basic_bitmap
	{
		public:
			// Create object from an array of values
			inline constexpr basic_bitmap(const std::array<bool, CHAR_BIT>& values) noexcept : m_byte{}
			{
				for (short i{0}; i < CHAR_BIT; i++)
					m_byte |= static_cast<unsigned char>(values[i]) << i;
			}

			// Create object from a single value
			inline constexpr basic_bitmap(const bool& value = false) noexcept
				: m_byte{ value ? std::numeric_limits<unsigned char>::max() : static_cast<unsigned char>(0) } {}

			// Flip `N`th bit at compile time
			template <short N>
			inline constexpr void flip(void) noexcept
			{
				m_byte ^= static_cast<unsigned char>(1) << N;
			}

			// Flip `n`th bit at runtime
			inline constexpr void flip(const short& n) noexcept
			{
				m_byte ^= static_cast<unsigned char>(1) << n;
			}

			// Return `N`th bit at compile time
			template <short N>
			inline constexpr bool at(void) const noexcept 
			{
				return (m_byte >> N) & static_cast<unsigned char>(1);
			}

			// Return `n`th bit at runtime
			inline constexpr bool at(const short& n) const noexcept
			{
				return (m_byte >> n) & static_cast<unsigned char>(1);
			}

			// Flip all bits at once
			inline constexpr void flip_all(void) noexcept
			{
				m_byte = ~m_byte;
			}

			// Set one bit to the desired value
			inline constexpr void set(const short& n, const bool& value)
			{
				m_byte = (m_byte & ~(static_cast<unsigned char>(1) << n)) | (static_cast<unsigned char>(value ? 1 : 0) << n);
			}

			// Set all bits to the same value at once at compile time
			template <bool B>
			inline constexpr void set_all(void) noexcept
			{
				m_byte = static_cast<unsigned char>( B ? std::numeric_limits<unsigned char>::max() : 0);
			}

			// Set all bits to the same value at once at runtime
			inline constexpr void set_all(const bool& value) noexcept
			{
				m_byte = static_cast<unsigned char>( value ? std::numeric_limits<unsigned char>::max() : 0);
			}

		private:
			unsigned char m_byte;
	};
}

#define FCP_COMPUTE_BYTES(Bits) ( (Bits == 0 ? 1 : 0) + Bits / CHAR_BIT + (Bits % CHAR_BIT == 0 ? 0 : 1) )
#define FCP_COMPUTE_BYTE_INDEX(n) ( ((n > 0) and (n % CHAR_BIT) == 0) ? (FCP_COMPUTE_BYTES(n)) : (FCP_COMPUTE_BYTES(n)-1) )

template <std::size_t Bits>
class Bitmap
{
	static_assert(0 <= Bits, "class Bitmap: `Bits` should be a positive number.\n");
	
	public:
#ifdef FCP_ALGODS_BITMAP_DEBUG
	constexpr static std::size_t _bits{ Bits };
#endif
		/// @Brief Create a bitmap from an array of boolean values
		inline constexpr Bitmap(const std::array<bool, Bits>& values) noexcept
		{
			std::size_t _i{0};
			for (std::size_t _byte{0}; _byte < FCP_COMPUTE_BYTES(Bits); _byte++)
			{
				for (short _bit{0}; _bit < CHAR_BIT; _bit++)
					m_bytes[_byte].set(_bit,values[_i++]);
			}
		}

		/// @Brief Create a bitmap with all bits set to the same value at once
		inline constexpr Bitmap(const bool& value = false) noexcept : m_bytes{}
		{
			for (internal::basic_bitmap& _byte : m_bytes)
				_byte.set_all(value);	
		}

		/// @Brief Flip `N`th bit at compile time
		template <std::size_t N>
		inline constexpr Bitmap<Bits>& flip(void) noexcept
		{
			static_assert(0 <= N and N <= (Bits - 1), "method Bitmap::flip<>(): N must be in the range [0, `Bits`-1].\n");

			m_bytes[FCP_COMPUTE_BYTE_INDEX(N)].template flip<N % CHAR_BIT>();
			return *this;
		}

		/// @Brief Flip `n`th bit at runtime 
		inline constexpr Bitmap<Bits>& flip(const std::size_t& n)
#ifndef FCP_ALGODS_BITMAP_DEBUG 
			noexcept
#endif
		{
#ifdef FCP_ALGODS_BITMAP_DEBUG
			if (n > Bits) throw std::out_of_range("method Bitmap::flip<>(): n must be in the range [0, `Bits`-1].\n"); 
#endif
			m_bytes[FCP_COMPUTE_BYTE_INDEX(n)].flip(n % CHAR_BIT);
			return *this;
		}

		/// @Brief Return `N`th bit at compile time
		/// @Detail The value is returned by VALUE not reference!
		template <std::size_t N>
		inline constexpr bool at(void) const noexcept
		{
			static_assert(0 <= N and N <= (Bits - 1), "method Bitmap::flip<>(): N must be in the range [0, `Bits`-1].\n");

			return m_bytes[FCP_COMPUTE_BYTE_INDEX(N)].template at<N % CHAR_BIT>();
		}

		/// @Brief Return `n`th bit at runtime
		/// @Detail The value is returned by VALUE not reference!
		inline constexpr bool at(const std::size_t& n) const 
#ifndef FCP_ALGODS_BITMAP_DEBUG
			noexcept
#endif
		{
#ifdef FCP_ALGODS_BITMAP_DEBUG
			if (n > Bits) throw std::out_of_range("method Bitmap::flip<>(): n must be in the range [0, `Bits`-1].\n"); 
#endif
			return m_bytes[FCP_COMPUTE_BYTE_INDEX(n)].at(n % CHAR_BIT);
		}

		/// @Brief Flip all bits at once
		inline constexpr Bitmap<Bits>& flip_all(void) noexcept
		{
			for (internal::basic_bitmap& _bit : m_bytes)
				_bit.flip_all();
			return *this;
		}

		/// @Brief Set all bits to the same value at once at compile time
		template <bool B>
		inline constexpr Bitmap<Bits>& set_all(void) noexcept
		{
			for (internal::basic_bitmap& _bit : m_bytes)
				_bit.set_all<B>();
			return *this;
		}

		/// @Brief Set all bits to the same value at once at runtime
		inline constexpr Bitmap<Bits>& set_all(const bool& value) noexcept
		{
			for (internal::basic_bitmap& _bit : m_bytes)
				_bit.set_all(value);
			return *this;
		}

	private:
		std::array<internal::basic_bitmap, FCP_COMPUTE_BYTES(Bits)> m_bytes;
};

FCP_NAMESPACE_ALGODS_END
FCP_NAMESPACE_END

template <std::size_t Bits>
std::ostream& operator<<(std::ostream& o, const fcp::algods::Bitmap<Bits> b)
{
	short _counter{0};
	for (std::size_t i{0}; i < Bits; i++)
	{
		o << b.at(i) << ' ';
		if(_counter++ == CHAR_BIT){ o << '\n'; _counter = 0; }
	}
	return o;
}

#endif	// FCP_ALGODS_BITMAP
