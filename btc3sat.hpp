// 3SAT_framework.hpp : headers
//

#include "3SAT_framework.hpp"

#ifndef __BTC3SAT_H__
#define __BTC3SAT_H__

void and_b3(int* num_parm, int** lst, bit_3sat** c, bit_3sat* a, bit_3sat* b);

void nand_b3(int* num_parm, int** lst, bit_3sat** c, bit_3sat* a, bit_3sat* b);

void or_b3(int* num_parm, int** lst, bit_3sat** c, bit_3sat* a, bit_3sat* b);

void nor_b3(int* num_parm, int** lst, bit_3sat** c, bit_3sat* a, bit_3sat* b);

void not_b3(int* num_parm, int** lst, bit_3sat** c, bit_3sat* a);

void xor_b3(int* num_parm, int** lst, bit_3sat** c, bit_3sat* a, bit_3sat* b);

void xnor_b3(int* num_parm, int** lst, bit_3sat** c, bit_3sat* a, bit_3sat* b);

int** bitaddsum_b3(int* num_parm, int** lst, bit_3sat** sum, bit_3sat* c_in, bit_3sat* a, bit_3sat* b);

int** bitaddcout_b3(int* num_parm, int** lst, bit_3sat** c_out, bit_3sat* c_in, bit_3sat* a, bit_3sat* b);

int** implies_b3(int* num_parm, int ** lst, bit_3sat** c, bit_3sat* a, bit_3sat* b);

int** equals_b3(int* num_parm, int *** lst, dec_3sat* a, dec_3sat* b, bool eq, __int64* len_para);

int** not_equals_b3(int* num_parm, int *** lst, dec_3sat* a, dec_3sat* b, __int64* len_para);

bit_3sat** pre_processing_b3(int* num_parm, bit_3sat** input, uint64_t input_len, int* output_len);

bit_3sat** Ch_b3(int* num_parm, int ** lst, bit_3sat** x, bit_3sat** y, bit_3sat** z);

bit_3sat** Maj_b3(int* num_parm, int ** lst, bit_3sat** x, bit_3sat** y, bit_3sat** z);

bit_3sat** ROTR_b3(int* num_parm, int ** lst, bit_3sat** x, int n);

bit_3sat** S0_b3(int* num_parm, int ** lst, bit_3sat** x);

bit_3sat** S1_b3(int* num_parm, int ** lst, bit_3sat** x);

bit_3sat** s0_b3(int* num_parm, int ** lst, bit_3sat** x);

bit_3sat** s1_b3(int* num_parm, int ** lst, bit_3sat** x);

bit_3sat** RND_b3(a, b, c, d, e, f, g, h, k);

bit_3sat** RNDr_b3(S, W, i);

void sha256_transform_b3(uint32_t* state, const uint32_t* block, int swap);

static void sha256d_80_swap_b3(uint32_t* hash, const uint32_t* data);

void sha256d_b3(unsigned char* hash, const unsigned char* data, int len);

static inline void sha256d_preextend_b3(uint32_t* W);

static inline void sha256d_prehash_b3(uint32_t* S, const uint32_t* W);

void sha256d_ms_b3(uint32_t* hash, uint32_t* W, const uint32_t* midstate, const uint32_t* prehash);

static inline void sha256d_ms_b3(uint32_t* hash, uint32_t* W, const uint32_t* midstate, const uint32_t* prehash);

bit_3sat** uint32_to_bit3sat_b3(__int64 parm);

bit_3sat** sha_256_b3(int* num_parm, bit_3sat** input, int intput_len);

#endif // !__b3FRAMEWORK_H__