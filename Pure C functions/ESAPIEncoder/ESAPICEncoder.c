/*
 *  ESAPICEncoder.c
 *  ESAPI
 *
 *  Created by DEEPAK SUBRAMANIAN on 4/16/11.
 *  Copyright 2011 OWASP Foundation. All rights reserved.
 *
 */

#include "ESAPICEncoder.h"
#include "ESAPICUrlEncoder.h"
#include <stdio.h>
#include "ESAPICBase64Encoder.h"
#include <string.h>

//#include "urlEncoder.c"	
const int numberOfAvailableCodecs = 2;
ESAPIStringOperation * (* encodingFunctionsArray[2] )( char * ) = { ESAPICUrlEncoderEncode , ESAPICBase64EncoderEncode };
ESAPIStringOperation * (* decodingFunctionsArray[2] )( char * ) = { ESAPICUrlEncoderDecode , ESAPICBase64EncoderDecode };

ESAPIStringOperation * ESAPICEncode ( char * inputString, ESAPIEncodingType typeOfEncoding )
{
	printf( "\nESAPICEncoder => ESAPI Encoder Encode with inputString as %s",inputString );
	ESAPIStringOperation * encodedStringOperation; 	
	if ( typeOfEncoding < numberOfAvailableCodecs )
	{
		encodedStringOperation = encodingFunctionsArray[typeOfEncoding]( inputString );
	}
	else
	{
		encodedStringOperation = ( ESAPIStringOperation * ) malloc( sizeof( ESAPIStringOperation ) + 1 );
		encodedStringOperation->operationSuccessful = false;
		char messageString[] = "This codec is not yet supported by the implementation";
		encodedStringOperation->errorDescription = ( char * ) malloc( sizeof( char ) * strlen( messageString ) );
		strcpy( encodedStringOperation->errorDescription, messageString );
	}
	return encodedStringOperation;
}

ESAPIStringOperation * ESAPICDecode ( char * inputString, ESAPIEncodingType typeOfEncoding )
{
	printf( "\nESAPICDecoder => ESAPI Encoder Decode with inputString as %s",inputString );
	ESAPIStringOperation * decodedStringOperation; 
	if ( typeOfEncoding < numberOfAvailableCodecs )
	{
		decodedStringOperation = decodingFunctionsArray[typeOfEncoding]( inputString );
	}
	else
	{
		decodedStringOperation = ( ESAPIStringOperation * ) malloc( sizeof( ESAPIStringOperation ) + 1 );
		decodedStringOperation->operationSuccessful = false;
		char messageString[] = "This codec is not yet supported by the implementation";
		decodedStringOperation->errorDescription = ( char * ) malloc( sizeof( char ) * strlen( messageString ) );
		strcpy( decodedStringOperation->errorDescription, messageString );
	}
	return decodedStringOperation;
}

ESAPIStringOperation * ESAPICCanonicalizationForSpecificEncodingType ( char * inputString , ESAPIEncodingType typeOfEncoding, bool strict )
{
	printf( "\nESAPICCanonicalize the given string %s -- %d",inputString, typeOfEncoding );
	int iteration = 0;
	//inputString = realloc(inputString, sizeof(inputString)+1);
	//char * inputStringBuf = inputString + sizeof(inputString) - 1;
	//inputStringBuf = '\0';
	
	char * stringBeforeDecoding = ( char * ) malloc( sizeof ( char ) * 1 );
	*stringBeforeDecoding = '\0';
	char * stringAfterDecoding = ( char * ) malloc( ( sizeof ( char ) ) * strlen( inputString ) + 1 );//inputString;
	strcpy( stringAfterDecoding, inputString );
	ESAPIStringOperation * decodingStringOperation = ( ESAPIStringOperation * ) malloc( sizeof( ESAPIStringOperation ) + 1 );
	decodingStringOperation->operationSuccessful = true;
	decodingStringOperation->returnString = stringAfterDecoding;
	decodingStringOperation->errorDescription = NULL;
	
	printf( "The string comparison value = %d", strcmp( stringAfterDecoding, stringBeforeDecoding ) );
	while ( strcmp( stringAfterDecoding, stringBeforeDecoding ) != 0 )
	{
		free( stringBeforeDecoding );
		free( decodingStringOperation );
		
		printf( "\n\n--------\n\nThe string is %s and inputString is %s",stringAfterDecoding, inputString );
		stringBeforeDecoding = stringAfterDecoding;
		if ( strict )
		{
			iteration++;
			if ( iteration > 1 )
			{
				decodingStringOperation = ( ESAPIStringOperation * ) malloc( sizeof( ESAPIStringOperation ) );
				decodingStringOperation->operationSuccessful = false;
				char messageString[] = "Multiple Encoding Error";
				decodingStringOperation->errorDescription = ( char * ) malloc( sizeof( char ) * strlen( messageString ));
				strcpy( decodingStringOperation->errorDescription, messageString );
				decodingStringOperation->returnString = NULL;
				//break;
			}
			else
			{
				//Do nothing - Just continue
			}
			
		}
		
		decodingStringOperation = ESAPICDecode( stringBeforeDecoding, typeOfEncoding );
		if ( decodingStringOperation->operationSuccessful )
		{
			stringAfterDecoding = decodingStringOperation->returnString;
			printf("\n\n-*-*-*-*\nThe Input String after decoding is %s", inputString);
			printf("\nThe pointer to inputString is %p and pointer to stringAfterDecoding is %p \n the pointer to struct operation is %p",inputString,stringAfterDecoding,decodingStringOperation);
		}
		else
		{
			//break;
		}
		printf( "\nString before decoding -- %s \nString after decoding -- %s", stringBeforeDecoding, stringAfterDecoding );
	}
	return decodingStringOperation;
	//return NULL;
}

ESAPIStringOperation * ESAPICCanonicalizationAllAvailableEncodings ( char * inputString, bool strict )
{
		printf("\n\nThe given string was %s", inputString);
	int iteration = 0, encoding = 0;
	char * stringBeforeDecoding = ( char * ) malloc( sizeof( char ) * 1 );
	*stringBeforeDecoding = '\0';
	char * stringAfterDecoding = ( char * ) malloc( sizeof( char ) * strlen( inputString ));//inputString;
	strcpy( stringAfterDecoding, inputString );
	ESAPIStringOperation * decodingStringOperation = ( ESAPIStringOperation * ) malloc( sizeof(ESAPIStringOperation) );
	decodingStringOperation->operationSuccessful = true;
	decodingStringOperation->returnString = stringAfterDecoding;
		printf("\n\nThe given string was %s", inputString);
	for ( iteration = 0, encoding = 0 ; encoding < numberOfAvailableCodecs ; encoding++ ) 
	{
		printf("\n\n\n==========================\n\n");
		printf( "\n\n\nCodec - %d\n\n", encoding );
		//free( stringBeforeDecoding );
		//free( decodingStringOperation );
		stringBeforeDecoding = stringAfterDecoding;
		
		decodingStringOperation = ESAPICCanonicalizationForSpecificEncodingType( stringBeforeDecoding, encoding, strict );
		if ( decodingStringOperation->operationSuccessful )
		{
			stringAfterDecoding = decodingStringOperation->returnString;
			printf("String after decoding is %s", stringAfterDecoding);
		}
		else
		{
			break;
		}
			printf("\n\nThe given string was %s", inputString);
		if ( strcmp( stringAfterDecoding, stringBeforeDecoding ) != 0 ) 
		{
			if ( strict )
			{
				iteration++;
				if ( iteration > 1 )
				{
					free( decodingStringOperation );
					free( stringAfterDecoding );
					free( stringBeforeDecoding );
					
					decodingStringOperation = ( ESAPIStringOperation * ) malloc( sizeof( ESAPIStringOperation ) );
					decodingStringOperation->operationSuccessful = false;
					char messageString[] = "Multiple Encoding Error";
					decodingStringOperation->errorDescription = ( char * ) malloc( sizeof(char) * strlen( messageString ));
					strcpy( decodingStringOperation->errorDescription, messageString );
					break;
				}
				else
				{
					//Do nothing - Just continue
				}
				
			}
			
		}
		
		printf( "\nString before decoding -- %s \nString after decoding -- %s", stringBeforeDecoding, stringAfterDecoding );
	}
	printf("\n\nThe given string was %s", inputString);
	return decodingStringOperation;

}