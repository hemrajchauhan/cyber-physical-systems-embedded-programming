/*
 * Fixed-width integer aliases and small bit-manipulation helpers.
 *
 * The XC16 compiler targets a 16-bit int architecture. These aliases
 * match the data widths used by the original course LCD interface.
 */

#ifndef TYPES_H
#define TYPES_H

#ifndef FALSE
#define FALSE 0U
#endif

#ifndef TRUE
#define TRUE 1U
#endif

#define BV(bit)              (1UL << (bit))
#define CLEARBIT(bit_field)  do { (bit_field) = 0; } while (0)
#define SETBIT(bit_field)    do { (bit_field) = 1; } while (0)
#define TOGGLEBIT(bit_field) do { (bit_field) ^= 1; } while (0)

typedef unsigned char      uint8_t;
typedef unsigned int       uint16_t;
typedef unsigned long int  uint32_t;
typedef signed char        int8_t;
typedef signed int         int16_t;
typedef signed long int    int32_t;

#endif /* TYPES_H */
