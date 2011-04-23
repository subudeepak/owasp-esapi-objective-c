/**
 *  ESAPICUrlEncoder.c
 *  ESAPI
 *
 *  Created by DEEPAK SUBRAMANIAN on 4/18/11.
 *  Copyright 2011 OWASP Foundation. All rights reserved.
 *	This code has been downloaded from http://www.geekhideout.com/urlcode.shtml on April 16, 2011
 */

#include "ESAPICUrlEncoder.h"
#include "ESAPICAuxiliaryFunctions.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

/** 
 @brief Returns a url-encoded version of the given input string
 
 IMPORTANT: be sure to free() the returned string after use 
 This code has been downloaded from http://www.geekhideout.com/urlcode.shtml on April 16, 2011
 
 @param inputString - This is the input string which needs to be decoded
 @return The decoded string IMPORTANT: be sure to free() the returned string after use 

 */
char * ESAPICUrlEncoderEncode ( char *inputString ) 
{
	printf("\n Encoding initiated");
	char *pstr = inputString , *buf = malloc( strlen( inputString ) * 3 + 1 ), *pbuf = buf;
	while ( *pstr ) 
	{
		if ( isalnum(*pstr) || *pstr == '-' || *pstr == '_' || *pstr == '.' || *pstr == '~' ) 
			*pbuf++ = *pstr;
		else if ( *pstr == ' ' ) 
			*pbuf++ = '+';
		else 
		{
			*pbuf++ = '%', *pbuf++ = to_hex( *pstr >> 4 ), *pbuf++ = to_hex( *pstr & 15);
		}
		pstr++;
	}
	*pbuf = '\0';
	return buf;
}

/**
 @brief Returns a url-decoded version of the given string
 
 This code has been downloaded from http://www.geekhideout.com/urlcode.shtml on April 16, 2011

 @param inputString - This is the input string which needs to be decoded
 @return The decoded string IMPORTANT: be sure to free() the returned string after use 
 */
char * ESAPICUrlEncoderDecode ( char *inputString ) 
{
	printf( "The inputString is %s",inputString );
	char *pstr = inputString, *buf = malloc( strlen( inputString ) + 1), *pbuf = buf;
	while ( *pstr ) 
	{
		if ( *pstr == '%' ) 
		{
			if ( pstr[1] && pstr[2] ) 
			{
				*pbuf++ = from_hex( pstr[1] ) << 4 | from_hex( pstr[2] );
				pstr += 2;
			}
		} 
		else if ( *pstr == '+' ) 
		{ 
			*pbuf++ = ' ';
		}	
		else 
		{
			*pbuf++ = *pstr;
		}
		pstr++;
	}
	*pbuf = '\0';
	return buf;
}

