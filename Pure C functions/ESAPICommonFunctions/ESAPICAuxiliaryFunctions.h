/*
 *  ESAPICAuxiliaryFunctions.h
 *  ESAPI
 *
 *  Created by DEEPAK SUBRAMANIAN on 4/18/11.
 *  Copyright 2011 OWASP Foundation. All rights reserved.
 *
 */

#include <stdbool.h>

/**
 @brief Sends the results and sets the required flags
 */
typedef struct
{
	bool operationSuccessful; ///< Indicates if the given operation was successful.
	char * returnString;  ///< The string to be returned after a successful operation.
	char * errorDescription; ///< The error description should the operation fail.
} ESAPIStringOperation;


/**
 @brief Returns the decimal value for a given hexadecimal character
 
 This code has been downloaded from http://www.geekhideout.com/urlcode.shtml on April 16, 2011

 @param hexadecimalChar - The given hexadecimal character
 
 @return - The equivalent decimal value
 
 {
	@code
	char int = from_hex('a');
	@endcode
 }
 
 */
char from_hex ( char hexadecimalChar );

/**
 @brief Returns the hexadecimal value for a given decimal character
 
 This code has been downloaded from http://www.geekhideout.com/urlcode.shtml on April 16, 2011

 @param decimalChar - The given decimal character
 
 @return - The hexadecimal equivalent value
 
 {
	@code
	char int = to_hex('9');
	@endcode
 }
 */
char to_hex ( char decimalChar );