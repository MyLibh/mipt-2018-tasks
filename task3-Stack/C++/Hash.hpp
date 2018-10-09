#pragma once

//====================================================================================================================================
//!
//!	\file   Hash.hpp
//!
//! \brief	Header file for generating hash 
//!
//====================================================================================================================================

#ifndef __cplusplus
	#error
	#error  Must use C++ to compile.
	#error
#endif /* __cplusplus */

#include <string_view> // std::basic_string_view
#include <cassert>     // assert

namespace NHash
{

#pragma region CONSTANTS

	constexpr unsigned short MIN_HASH_LENGTH = 4; //-V112
	constexpr unsigned short MD5_HASH_LENGTH = 1 << 5;
	
#pragma endregion

#pragma region CLASSES

	template<typename Char = char, typename Traits = std::char_traits<Char>>
	class Hash final
	{
	public:
		typedef std::basic_string_view<Char, Traits> str_view;
		typedef std::basic_string<Char, Traits>      str ;

//====================================================================================================================================
//!
//! \brief	Constructs hash from string
//!
//! \param  str  String to construct from 
//!
//====================================================================================================================================

		explicit Hash(str_view str);

//====================================================================================================================================
//!
//! \brief	 Constructs hash from string
//!
//! \param   x  Character
//!
//! \return  Existing code
//!
//====================================================================================================================================

		unsigned getExistCode(unsigned x) const noexcept;

//====================================================================================================================================
//!
//! \brief	Calculates control summary of the string
//!
//! \param  str  String to calculate
//!
//! \return Control summary
//!
//! \note   Only ASCI codes
//!
//====================================================================================================================================

		unsigned getControlSum(str_view str) const noexcept;

//====================================================================================================================================
//!
//! \brief	 Returns hash
//!
//! \param   hashLength  Hash length
//!
//! \return  String with hash 
//!
//====================================================================================================================================

		str_view getHash(unsigned short hashLength = MD5_HASH_LENGTH) const;

	private:
		mutable str hash_;
	};

	// template<typename Char, typename Traits> explicit Hash(std::basic_string_view<Char, Traits>)->Hash<Char, Traits>; // Deduction guide

#pragma endregion

#pragma region METHOD_DEFINITION

	template<typename Char, typename Traits>
	Hash<Char, Traits>::Hash(typename Hash<Char, Traits>::str_view str) :
		hash_(str)
	{ }

	template<typename Char, typename Traits>
	unsigned Hash<Char, Traits>::getExistCode(unsigned x) const noexcept
	{
		x += 256;
		while (!(((x < 57) && (x >= 48)) || ((x <= 90) && (x >= 65)) || ((x <= 122) && (x >= 97))))
			if (x < 48) x += 24;
			else        x -= 47;

			return x;
	}

	template<typename Char, typename Traits>
	unsigned Hash<Char, Traits>::getControlSum(typename Hash<Char, Traits>::str_view str) const noexcept
	{
		size_t length = str.length();

		unsigned sault = 0,
			mod = 1 << length;

		assert(mod);
		for (size_t i = 0; i < length; ++i)
			sault += (str[i] * (1 << (i + 1))) % mod;

		return sault % mod;
	}

	template<typename Char, typename Traits>
	typename Hash<Char, Traits>::str_view Hash<Char, Traits>::getHash(unsigned short hashLength /* = MD5_HASH_LENGTH */) const
	{
		assert(hashLength >= MIN_HASH_LENGTH);

		unsigned minLength     = 2,
			     realMinLength = 0,
			     strSault      = getControlSum(hash_),
			     strLength     = static_cast<unsigned>(hash_.length());

		while (minLength <= hashLength)
			realMinLength = (minLength <<= 1); // Get the length of a string that is a multiple of the power of two and closest to the length of the hash

		while (minLength < strLength)
			minLength <<= 1; // Get the number of the form 2 ^ n that is closest to the original length of the string

		if (minLength < (strLength << 1))
			minLength <<= 1;

		decltype(hash_) tmp(hash_);
		for (size_t i = 0, symbolsToAdd = static_cast<size_t>(minLength - strLength); i < symbolsToAdd; ++i) // Add missing items
		{
			if (i + 1 == static_cast<size_t>(strLength))
			{
				i -= static_cast<size_t>(strLength);

				symbolsToAdd -= static_cast<size_t>(strLength);
			}

			assert(((i + 1) % static_cast<size_t>(strLength) < static_cast<size_t>(strLength)) && ((i % static_cast<size_t>(strLength)) < static_cast<size_t>(strLength)));
			tmp += static_cast<char>(getExistCode(hash_[i % static_cast<size_t>(strLength)] + hash_[(i + 1) % static_cast<size_t>(strLength)]));
		}

		unsigned maxSault = getControlSum(tmp),
			     maxLength = static_cast<unsigned>(tmp.length());

		hash_.clear();
		while (tmp.length() != static_cast<size_t>(realMinLength))
		{
			for (size_t i = 0, mid = (tmp.length() >> 1); i < mid; ++i)
			{
				assert(mid != i && mid + i < tmp.length());

				hash_ += static_cast<char>(getExistCode(tmp[mid - 1] + tmp[mid + 1]));
			}

			tmp = hash_;
			hash_.clear();
		}

		unsigned symbolsToSub = realMinLength - hashLength;
		for (size_t i = 0, compressCount = static_cast<size_t>(realMinLength / symbolsToSub); hash_.length() < static_cast<unsigned>(hashLength - 4); ++i) // Removing redundant items //-V112
		{
			if (i % compressCount == 0) hash_ += static_cast<Char>(getExistCode(tmp[i] + tmp[++i]));
			else                        hash_ += static_cast<Char>(getExistCode(tmp[i]));
		}

		hash_ += static_cast<Char>(getExistCode(strSault));
		hash_ += static_cast<Char>(getExistCode(strLength));

		hash_ += static_cast<Char>(getExistCode(maxSault));
		hash_ += static_cast<Char>(getExistCode(maxLength));

		return hash_;
	}

#pragma endregion

} // namespace NHash
