#include "OneginSort.h"

#include <stdio.h>  // fopen_s, printf, fread_s, fclose, fprintf, rewind, _fseeki64, _ftelli64
#include <stdlib.h> // malloc, realloc, free, qsort_s
#include <search.h> // qsort_s

text_t ReadFile(const char* __restrict cpPath, size_t* __restrict pLinesNum)
{
	text_t text   = NULL;
	FILE   *pFile = NULL;
	*pLinesNum    = 0ull;
	if(fopen_s(&pFile, cpPath, "r") != 0)
	{
		printf("Cannot open the file\n");

		return text;
	}

	_fseeki64(pFile, 0ll, SEEK_END);
	size_t filesize = _ftelli64(pFile);
	rewind(pFile);

	char *pBuffer = (char*)malloc(filesize * sizeof(char));
	if (!pBuffer)
		abort();

	fread_s(pBuffer, filesize, sizeof(char), filesize, pFile);

	text = (text_t)malloc(++(*pLinesNum) * sizeof(char*));
	if (!text)
	{
		free(pBuffer);

		abort();
	}
	text[*pLinesNum - 1] = pBuffer;
	while (++pBuffer)
		if (*pBuffer == '\n')
		{
			*pBuffer = '\0';
			
			/*text_t newText = (text_t)realloc(text, ++(*pLinesNum));
			if (!newText)
			{
				free(text);
				free(pBuffer);

				abort();
			}

			text = newText; // Should not free 'newText' because of swap. Also set2NULL(it will not be used)

			text[*pLinesNum] = ++pBuffer;*/
		}
	// Should not free 'pBuffer' because of moving the pointer to the 'text'. Also set2NULL
	fclose(pFile);

	return text;
}

bool Write2File(const char* __restrict cpPath, const text_t cText, size_t textSize)
{
	FILE *pFile = NULL;
	if (fopen_s(&pFile, cpPath, "w") != 0)
		return false;

	for (size_t i = 0ull; i < textSize; ++i)
		fprintf_s(pFile, "%s\n", cText[i]);

	fclose(pFile);

	return true;
}

static inline int __cdecl TowardTextSortComparator(void* __restrict pContext, const void* __restrict cpStr1, const void* __restrict cpStr2)
{
	_CRT_UNUSED(pContext);

	char *pStr1 = (char*)cpStr1;
	char *pStr2 = (char*)cpStr2;

	while (++pStr1 && ++pStr2)
		if (*pStr1 != *pStr2)
			return (*pStr1 > *pStr2);

	return (*pStr1 == '\0' ? true : false);
}

void TowardTextSort(text_t text, size_t textSize)
{
	qsort_s(text, textSize, sizeof(char*), TowardTextSortComparator, NULL);
}

static inline int __cdecl BackwardTextSortComparator(void* __restrict pContext, const void* __restrict cpStr1, const void* __restrict cpStr2)
{
	_CRT_UNUSED(pContext);

	char *pStr1 = (char*)cpStr1; while (++pStr1); // Set the pointer to the end of the string
	char *pStr2 = (char*)cpStr2; while (++pStr2); 

	while (--pStr1 != (char*)cpStr1 && --pStr2 != (char*)cpStr2)
		if (*pStr1 != *pStr2)
			return (*pStr1 < *pStr2);

	return (*pStr1 == *(char*)cpStr1 ? true : false);
}

void BackwardTextSort(text_t text, size_t textSize)
{
	qsort_s(text, textSize, sizeof(char*), BackwardTextSortComparator, NULL);
}


