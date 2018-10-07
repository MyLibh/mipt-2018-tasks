#pragma once

#ifndef __ONEGINSORT_HPP_INCLUDED__
#define __ONEGINSORT_HPP_INCLUDED__

#if (_MSVC_LANG < 201703L) 
#error Must use ISO C++17 Standart
#endif /* __cplusplus < 201703L */

#include <filesystem>

using line_t = std::string;
using text_t = std::vector<line_t>;

//====================================================================================================================================
//!
//! \brief  Reads the file
//! 
//! \param  crPath  Path to the file
//!
//! \return  Array of lines(std::string, ending with '\n')
//!
//====================================================================================================================================

text_t ReadFile(const std::filesystem::path &crPath);

//====================================================================================================================================
//!
//! \brief  Writes to file
//! 
//! \param  crPath  Path to the file
//! \param  crText  Text for writing
//!
//! \return  TRUE if successed overwise FALSE
//!
//====================================================================================================================================

bool Write2File(const std::filesystem::path &crPath, const text_t &crText);

//====================================================================================================================================
//!
//! \brief  Sorts string from the beginning using std::lexicographical_compare 
//! 
//! \param  rText  Text for sorting
//!
//====================================================================================================================================

void TowardTextSort(text_t &rText);

//====================================================================================================================================
//!
//! \brief  Sorts string from the end using std::lexicographical_compare
//! 
//! \param  rText  Text for sorting
//!
//====================================================================================================================================

void BackwardTextSort(text_t &rText);

#endif /* __ONEGINSORT_HPP_INCLUDED__ */