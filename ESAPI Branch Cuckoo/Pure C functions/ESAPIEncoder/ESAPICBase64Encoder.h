/*
 *  ESAPICBase64Encoder.h
 *  ESAPI
 *
 *  Created by DEEPAK SUBRAMANIAN on 4/24/11.
 *  Copyright 2011 OWASP Foundation. All rights reserved.
 *
 */


#include "ESAPICAuxiliaryFunctions.h"
#include <stdlib.h>

#ifndef ESAPICBase64Encoder_H
# define ESAPICBase64Encoder_H

ESAPIStringOperation * ESAPICBase64EncoderEncode ( char * inputString );

ESAPIStringOperation * ESAPICBase64EncoderDecode ( char * inputString );

/**
 @brief Checks if the gven character is a base64 character
 
 @param givenCharacter - The character to verify as base64
 
 @return true - if the given character passes the test for base64. false if the test fails
 */
bool isbase64( char givenCharacter );
#endif /*ESAPICBase64Encoder_H*/