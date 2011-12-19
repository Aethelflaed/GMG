#include "stringCase.h"

void strtolower(char* string)
{
	while (*string != 0)
	{
		if (*string >= 'A' && *string <= 'Z')
		{
			*string = *string + 'a' - 'A';
		}
		string++;
	}
}

void strtoupper(char* string)
{
	while (*string != 0)
	{
		if (*string >= 'a' && *string <= 'z')
		{
			*string = *string + 'A' - 'a';
		}
		string++;
	}
}

