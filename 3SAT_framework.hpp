// 3SAT_framework.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#ifndef __3SATFRAMEWORK_H__
#define __3SATFRAMEWORK_H__

//#include "../tiny-bignum-c/bn.h"


struct nlist { /* table entry: */
    struct nlist* next; /* next entry in chain */
    char* name; /* defined name */
    char* defn; /* replacement text */
};

// single bit

typedef struct {

    int id;

} bit;

// integer with decimal

typedef struct {

    char name[17]; // var name of integer
    bit** bits; // bit string
    int   sz; // size in bits of number
    int   bd_sz; // before decimal size
    int   ad_sz; // after decimal size

} dec;

/*

// floating point

typedef struct {

    char name[17] ; // var name of float
    bit* bits   ; // bit string
    int   sz    ; // size in bits of number
    int   mnt_sz; // mantissa size
    int   exp_sz; // exponent size
    // bit 0 is sign bit
    // bits 1-mnt_sz are mantissa
    // bits mnt_sz + 1 - mnt_sz + 1 + exp_sz are exponent

} flt ;

*/

bit* create_bit(int* num_parm);

dec* create_dec(int* num_parm, char* name_parm, int bd_sz_parm, int ad_sz_parm);

char* and_3sat(int* num_parm, char* name, bit* c, bit* a, bit* b);

char* nand_3sat(int* num_parm, char* name, bit* c, bit* a, bit* b);

char* or_3sat(int* num_parm, char* name, bit* c, bit* a, bit* b);

char* nor_3sat(int* num_parm, char* name, bit* c, bit* a, bit* b);

char* not_3sat(int* num_parm, char* name, bit* c, bit* a);

char* xor_3sat(int* num_parm, char* name, bit* c, bit* a, bit* b);

char* xnor_3sat(int* num_parm, char* name, bit* c, bit* a, bit* b);

char* bitaddsum_3sat(int* num_parm, char* name, bit* sum, bit* c_in, bit* a, bit* b);

char* bitaddcout_3sat(int* num_parm, char* name, bit* c_out, bit* c_in, bit* a, bit* b);

char* implies_3sat(int* num_parm, char* name, bit* c, bit* a, bit* b);

char* dec_add(int* num_parm, char* name, dec* c, dec* a, dec* b, bool discard_final_c_out);

char* twos_comp_3sat(int* num_parm, char* name, dec* c, dec* a);

char* dec_sub(int* num_parm, char* name, dec* c, dec* a, dec* b);

char* equals(int* num_parm, char* name, dec* a, dec* b, bool eq);

char* not_equals(int* num_parm, char* name, dec* a, dec* b);

char* dec_mul(int * num_parm, char* name, dec* c, dec* a, dec* b, int bd_sz, int ad_sz);

char* dec_div(int* num_parm, char* name, dec * c, dec * a, dec * b);

char* dec_sqrt(int* num_parm, char* name, dec* c, dec* a);

//void bignum_from_str_oct(bn* c_bn, char* c_str, int len);

inline int octal_from_char(char c);

//void bignum_from_str_oct(bn* c_bn, char* c_str, int len);

inline int decimal_from_char(char c);

inline int int_from_hex_char(char c);

inline char hex_char_from_int(int a);

//void bignum_from_str_dec(bn* c_bn, char* c_str, int len);

int** input_from_char_buf(int* num_parm, char* buf_3sat, int* k);

char* get_factors(char* c_str);

#endif // !__3SATFRAMEWORK_H__