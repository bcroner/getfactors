// 3SAT_framework.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#ifndef __3SATFRAMEWORK_H__
#define __3SATFRAMEWORK_H__


struct nlist { /* table entry: */
    struct nlist* next; /* next entry in chain */
    char* name; /* defined name */
    char* defn; /* replacement text */
};

// single bit

typedef struct {

    int id;

} bit_3sat;

// integer with decimal

typedef struct {

    bit_3sat** bits; // bit string
    int   sz; // size in bits of number
    int   bd_sz; // before decimal size
    int   ad_sz; // after decimal size

} dec_3sat;

// natural number

typedef struct {

    bit_3sat** bits; // bit string
    int   sz; // size in bits of number

} nat_3sat;

bit_3sat* create_bit(int* num_parm);

dec_3sat* create_dec(int* num_parm, int bd_sz_parm, int ad_sz_parm);

nat_3sat* create_nat(int* num_parm, int sz_parm);

char* and_3sat(int* num_parm, bit_3sat** c, bit_3sat* a, bit_3sat* b, int * len_para);

char* nand_3sat(int* num_parm, bit_3sat** c, bit_3sat* a, bit_3sat* b, int* len_para);

char* or_3sat(int* num_parm, bit_3sat** c, bit_3sat* a, bit_3sat* b, int* len_para);

char* nor_3sat(int* num_parm, bit_3sat** c, bit_3sat* a, bit_3sat* b, int* len_para);

char* not_3sat(int* num_parm, bit_3sat** c, bit_3sat* a, int* len_para);

char* xor_3sat(int* num_parm, bit_3sat** c, bit_3sat* a, bit_3sat* b, int* len_para);

char* xnor_3sat(int* num_parm, bit_3sat** c, bit_3sat* a, bit_3sat* b, int* len_para);

char* bitaddsum_3sat(int* num_parm, bit_3sat** sum, bit_3sat* c_in, bit_3sat* a, bit_3sat* b, int* len_para);

char* bitaddcout_3sat(int* num_parm, bit_3sat** c_out, bit_3sat* c_in, bit_3sat* a, bit_3sat* b, int* len_para);

char* implies_3sat(int* num_parm, bit_3sat** c, bit_3sat* a, bit_3sat* b, int* len_para);

char* dec_add(int* num_parm, dec_3sat** c, dec_3sat* a, dec_3sat* b, bool discard_final_c_out, int* len_para);

char* nat_add(int* num_parm, nat_3sat** c, nat_3sat* a, nat_3sat* b, bool discard_final_c_out, int* len_para);

char* twos_comp_3sat(int* num_parm, dec_3sat** c, dec_3sat* a, int* len_para);

char* dec_sub(int* num_parm, dec_3sat** c, dec_3sat* a, dec_3sat* b, int* len_para);

char* dec_equals(int* num_parm, dec_3sat* a, dec_3sat* b, bool eq, __int64* len_para);

char* nat_equals(int* num_parm, nat_3sat* a, nat_3sat* b, bool eq, __int64* len_para);

char* dec_not_equals(int* num_parm, dec_3sat* a, dec_3sat* b, __int64* len_para);

char* nat_not_equals(int* num_parm, nat_3sat* a, nat_3sat* b, __int64* len_para);

char* dec_mul(int * num_parm, dec_3sat** c, dec_3sat* a, dec_3sat* b, int bd_sz, int ad_sz, __int64* len_para);

char* nat_mul(int* num_parm, nat_3sat** c, nat_3sat* a, nat_3sat* b, int sz, __int64* len_para);

char* dec_div(int * num_parm, dec_3sat * c, dec_3sat * a, dec_3sat ** b, __int64* len_para);

char* dec_sqrt(int* num_parm, dec_3sat* c, dec_3sat** a, __int64* len_para);

//void bignum_from_str_oct(bn* c_bn, char* c_str, int len);

inline int octal_from_char(char c);

//void bignum_from_str_oct(bn* c_bn, char* c_str, int len);

inline int decimal_from_char(char c);

inline int int_from_hex_char(char c);

inline char hex_char_from_int(int a);

bool* hex2bool(const char* a, int sz);

//void bignum_from_str_dec(bn* c_bn, char* c_str, int len);

int** input_from_char_buf(char* buf_3sat, __int64 buf_3sat_sz, int* k, bool cnf);

char* dec_to_str(bool* decodable_buf, dec_3sat* a, int* str_sz);

char* nat_to_str(bool* decodable_buf, nat_3sat* a, int* str_sz);

char* dec_get_factors(char* c_str, int c_str_buf_sz, int * len_para);

char* nat_get_factors(char* c_str, int c_str_buf_sz, int* len_para);

#endif // !__3SATFRAMEWORK_H__