/*
 *  ESAPIEncoderExample.c
 *  ESAPI
 *
 *  Created by DEEPAK SUBRAMANIAN on 4/22/11.
 *  Copyright 2011 OWASP Foundation. All rights reserved.
 *
 */
#include <stdio.h>
#include "ESAPICEncoder.h"
#include <curses.h>
#include <string.h>

int main( void )//int argc, char *argv[]
{
	char givenString[] = "https://www.owasp.org/index.php/Category:OWASP_Enterprise_Security_API#tab=Objective_C";
	char *pointerToString = givenString; //Should not free this pointer - It will free itself.
	char *stringToDecode; //Will be given memory once the encoded string is obtained.
	printf( "%s",givenString );
	
	
	//Starting Encoding
	printf( "\nStarting Encoding ............\n" );
	ESAPIStringOperation * encodingOperation = ESAPIEncode( pointerToString, ESAPIEncodingTypeURLEncoding );
	if ( encodingOperation->operationSuccessful ) //Operation was successful
	{
		printf( "\nOperation Successful" );
		printf( "\nThe string obtained is %s",encodingOperation->returnString );
		stringToDecode = ( char * ) malloc(sizeof( encodingOperation->returnString ) + 1);
		strcpy( stringToDecode, encodingOperation->returnString );
		printf( "\nThe string to decode is %s",stringToDecode );
		free( encodingOperation->returnString );
	}
	else //Operation Failed
	{
		printf( "\nOperation Failed" );
		printf( "\nThe reason for failure: %s",encodingOperation->errorDescription );
		free( encodingOperation->errorDescription );
	}
	free( encodingOperation );
	
	//Starting Decoding
	printf( "\nStarting Decoding......... with stringToDecode as %s\n",stringToDecode );
	ESAPIStringOperation * decodingOperation = ESAPIDecode( stringToDecode, ESAPIEncodingTypeURLEncoding );
	if ( decodingOperation->operationSuccessful ) //Operation was successful
	{
		printf( "\nOperation Successful" );
		printf( "\nThe string obtained is %s",decodingOperation->returnString );		
	}
	else //Operation Failed
	{
		printf( "\nOperation Failed" );
		printf( "\nThe reason for failure: %s",decodingOperation->errorDescription );
		free( decodingOperation->errorDescription );
	}
	free( decodingOperation );
	free( stringToDecode );
	getchar();
	return 0;
}