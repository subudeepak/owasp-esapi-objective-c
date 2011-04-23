/*
 *  ESAPICAuxiliaryFunctions.c
 *  ESAPI
 *
 *  Created by DEEPAK SUBRAMANIAN on 4/18/11.
 *  Copyright 2011 OWASP Foundation. All rights reserved.
 *
 */

#include "ESAPICAuxiliaryFunctions.h"

/**
 @brief Converts a hex character to its integer value 
 */
char from_hex(char ch) 
{
	return isdigit(ch) ? ch - '0' : tolower(ch) - 'a' + 10;
}

/**
 @brief Converts an integer value to its hex character
 */
char to_hex(char code) 
{
	static char hex[] = "0123456789abcdef";
	return hex[code & 15];
}
