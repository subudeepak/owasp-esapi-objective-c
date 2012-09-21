//
//  ESAPIEncoder.m
//  ESAPI
//
//  Created by DEEPAK SUBRAMANIAN on 6/11/11.
//  Copyright 2011 OWASP Foundation. All rights reserved.
//

#import "ESAPIEncoder.h"
#import "ESAPICEncoder.h"

@implementation ESAPIEncoder
/**
 @brief This function is used to encode the given string with the given encoding and return the encoded string.
 
 @param givenString - The given string to be encoded.
 @param encodingType - The type of encoding to be encoded with.
 
 */
- (NSString *) encodeString:(NSString *) givenString withEncoding:(ESAPIEncodingType) encodingType
{
	NSAutoreleasePool * pool = [[NSAutoreleasePool alloc] init];
	NSString * returnString = nil;
	@try 
	{
		returnString = [givenString encodeWithEncoding:encodingType];
	}
	@catch (NSException * e) 
	{
		NSLog(@"Exception in ESAPIEncoder encodeString");
	}
	@finally 
	{
		[pool drain]; 
		return (returnString == nil || returnString == NULL || [returnString isEqual:[NSNull null]] ) ? nil : [returnString autorelease];
	}
	
}
/**
 @brief This function is used to decode the given string with the given encoding and return the decoded string.
 
 @param givenString - The given string to be decoded.
 @param encodingType - The type of encoding to be decoded with.
 
 */
- (NSString *) decodeString:(NSString *) givenString withEncoding:(ESAPIEncodingType) encodingType
{
	NSAutoreleasePool * pool = [[NSAutoreleasePool alloc] init];
	NSString * returnString = nil;
	@try 
	{
		returnString = [givenString decodeWithEncoding:encodingType];
	}
	@catch (NSException * e) 
	{
		NSLog(@"Exception in ESAPIEncoder decodeString %@ with");
	}
	@finally 
	{
		[pool drain]; 
		return (returnString == nil || returnString == NULL || [returnString isEqual:[NSNull null]] ) ? nil : [returnString autorelease];
	}
	
}
/**
 @brief This function is used to canonicalize the given string with the given encoding and return the encoded string.
 
 @param givenString - The given string to be encoded.
 @param encodingType - The type of encoding to be encoded with.
 @param strict - The boolean value which is used 
 */
- (NSString *) canonicalizeString:(NSString *) givenString forSpecificEncoding:(ESAPIEncodingType) encodingType strict:(BOOL) strict
{
	NSAutoreleasePool * pool = [[NSAutoreleasePool alloc] init];
	NSString * returnString = nil;
	@try 
	{
		returnString = [givenString canonicalStringForSpecificEncoding:encodingType isStrict:strict];
	}
	@catch (NSException * e) 
	{
		NSLog(@"Exception in ESAPIEncoder canonicalizeString");
	}
	@finally 
	{
		[pool drain]; 
		return (returnString == nil || returnString == NULL || [returnString isEqual:[NSNull null]] ) ? nil : [returnString autorelease];
	}	
}

- (NSString *) canonicalizeStringForAllAvailableEncodings:(NSString *) givenString strict:(BOOL) strict
{
	NSAutoreleasePool * pool = [[NSAutoreleasePool alloc] init];
	NSString * returnString = nil;
	@try 
	{
		returnString = [givenString canonicalStringForAllAvailableEncodingsStrict:strict];
	}
	@catch (NSException * e) 
	{
		NSLog(@"Exception in ESAPIEncoder canonicalizeStringForAllAvailableEncodings");
	}
	@finally 
	{
		[pool drain]; 
		return (returnString == nil || returnString == NULL || [returnString isEqual:[NSNull null]] ) ? nil : [returnString autorelease];
	}
}
@end

@implementation NSString ( ESAPIEncoderMethods )

/**
 @brief This function is used to encode the given string with the given encoding type.
 */
- (NSString *) encodeWithEncoding:(ESAPIEncodingType) encodingType
{
	NSAutoreleasePool * pool = [[NSAutoreleasePool alloc] init];
	NSString * returnString = nil;
	@try 
	{
		char * givenString = [self UTF8String];
		ESAPIStringOperation * encodedString = ESAPICEncode(givenString, encodingType);
		if ( encodedString != NULL ) 
		{
			if ( encodedString->operationSuccessful )
			{
				returnString = [ [NSString alloc] initWithCString:encodedString->returnString ];
				free(encodedString->returnString);
			}
			else
			{
				NSLog(@"Encoding failed because %s",encodedString->errorDescription);
				free(encodedString->errorDescription);
			}
			free(encodedString);
		}
	}
	@catch (NSException * e) 
	{
		NSLog(@"Exception in ESAPIEncoder NSString encodeWithEncoding");
	}
	@finally 
	{
		[pool drain]; 
		return (returnString == nil || returnString == NULL || [returnString isEqual:[NSNull null]] ) ? nil : [returnString autorelease];
	}
}
/**
 @brief This function is used to decode the string with a specific encoding.
 */
- (NSString *) decodeWithEncoding:(ESAPIEncodingType) encodingType
{
	NSAutoreleasePool * pool = [[NSAutoreleasePool alloc] init];
	NSString * returnString = nil;
	@try 
	{
		char * givenString = [self UTF8String];
		ESAPIStringOperation * decodedString = ESAPICDecode(givenString, encodingType);
		if ( decodedString != NULL ) 
		{
			if ( decodedString->operationSuccessful )
			{
				returnString = [ [NSString alloc] initWithCString:decodedString->returnString ];
				free(decodedString->returnString);
			}
			else
			{
				NSLog(@"Encoding failed because %s",decodedString->errorDescription);
				free(decodedString->errorDescription);
			}
			free(decodedString);
		}
	}
	@catch (NSException * e) 
	{
		NSLog(@"Exception in ESAPIEncoder NSString decodeWithEncoding");
	}
	@finally 
	{
		[pool drain]; 
		return (returnString == nil || returnString == NULL || [returnString isEqual:[NSNull null]] ) ? nil : [returnString autorelease];
	}
}

 
- (NSString *) canonicalStringForSpecificEncoding:(ESAPIEncodingType) encodingType isStrict:(BOOL) strict
{
	NSAutoreleasePool * pool = [[NSAutoreleasePool alloc] init];
	NSString * returnString = nil;
	@try 
	{
		char * givenString = [self UTF8String];
		ESAPIStringOperation * canonicalString = ESAPICCanonicalizationForSpecificEncodingType(givenString, encodingType, strict);//ESAPICDecode(givenString, encodingType);
		if ( canonicalString != NULL ) 
		{
			if ( canonicalString->operationSuccessful )
			{
				returnString = [ [NSString alloc] initWithCString:canonicalString->returnString ];
				free(canonicalString->returnString);
			}
			else
			{
				NSLog(@"Encoding failed because %s",canonicalString->errorDescription);
				free(canonicalString->errorDescription);
			}
			free(canonicalString);
		}
	}
	@catch (NSException * e) 
	{
		NSLog(@"Exception in ESAPIEncoder NSString decodeWithEncoding");
	}
	@finally 
	{
		[pool drain]; 
		return (returnString == nil || returnString == NULL || [returnString isEqual:[NSNull null]] ) ? nil : [returnString autorelease];
	}
}

- (NSString *) canonicalStringForAllAvailableEncodingsStrict:(BOOL) strict
{
	NSAutoreleasePool * pool = [[NSAutoreleasePool alloc] init];
	NSString * returnString = nil;
	@try 
	{
		char * givenString = [self UTF8String];
		ESAPIStringOperation * canonicalString = ESAPICCanonicalizationAllAvailableEncodings(givenString, strict);//ESAPICCanonicalizationForSpecificEncodingType(givenString, encodingType, strict);
		if ( canonicalString != NULL ) 
		{
			if ( canonicalString->operationSuccessful )
			{
				returnString = [ [NSString alloc] initWithCString:canonicalString->returnString ];
				free(canonicalString->returnString);
			}
			else
			{
				NSLog(@"Encoding failed because %s",canonicalString->errorDescription);
				free(canonicalString->errorDescription);
			}
			free(canonicalString);
		}
	}
	@catch (NSException * e) 
	{
		NSLog(@"Exception in ESAPIEncoder NSString decodeWithEncoding");
	}
	@finally 
	{
		[pool drain]; 
		return (returnString == nil || returnString == NULL || [returnString isEqual:[NSNull null]] ) ? nil : [returnString autorelease];
	}
}

@end
