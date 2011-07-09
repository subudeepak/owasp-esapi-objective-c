//
//  ESAPIEncoder.h
//  ESAPI
//
//  Created by DEEPAK SUBRAMANIAN on 6/11/11.
//  Copyright 2011 OWASP Foundation. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "ESAPICEncoder.h"
/**
 @brief Overload of the NSString method for encoding.
 */
@interface NSString ( ESAPIEncoderMethods )
- (NSString *) encodeWithEncoding:(ESAPIEncodingType) encodingType;
- (NSString *) decodeWithEncoding:(ESAPIEncodingType) encodingType;
- (NSString *) canonicalStringForAllAvailableEncodingsStrict:(BOOL) strict;
- (NSString *) canonicalStringForSpecificEncoding:(ESAPIEncodingType) encodingType isStrict:(BOOL) strict;
@end

/**
 @brief This is the interface 
 */
@interface ESAPIEncoder : NSObject
{

}
- (NSString *) encodeString:(NSString *) givenString withEncoding:(ESAPIEncodingType) encodingType;
- (NSString *) decodeString:(NSString *) givenString withEncoding:(ESAPIEncodingType) encodingType;
- (NSString *) canonicalizeString:(NSString *) givenString forSpecificEncoding:(ESAPIEncodingType) encodingType strict:(BOOL) strict;
- (NSString *) canonicalizeStringForAllAvailableEncodings:(NSString *) givenString strict:(BOOL) strict;
@end
