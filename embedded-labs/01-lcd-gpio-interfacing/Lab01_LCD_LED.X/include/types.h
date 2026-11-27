/*
 * File: types.h
 * Purpose: Fixed-width type aliases and bit-operation helpers used by the
 *          supplied course LCD library and board support code.
 *
 * Note: These typedefs are retained for compatibility with the supplied
 *       library. Do not combine this header with <stdint.h> in the same
 *       translation unit unless the typedefs are reconciled first.
 */

#ifndef CPS_TYPES_H
#define CPS_TYPES_H

#ifndef FALSE
#define FALSE 0u
#endif

#ifndef TRUE
#define TRUE 1u
#endif

#define BV(bit)          (1u << (bit))
#define CLEARBIT(bit)    do { (bit) = 0; } while (0)
#define SETBIT(bit)      do { (bit) = 1; } while (0)
#define TOGGLEBIT(bit)   do { (bit) ^= 1; } while (0)

/* XC16 for this 16-bit target uses 8-, 16- and 32-bit integer widths here. */
typedef unsigned char      uint8_t;
typedef unsigned int       uint16_t;
typedef unsigned long int  uint32_t;
typedef signed char        int8_t;
typedef signed int         int16_t;
typedef signed long int    int32_t;

#endif /* CPS_TYPES_H */
