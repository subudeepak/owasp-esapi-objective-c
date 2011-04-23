/*
 *  ESAPICEncoder.h
 *  ESAPI
 *	OWASP Enterprise Security API (ESAPI)
 * 
 *	This file is part of the Open Web Application Security Project (OWASP)
 *	Enterprise Security API (ESAPI) project. For details, please see
 *	<a href="http://www.owasp.org/index.php/ESAPI">http://www.owasp.org/index.php/ESAPI</a>.
 * 
 *	The ESAPI is published by OWASP under the BSD license. You should read and accept the
 *	LICENSE before you use, modify, and/or redistribute this software.
 *
 *  Created by DEEPAK SUBRAMANIAN on 4/16/11.
 *  Copyright 2011 OWASP Foundation. All rights reserved.
 *
 */

#include <stdlib.h>
#include "ESAPICAuxiliaryFunctions.h"
/**
 @brief This is the header of the ESAPI C Encoder Functions. These function are designed to assist in encoding functionality in various scenarios.
 
 <br>
 Encoding:
 
 </br>
 
 Currently Supported  Encodings:
 <ol>
 <li>URL Encoding</li>
 <li></li>
 <ol>
 <br></br>
 
 The OWASP ESAPI C Library is still not complete and the release is a ALPHA QUALITY release. 
 Kindly let us know of any bugs through email to deepak.subramanian@owasp.org
*/

/**
 @brief The enum that describes the possible encodings available with the ESAPI Library
 */
typedef enum
{
	ESAPIEncodingTypePercentEncoding = 1,///< Percentage encoding is generally used in the get and post requests to cate for multiple parameters.
	ESAPIEncodingTypeURLEncoding = 1, ///< Same as percent encoding. Catering for redundancy of names.
	ESAPIEncodingTypeBase64Encoding = 2 ///< The base64 encoding.
} ESAPIEncodingType;

/**
 @brief This function is used to encode the given string and return the resultant encoded string.
 
 @param inputString - The string to be encoded.
 @param typeOfEncoding - The type of encoding required.
 @return encodedString - The encoded string using the ESAPIEncodingType is returned.
 
 {
	@code
	char inputString[] = "sometext";
	ESAPIStringOperation * encodedStringOperation = ESAPIEncode ( inputString, ESAPIEncodingTypePercentEncoding );
	if ( encodedStringOperation->operationSuccessful )
	{
		char * encodedString = encodedStringOperation->returnString;
		//Use the encodedString for operations.
		free ( encodedString );
	}
	else
	{
		char * errorDescription = encodedStringOperation->errorDescription;
		//The encoding has failed. Manage accordingly.
		free ( errorDescription );
	}
	free ( encodedStringOperation );
	@endcode
 }
 */
ESAPIStringOperation * ESAPIEncode ( char * inputString, ESAPIEncodingType typeOfEncoding );


/**
 @brief This function is used to decode the given string and return the resultant decoded string.
 
 @param inputString - The string to be encoded.
 @param typeOfEncoding - The type of encoding required
 
 {
	@code
	char inputString[] = "sometext";
	ESAPIStringOperation * decodedStringOperation = ESAPIDecode ( inputString, ESAPIEncodingTypePercentEncoding );
	if ( *decodedStringOperation->operationSuccessful )
	{
		char * decodedString = decodedStringOperation->returnString;
		//Use the decodedString for operations.
		free ( decodedString );
	}
	else
	{
		char * errorDescription = encodedStringOperation->errorDescription;
		//The decoding has failed. Manage accordingly.
		free ( errorDescription );
	}
	free ( decodedStringOperation );
	@endcode
 }
 */
ESAPIStringOperation * ESAPIDecode ( char * inputString, ESAPIEncodingType typeOfEncoding );

