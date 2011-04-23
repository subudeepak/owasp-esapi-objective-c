/*
 *  ESAPIEncoderExample.c
 *  ESAPI
 *
 *  Created by DEEPAK SUBRAMANIAN on 4/22/11.
 *  Copyright 2011 OWASP Foundation. All rights reserved.
 *
 */
#include <stdio.h>
#include "ESAPIEncoderExample.h"
#include "ESAPICEncoder.h"

int main( void )
{
	char givenString[] = "https://www.owasp.org/index.php/Category:OWASP_Enterprise_Security_API#tab=Objective_C";
	char *pointerToString = givenString;
	printf( "%s",givenString );
	ESAPIStringOperation * encodingOperation = ESAPIEncode( pointerToString, ESAPIEncodingTypeURLEncoding );
	if ( encodingOperation->operationSuccessful ) 
	{
		printf("Operation Successful");
		printf("The string obtained is %s",(encodingOperation->returnString));
	}
	else
	{
		printf("Operation Failed");
		printf("The reason for failure: %s",(encodingOperation->errorDescription));
	}

}