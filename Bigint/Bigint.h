/*
* bigint.h
*
*  Created on: Mar 4, 2019
*      Author: B Radu
*/

#ifndef _BIGINT_H_
#define _BIGINT_H_


/*****************************************************************************
*                                  Includes                                  *
******************************************************************************/
#include <stdint.h>
#include "Bigint_cfg.h"


/*****************************************************************************
*                              Macro Definitions                             *
******************************************************************************/
#define  BIGINT_UNIT_SIZE    8u
#define  BIGINT_UNIT_MASK    0xFFu


/*****************************************************************************/
extern  uint8_t  Bigint_Compare( uint8_t *data1 , uint8_t *data2 , uint16_t size ) ;

extern  void     Bigint_Fill( uint8_t *dest , uint8_t value , uint16_t size ) ;

extern  void     Bigint_Copy( uint8_t *dest , uint8_t *src , uint16_t size ) ;

extern  void     Bigint_Add( uint8_t *data1 , uint8_t *data2 , uint8_t *dest , uint16_t size1 , uint16_t size2 ) ;

extern  void     Bigint_Substract( uint8_t *minuend , uint8_t *sinuend , uint8_t *difference , uint16_t size1 , uint16_t size2 ) ;

extern  uint8_t  Bigint_ReadBit( uint8_t *data , uint16_t bit_position ) ;

extern  void     Bigint_WriteBit( uint8_t *data , uint16_t bit_position , uint8_t bit_value ) ;

extern  void     Bigint_ShiftLeft( uint8_t *data , uint8_t *dest , uint16_t shift_size , uint16_t size ) ;

extern  void     Bigint_ShiftRight( uint8_t *data , uint8_t *dest , uint16_t shift_size , uint16_t size ) ;

extern  void     Bigint_And( uint8_t *data1 , uint8_t *data2 , uint8_t *dest , uint16_t size ) ;

extern  void     Bigint_Or( uint8_t *data1 , uint8_t *data2 , uint8_t *dest , uint16_t size ) ;

extern  void     Bigint_Xor( uint8_t *data1 , uint8_t *data2 , uint8_t *dest , uint16_t size ) ;

extern  void     Bigint_Multiply( uint8_t *data1 , uint8_t *data2 , uint8_t *dest , uint16_t size1 , uint16_t size2 ) ;

extern  void     Bigint_Divide( uint8_t *dividend , uint8_t *divisor , uint8_t *quotient , uint8_t *remainder , uint16_t size_dend , uint16_t size_dsor ) ;

extern  void     bigint_ModularExponentiation( uint8_t *base , uint8_t *exponent , uint8_t *modulus , uint8_t *result , uint16_t size ) ;

extern  uint8_t  Bigint_VerifyPrime( uint8_t *number , uint16_t precision , uint16_t size ) ;


#endif /* _BIGINT_H_ */
