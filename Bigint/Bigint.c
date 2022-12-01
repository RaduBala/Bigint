/*
* bigint.c
*
*  Created on: Mar 4, 2019
*      Author: B Radu
*/
/*****************************************************************************
*                                  Includes                                  *
******************************************************************************/
#include <stdint.h>
#include <string.h>

#include "Bigint.h"


/*****************************************************************************
*                              Global variables                              *
******************************************************************************/

/*****************************************************************************/
/*
** \brief  Auxiliary variable used in multiplication operation.
*/
uint8_t  Bigint_mulAuxVar[ BIGINT_MAX_SIZE + 1u ] ;


/*****************************************************************************/
/*
** \brief  Auxiliary variable used in division operation.
*/
uint8_t  Bigint_divAuxVar[ BIGINT_MAX_SIZE + 1u ] ;


/*****************************************************************************/
/*
** \brief  Auxiliary variable used in modular exponentiation operation.
*/
uint8_t  Bigint_modExpAuxVar[ BIGINT_MAX_SIZE + 1u ] ;


/*****************************************************************************/
/*
** \brief  Auxiliary variable used in prime number verification operation.
*/
uint8_t  Bigint_verifyPrimeAux[ BIGINT_MAX_SIZE + 1u ] ;


/*****************************************************************************/
/*
** \brief  Auxiliary variable used in prime number verification operation.
*/
uint8_t  Bigint_verifyPrimeExp[ BIGINT_MAX_SIZE + 1u ] ;


/*****************************************************************************/
/*
** \brief  Auxiliary variable used in prime number verification operation.
*/
uint8_t  Bigint_verifyPrimeFermatRdn[ BIGINT_MAX_SIZE + 1u ] ;


/*****************************************************************************
*                                 Functions                                  *
******************************************************************************/

/*****************************************************************************/
/*
** \brief  Compare to big integers and return the index of the bigger one or 0
**         in case of equality.
**
** \param  data1    first data to compare
** \param  data2    second data to compare
** \param  size1    the size of the first data
** \param  size2    the size of the second data
**
** \return  - 1 if data1 is bigger
**          - 2 is data2 is bigger
**          - 0 for equality
*/
uint8_t  Bigint_Compare ( uint8_t *data1 , uint8_t *data2 , uint16_t size1 , uint16_t size2 )
{
    uint16_t ndx        = size1 > size2 ? size1 : size2 ;
    uint8_t  data1_unit = 0u ;
    uint8_t  data2_unit = 0u ;
    uint8_t  retVal     = 0u ;

    while ( ndx > 0u )
    {
        ndx-- ;
        
        data1_unit = ndx < size1 ? data1[ndx] : 0u; 
        data2_unit = ndx < size2 ? data2[ndx] : 0u ;

        if ( data1_unit > data2_unit )
        {
            retVal = 1u ;
            
            break;
        }
        else
        if ( data1_unit < data2_unit )
        {
            retVal = 2u ;
            
            break;
        }
    }

    return retVal ;
}


/*****************************************************************************/
/*
** \brief
*/
void  Bigint_Fill ( uint8_t *dest , uint8_t value , uint16_t size )
{
    memset( dest , value , size ) ;
}


/*****************************************************************************/
/*
** \brief  Copy data from a big integer to another big integer.
**
** \param  dest    destination data
** \param  src     source data
** \param  size    the size of destination
**
** \return  none
*/
void  Bigint_Copy ( uint8_t *dest , uint8_t *src , uint16_t size )
{
    memcpy( dest , src , size ) ;
}


/*****************************************************************************/
/*
** \brief  Make the sum of 2 big integers.
**
** \param  data1    first data to add
** \param  data2    second data to add
** \param  dest     destination of the add operation
** \param  size1    the size of the first data
** \param  size2    the size of the second data
**
** \return  none
*/
void  Bigint_Add ( uint8_t *data1 , uint8_t *data2 , uint8_t *dest , uint16_t size1 , uint16_t size2 )
{
    uint8_t  data1_unit = 0u ;
    uint8_t  data2_unit = 0u ;
    uint8_t  carry      = 0u ;
    uint32_t sum        = 0u ;
    uint16_t ndx        = 0u ;
    uint16_t sum_size   = size1 > size2 ? size1 : size2 ;

    for ( ndx = 0u ; ndx < sum_size ; ndx++ )
    {
        data1_unit = ndx < size1 ? data1[ndx] : 0u ;
        data2_unit = ndx < size2 ? data2[ndx] : 0u ;

        sum = (uint32_t)(data1_unit + data2_unit + carry) ;
    
        dest[ndx] = (uint8_t)sum ;
    
        carry = (uint8_t)(sum >> BIGINT_UNIT_SIZE) ;
    }

    dest[ndx] += carry ;
}


/*****************************************************************************/
/*
** \brief  Subtract 2 big integers. The condition for this operation to work
** 		   is that minuend > sinuend.
**
** \param  minuend        big integer data from where to subtract
** \param  sinuend        big integer data to subtract from the minuend
** \param  difference     destination of the subtract operation
** \param  size1          the size of the first minuend
** \param  size2          the size of the second sinuend
**
** \return  none
*/
void  Bigint_Substract ( uint8_t *minuend , uint8_t *sinuend , uint8_t *difference , uint16_t size1 , uint16_t size2 )
{
    uint32_t minuend_unit   = 0u;
    uint32_t sinuend_unit   = 0u;
    uint8_t  carry          = 0u;
    uint8_t  carry_ovr_flag = 0u;
    uint16_t ndx            = 0u;

    for ( ndx = 0u; ndx < size1; ndx++ )
    {
        sinuend_unit = ndx < size2 ? sinuend[ndx] : 0u ;
        minuend_unit = minuend[ndx] ;

        if ( minuend_unit >= carry  )
        {
            minuend_unit -= carry ;
        
            carry = 0u;
        }
        else
        {
            if ( minuend_unit > 0u )
            {
                minuend_unit = 0u ;

                carry -= carry - minuend_unit ;
            }
            else
            {
                carry_ovr_flag = 1u ;
            }
        }
        
        if ( minuend_unit < sinuend_unit )
        {
            if ( carry_ovr_flag == 0u )
            {
                carry++ ;

                minuend_unit |= BIGINT_UNIT_MASK + 1u ;
            }
            else
            {
                carry_ovr_flag = 0u ;
        
                minuend_unit = BIGINT_UNIT_MASK ;
            }
        }
        else
        {
            if ( carry_ovr_flag == 1u )
            {
                carry_ovr_flag = 0u ;
        
                minuend_unit = BIGINT_UNIT_MASK ;
            }
        }

        difference[ndx] = minuend_unit - sinuend_unit ;
    }
}


/*****************************************************************************/
/*
** \brief  Read one bit from a big integer data.
**
** \param  data            big integer data from where the bit will be read
** \param  bit_position    the bit position to be read from big integer data
**
** \return  bit value
*/
uint8_t  Bigint_ReadBit ( uint8_t *data , uint16_t bit_position )
{
    uint16_t bit_byte_ndx = bit_position / BIGINT_UNIT_SIZE ;
    uint8_t  bit_byte_pos = bit_position % BIGINT_UNIT_SIZE ;
    uint8_t  ret_val      = (data[bit_byte_ndx] & (1u << bit_byte_pos)) >> bit_byte_pos ;

    return ret_val ;
}


/*****************************************************************************/
/*
** \brief  Set the value for one bit in a big integer data.
**
** \param  data            big integer data from where the bit will be set
** \param  bit_position    the bit position to be set in big integer data
** \param  bit_value
**
** \return  none
*/
void  Bigint_WriteBit ( uint8_t *data , uint16_t bit_position , uint8_t bit_value )
{
    uint16_t bit_byte_ndx = bit_position / BIGINT_UNIT_SIZE ;
    uint8_t  bit_byte_pos = bit_position % BIGINT_UNIT_SIZE ;

    if ( bit_value == 0u )
    {
        data[bit_byte_ndx] &= ~(1u << bit_byte_pos) ;
    }
    else
    {
        data[bit_byte_ndx] |= 1u << bit_byte_pos ;
    }
}


/*****************************************************************************/
/*
** \brief  Shift to the left a big integer.
**
** \param  data          big integer data to be shifted
** \param  dest          destination of shift to the left operation
** \param  shift_size    number of bits to be shifted
** \param  size          the size of data
**
** \return  none
*/
void  Bigint_ShiftLeft ( uint8_t *data , uint8_t *dest , uint16_t shift_size , uint16_t size )
{
    uint16_t unit_ndx        = 0u ;
    uint8_t  carry_old       = 0u ;
    uint8_t  carry_new       = 0u ;
    uint8_t  unit_shift_size = 0u ;

    Bigint_Copy( dest , data , size ) ;

    while ( shift_size > 0u)
    {
        if ( shift_size < BIGINT_UNIT_SIZE )
        {
            unit_shift_size = BIGINT_UNIT_SIZE - shift_size ;
            unit_shift_size = BIGINT_UNIT_SIZE - unit_shift_size ;

            shift_size = 0u ;
        }
        else
        {
            shift_size -= BIGINT_UNIT_SIZE ;

            unit_shift_size = BIGINT_UNIT_SIZE ;
        }

        carry_old = 0u ;
        carry_new = 0u ;
        
        for ( unit_ndx = 0u ; unit_ndx < size ; unit_ndx++ )
        {
            carry_new = dest[unit_ndx] >> (BIGINT_UNIT_SIZE - unit_shift_size) ;

            dest[unit_ndx] = dest[unit_ndx] << unit_shift_size ;

            dest[unit_ndx] |= carry_old ;

            carry_old = carry_new ;
        }
    }
}


/*****************************************************************************/
/*
** \brief  Shift to the right a big integer.
**
** \param  data          big integer data to be shifted
** \param  dest          destination of shift to the right operation
** \param  shift_size    number of bits to be shifted
** \param  size          the size of data
**
** \return  none
*/
void  Bigint_ShiftRight ( uint8_t *data , uint8_t *dest , uint16_t shift_size , uint16_t size )
{
    uint16_t unit_ndx        = 0u ;
    uint8_t  carry_old       = 0u ;
    uint8_t  carry_new       = 0u ;
    uint8_t  unit_shift_size = 0u ;

    Bigint_Copy( dest , data , size ) ;

    while ( shift_size > 0u )
    {
        if ( shift_size < BIGINT_UNIT_SIZE )
        {
            unit_shift_size = BIGINT_UNIT_SIZE - shift_size ;
            unit_shift_size = BIGINT_UNIT_SIZE - unit_shift_size ;
        
            shift_size = 0u ;
        }
        else
        {
            shift_size -= BIGINT_UNIT_SIZE ;

            unit_shift_size = BIGINT_UNIT_SIZE ;
        }

        carry_old = 0u ;
        carry_new = 0u ;
        unit_ndx  = size ;

        while ( unit_ndx > 0u )
        {
            unit_ndx--;

            carry_new = dest[unit_ndx] << (BIGINT_UNIT_SIZE - unit_shift_size) ;

            dest[unit_ndx] = dest[unit_ndx] >> unit_shift_size ;

            dest[unit_ndx] |= carry_old ;

            carry_old = carry_new ;
        }
    }
}


/*****************************************************************************/
/*
** \brief  Make an and bits operation between 2 big integers.
**
** \param  data1    first data to make an and with the second data
** \param  data2    second data to make an and with the first data
** \param  dest     destination of the and operation
** \param  size
**
** \return  none
*/
void  Bigint_And ( uint8_t *data1 , uint8_t *data2 , uint8_t *dest , uint16_t size )
{
    uint16_t unit_ndx = 0u;

    for ( unit_ndx = 0u ; unit_ndx < size ; unit_ndx++ )
    {
        dest[unit_ndx] = data1[unit_ndx] & data2[unit_ndx] ;
    }
}


/*****************************************************************************/
/*
** \brief  Make an or bits operation between 2 big integers.
**
** \param  data1    first data to make an or with the second data
** \param  data2    second data to make an or with the first data
** \param  dest     destination of the or operation
** \param  size
**
** \return  none
*/
void  Bigint_Or ( uint8_t *data1 , uint8_t *data2 , uint8_t *dest , uint16_t size )
{
    uint16_t unit_ndx = 0u ;

    for ( unit_ndx = 0u ; unit_ndx < size ; unit_ndx++ )
    {
        dest[unit_ndx] = data1[unit_ndx] | data2[unit_ndx] ;
    }
}


/*****************************************************************************/
/*
** \brief
**
** \param  data1
** \param  data2
** \param  dest
** \param  size
**
** \return  none
*/
void  Bigint_Xor ( uint8_t *data1 , uint8_t *data2 , uint8_t *dest , uint16_t size )
{
    uint16_t unit_ndx = 0u ;

    for ( unit_ndx = 0u ; unit_ndx < size ; unit_ndx++ )
    {
        dest[unit_ndx] = data1[unit_ndx] ^ data2[unit_ndx] ;
    }
}


/*****************************************************************************/
/*
** \brief  Multiply 2 big integers. This operation required destination big integer
** 		   to have the size = size_data1 + size_data2, otherwise the operation may
** 		   lead to an overflow and corrupt the memory.
**
** \param  data1        first big integer to be multiplied with second big integer
** \param  data2        second big integer to be multiplied with first big integer
** \param  dest         destination of the multiplication operation
** \param  size1        the size of the first data1
** \param  size2        the size of the second data2
** \param  size_dest    the size of destination
**
** \return  none
*/
void  Bigint_Multiply ( uint8_t *data1 , uint8_t *data2 , uint8_t *dest , uint16_t size1 , uint16_t size2 )
{
    uint16_t ndx1      = 0u ;
    uint16_t ndx2      = 0u ;
    uint32_t prod      = 0u ;
    uint8_t  carry     = 0u ;
    uint8_t  carry_sum = 0u ;

    Bigint_Fill( Bigint_mulAuxVar , 0u , size1 + size2 ) ;

    for ( ndx1 = 0u ; ndx1 < size1 ; ndx1++ )
    {
        carry     = 0u ;
        carry_sum = 0u ;
    
        for ( ndx2 = 0u ; ndx2 < size2 ; ndx2++ )
        {
            prod = data1[ndx1] * data2[ndx2] + carry_sum ;

            carry_sum = (Bigint_mulAuxVar[ndx1 + ndx2] + (uint8_t)(prod + carry)) >> BIGINT_UNIT_SIZE ;
    
            Bigint_mulAuxVar[ndx1 + ndx2] += (uint8_t)(prod + carry) ;
    
            carry = (uint8_t)(prod >> BIGINT_UNIT_SIZE) + (uint8_t)(((uint8_t)prod + carry) >> BIGINT_UNIT_SIZE) ;
        }

        Bigint_mulAuxVar[ndx1 + ndx2] = carry + carry_sum ;
    }

    Bigint_Copy( dest , Bigint_mulAuxVar , size1 + size2 ) ;
}


/*****************************************************************************/
/*
** \brief  Divide 2 big integers. The condition for this operation to work
** 	       is that divisor must be different than 0 and the remainder size
**         shall be size_dsor.
**
** \param  dividend     big integers data to be divided
** \param  divisor      big integer data to divide with
** \param  quotient     the division result
** \param  remainder    the remaining data from devision ( R = dividend - divisor * quotient )
** \param  size_dend    the size of dividend
** \param  size_dsor    the size of divisor
**
** \return  none
*/
void  Bigint_Divide ( uint8_t *dividend , uint8_t *divisor , uint8_t *quotient , uint8_t *remainder , uint16_t size_dend , uint16_t size_dsor )
{
    uint32_t bit_ndx      = size_dend * BIGINT_UNIT_SIZE ;
    uint8_t  divisor_zero = 0u ;
    uint8_t  bit_value    = 0u ;

    Bigint_Fill( Bigint_divAuxVar , 0u , size_dsor + 1u ) ;

    if ( quotient != (uint8_t*)0u )
    {
        Bigint_Fill( quotient , 0u , size_dend ) ;
    }

    if ( Bigint_Compare( divisor , &divisor_zero , size_dsor , 1u ) != 0u )
    {
        if ( Bigint_Compare( dividend , divisor , size_dend , size_dsor ) != 2u )
        {
            while ( bit_ndx > 0u )
            {
                bit_ndx-- ;

                Bigint_ShiftLeft( Bigint_divAuxVar , Bigint_divAuxVar , 1u , size_dsor + 1u ) ;

                bit_value = Bigint_ReadBit( dividend , bit_ndx ) ;

                Bigint_WriteBit( Bigint_divAuxVar , 0u , bit_value ) ;

                if ( Bigint_Compare( Bigint_divAuxVar , divisor , size_dsor + 1u , size_dsor ) != 2u )
                {
                    Bigint_Substract( Bigint_divAuxVar , divisor , Bigint_divAuxVar , size_dsor + 1u , size_dsor ) ;

                    if ( quotient != (uint8_t*)0u )
                    {
                        Bigint_WriteBit( quotient , bit_ndx , 1u ) ;
                    }
                }
            }
        }
        else
        {
            Bigint_Copy( Bigint_divAuxVar , dividend , size_dend ) ;
        }
    }

    Bigint_Copy( remainder , Bigint_divAuxVar , size_dsor ) ;
}


/*****************************************************************************/
/*
** \brief  Make modular exponential operation ( base ^ exponent % modulus ). This operation required the size
**         to be the same for all the parameters except result size, which must be size + 1.
**
** \param  base        base of operation
** \param  exponent    exponent of the base
** \param  modulus     operator to make mod operation with
** \param  result      the result of the whole operation
** \param  size        size of parameters
**
** \return  none
*/
void  Bigint_ModularExponentiation ( uint8_t *base , uint8_t *exponent , uint8_t *modulus , uint8_t *result , uint16_t size )
{
    uint16_t bit_ndx        = size * BIGINT_UNIT_SIZE ;
    uint8_t  bit_value      = 0u ;
    uint8_t  first_bit_flag = 0u ;
    
    Bigint_Fill( Bigint_modExpAuxVar , 0u , BIGINT_MAX_SIZE ) ;
    
    Bigint_Copy( result , base , size ) ;
    
    while ( bit_ndx > 0u )
    {
        if ( first_bit_flag == 0u )
        {
            bit_ndx-- ;
            
            bit_value = Bigint_ReadBit( exponent , bit_ndx ) ;
            
            if ( bit_value != 0u )
            {
                first_bit_flag = 1u ;
            }
        }
        else
        {
            bit_ndx-- ;
            
            bit_value = Bigint_ReadBit( exponent, bit_ndx) ;
            
            Bigint_Multiply( result , result , Bigint_modExpAuxVar , size , size ) ;
            
            Bigint_Divide( Bigint_modExpAuxVar , modulus , NULL , result , size * 2 , size ) ;
            
            if ( bit_value == 1u )
            {
                Bigint_Multiply( result , base , Bigint_modExpAuxVar , size , size ) ;
            
                Bigint_Divide( Bigint_modExpAuxVar , modulus , NULL , result , size * 2 , size ) ;
            }
        }
    }
}


/*****************************************************************************/
/*
** \brief  Verify if a number is prime using Fermat primality test.
**
** \param  number      number to be verified if is prime
** \param  precision   number of precision steps in Fermat algorithm
** \param  size        the size in bytes of the number
**
** \return  none
*/
uint8_t  Bigint_VerifyPrime ( uint8_t *number , uint16_t precision , uint16_t size )
{
    uint8_t  one[]       = { 1u } ;
    uint8_t  two[]       = { 2u } ;
    uint16_t ndx         = 0u ;
    uint8_t  isPrimeFlag = 1u ;

    Bigint_Fill( Bigint_verifyPrimeExp       , 0u , BIGINT_MAX_SIZE ) ;
    Bigint_Fill( Bigint_verifyPrimeFermatRdn , 0u , BIGINT_MAX_SIZE ) ;

    Bigint_Substract( number , one , Bigint_verifyPrimeExp , size , 1u ) ;

    Bigint_Divide( number , two , Bigint_verifyPrimeFermatRdn , Bigint_verifyPrimeAux , size , 1u ) ;

    Bigint_Fill( Bigint_verifyPrimeAux , 0u , BIGINT_MAX_SIZE ) ;

    for ( ndx = 0 ; ndx < precision ; ndx++ )
    {
        Bigint_ModularExponentiation( Bigint_verifyPrimeFermatRdn , Bigint_verifyPrimeExp , number , Bigint_verifyPrimeAux , size ) ;
        
        if ( Bigint_Compare( Bigint_verifyPrimeAux , one , size , 1u ) != 0u )
        {
            isPrimeFlag = 0u ;
        }

        Bigint_Add( Bigint_verifyPrimeFermatRdn , one , Bigint_verifyPrimeFermatRdn , size , 1u ) ;
    }

    return isPrimeFlag ;
}
