#ifndef __ONEGINSORT_H_INCLUDED__
#define __ONEGINSORT_H_INCLUDED__

#include <stdbool.h>
#include <stddef.h>

#define MAX_PATH_LENGTH 256u

typedef char* line_t;
typedef line_t* __restrict text_t;

#ifdef _cplusplus
extern "C" {
#endif /* _cplusplus */

//====================================================================================================================================
//!
//! \brief  Reads the file
//! 
//! \param       cpPath     Path to the file
//! \param[out]  pTextSize  Var to store output array size
//!
//! \return  Array of lines(strings, ending with '\n')
//!
//! \note  Aborts in case of bad allocation
//!
//====================================================================================================================================

text_t ReadFile(const char* __restrict cpPath, size_t* __restrict pTextSize);

//====================================================================================================================================
//!
//! \brief  Writes to file
//! 
//! \param  cpPath    Path to the file
//! \param  cpText    Text for writing
//! \param  textSize  Size of the text(number of lines)
//!
//! \return  TRUE if successed overwise FALSE
//!
//====================================================================================================================================

bool Write2File(const char* __restrict cpPath, const text_t cText, size_t textSize);

//====================================================================================================================================
//!
//! \brief  Sorts string from the beginning using std::lexicographical_compare 
//!
//! \param[out]  pText     Text for sortingtextSize
//! \param       textSize  Size of the text
//!
//====================================================================================================================================

void TowardTextSort(text_t text, size_t textSize);

//====================================================================================================================================
//!
//! \brief  Sorts string from the end using std::lexicographical_compare
//! 
//! \param[out]  pText     Text for sortingtextSize
//! \param       textSize  Size of the text
//!
//====================================================================================================================================

void BackwardTextSort(text_t text, size_t textSize);

#ifdef _cplusplus
} // extern "C"
#endif /* _cplusplus */

#endif /* __ONEGINSORT_H_INCLUDED__ */