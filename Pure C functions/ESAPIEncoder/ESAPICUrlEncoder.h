/*
 *  ESAPICUrlEncoder.h
 *  ESAPI
 *
 *  Created by DEEPAK SUBRAMANIAN on 4/18/11.
 *  Copyright 2011 OWASP Foundation. All rights reserved.
 *
 */

/** 
 @brief Returns a url-encoded version of the given input string
 
 IMPORTANT: be sure to free() the returned string after use 
 This code has been downloaded from http://www.geekhideout.com/urlcode.shtml on April 16, 2011
 
 @param inputString - This is the input string which needs to be decoded
 @return The decoded string IMPORTANT: be sure to free() the returned string after use 
 
 */
char * ESAPICUrlEncoderEncode ( char *inputString );

/**
 @brief Returns a url-decoded version of the given string
 
 This code has been downloaded from http://www.geekhideout.com/urlcode.shtml on April 16, 2011
 
 @param inputString - This is the input string which needs to be decoded
 @return The decoded string IMPORTANT: be sure to free() the returned string after use 
 */
char * ESAPICUrlEncoderDecode ( char *inputString );
