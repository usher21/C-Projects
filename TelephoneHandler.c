#include <string.h>
#include "TelephoneHandler.h"

/*--------------------------------------------------------------------------------------------------------*/

void deleteSpaces(char *str)
{
	int i = 0;

	while(str[i] != '\0') {
		while (str[i] == ' ')
		{
			for (int j = i; j < strlen(str); ++j)
			{
				str[j] = str[j + 1];
			}
		}
		i++;
	}
}

/*--------------------------------------------------------------------------------------------------------*/

bool isValidNum(char *num)
{
	return isNumString(num) && isValidIntial(num) && strlen(num) == 9;
}

/*--------------------------------------------------------------------------------------------------------*/

bool isNumString(char *num)
{
	for (int i = 0; i < strlen(num); ++i)
	{
		if (!isNum(num[i]))
		{
			return false;
		}
	}

	return true;
}

/*--------------------------------------------------------------------------------------------------------*/

bool isNum(char car)
{
	return car >= '0' && car <= '9';
}

/*--------------------------------------------------------------------------------------------------------*/

bool isValidIntial(char *num)
{
	return (num[0] == '7' ) && (num[1] == '8' || num[1] == '7' || num[1] == '6' || num[1] == '5' || num[1] == '0');
}

/*------------------------------------------------------------------------------------------*/

char *formatNum(char *num)
{
	static char numero[13];

	numero[0] = num[0];
	numero[1] = num[1];
	numero[2] = ' ';
	numero[3] = num[2];
	numero[4] = num[3];
	numero[5] = num[4];
	numero[6] = ' ';
	numero[7] = num[5];
	numero[8] = num[6];
	numero[9] = ' ';
	numero[10] = num[7];
	numero[11] = num[8];

	return numero;
}

/*------------------------------------------------------------------------------------------*/
