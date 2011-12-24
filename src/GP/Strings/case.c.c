#include "case.h"

char* strtolower(char* string)
{
	char* stringBegin = string;
	while (*string != 0)
	{
		if (*string >= 'A' && *string <= 'Z')
		{
			*string = *string + 'a' - 'A';
		}
		string++;
	}
	return stringBegin;
}

char* strtoupper(char* string)
{
	char* stringBegin = string;
	while (*string != 0)
	{
		if (*string >= 'a' && *string <= 'z')
		{
			*string = *string + 'A' - 'a';
		}
		string++;
	}
	return stringBegin;
}

