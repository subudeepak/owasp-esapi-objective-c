/*
 *  ESAPICBase64Encoder.c
 *  ESAPI
 *
 *  Created by DEEPAK SUBRAMANIAN on 4/24/11.
 *  Copyright 2011 OWASP Foundation. All rights reserved.
 *
 */

#include "ESAPICBase64Encoder.h"
#include <ctype.h>
#include <string.h>
#include <stdio.h>

/* Get UCHAR_MAX. */
#include <limits.h>

# define BASE64_ENCODE_LENGTH(inlen) ((((inlen) + 2) / 3) * 4)
# define BASE64_DECODE_LENGTH(inlen) (3 * (inlen / 4) + 2)


/*
 With this approach this file works independent of the charset used
 (think EBCDIC).  However, it does assume that the characters in the
 Base64 alphabet (A-Za-z0-9+/) are encoded in 0..255.  POSIX
 1003.1-2001 require that char and unsigned char are 8-bit
 quantities, though, taking care of that problem.  But this may be a
 potential problem on non-POSIX C99 platforms.
 
 IBM C V6 for AIX mishandles "#define B64(x) ...'x'...", so use "_"
 as the formal parameter rather than "x".  
 */
#define B64(_)					\
((_) == 'A' ? 0				\
: (_) == 'B' ? 1				\
: (_) == 'C' ? 2				\
: (_) == 'D' ? 3				\
: (_) == 'E' ? 4				\
: (_) == 'F' ? 5				\
: (_) == 'G' ? 6				\
: (_) == 'H' ? 7				\
: (_) == 'I' ? 8				\
: (_) == 'J' ? 9				\
: (_) == 'K' ? 10				\
: (_) == 'L' ? 11				\
: (_) == 'M' ? 12				\
: (_) == 'N' ? 13				\
: (_) == 'O' ? 14				\
: (_) == 'P' ? 15				\
: (_) == 'Q' ? 16				\
: (_) == 'R' ? 17				\
: (_) == 'S' ? 18				\
: (_) == 'T' ? 19				\
: (_) == 'U' ? 20				\
: (_) == 'V' ? 21				\
: (_) == 'W' ? 22				\
: (_) == 'X' ? 23				\
: (_) == 'Y' ? 24				\
: (_) == 'Z' ? 25				\
: (_) == 'a' ? 26				\
: (_) == 'b' ? 27				\
: (_) == 'c' ? 28				\
: (_) == 'd' ? 29				\
: (_) == 'e' ? 30				\
: (_) == 'f' ? 31				\
: (_) == 'g' ? 32				\
: (_) == 'h' ? 33				\
: (_) == 'i' ? 34				\
: (_) == 'j' ? 35				\
: (_) == 'k' ? 36				\
: (_) == 'l' ? 37				\
: (_) == 'm' ? 38				\
: (_) == 'n' ? 39				\
: (_) == 'o' ? 40				\
: (_) == 'p' ? 41				\
: (_) == 'q' ? 42				\
: (_) == 'r' ? 43				\
: (_) == 's' ? 44				\
: (_) == 't' ? 45				\
: (_) == 'u' ? 46				\
: (_) == 'v' ? 47				\
: (_) == 'w' ? 48				\
: (_) == 'x' ? 49				\
: (_) == 'y' ? 50				\
: (_) == 'z' ? 51				\
: (_) == '0' ? 52				\
: (_) == '1' ? 53				\
: (_) == '2' ? 54				\
: (_) == '3' ? 55				\
: (_) == '4' ? 56				\
: (_) == '5' ? 57				\
: (_) == '6' ? 58				\
: (_) == '7' ? 59				\
: (_) == '8' ? 60				\
: (_) == '9' ? 61				\
: (_) == '+' ? 62				\
: (_) == '/' ? 63				\
: -1)

/**
 @brief This is the character array that is used to get the appropriate character encoding for a given character value. This uses a whitelisting method. 0xValue means the value is a hex.
 
 */
static const signed char b64[0x100] = { B64 (0), B64 (1), B64 (2), B64 (3),
	B64 (4), B64 (5), B64 (6), B64 (7), B64 (8), B64 (9), B64 (10),
	B64 (11), B64 (12), B64 (13), B64 (14), B64 (15), B64 (16),
	B64 (17), B64 (18), B64 (19), B64 (20), B64 (21), B64 (22),
	B64 (23), B64 (24), B64 (25), B64 (26), B64 (27), B64 (28),
	B64 (29), B64 (30), B64 (31), B64 (32), B64 (33), B64 (34),
	B64 (35), B64 (36), B64 (37), B64 (38), B64 (39), B64 (40),
	B64 (41), B64 (42), B64 (43), B64 (44), B64 (45), B64 (46),
	B64 (47), B64 (48), B64 (49), B64 (50), B64 (51), B64 (52),
	B64 (53), B64 (54), B64 (55), B64 (56), B64 (57), B64 (58),
	B64 (59), B64 (60), B64 (61), B64 (62), B64 (63), B64 (64),
	B64 (65), B64 (66), B64 (67), B64 (68), B64 (69), B64 (70),
	B64 (71), B64 (72), B64 (73), B64 (74), B64 (75), B64 (76),
	B64 (77), B64 (78), B64 (79), B64 (80), B64 (81), B64 (82),
	B64 (83), B64 (84), B64 (85), B64 (86), B64 (87), B64 (88),
	B64 (89), B64 (90), B64 (91), B64 (92), B64 (93), B64 (94),
	B64 (95), B64 (96), B64 (97), B64 (98), B64 (99), B64 (100),
	B64 (101), B64 (102), B64 (103), B64 (104), B64 (105), B64 (106),
	B64 (107), B64 (108), B64 (109), B64 (110), B64 (111), B64 (112),
	B64 (113), B64 (114), B64 (115), B64 (116), B64 (117), B64 (118),
	B64 (119), B64 (120), B64 (121), B64 (122), B64 (123), B64 (124),
	B64 (125), B64 (126), B64 (127), B64 (128), B64 (129), B64 (130),
	B64 (131), B64 (132), B64 (133), B64 (134), B64 (135), B64 (136),
	B64 (137), B64 (138), B64 (139), B64 (140), B64 (141), B64 (142),
	B64 (143), B64 (144), B64 (145), B64 (146), B64 (147), B64 (148),
	B64 (149), B64 (150), B64 (151), B64 (152), B64 (153), B64 (154),
	B64 (155), B64 (156), B64 (157), B64 (158), B64 (159), B64 (160),
	B64 (161), B64 (162), B64 (163), B64 (164), B64 (165), B64 (166),
	B64 (167), B64 (168), B64 (169), B64 (170), B64 (171), B64 (172),
	B64 (173), B64 (174), B64 (175), B64 (176), B64 (177), B64 (178),
	B64 (179), B64 (180), B64 (181), B64 (182), B64 (183), B64 (184),
	B64 (185), B64 (186), B64 (187), B64 (188), B64 (189), B64 (190),
	B64 (191), B64 (192), B64 (193), B64 (194), B64 (195), B64 (196),
	B64 (197), B64 (198), B64 (199), B64 (200), B64 (201), B64 (202),
	B64 (203), B64 (204), B64 (205), B64 (206), B64 (207), B64 (208),
	B64 (209), B64 (210), B64 (211), B64 (212), B64 (213), B64 (214),
	B64 (215), B64 (216), B64 (217), B64 (218), B64 (219), B64 (220),
	B64 (221), B64 (222), B64 (223), B64 (224), B64 (225), B64 (226),
	B64 (227), B64 (228), B64 (229), B64 (230), B64 (231), B64 (232),
	B64 (233), B64 (234), B64 (235), B64 (236), B64 (237), B64 (238),
	B64 (239), B64 (240), B64 (241), B64 (242), B64 (243), B64 (244),
	B64 (245), B64 (246), B64 (247), B64 (248), B64 (249), B64 (250),
	B64 (251), B64 (252), B64 (253), B64 (254), B64 (255) };

#if UCHAR_MAX == 255
# define uchar_in_range(c) true
#else
# define uchar_in_range(c) ((c) <= 255)
#endif
/* C89 compliant way to cast 'char' to 'unsigned char'. */
static inline unsigned char to_uchar(char ch) 
{
	return ch;
}
/**
 @brief Checks if the gven character is a base64 character
 
 
 Return true if CH is a character from the Base64 alphabet, and
 false otherwise.  Note that '=' is padding and not considered to be
 part of the alphabet.  
 
 @param givenCharacter - The character to verify as base64
 
 @return true - if the given character passes the test for base64. false if the test fails
 
 */
bool isbase64(char ch) 
{
	return uchar_in_range (to_uchar (ch)) && 0 <= b64[to_uchar(ch)];
}
/**
 @brief ESAPICBase64EncoderEncode - This function is used to encode a given inputString and return the string operation.
 
 @param inputString - The given string to be encoded
 @return The output of the string operation.-> The encoded string.
 */
ESAPIStringOperation * ESAPICBase64EncoderEncode ( char * inputString )
{
	printf( "\nThe String to encode is %s",inputString );
	ESAPIStringOperation * base64EncodeOperation = ( ESAPIStringOperation * ) malloc( sizeof( ESAPIStringOperation ) );
	if ( base64EncodeOperation != NULL ) 
	{
		//The length of the input and output strings
		int inputLength = strlen( inputString );
		int outputLength = ( BASE64_ENCODE_LENGTH( strlen( inputString ) ) + 1 );
		printf( "\n The input string is of length %d and the output expected is of length %d", inputLength, outputLength );
		
		//Allocate the memory for the encoded string.
		char * encodedString = ( char * ) malloc( sizeof( char ) * outputLength );
		
		//If the encoded string is NULL do the necessary operations
		if ( encodedString == NULL ) 
		{
			base64EncodeOperation->operationSuccessful = false;
			printf( "\nFAILED THE ENCODING DUE TO MEMORY ALLOC FAILURE" );
			char errorMessage[] = "M_Fail";///< Could be low on memory so a very short desc is used
			base64EncodeOperation->errorDescription = ( char * ) malloc( sizeof( errorMessage ) );
			strcpy( base64EncodeOperation->errorDescription, errorMessage );
			base64EncodeOperation->returnString = NULL;
		}
		else //Do the encoding
		{
			base64EncodeOperation->returnString = encodedString;
			static const char b64str[64] =
			"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
			
			while ( ( inputLength != 0 ) && ( outputLength != 0 ) ) 
			{
				*encodedString++ = b64str[(to_uchar(inputString[0]) >> 2) & 0x3f];
				if (!--outputLength)
					break;
				*encodedString++ = b64str[((to_uchar(inputString[0]) << 4) + (--inputLength ? to_uchar(inputString[1])
														   >> 4 : 0)) & 0x3f];
				if (!--outputLength)
					break;
				*encodedString++ = ( inputLength ? b64str[((to_uchar(inputString[1]) << 2) + (--inputLength ? to_uchar(
																					   inputString[2]) >> 6 : 0)) & 0x3f] : '=');
				if (!--outputLength)
					break;
				*encodedString++ = inputLength ? b64str[to_uchar(inputString[2]) & 0x3f] : '=';
				if (!--outputLength)
					break;
				if ( inputLength )
					inputLength--;
				if ( inputLength )
					inputString += 3;
			}
			printf( "\nThe encoded string is %s",encodedString );
			
			if ( outputLength )
				*encodedString = '\0';
			
			printf( "\nThe return string is %s",base64EncodeOperation->returnString );
			
			base64EncodeOperation->operationSuccessful = true;
			base64EncodeOperation->errorDescription = NULL;
		}
		return base64EncodeOperation;
	}
	else
	{
		return NULL;
	}	
}

/**
 @brief ESAPICBase64EncoderDecode - This function is used to decode a given inputString and return the string operation.
 
 @param inputString - The given string to be decoded
 @return The output of the string operation.-> The decoded string.
 */
ESAPIStringOperation * ESAPICBase64EncoderDecode ( char * inputString )
{
	printf( "\nThe String to decode is %s",inputString );
	ESAPIStringOperation * base64DecodeOperation = ( ESAPIStringOperation * ) malloc( sizeof( ESAPIStringOperation ) );
	if ( base64DecodeOperation != NULL ) 
	{
		//The length of the input and output strings
		int inputLength = strlen( inputString );
		/*
		 This may allocate a few bytes too much, depending on input,
		 but it's not worth the extra CPU time to compute the exact amount.
		 The exact amount is 3 * inlen / 4, minus 1 if the input ends
		 with "=" and minus another 1 if the input ends with "==".
		 Dividing before multiplying avoids the possibility of overflow.  
		 
		 However, to canonicalize, a non Base64 string must be returned as such..
		 */
		int outputLength = ( BASE64_DECODE_LENGTH( strlen( inputString ) ) + 1 );
		printf( "\n The input string is of length %d and the output expected is of length %d", inputLength, outputLength );
		
		//Allocate the memory for the encoded string.
		char * decodedString = ( char * ) malloc( sizeof( char ) * outputLength );
		char * inputBuf = inputString;

		//If the encoded string is NULL do the necessary operations
		if ( decodedString == NULL ) 
		{
			base64DecodeOperation->operationSuccessful = false;
			printf( "\nFAILED THE ENCODING DUE TO MEMORY ALLOC FAILURE" );
			char errorMessage[] = "M_Fail";///< Could be low on memory so a very short desc is used
			base64DecodeOperation->errorDescription = ( char * ) malloc( sizeof( errorMessage ) );
			strcpy( base64DecodeOperation->errorDescription, errorMessage );
			base64DecodeOperation->returnString = NULL;
			
		}
		else //Do the decoding
		{
			//Assign the starting address
			base64DecodeOperation->returnString = decodedString;
			while ( inputLength >= 2 ) 
			{
				printf("Something");
				if ( !isbase64( inputString[0] ) || !isbase64( inputString[1] ) )
					break;
				
				if ( outputLength ) 
				{
					*decodedString++
					= ((b64[to_uchar(inputString[0])] << 2)
					   | (b64[to_uchar(inputString[1])] >> 4));
					outputLength--;
				}
				
				if (inputLength == 2)
					break;
				
				if ( inputString[2] == '=' )
				{
					if (inputLength != 4)
						break;
					
					if (inputString[3] != '=')
						break;
					
				} 
				else 
				{
					if ( !isbase64( inputString[2] ))
						break;
					
					if ( outputLength ) 
					{
						*decodedString++ = (((b64[to_uchar(inputString[1])] << 4) & 0xf0) | (b64[to_uchar(
																										  inputString[2])] >> 2));
						outputLength--;
					}
					
					if (inputLength == 3)
						break;
					
					if (inputString[3] == '=') 
					{
						if (inputLength != 4)
							break;
					} 
					else 
					{
						if (!isbase64(inputString[3]))
							break;
						
						if ( outputLength ) 
						{
							*decodedString++ = (((b64[to_uchar(inputString[2])] << 6) & 0xc0)
												| b64[to_uchar(inputString[3])]);
							outputLength--;
						}
					}
					
				}
				inputString += 4;
				inputLength -= 4;				
			}
			
			
			if ( outputLength )
			{
				 *decodedString = '\0';
			}
			if ( inputLength != 0 )
			{
				realloc( base64DecodeOperation->returnString, strlen( base64DecodeOperation->returnString ));
				strcpy( base64DecodeOperation->returnString, inputBuf );
			}
			else 
			{
				realloc( base64DecodeOperation->returnString, strlen( base64DecodeOperation->returnString ) );
				printf( "Decoded string is %s",base64DecodeOperation->returnString );
			}	
			base64DecodeOperation->operationSuccessful = true;
			base64DecodeOperation->errorDescription = NULL;
		}


		return base64DecodeOperation;
	}
	else
	{
		printf("Memory Allocation Failed");
		return NULL;
	}	
	
}