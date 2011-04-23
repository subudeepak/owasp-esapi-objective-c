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
#include <string.h>

//#include "urlEncoder.c"	

ESAPIStringOperation * ESAPIEncode ( char * inputString, ESAPIEncodingType typeOfEncoding )
{
	printf( "\nESAPICEncoder => ESAPI Encoder Encode with inputString as %s",inputString );
	//Initiate a encodedStringOperation (Allocate memory)
	//ESAPIStringOperation temp;
	ESAPIStringOperation * encodedStringOperation = ( ESAPIStringOperation * ) malloc( sizeof(ESAPIStringOperation) + 1 );
	//The operation to be performed is still not complete - Mark as unsuccessful
	encodedStringOperation->operationSuccessful = false;
	//Check which encoding to perform
	switch ( typeOfEncoding )
	{
		case ESAPIEncodingTypeURLEncoding: //ESAPIEncodingTypePercentEncoding
		{
			//Perform encoding
			encodedStringOperation->returnString = ESAPICUrlEncoderEncode( inputString ); //Perform Url Encoding
			//Set operation as successful
			encodedStringOperation->operationSuccessful = true;
		}
			break;
			
		case ESAPIEncodingTypeBase64Encoding:
		{
			//INCOMPLETE
			//Set operation successful as false
			encodedStringOperation->operationSuccessful = false;
			//Set an error description message
			encodedStringOperation->errorDescription = "This Encoding is not yet implemented";
		}
			break;

		default:
		{
			//Invalid encoding
			//Set operation as failed
			encodedStringOperation->operationSuccessful = false;
			//Set an error message
			(encodedStringOperation->errorDescription) = "Invalid encoding error - This encoding is currently not supported";
		}
			break;
	}
	return encodedStringOperation;
}


ESAPIStringOperation * ESAPIDecode ( char * inputString, ESAPIEncodingType typeOfEncoding )
{
	printf( "\nESAPICEncoder => ESAPI Encoder Decode with inputString as %s",inputString );
	//Initiate a decodedStringOperation (Allocate memory)
	//ESAPIStringOperation temp;
	ESAPIStringOperation * decodedStringOperation = ( ESAPIStringOperation * ) malloc( sizeof(ESAPIStringOperation) + 1 );
	//The operation to be performed is still not complete - Mark as unsuccessful
	decodedStringOperation->operationSuccessful = false;
	//Check which encoding whose decoding to perform
	switch ( typeOfEncoding )
	{
		case ESAPIEncodingTypeURLEncoding: //ESAPIEncodingTypePercentEncoding
		{
			//Perform decoding
			decodedStringOperation->returnString = ESAPICUrlEncoderDecode( inputString ); //Perform Url Decoding
			//Set operation as successful
			decodedStringOperation->operationSuccessful = true;
		}
			break;
			
		case ESAPIEncodingTypeBase64Encoding:
		{
			//INCOMPLETE
			//Set operation successful as false
			decodedStringOperation->operationSuccessful = false;
			//Set an error description message
			char message[] = "This Encoding is not yet implemented";
			decodedStringOperation->errorDescription = malloc( sizeof( message ) );
			strcpy( decodedStringOperation->errorDescription, message );
		}
			break;
			
		default:
		{
			//Invalid encoding
			//Set operation as failed
			decodedStringOperation->operationSuccessful = false;
			//Set an error message
			char message[] = "Invalid encoding error - This encoding is currently not supported";
			decodedStringOperation->errorDescription = malloc( sizeof( message ) );
			strcpy( decodedStringOperation->errorDescription, message );
		}
			break;
	}
	return decodedStringOperation;
}

ESAPIStringOperation * ESAPICanonicalizationForSpecificEncodingType ( ESAPIEncodingType typeOfEncoding, bool strict )
{
	return NULL;
}

ESAPIStringOperation * ESAPICanonicalizationAllAvailableEncodings ( bool strict )
{
	return NULL;
}