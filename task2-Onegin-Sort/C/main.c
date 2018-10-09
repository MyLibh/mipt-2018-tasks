#include "OneginSort.h"

#include <stdio.h>  // printf, scanf_s
#include <stdlib.h> // system
#include <string.h> // strncpy, strcat, strlen

#define _CRT_SECURE_NO_WARNINGS // Disable error C4996:

char *NULL_TOKEN = NULL;

int main(void)
{
	int  rc = 0;
	char path[MAX_PATH_LENGTH] = "";

	printf("Enter path:\n");
	scanf_s("%s", path, MAX_PATH_LENGTH);

	size_t textSize = 0ull;
	text_t text4tts = ReadFile(path, &textSize);
	if (!textSize)
	{
		system("pause");
		return 1;
	}

	TowardTextSort(text4tts, textSize);

	char *pFilepathWithoutStem      = strtok_s(path, ".", &NULL_TOKEN);
	char  path4tts[MAX_PATH_LENGTH] = "";
	strcat_s(path4tts, MAX_PATH_LENGTH, "_toward.");
	strcat_s(path4tts, MAX_PATH_LENGTH, strtok_s(pFilepathWithoutStem, ".", &NULL_TOKEN));
	if (!Write2File(path4tts, text4tts, textSize))
	{
		printf("Cannot write to file\n"); // D:\Aleksei\Documents\Github\mipt-2018-tasks\task2-Onegin-Sort\res\orig.txt
		rc = 1;

		goto cleanup;
	}

cleanup:
	free(text4tts[0]); // Or all block?
	free(text4tts);

	system("pause");
	return rc;
}