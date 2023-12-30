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

} bit;

// integer with decimal

typedef struct {

    bit** bits; // bit string
    int   sz; // size in bits of number
    int   bd_sz; // before decimal size
    int   ad_sz; // after decimal size

} dec;

bit* create_bit(int* num_parm);

dec* create_dec(int* num_parm, int bd_sz_parm, int ad_sz_parm);

char* and_3sat(int* num_parm, bit** c, bit* a, bit* b, int * len_para);

char* nand_3sat(int* num_parm, bit** c, bit* a, bit* b, int* len_para);

char* or_3sat(int* num_parm, bit** c, bit* a, bit* b, int* len_para);

char* nor_3sat(int* num_parm, bit** c, bit* a, bit* b, int* len_para);

char* not_3sat(int* num_parm, bit** c, bit* a, int* len_para);

char* xor_3sat(int* num_parm, bit** c, bit* a, bit* b, int* len_para);

char* xnor_3sat(int* num_parm, bit** c, bit* a, bit* b, int* len_para);

char* bitaddsum_3sat(int* num_parm, bit** sum, bit* c_in, bit* a, bit* b, int* len_para);

char* bitaddcout_3sat(int* num_parm, bit** c_out, bit* c_in, bit* a, bit* b, int* len_para);

char* implies_3sat(int* num_parm, bit** c, bit* a, bit* b, int* len_para);

char* dec_add(int* num_parm, dec** c, dec* a, dec* b, bool discard_final_c_out, int* len_para);

char* twos_comp_3sat(int* num_parm, dec** c, dec* a, int* len_para);

char* dec_sub(int* num_parm, dec** c, dec* a, dec* b, int* len_para);

char* equals(int* num_parm, dec* a, dec* b, bool eq, int* len_para);

char* not_equals(int* num_parm, dec* a, dec* b, int* len_para);

char* dec_mul(int * num_parm, dec** c, dec* a, dec* b, int bd_sz, int ad_sz, int* len_para);

char* dec_div(int* num_parm, dec * c, dec * a, dec * b, int* len_para);

char* dec_sqrt(int* num_parm, dec* c, dec* a, int* len_para);

//void bignum_from_str_oct(bn* c_bn, char* c_str, int len);

inline int octal_from_char(char c);

//void bignum_from_str_oct(bn* c_bn, char* c_str, int len);

inline int decimal_from_char(char c);

inline int int_from_hex_char(char c);

inline char hex_char_from_int(int a);

//void bignum_from_str_dec(bn* c_bn, char* c_str, int len);

int** input_from_char_buf(int* num_parm, char* buf_3sat, int buf_3sat_sz, int* k);

char* dec_to_str(bool* decodable_buf, dec* a, int* str_sz);

char* get_factors(char* c_str, int c_str_buf_sz, int* len_para);

#endif // !__3SATFRAMEWORK_H__