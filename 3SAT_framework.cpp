// 3SAT_framework.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#ifndef __3SATFRAMEWORK_C__
#define __3SATFRAMEWORK_C__

#include "3SAT_framework.hpp"
#include "3SATBaseConsole.hpp"

#include <iostream>
#include <stdio.h>

// Tseytin transformations being employed here to convert operations to 3-CNF

bit_3sat* create_bit(int* num_parm) {

    bit_3sat* ret = new bit_3sat();
    
    ret->id = *num_parm;

    if ( *num_parm != FALSE_3SAT && *num_parm != TRUE_3SAT)
        (*num_parm)++;

    return ret;

}

dec_3sat* create_dec(int * num_parm, int bd_sz_parm, int ad_sz_parm) {

    dec_3sat* ret = new dec_3sat();
    ret->bd_sz = bd_sz_parm;
    ret->ad_sz = ad_sz_parm;
    ret->sz = bd_sz_parm + ad_sz_parm;
    ret->bits = new bit_3sat * [ret->sz];
    for (int i = 0; i < ret->sz; i++)
        ret->bits[i] = create_bit(num_parm);
    return ret;

}

nat_3sat* create_nat(int* num_parm, int sz_parm) {

    nat_3sat* ret = new nat_3sat();
    ret->sz = sz_parm;
    ret->bits = new bit_3sat * [ret->sz];
    for (int i = 0; i < ret->sz; i++)
        ret->bits[i] = create_bit(num_parm);
    return ret;

}


// c = a and b: (~a or ~b or c) (a or ~c) (b or ~c)

char* and_3sat(int * num_parm, bit_3sat** c, bit_3sat* a, bit_3sat* b, int *len_para) {

    *c = create_bit(num_parm);
    char** lst = new char* [3];
    for (int i = 0; i < 3; i++)
        lst[i] = new char[64];

    /*
    sprintf_s(lst[0], "-%d -%d %d", a->id, b->id, c->id);
    sprintf_s(lst[1], "%d -%d", a->id, c->id);
    sprintf_s(lst[2], "%d -%d", b->id, c->id);
    */

    sprintf_s(lst[0], 64, "%d %d %d", -a->id, -b->id, (*c)->id);
    sprintf_s(lst[1], 64, "%d %d %d", a->id, -(*c)->id, FALSE_3SAT);
    sprintf_s(lst[2], 64, "%d %d %d", b->id, -(*c)->id, FALSE_3SAT);

    int ret_len = (int)strnlen_s(lst[0], 64) + (int)strnlen_s(lst[1], 64) + (int)strnlen_s(lst[2], 64) + 3 * (int)strnlen_s("\n", 2) + 1;
    char* ret = new char[ret_len];

    int len = 0;
    for (int i = 0; i < 3; i++) {
        sprintf_s(&(ret[len]), ret_len-len, "%s\n", lst[i]);
        len += (int) strnlen_s(lst[i], 64) + (int) strnlen_s("\n", 2);
        delete lst[i];
    }

    *len_para = ret_len - 1;

    delete [] lst;

    return ret;

}

// c = a nand b: (~a or ~b or ~c) (a or c) (b or c)

char* nand_3sat(int * num_parm, bit_3sat** c, bit_3sat* a, bit_3sat* b, int *len_para) {

    *c = create_bit(num_parm);
    char** lst = new char* [3];
    for (int i = 0; i < 3; i++)
        lst[i] = new char[64];

    /*
    sprintf_s(lst[0], "-%d -%d -%d", a->id, b->id, c->id);
    sprintf_s(lst[1], "%d %d", a->id, c->id);
    sprintf_s(lst[2], "%d %d", b->id, c->id);
    */

    sprintf_s(lst[0], 64, "%d %d %d", -a->id, -b->id, -(*c)->id);
    sprintf_s(lst[1], 64, "%d %d %d", a->id, (*c)->id, FALSE_3SAT);
    sprintf_s(lst[2], 64, "%d %d %d", b->id, (*c)->id, FALSE_3SAT);

    int ret_len = (int)strnlen_s(lst[0], 64) + (int)strnlen_s(lst[1], 64) + (int)strnlen_s(lst[2], 64)+ 3 * (int)strnlen_s("\n", 2) + 1;
    char* ret = new char[ret_len];

    int len = 0;
    for (int i = 0; i < 3; i++) {
        sprintf_s(&ret[len], ret_len-len, "%s\n", lst[i]);
        len += (int) strnlen_s(lst[i], 64) + (int) strnlen_s("\n", 2);
        delete lst[i];
    }

    *len_para = len;

    delete [] lst;

    return ret;

}

// c = a or b: (a or b or ~c) (~a or c) (~b or c)

char* or_3sat(int * num_parm, bit_3sat** c, bit_3sat *a, bit_3sat* b, int *len_para) {

    *c = create_bit(num_parm);
    char** lst = new char* [3];
    for (int i = 0; i < 3; i++)
        lst[i] = new char[64];

    /*
    sprintf_s(lst[0], "%d %d -%d", a->id, b->id, c->id);
    sprintf_s(lst[1], "-%d %d", a->id, c->id);
    sprintf_s(lst[2], "-%d %d", b->id, c->id);
    */

    sprintf_s(lst[0], 64, "%d %d %d", a->id, b->id, -(*c)->id);
    sprintf_s(lst[1], 64, "%d %d %d", -a->id, (*c)->id, FALSE_3SAT);
    sprintf_s(lst[2], 64, "%d %d %d", -b->id, (*c)->id, FALSE_3SAT);

    int ret_len = (int)strnlen_s(lst[0], 64) + (int)strnlen_s(lst[1], 64) + (int)strnlen_s(lst[2], 64) + 3 * (int)strnlen_s("\n", 2) + 1;
    char* ret = new char[ret_len];

    int len = 0;
    for (int i = 0; i < 3; i++) {
        sprintf_s(&ret[len], ret_len-len, "%s\n", lst[i]);
        len += (int) strnlen_s(lst[i], 64) + (int) strnlen_s("\n", 2);
        delete lst[i];
    }

    *len_para = len;

    delete [] lst;

    return ret;

}

// c = a nor b: (a or b or c) (~a or ~c) (~b or ~c)

char* nor_3sat(int* num_parm, bit_3sat** c, bit_3sat* a, bit_3sat* b, int* len_para) {

    *c = create_bit(num_parm);
    char** lst = new char* [3];
    for (int i = 0; i < 3; i++)
        lst[i] = new char[64];

    /*
    sprintf_s(lst[0], "%d %d %d", a->id, b->id, c->id);
    sprintf_s(lst[1], "-%d -%d", a->id, c->id);
    sprintf_s(lst[2], "-%d -%d", b->id, c->id);
    */

    sprintf_s(lst[0], 64, "%d %d %d", a->id, b->id, (*c)->id);
    sprintf_s(lst[1], 64, "%d %d %d", -a->id, -(*c)->id, FALSE_3SAT);
    sprintf_s(lst[2], 64, "%d %d %d", -b->id, -(*c)->id, FALSE_3SAT);

    int ret_len = (int)strnlen_s(lst[0], 64) + (int)strnlen_s(lst[1], 64) + (int)strnlen_s(lst[2], 64) + 3 * (int)strnlen_s("\n", 2) + 1;
    char* ret = new char[ret_len];

    int len = 0;
    for (int i = 0; i < 3; i++) {
        sprintf_s(&(ret[len]), ret_len-len, "%s\n", lst[i]);
        len += (int) strnlen_s(lst[i], 64) + (int) strnlen_s("\n", 2);
        delete lst[i];
    }

    *len_para = len;

    delete [] lst;

    return ret;

}

// c = not a: (~a or ~c) (a or c)

char* not_3sat(int * num_parm, bit_3sat** c, bit_3sat* a, int *len_para) {

    *c = create_bit(num_parm);
    char** lst = new char* [4];
    for (int i = 0; i < 2; i++)
        lst[i] = new char[64];

    /*
    sprintf_s(lst[0], "-%d -%d", a->id, c->id);
    sprintf_s(lst[1], "%d %d", a->id, c->id);
    */

    sprintf_s(lst[0], 64, "%d %d %d", -a->id, -(*c)->id, FALSE_3SAT);
    sprintf_s(lst[1], 64, "%d %d %d", a->id, (*c)->id, FALSE_3SAT);

    int ret_len = (int)strnlen_s(lst[0], 64) + (int)strnlen_s(lst[1], 64) + 2 * (int)strnlen_s("\n", 2) + 1;

    char* ret = new char[ret_len];

    int len = 0;
    for (int i = 0; i < 2; i++) {
        sprintf_s(&ret[len], ret_len-len, "%s\n", lst[i]);
        len += (int) strnlen_s(lst[i], 64) + (int) strnlen_s("\n", 2);
        delete lst[i];
    }

    *len_para = len;

    delete [] lst;

    return ret;

}

// c = a xor b: (~a or ~b or ~c) (a or b or ~c) (a or ~b or c) (~a or b or c)

char* xor_3sat(int * num_parm, bit_3sat** c, bit_3sat* a, bit_3sat* b, int *len_para) {

    *c = create_bit(num_parm);
    char** lst = new char* [4];
    for (int i = 0; i < 4; i++)
        lst[i] = new char[64];

    sprintf_s(lst[0], 64, "%d %d %d", -a->id, -b->id, -(*c)->id);
    sprintf_s(lst[1], 64, "%d %d %d", a->id, b->id, -(*c)->id);
    sprintf_s(lst[2], 64, "%d %d %d", a->id, -b->id, (*c)->id);
    sprintf_s(lst[3], 64, "%d %d %d", -a->id, b->id, (*c)->id);

    int ret_len = 1;
    for (int i = 0; i < 4; i++)
        ret_len += (int)strnlen_s(lst[i], 64) + (int)strnlen_s("\n", 2);

    char* ret = new char[ret_len];

    int len = 0;
    for (int i = 0; i < 4; i++) {
        sprintf_s(&(ret[len]), ret_len-len, "%s\n", lst[i]);
        len += (int) strnlen_s(lst[i], 64) + (int) strnlen_s("\n", 2);
        delete [] lst[i];
    }

    *len_para = len;

    delete [] lst;

    return ret;

}

// c = a xnor b: (~a or ~b or c) (a or b or c) (a or ~b or ~c) (~a or b or ~c)

char* xnor_3sat(int * num_parm, bit_3sat** c, bit_3sat* a, bit_3sat* b, int *len_para) {

    *c = create_bit(num_parm);
    char** lst = new char* [4];
    for (int i = 0; i < 4; i++)
        lst[i] = new char[64];

    sprintf_s(lst[0], 64, "%d %d %d", -a->id, -b->id, (*c)->id);
    sprintf_s(lst[1], 64, "%d %d %d", a->id, b->id, (*c)->id);
    sprintf_s(lst[2], 64, "%d %d %d", a->id, -b->id, -(*c)->id);
    sprintf_s(lst[3], 64, "%d %d %d", -a->id, b->id, -(*c)->id);

    int ret_len = 1;
    for (int i = 0; i < 4; i++)
        ret_len += (int)strnlen_s(lst[i], 64) + (int) strnlen_s("\n", 2);

    char* ret = new char[ret_len];

    int len = 0;
    for (int i = 0; i < 4; i++) {
        sprintf_s(&(ret[len]), ret_len-len, "%s\n", lst[i]);
        len += (int) strnlen_s(lst[i], 64) + (int) strnlen_s("\n", 2);
        delete lst[i];
    }

    *len_para = len;

    delete [] lst;

    return ret;

}

// bitadd = a + b + cin: cin xor (a xor b) = (~a or ~b or ~c) (a or b or ~c) (a or ~b or c) (~a or b or c)

char* bitaddsum_3sat(int * num_parm, bit_3sat** sum, bit_3sat* c_in, bit_3sat* a, bit_3sat* b, int *len_para) {

    bit_3sat * c;

    int x1_len = 0;
    char* x1 = xor_3sat(num_parm, &c, a, b, &x1_len);

    int x2_len = 0;
    char* x2 = xor_3sat(num_parm, sum, c_in, c, &x2_len);

    int ret_len = x1_len + x2_len + 1;
    char* ret = new char[ret_len];

    int pos = 0;

    strcpy_s(&(ret[pos]), ret_len-pos, x1);
    pos += x1_len;
    strcpy_s(&(ret[pos]), ret_len-pos, x2);
    pos += x2_len;
    
    *len_para = pos;

    delete c;

    delete x1;
    delete x2;

    return ret;

}

// bitcout = a + b + cin: (a and b) or (b and cin) or (a and cin):

char* bitaddcout_3sat(int * num_parm, bit_3sat** c_out, bit_3sat* c_in, bit_3sat* a, bit_3sat* b, int *len_para) {

    bit_3sat * a1;
    bit_3sat * a2;
    bit_3sat * a3;
    bit_3sat * o1;

    int a1_len = 0;
    char* a1_str = and_3sat(num_parm, &a1, a, b, &a1_len);
    int a2_len = 0;
    char* a2_str = and_3sat(num_parm, &a2, a, c_in, &a2_len);
    int a3_len = 0;
    char* a3_str = and_3sat(num_parm, &a3, b, c_in, &a3_len);
    int o1_len = 0;
    char* o1_str = or_3sat(num_parm, &o1, a1, a2, &o1_len);
    int o2_len = 0;
    char* o2_str = or_3sat(num_parm, c_out, a3, o1, &o2_len);

    int ret_len = a1_len + a2_len + a3_len + o1_len + o2_len + 1;
    char* ret = new char[ret_len];

    int pos = 0;

    strcpy_s(&(ret[pos]), ret_len-pos, a1_str);
    pos += a1_len;
    strcpy_s(&(ret[pos]), ret_len-pos, a2_str);
    pos += a2_len;
    strcpy_s(&(ret[pos]), ret_len-pos, a3_str);
    pos += a3_len;
    strcpy_s(&(ret[pos]), ret_len-pos, o1_str);
    pos += o1_len;
    strcpy_s(&(ret[pos]), ret_len-pos, o2_str);
    pos += o2_len;

    *len_para = pos;

    delete a1;
    delete a2;
    delete a3;
    delete o1;

    delete a1_str;
    delete a2_str;
    delete a3_str;
    delete o1_str;
    delete o2_str;

    return ret;
}

// implies = a->b: (~a or b)

char* implies_3sat(int * num_parm, bit_3sat** c, bit_3sat* a, bit_3sat* b, int *len_para) {

    int pos = 0;

    // invert a

    int not_len = 0;

    bit_3sat* a_inv = NULL;
    char* not_a_str = not_3sat(num_parm, &a_inv , a , &not_len);

    // or with b

    int or_len = 0;
    char* or_str = or_3sat(num_parm, c, a_inv, b, &or_len);

    int ret_len = not_len + or_len + 1;

    char* ret = new char[ret_len];

    strcpy_s(&(ret[pos]), ret_len - pos, not_a_str);
    pos += not_len;
    strcpy_s(&(ret[pos]), ret_len - pos, or_str);
    pos += or_len;

    *len_para = pos;

    delete not_a_str;
    delete or_str;

    return ret;

}

// dec_add c = a + b

char* dec_add(int * num_parm, dec_3sat** c, dec_3sat* a, dec_3sat* b, bool discard_final_c_out, int *len_para) {

    // find the largest number of bits

    int bd_bits = a->bd_sz > b->bd_sz ? a->bd_sz : b->bd_sz ;
    int ad_bits = a->ad_sz > b->ad_sz ? a->ad_sz : b->ad_sz ;
    int tt_bits = bd_bits + ad_bits;

    // create modified a and b

    dec_3sat* a_mod = new dec_3sat();
    dec_3sat* b_mod = new dec_3sat();

    a_mod->ad_sz = ad_bits;
    a_mod->bd_sz = bd_bits;
    a_mod->sz = tt_bits;

    b_mod->ad_sz = ad_bits;
    b_mod->bd_sz = bd_bits;
    b_mod->sz = tt_bits;

    a_mod->bits = new bit_3sat * [tt_bits];
    b_mod->bits = new bit_3sat * [tt_bits];

    // populate a_mod and b_mod

    int a_ad_extra = ad_bits > a->ad_sz ? ad_bits - a->ad_sz : 0;
    int a_bd_extra = bd_bits > a->bd_sz ? bd_bits - a->bd_sz : 0;

    int b_ad_extra = ad_bits > b->ad_sz ? ad_bits - b->ad_sz : 0;
    int b_bd_extra = bd_bits > b->bd_sz ? bd_bits - b->bd_sz : 0;

    // sign-extend for bd

    int a_mod_start = 0;
    int b_mod_start = 0;

    for (a_mod_start = 0; a_mod_start < a_bd_extra; a_mod_start++) {
        a_mod->bits[a_mod_start] = new bit_3sat();
        a_mod->bits[a_mod_start]->id = a->bits[0]->id;
    }

    for (b_mod_start = 0; b_mod_start < b_bd_extra; b_mod_start++) {
        b_mod->bits[b_mod_start] = new bit_3sat();
        b_mod->bits[b_mod_start]->id = b->bits[0]->id;
    }

    // copy over bits

    for (int i = 0; i < a->sz; i++) {
        a_mod->bits[a_mod_start + i] = new bit_3sat();
        a_mod->bits[a_mod_start + i]->id = a->bits[i]->id;
    }

    for (int i = 0; i < b->sz; i++) {
        b_mod->bits[b_mod_start + i] = new bit_3sat();
        b_mod->bits[b_mod_start + i]->id = b->bits[i]->id;
    }

    // rpad with 0s

    int a_rpad = a_mod->ad_sz > a->ad_sz ? a_mod->ad_sz - a->ad_sz : 0;
    int b_rpad = b_mod->ad_sz > b->ad_sz ? b_mod->ad_sz - b->ad_sz : 0;

    for (int i = 0; i < a_rpad; i++) {
        a_mod->bits[a_mod_start + a->sz + i] = new bit_3sat();
        a_mod->bits[a_mod_start + a->sz + i]->id = FALSE_3SAT;
    }

    for (int i = 0; i < b_rpad; i++) {
        b_mod->bits[b_mod_start + b->sz + i] = new bit_3sat();
        b_mod->bits[b_mod_start + b->sz + i]->id = FALSE_3SAT;
    }

    // instantiate c

    *c = new dec_3sat();
    (*c)->bd_sz = bd_bits;
    (*c)->ad_sz = ad_bits;
    (*c)->sz = tt_bits + (discard_final_c_out ? 0 : 1);
    (*c)->bits = new bit_3sat * [(*c)->sz];

    bit_3sat* c_in = new bit_3sat();
    c_in->id = FALSE_3SAT;
    bit_3sat* c_out = NULL;

    // create sum_str and c_out_str buffers

    int* sum_str_len = new int[tt_bits];
    char** sum_strs = new char* [tt_bits];
    for (int i = 0; i < tt_bits; i++)
        sum_strs[i] = new char[256];

    int* cout_str_len = new int[tt_bits];
    char** cout_strs = new char* [tt_bits];
    for (int i = 0; i < tt_bits; i++)
        cout_strs[i] = new char[512];

    // perform the first addition with a zero for carry_in

    char* sum_str = bitaddsum_3sat(num_parm, &((*c)->bits [(*c)->sz - 1]), c_in, a_mod->bits[a_mod->sz - 1], b_mod->bits[b_mod->sz - 1], &(sum_str_len[tt_bits - 1]));
    strcpy_s(sum_strs[tt_bits - 1], 256, sum_str);

    char* c_out_str = bitaddcout_3sat(num_parm, &c_out, c_in, a_mod->bits[a_mod->sz - 1], b_mod->bits[b_mod->sz - 1], &(cout_str_len[tt_bits - 1]));
    strcpy_s(cout_strs[tt_bits - 1], 512, c_out_str);
    delete c_in;
    c_in = c_out;

    delete sum_str;
    delete c_out_str;

    // perform all the rest of the additions

    for (int i = 1; i < tt_bits; i++) {

        char* sum_str = bitaddsum_3sat(num_parm, &((*c)->bits[(*c)->sz - i - 1]), c_in, a_mod->bits[a_mod->sz - i - 1], b_mod->bits[b_mod->sz - i - 1],
            &(sum_str_len[tt_bits - i - 1]));
        strcpy_s(sum_strs[tt_bits - i - 1], 256, sum_str);

        char* c_out_str = bitaddcout_3sat(num_parm, &c_out, c_in, a_mod->bits[a_mod->sz - i - 1], b_mod->bits[b_mod->sz - i - 1], &(cout_str_len[tt_bits - i - 1]));
        strcpy_s(cout_strs[tt_bits - i - 1], 512, c_out_str);
        delete c_in;
        c_in = c_out;

        delete sum_str;
        delete c_out_str;
    }

    // set the msb of c as the final carry_out value

    if (discard_final_c_out)
        delete c_in;
    else
        (*c)->bits[0] = c_in;

    // create ret string

    int ret_sz = 1;
    for (int i = 0; i < tt_bits; i++) {
        ret_sz += sum_str_len[i];
        ret_sz += cout_str_len[i];
    }

    char* ret = new char[ret_sz];

    // populate ret string

    int pos = 0;

    for (int i = 0; i < tt_bits; i++) {
        strcpy_s(&(ret[pos]), ret_sz - pos, sum_strs[i]);
        pos += sum_str_len[i];
        strcpy_s(&(ret[pos]), ret_sz - pos, cout_strs[i]);
        pos += cout_str_len[i];
    }

    *len_para = pos;

    // clean up

    for (int i = 0; i < tt_bits; i++) {
        delete sum_strs[i];
        delete cout_strs[i];
    }
    delete [] sum_strs;
    delete [] cout_strs;
    delete [] sum_str_len;
    delete [] cout_str_len;

    // return the buffer of 3-CNF

    return ret;

}

char* nat_add(int* num_parm, nat_3sat** c, nat_3sat* a, nat_3sat* b, bool discard_final_c_out, int* len_para) {

    // find the largest number of bits

    int tt_bits = a->sz > b->sz ? a->sz : b->sz ;

    // create modified a and b

    nat_3sat* a_mod = new nat_3sat();
    nat_3sat* b_mod = new nat_3sat();

    a_mod->sz = tt_bits;

    b_mod->sz = tt_bits;

    a_mod->bits = new bit_3sat * [tt_bits];
    b_mod->bits = new bit_3sat * [tt_bits];

    // populate a_mod and b_mod

    int a_extra = tt_bits - a->sz;
    int b_extra = tt_bits - b->sz;

    // sign-extend for bd

    int a_mod_start = 0;
    int b_mod_start = 0;

    for (a_mod_start = 0; a_mod_start < a_extra; a_mod_start++) {
        a_mod->bits[a_mod_start] = new bit_3sat();
        a_mod->bits[a_mod_start]->id = FALSE_3SAT;
    }

    for (b_mod_start = 0; b_mod_start < b_extra; b_mod_start++) {
        b_mod->bits[b_mod_start] = new bit_3sat();
        b_mod->bits[b_mod_start]->id = FALSE_3SAT;
    }

    // copy over bits

    for (int i = 0; i < a->sz; i++) {
        a_mod->bits[a_mod_start + i] = new bit_3sat();
        a_mod->bits[a_mod_start + i]->id = a->bits[i]->id;
    }

    for (int i = 0; i < b->sz; i++) {
        b_mod->bits[b_mod_start + i] = new bit_3sat();
        b_mod->bits[b_mod_start + i]->id = b->bits[i]->id;
    }

    // instantiate c

    *c = new nat_3sat();
    (*c)->sz = tt_bits + (discard_final_c_out ? 0 : 1);
    (*c)->bits = new bit_3sat * [(*c)->sz];

    bit_3sat* c_in = new bit_3sat();
    c_in->id = FALSE_3SAT;
    bit_3sat* c_out = NULL;

    // create sum_str and c_out_str buffers

    int* sum_str_len = new int[tt_bits];
    char** sum_strs = new char* [tt_bits];
    for (int i = 0; i < tt_bits; i++)
        sum_strs[i] = new char[256];

    int* cout_str_len = new int[tt_bits];
    char** cout_strs = new char* [tt_bits];
    for (int i = 0; i < tt_bits; i++)
        cout_strs[i] = new char[512];

    // perform the first addition with a zero for carry_in

    char* sum_str = bitaddsum_3sat(num_parm, &((*c)->bits[(*c)->sz - 1]), c_in, a_mod->bits[a_mod->sz - 1], b_mod->bits[b_mod->sz - 1], &(sum_str_len[tt_bits - 1]));
    strcpy_s(sum_strs[tt_bits - 1], 256, sum_str);

    char* c_out_str = bitaddcout_3sat(num_parm, &c_out, c_in, a_mod->bits[a_mod->sz - 1], b_mod->bits[b_mod->sz - 1], &(cout_str_len[tt_bits - 1]));
    strcpy_s(cout_strs[tt_bits - 1], 512, c_out_str);
    delete c_in;
    c_in = c_out;

    delete sum_str;
    delete c_out_str;

    // perform all the rest of the additions

    for (int i = 1; i < tt_bits; i++) {

        char* sum_str = bitaddsum_3sat(num_parm, &((*c)->bits[(*c)->sz - i - 1]), c_in, a_mod->bits[a_mod->sz - i - 1], b_mod->bits[b_mod->sz - i - 1],
            &(sum_str_len[tt_bits - i - 1]));
        strcpy_s(sum_strs[tt_bits - i - 1], 256, sum_str);

        char* c_out_str = bitaddcout_3sat(num_parm, &c_out, c_in, a_mod->bits[a_mod->sz - i - 1], b_mod->bits[b_mod->sz - i - 1], &(cout_str_len[tt_bits - i - 1]));
        strcpy_s(cout_strs[tt_bits - i - 1], 512, c_out_str);
        delete c_in;
        c_in = c_out;

        delete sum_str;
        delete c_out_str;
    }

    // set the msb of c as the final carry_out value

    if (discard_final_c_out)
        delete c_in;
    else
        (*c)->bits[0] = c_in;

    // create ret string

    int ret_sz = 1;
    for (int i = 0; i < tt_bits; i++) {
        ret_sz += sum_str_len[i];
        ret_sz += cout_str_len[i];
    }

    char* ret = new char[ret_sz];

    // populate ret string

    int pos = 0;

    for (int i = 0; i < tt_bits; i++) {
        strcpy_s(&(ret[pos]), ret_sz - pos, sum_strs[i]);
        pos += sum_str_len[i];
        strcpy_s(&(ret[pos]), ret_sz - pos, cout_strs[i]);
        pos += cout_str_len[i];
    }

    *len_para = pos;

    // clean up

    for (int i = 0; i < tt_bits; i++) {
        delete sum_strs[i];
        delete cout_strs[i];
    }
    delete [] sum_strs;
    delete [] cout_strs;
    delete [] sum_str_len;
    delete [] cout_str_len;

    // return the buffer of 3-CNF

    return ret;

}

// twos_complement = -a

char* twos_comp_3sat(int* num_parm, dec_3sat** c, dec_3sat* a, int *len_para) {

    // create not_3sat_strs and not_3sat_len

    char** not_3sat_strs = new char *[a->sz];
    for (int i = 0; i < a->sz; i++)
        not_3sat_strs[i] = new char[64];

    int* not_3sat_len = new int[a->sz];
    for (int i = 0; i < a->sz; i++)
        not_3sat_len[i] = 0;

    // invert a

    dec_3sat* a_inv = new dec_3sat();
    a_inv->sz = a->sz;
    a_inv->ad_sz = a->ad_sz;
    a_inv->bd_sz = a->bd_sz;
    a_inv->bits = new bit_3sat * [a_inv->sz]();
    for (int i = 0; i < a_inv->sz; i++) {
        char * not_str = not_3sat(num_parm, &a_inv->bits[i], a->bits[i], &(not_3sat_len[i]));
        strcpy_s(not_3sat_strs[i], 64, not_str);
    }

    // create one, adjusting for any fractions

    dec_3sat* b = new dec_3sat();
    b->sz = 2;
    b->bd_sz = 2;
    b->ad_sz = 0;
    b->bits = new bit_3sat * [2];
    b->bits[0] = new bit_3sat();
    b->bits[0]->id = FALSE_3SAT;
    b->bits[1] = new bit_3sat();
    b->bits[1]->id = TRUE_3SAT;

    // perform the addition discarding the final carry

    int add_str_len = 0;

    char* add_str = dec_add(num_parm, c, b, a_inv, true, &add_str_len);

    // calculate size of ret string and copy over all data

    int ret_sz = 0;

    for (int i = 0; i < a->sz; i++)
        ret_sz += not_3sat_len[i];
    ret_sz += add_str_len;

    char* ret = new char[ret_sz];

    int pos = 0;

    for (int i = 0; i < a->sz; i++) {
        strcpy_s(&(ret[pos]), not_3sat_len[i], not_3sat_strs[i]);
        pos += not_3sat_len[i];
    }
    strcpy_s(&(ret[pos]), add_str_len, add_str);
    pos += add_str_len;

    ret[pos] = '\0';

    // clean up

    for (int i = 0; i < a->sz; i++)
        delete not_3sat_strs[i];
    delete [] not_3sat_strs;

    delete add_str;
    delete [] not_3sat_len;

    *len_para = pos;

    // return 3sat source

    return ret;
}

// dec_sub c = a + -b

char* dec_sub(int* num_parm, dec_3sat** c, dec_3sat* a, dec_3sat* b, int *len_para) {

    int buf_sz = (64 + 768) * b->sz + 768 * (a->sz > b->sz ? a->sz : b->sz);
    char* ret = new char[buf_sz];
    int pos = 0;

    dec_3sat* twos_b = NULL;

    int twos_str_len = 0;
    char* twos_str = twos_comp_3sat(num_parm, &twos_b, b, &twos_str_len);
    strcpy_s(&(ret[pos]), twos_str_len, twos_str);
    pos += twos_str_len;

    int add_str_len = 0;
    char* add_str = dec_add(num_parm, c, a, twos_b, false, &add_str_len);
    strcpy_s(&(ret[pos]), add_str_len, add_str);
    pos += add_str_len;

    *len_para = twos_str_len + add_str_len;

    delete twos_str;
    delete add_str;

    return ret;

}

// force equals

char* dec_equals(int * num_parm, dec_3sat* a, dec_3sat* b, bool eq, __int64* len_para) {

    // c = a xnor b
    // d = and all c bits together
    // d must be equal to T

    // create modified a and b for comparison purposes

    dec_3sat* a_mod;
    dec_3sat* b_mod;

    int bd_sz = a->bd_sz < b->bd_sz ? a->bd_sz : b->bd_sz;
    int a_start = bd_sz < a->bd_sz ? a->bd_sz - bd_sz : a->bd_sz;
    int b_start = bd_sz < b->bd_sz ? b->bd_sz - bd_sz : b->bd_sz;

    // sign-extend, if necessary

    int ad_sz = a->ad_sz > b->ad_sz ? a->ad_sz : b->bd_sz;
    int a_sign_ext = ad_sz - a->ad_sz;
    int b_sign_ext = ad_sz - b->ad_sz;

    // instantiate a_mod and b_mod
    a_mod = new dec_3sat();
    a_mod->ad_sz = ad_sz;
    a_mod->bd_sz = bd_sz;
    a_mod->sz = ad_sz + bd_sz;
    a_mod->bits = new bit_3sat * [ad_sz + bd_sz];

    b_mod = new dec_3sat();
    b_mod->ad_sz = ad_sz;
    b_mod->bd_sz = bd_sz;
    b_mod->sz = ad_sz + bd_sz;
    b_mod->bits = new bit_3sat * [ad_sz + bd_sz];

    // sign-extend a
    for (int i = 0; i < a_start; i++) {
        a_mod->bits[i] = new bit_3sat();
        a_mod->bits[i]->id = a->bits[0]->id;
    }

    // sign-extend b
    for (int i = 0; i < b_start; i++) {
        b_mod->bits[i] = new bit_3sat();
        b_mod->bits[i]->id = b->bits[0]->id;
    }

    // copy over data for a
    for (int i = a_start; i < a->sz - a_sign_ext; i++) {
        a_mod->bits[i] = new bit_3sat();
        a_mod->bits[i]->id = a->bits[i]->id;
    }

    // copy over data for b
    for (int i = b_start; i < b->sz - b_sign_ext; i++) {
        b_mod->bits[i] = new bit_3sat();
        b_mod->bits[i]->id = b->bits[i]->id;
    }

    // rpad a with 0s out to length
    for (int i = a->sz - a_sign_ext; i < bd_sz + ad_sz; i++) {
        a_mod->bits[i] = new bit_3sat();
        a_mod->bits[i]->id = FALSE_3SAT;
    }

    // rpad b with 0s out to length
    for (int i = b->sz - b_sign_ext; i < bd_sz + ad_sz; i++) {
        b_mod->bits[i] = new bit_3sat();
        b_mod->bits[i]->id = FALSE_3SAT;
    }

    // create return buffer

    int buf_sz = (bd_sz + ad_sz) * (128 + 128) + 128;
    char* ret = new char[buf_sz];
    int pos = 0;

    // xnor them all together

    int* xnor_str_len = new int[bd_sz + ad_sz];
    for (int i = 0; i < bd_sz + ad_sz; i++)
        xnor_str_len[i] = 0;

    dec_3sat* c = create_dec(num_parm, bd_sz, ad_sz);
    for (int i = 0; i < bd_sz + ad_sz; i++) {
        char* xnor_str = xnor_3sat(num_parm, &c->bits[i], a_mod->bits[i], b_mod->bits[i], & (xnor_str_len[i]));
        strcpy_s(&(ret[pos]), buf_sz - pos, xnor_str);
        pos += xnor_str_len[i];
    }

    // and all those xnors together

    int* and_str_len = new int[c->sz];
    for (int i = 0; i < c->sz; i++)
        and_str_len[i] = 0;

    int id = c->bits[0]->id;

    bit_3sat* d = new bit_3sat();
    d->id = id;

    for (int i = 1; i < c->sz; i++) {
        bit_3sat* temp = NULL;
        char* and_str = and_3sat(num_parm, &temp, d, c->bits[i], &(and_str_len[i]));
        strcpy_s(&(ret[pos]), buf_sz - pos, and_str);
        pos += and_str_len[i];
        bit_3sat* dump = d;
        d = temp;
        delete dump;
    }

    // verify that d xnors with eq (set to either true or false)

    int final_xnor_str_len = 0;

    bit_3sat* eq_bit = new bit_3sat();
    eq_bit->id = eq ? TRUE_3SAT : FALSE_3SAT;

    bit_3sat* f = NULL;
    char* final_xnor_str = xnor_3sat(num_parm, &f, d, eq_bit, &final_xnor_str_len);
    strcpy_s(&(ret[pos]), buf_sz - pos, final_xnor_str);
    pos += final_xnor_str_len;

    *len_para = pos;

    delete final_xnor_str;
    delete [] xnor_str_len;
    delete [] and_str_len;

    return ret;

}

char* nat_equals(int* num_parm, nat_3sat* a, nat_3sat* b, bool eq, __int64* len_para) {

    // c = a xnor b
    // d = and all c bits together
    // d must be equal to T
    
    // create modified a and b for comparison purposes

    //nat_3sat* a_mod;
    //nat_3sat* b_mod;

    int num_sz = a->sz > b->sz ? a->sz : b->sz;
/*    int a_start = num_sz < a->sz ? a->sz - num_sz : a->sz;
    int b_start = num_sz < b->sz ? b->sz - num_sz : b->sz;

    int a_sign_ext = num_sz - a->sz;
    int b_sign_ext = num_sz - b->sz;

    // instantiate a_mod and b_mod
    a_mod = new nat_3sat();
    a_mod->sz = num_sz;
    a_mod->bits = new bit_3sat * [num_sz];

    b_mod = new nat_3sat();
    b_mod->sz = num_sz;
    b_mod->bits = new bit_3sat * [num_sz];

    // extend a with FALSE_3SAT
    for (int i = 0; i < a_start; i++) {
        a_mod->bits[i] = new bit_3sat();
        a_mod->bits[i]->id = FALSE_3SAT;
    }

    // extend a with FALSE_3SAT
    for (int i = 0; i < b_start; i++) {
        b_mod->bits[i] = new bit_3sat();
        b_mod->bits[i]->id = FALSE_3SAT;
    }

    // copy over data for a
    for (int i = a_start; i < a->sz - a_sign_ext; i++) {
        a_mod->bits[i] = new bit_3sat();
        a_mod->bits[i]->id = a->bits[i]->id;
    }

    // copy over data for b
    for (int i = b_start; i < b->sz - b_sign_ext; i++) {
        b_mod->bits[i] = new bit_3sat();
        b_mod->bits[i]->id = b->bits[i]->id;
    }
    */
    // create return buffer

    int buf_sz = (num_sz) * (128 + 128) + 128;
    char* ret = new char[buf_sz];
    int pos = 0;

    // xnor them all together

    int* xnor_str_len = new int[num_sz];
    for (int i = 0; i < num_sz; i++)
        xnor_str_len[i] = 0;

    nat_3sat* c = create_nat(num_parm, num_sz);
    for (int i = 0; i < num_sz; i++) {
        char* xnor_str = xnor_3sat(num_parm, &c->bits[i], a->bits[i], b->bits[i], &(xnor_str_len[i]));
        strcpy_s(&(ret[pos]), buf_sz - pos, xnor_str);
        pos += xnor_str_len[i];
    }

    // and all those xnors together

    int* and_str_len = new int[c->sz];
    for (int i = 0; i < c->sz; i++)
        and_str_len[i] = 0;

    int id = c->bits[0]->id;

    bit_3sat* d = new bit_3sat();
    d->id = id;

    for (int i = 1; i < c->sz; i++) {
        bit_3sat* temp = NULL;
        char* and_str = and_3sat(num_parm, &temp, d, c->bits[i], &(and_str_len[i]));
        strcpy_s(&(ret[pos]), buf_sz - pos, and_str);
        pos += and_str_len[i];
        bit_3sat* dump = d;
        d = temp;
        delete dump;
    }

    // verify that d xnors with eq (set to either true or false)

    int final_xnor_str_len = 0;

    bit_3sat* eq_bit = new bit_3sat();
    eq_bit->id = eq ? TRUE_3SAT : FALSE_3SAT;

    bit_3sat* f = NULL;
    char* final_xnor_str = xnor_3sat(num_parm, &f, d, eq_bit, &final_xnor_str_len);
    strcpy_s(&(ret[pos]), buf_sz - pos, final_xnor_str);
    pos += final_xnor_str_len;

    *len_para = pos;

    delete final_xnor_str;
    delete [] xnor_str_len;
    delete [] and_str_len;

    return ret;

}

// force not equals

char* dec_not_equals(int* num_parm, dec_3sat* a, dec_3sat* b, __int64 *len_para) {

    return dec_equals(num_parm, a, b, false, len_para);

}

char* nat_not_equals(int* num_parm, nat_3sat* a, nat_3sat* b, __int64* len_para) {

    return nat_equals(num_parm, a, b, false, len_para);

}

// dec_mul c = a * b

char* dec_mul(int* num_parm, dec_3sat** c, dec_3sat* a, dec_3sat* b, int bd_sz, int ad_sz, __int64 *len_para) {

    // create the buffers to collect the initial 3CNF

    char*** and_strs = new char** [b->sz];
    for (int i = 0; i < b->sz; i++)
        and_strs[i] = new char* [a->sz];

    int** and_str_itmd_ab = new int* [b->sz];
    for (int i = 0; i < b->sz; i++) {
        and_str_itmd_ab[i] = new int[a->sz];
        for (int j = 0; j < a->sz; j++)
            and_str_itmd_ab[i][j] = 0;
    }

    // create the first intermediate number

    dec_3sat* itmd_c = new dec_3sat();
    itmd_c->bits = new bit_3sat * [bd_sz + ad_sz];
    itmd_c->sz = bd_sz + ad_sz;
    itmd_c->bd_sz = bd_sz;
    itmd_c->ad_sz = ad_sz;

    for (int j = 0; j < a->sz; j++) {
        char * and_str = and_3sat(num_parm, &itmd_c->bits[itmd_c->sz - j - 1], a->bits[a->sz - j - 1], b->bits[b->sz - 1], &(and_str_itmd_ab[0][j]));
        and_strs[0][j] = new char[and_str_itmd_ab[0][j] + 1];
        strcpy_s(and_strs[0][j], and_str_itmd_ab[0][j] + 1, and_str);
        delete[] and_str;
    }

    for (int j = 0; j < itmd_c->sz - a->sz; j++) {
        itmd_c->bits[j] = new bit_3sat();
        itmd_c->bits[j]->id = FALSE_3SAT;
    }

    // create the sum strings and their lengths

    char** sum_strs = new char* [b->sz];

    int* sum_str_len = new int[b->sz];
    for (int i = 0; i < b->sz; i++)
        sum_str_len[i] = 0;

    sum_strs[0] = new char[2];
    strcpy_s(sum_strs[0], 2, "");
    sum_str_len[0] = (int)strnlen_s(sum_strs[0], 2);

    for (int i = 1; i < b->sz; i++) {
        dec_3sat* itmd_b = itmd_c;
        dec_3sat* itmd_a = new dec_3sat();
        itmd_a->bits = new bit_3sat * [ad_sz + bd_sz];
        itmd_a->sz = ad_sz + bd_sz;
        itmd_a->bd_sz = bd_sz;
        itmd_a->ad_sz = ad_sz;
        for (int j = 0; j < i; j++) {
            itmd_a->bits[itmd_a->sz - j - 1] = new bit_3sat();
            itmd_a->bits[itmd_a->sz - j - 1]->id = FALSE_3SAT;
        }
        int limit = a->sz + i; // < bd_sz + ad_sz ? a->sz + i : bd_sz + ad_sz;
        for (int j = i; j < limit; j++) {
            char* and_str = and_3sat(num_parm, &itmd_a->bits[itmd_a->sz - j - 1], a->bits[a->sz - 1 - (j - i)],
                b->bits[b->sz - i - 1], &(and_str_itmd_ab[i][j-i]));
            and_strs[i][j - i] = new char[and_str_itmd_ab[i][j - i] + 1];
            strcpy_s(and_strs [i][j-i], and_str_itmd_ab[i][j - i] + 1, and_str);
            delete[] and_str;
        }
        for (int j = 0; j < itmd_a->sz - limit; j++) {
            itmd_a->bits[j] = new bit_3sat();
            itmd_a->bits[j]->id = FALSE_3SAT;
        }
        char* sum_str = dec_add(num_parm, &itmd_c, itmd_a, itmd_b, true, &(sum_str_len[i]));
        sum_strs[i] = new char[sum_str_len[i] + 1];
        strcpy_s(sum_strs [i], sum_str_len[i] + 1, sum_str);
        for (int i = 0; i < itmd_a->sz; i++)
            delete itmd_a->bits[i];
        delete itmd_a;
        delete sum_str;
    }

    // copy itmd_c to c truncated according to bd_sz and ad_sz

    *c = create_dec(num_parm, bd_sz, ad_sz);

    // if c->bd_sz > itmd_c->bd_sz, sign-extend itmd_c to size of c before decimal

    int c_start = 0;
    int itmd_c_start = 0;

    if ((*c)->bd_sz > itmd_c->bd_sz) {
        for (int i = 0; i < (*c)->bd_sz - itmd_c->bd_sz; i++) {
            (*c)->bits[i] = new bit_3sat();
            (*c)->bits[i]->id = itmd_c->bits[0]->id;
        }
        c_start = (*c)->bd_sz - itmd_c->bd_sz;
    }
    else
        itmd_c_start = itmd_c->bd_sz - (*c)->bd_sz;

    // calculate number of bits to copy over

    int copy_over = (*c)->sz > itmd_c->sz ? itmd_c->sz : (*c)->sz;

    // copy over that many bits

    for (int i = 0; i < copy_over; i++) {
        (*c)->bits[c_start + i] = new bit_3sat();
        (*c)->bits[c_start + i]->id = itmd_c->bits[itmd_c_start + i]->id;
    }

    // calculate rpad

    int c_rpad = (*c)->ad_sz > itmd_c->ad_sz ? (*c)->ad_sz - itmd_c->ad_sz : 0;

    // rpad with false

    for (int i = 0; i < c_rpad; i++) {
        (*c)->bits[c_start + copy_over + i] = new bit_3sat();
        (*c)->bits[c_start + copy_over + i]->id = FALSE_3SAT;
    }
    

    // create the return buffer and populate with 3CNF

    __int64 buf_sz = 1;

    for (int i = 0; i < b->sz; i++) {
        buf_sz += sum_str_len[i];
        for (int j = 0; j < a->sz; j++)
            buf_sz += and_str_itmd_ab[i][j];
    }

    char* ret = new char[buf_sz];
    __int64 pos = 0;

    for (int i = 0; i < b->sz; i++) {
        if (sum_str_len[i] > 0) {
            strcpy_s(&(ret[pos]), buf_sz - pos, sum_strs[i]);
            pos += sum_str_len[i];
        }
        for (int j = 0; j < a->sz; j++) {
            if (and_str_itmd_ab[i][j] > 0) {
                strcpy_s(&(ret[pos]), buf_sz - pos, and_strs[i][j]);
                pos += and_str_itmd_ab[i][j];
            }
        }
    }


    // delete all work buffers

    for (int i = 0; i < b->sz; i++) {
        for (int j = 0; j < a->sz; j++)
            if (and_str_itmd_ab[i][j] > 0)
                delete and_strs[i][j];
            delete and_strs[i];
    }
    for (int i = 1; i < b->sz; i++)
        if ( sum_str_len[i] > 0)
            delete sum_strs[i];
    delete [] sum_strs;
    delete [] and_strs;
    for (int i = 0; i < b->sz; i++)
        delete and_str_itmd_ab[i];
    delete [] and_str_itmd_ab;
    delete [] sum_str_len;

    *len_para = pos;

    return ret;

}

///*
char* nat_mul(int* num_parm, nat_3sat** c, nat_3sat* a, nat_3sat* b, int sz, __int64* len_para) {

    // create the buffers to collect the initial 3CNF

    char*** and_strs = new char** [b->sz];
    for (int i = 0; i < b->sz; i++)
        and_strs[i] = new char* [a->sz];

    int** and_str_itmd_ab = new int* [b->sz];
    for (int i = 0; i < b->sz; i++) {
        and_str_itmd_ab[i] = new int[a->sz];
        for (int j = 0; j < a->sz; j++)
            and_str_itmd_ab[i][j] = 0;
    }

    // create the first intermediate number

    nat_3sat* itmd_c = new nat_3sat();
    itmd_c->bits = new bit_3sat * [sz];
    itmd_c->sz = sz;

    for (int j = 0; j < a->sz; j++) {
        char* and_str = and_3sat(num_parm, &itmd_c->bits[itmd_c->sz - j - 1], a->bits[a->sz - j - 1], b->bits[b->sz - 1], &(and_str_itmd_ab[0][j]));
        and_strs[0][j] = new char[and_str_itmd_ab[0][j] + 1];
        strcpy_s(and_strs[0][j], and_str_itmd_ab[0][j] + 1, and_str);
        delete[] and_str;
    }

    for (int j = 0; j < itmd_c->sz - a->sz; j++) {
        itmd_c->bits[j] = new bit_3sat();
        itmd_c->bits[j]->id = FALSE_3SAT;
    }

    // create the sum strings and their lengths

    char** sum_strs = new char* [b->sz];

    int* sum_str_len = new int[b->sz];
    for (int i = 0; i < b->sz; i++)
        sum_str_len[i] = 0;

    sum_strs[0] = new char[2];
    strcpy_s(sum_strs[0], 2, "");
    sum_str_len[0] = (int)strnlen_s(sum_strs[0], 2);

    for (int i = 1; i < b->sz; i++) {
        nat_3sat* itmd_b = itmd_c;
        nat_3sat* itmd_a = new nat_3sat();
        itmd_a->bits = new bit_3sat * [sz];
        itmd_a->sz = sz;
        for (int j = 0; j < i; j++) {
            itmd_a->bits[itmd_a->sz - j - 1] = new bit_3sat();
            itmd_a->bits[itmd_a->sz - j - 1]->id = FALSE_3SAT;
        }
        int limit = a->sz + i; // < bd_sz + ad_sz ? a->sz + i : bd_sz + ad_sz;
        for (int j = i; j < limit; j++) {
            char* and_str = and_3sat(num_parm, &itmd_a->bits[itmd_a->sz - j - 1], a->bits[a->sz - 1 - (j - i)],
                b->bits[b->sz - i - 1], &(and_str_itmd_ab[i][j - i]));
            and_strs[i][j - i] = new char[and_str_itmd_ab[i][j - i] + 1];
            strcpy_s(and_strs[i][j - i], and_str_itmd_ab[i][j - i] + 1, and_str);
            delete[] and_str;
        }
        for (int j = 0; j < itmd_a->sz - limit; j++) {
            itmd_a->bits[j] = new bit_3sat();
            itmd_a->bits[j]->id = FALSE_3SAT;
        }
        char* sum_str = nat_add(num_parm, &itmd_c, itmd_a, itmd_b, true, &(sum_str_len[i]));
        sum_strs[i] = new char[sum_str_len[i] + 1];
        strcpy_s(sum_strs[i], sum_str_len[i] + 1, sum_str);
        for (int i = 0; i < itmd_a->sz; i++)
            delete itmd_a->bits[i];
        delete itmd_a;
        delete sum_str;
    }

    // copy itmd_c to c truncated according to bd_sz and ad_sz

    *c = create_nat(num_parm, sz);

    // if c->bd_sz > itmd_c->bd_sz, pad with FALSE_3SAT

    int c_start = 0;
    int itmd_c_start = 0;

    if ((*c)->sz > itmd_c->sz) {
        for (int i = 0; i < (*c)->sz - itmd_c->sz; i++) {
            (*c)->bits[i] = new bit_3sat();
            (*c)->bits[i]->id = FALSE_3SAT;
        }
        c_start = (*c)->sz - itmd_c->sz;
    }
    else
        itmd_c_start = itmd_c->sz - (*c)->sz;

    // calculate number of bits to copy over

    int copy_over = (*c)->sz > itmd_c->sz ? itmd_c->sz : (*c)->sz;

    // copy over that many bits

    for (int i = 0; i < copy_over; i++) {
        (*c)->bits[c_start + i] = new bit_3sat();
        (*c)->bits[c_start + i]->id = itmd_c->bits[itmd_c_start + i]->id;
    }

    // create the return buffer and populate with 3CNF

    __int64 buf_sz = 1;

    for (int i = 0; i < b->sz; i++) {
        buf_sz += sum_str_len[i];
        for (int j = 0; j < a->sz; j++)
            buf_sz += and_str_itmd_ab[i][j];
    }

    char* ret = new char[buf_sz];
    __int64 pos = 0;

    for (int i = 0; i < b->sz; i++) {
        if (sum_str_len[i] > 0) {
            strcpy_s(&(ret[pos]), buf_sz - pos, sum_strs[i]);
            pos += sum_str_len[i];
        }
        for (int j = 0; j < a->sz; j++) {
            if (and_str_itmd_ab[i][j] > 0) {
                strcpy_s(&(ret[pos]), buf_sz - pos, and_strs[i][j]);
                pos += and_str_itmd_ab[i][j];
            }
        }
    }


    // delete all work buffers

    for (int i = 0; i < b->sz; i++) {
        for (int j = 0; j < a->sz; j++)
            if (and_str_itmd_ab[i][j] > 0)
                delete and_strs[i][j];
        delete and_strs[i];
    }
    for (int i = 1; i < b->sz; i++)
        if (sum_str_len[i] > 0)
            delete sum_strs[i];
    delete [] sum_strs;
    delete [] and_strs;
    for (int i = 0; i < b->sz; i++)
        delete and_str_itmd_ab[i];
    delete [] and_str_itmd_ab;
    delete [] sum_str_len;

    *len_para = pos;

    return ret;

}
//*/


// dec_div: b = c/a; a*b = c

char* dec_div(int* num_parm, dec_3sat* c, dec_3sat* a, dec_3sat** b, __int64* len_para) {

    // calculate sizes after decimal and before decimal

    int ad_sz = (c->ad_sz > a->ad_sz ? c->ad_sz : a->ad_sz) + 1;
    int bd_sz = c->bd_sz > a->bd_sz ? c->bd_sz - a->bd_sz : a->bd_sz - c->bd_sz;
    int sz = ad_sz + bd_sz;

    *b = create_dec(num_parm, bd_sz, ad_sz);

    __int64 dec_mul_str_len = 0;

    dec_3sat* itmd_c = create_dec(num_parm, c->bd_sz, c->ad_sz);
    char* dec_mul_str = dec_mul(num_parm, &itmd_c, a, *b, bd_sz, ad_sz, & dec_mul_str_len);

    __int64 equals_str_len = 0;

    char * equals_str = dec_equals(num_parm, c, itmd_c, true, &equals_str_len);

    char* ret = new char[dec_mul_str_len + equals_str_len];
    strcpy_s(&(ret[0]), dec_mul_str_len, dec_mul_str);
    strcpy_s(&(ret[dec_mul_str_len]), equals_str_len, equals_str);

    *len_para = dec_mul_str_len + equals_str_len;

    delete dec_mul_str;
    delete equals_str;

    return ret;
}

// dec_sqrt: a = sqrt(c); a*a = c

char* dec_sqrt(int* num_parm, dec_3sat* c, dec_3sat** a, __int64 *len_para) {
    // calculate sizes after decimal and before decimal

    int ad_sz = c->ad_sz + c->sz;
    int bd_sz = c->bd_sz / 2 + c->bd_sz % 2;
    int sz = ad_sz + bd_sz;

    *a = create_dec(num_parm, bd_sz, ad_sz);

    __int64 dec_mul_str_len = 0;

    dec_3sat* itmd_c = create_dec(num_parm, c->bd_sz, c->ad_sz);
    char* dec_mul_str = dec_mul(num_parm, &itmd_c, *a, *a, bd_sz, ad_sz, &dec_mul_str_len);

    __int64 equals_str_len = 0;

    char * equals_str = dec_equals(num_parm, c, itmd_c, true, & equals_str_len);

    char* ret = new char[dec_mul_str_len + equals_str_len];
    strcpy_s(&(ret[0]), dec_mul_str_len, dec_mul_str);
    strcpy_s(&(ret[dec_mul_str_len]), equals_str_len, equals_str);

    *len_para = dec_mul_str_len + equals_str_len;

    delete dec_mul_str;
    delete equals_str;

    return ret;
}

inline int octal_from_char(char c) {

    switch (c) {
    case '0': return 0;
    case '1': return 1;
    case '2': return 2;
    case '3': return 3;
    case '4': return 4;
    case '5': return 5;
    case '6': return 6;
    case '7': return 7;
    default: return 0;
    }
}

inline int int_from_hex_char(char c) {

    if (c >= 'A' && c <= 'F')
        c = c + ('a' - 'A');

    switch (c) {
    case '0': return 0;
    case '1': return 1;
    case '2': return 2;
    case '3': return 3;
    case '4': return 4;
    case '5': return 5;
    case '6': return 6;
    case '7': return 7;
    case '8': return 8;
    case '9': return 9;
    case 'a': return 10;
    case 'b': return 11;
    case 'c': return 12;
    case 'd': return 13;
    case 'e': return 14;
    case 'f': return 15;
    default: return 0;
    }
}

inline char hex_char_from_int(int a) {
    switch (a) {
    case 0: return '0';
    case 1: return '1';
    case 2: return '2';
    case 3: return '3';
    case 4: return '4';
    case 5: return '5';
    case 6: return '6';
    case 7: return '7';
    case 8: return '8';
    case 9: return '9';
    case 10: return 'a';
    case 11: return 'b';
    case 12: return 'c';
    case 13: return 'd';
    case 14: return 'e';
    case 15: return 'f';
    default: return '0';
    }
}

inline int decimal_from_char(char c) {

    switch (c) {
    case '0': return 0;
    case '1': return 1;
    case '2': return 2;
    case '3': return 3;
    case '4': return 4;
    case '5': return 5;
    case '6': return 6;
    case '7': return 7;
    case '8': return 8;
    case '9': return 9;
    default: return 0;
    }
}

int** input_from_char_buf(char * buf_3sat, __int64 buf_3sat_sz, int * k, bool cnf) {

    // count the newlines for k where no clause has a TRUE value in it

    __int64 pos = 0;

    while (buf_3sat[pos] != '\0') {

        char temp[128];

        __int64 t_pos = 0;

        while (buf_3sat[pos] != '\n') {
            temp[t_pos] = buf_3sat[pos];
            t_pos++;
            pos++;
        }
        temp[t_pos] = '\0';

        int a;
        int b;
        int c;

        sscanf_s(temp, "%d %d %d", &a, &b, &c);

        if ((cnf || (!cnf && a != TRUE_3SAT && b != TRUE_3SAT && c != TRUE_3SAT)) && 
            a != -b && a != -c && b != -c)
            (*k)++;

        pos++;
    }

    // copy over all the tuples

    int** ret = new int* [*k];

    pos = 0;

    __int64 iter = 0;

    while (buf_3sat[pos] != '\0') {

        char temp[128];

        __int64 t_pos = 0;

        while (buf_3sat[pos] != '\n') {
            temp[t_pos] = buf_3sat[pos];
            t_pos++;
            pos++;
        }
        temp[t_pos] = '\0';

        ret[iter] = new int[3];

        int a;
        int b;
        int c;

        sscanf_s(temp, "%d %d %d", &a, &b, &c);

        if ((cnf || (!cnf && a != TRUE_3SAT && b != TRUE_3SAT && c != TRUE_3SAT)) &&
            a != -b && a != -c && b != -c) {
            ret[iter][0] = !cnf ? a : a < 0 ? a - 1 : a + 1;
            ret[iter][1] = !cnf ? b : b < 0 ? b - 1 : b + 1;
            ret[iter][2] = !cnf ? c : c < 0 ? c - 1 : c + 1;
            iter++;
        }
        pos++;
    }

    return ret;

}

char* dec_to_str(bool * decodable_buf, dec_3sat * a, int * str_sz) {

    // rtrim trailing zeros and calculate rpad out to a multiple of 4
    int last_nonzero_offs = 0;
    while (last_nonzero_offs < a->ad_sz && a->bits[a->sz - last_nonzero_offs - 1]->id == FALSE_3SAT && 
        !decodable_buf [a->bits[a->sz - last_nonzero_offs - 1]->id - 2])
        last_nonzero_offs++;

    int rpad = last_nonzero_offs < a->ad_sz - 1 ? 4 - (a->ad_sz - last_nonzero_offs - 1) % 4 : 0;

    // find first nonzero bit and calculate lpad out to a multiple of 4
    int first_nonzero_offs = 0;
    while (first_nonzero_offs < a->bd_sz && a->bits[first_nonzero_offs]->id == FALSE_3SAT &&
        !decodable_buf[a->bits[first_nonzero_offs]->id - 2])
        first_nonzero_offs++;

    int lpad = first_nonzero_offs < a->bd_sz ? (a->bd_sz - first_nonzero_offs) % 4 : 4;

    // calculate size of the buffer

    int bool_buf_ad_sz = a->ad_sz - last_nonzero_offs + rpad ;
    int bool_buf_bd_sz = a->bd_sz - first_nonzero_offs + lpad ;
    int bool_buf_sz = bool_buf_ad_sz + bool_buf_bd_sz;

    // instantiate boolean buffer

    int* bool_buf = new int[bool_buf_sz];

    // lpad with zeros for multiple of 4
    for (int i = 0; i < lpad; i++)
        bool_buf[i] = 0;

    // copy over boolean bits

    for (int i = 0; i < a->sz - last_nonzero_offs - first_nonzero_offs; i++) {
        if (a->bits[first_nonzero_offs + i]->id == TRUE_3SAT)
            bool_buf[lpad + i] = 1;
        else if (a->bits[first_nonzero_offs + i]->id == FALSE_3SAT)
            bool_buf[lpad + i] = 0;
        else
            bool_buf[lpad + i] = decodable_buf[a->bits[first_nonzero_offs + i]->id - 2];
    }
    
    // rpad with 0s to make multiple of 4
    for (int i = 0; i < rpad; i++)
        bool_buf[lpad + a->sz - last_nonzero_offs - first_nonzero_offs + i] = 0;

    int num_hex_bd = bool_buf_bd_sz / 4;
    int num_hex_ad = bool_buf_ad_sz / 4;

    * str_sz = num_hex_bd + num_hex_ad + (num_hex_ad == 0 ? 0 : 1) + 1;
    char* ret_str = new char[*str_sz];
    
    int hexbits[4];

    // position in return string
    int ret_str_pos = 0;

    // do the before-the-decimal part

    int bd_hex_pos = 0;

    while (bd_hex_pos < num_hex_bd) {

        hexbits[0] = hexbits[1] = hexbits[2] = hexbits[3] = 0;

        for (int i = 0; i < 4; i++)
            hexbits[3 - i] = bool_buf[bd_hex_pos * 4 + i];
        ret_str[ret_str_pos] = hex_char_from_int(hexbits[3] * 8 + hexbits[2] * 4 + hexbits[1] * 2 + hexbits[0]);
        
        bd_hex_pos++;
        ret_str_pos++;
    }

    // fill in decimal point if needed

    if (num_hex_ad > 0) {
        ret_str[ret_str_pos] = '.';
        ret_str_pos++;
    }

    // do the after-the-decimal part
    int ad_hex_pos = 0;

    while (ad_hex_pos < num_hex_ad) {

        hexbits[0] = hexbits[1] = hexbits[2] = hexbits[3] = 0;

        for (int i = 0; i < 4; i++)
            hexbits[3 - i] = bool_buf[num_hex_bd * 4 + ad_hex_pos * 4 + i];
        ret_str[ret_str_pos + ad_hex_pos] = hex_char_from_int(hexbits[3] * 8 + hexbits[2] * 4 + hexbits[1] * 2 + hexbits[0]);

        ad_hex_pos++;
        ret_str_pos++;
    }

    // null-terminate return string

    ret_str[ret_str_pos] = '\0';

    return ret_str;
}

char* nat_to_str(bool* decodable_buf, nat_3sat* a, int* str_sz) {

    int amod4 = a->sz % 4;

    int bool_buf_sz = a->sz + amod4;

    int* bool_buf = new int[bool_buf_sz];

    for (int i = 0; i < bool_buf_sz; i++)
        bool_buf[i] = 0;

    for (int i = 0; i < a->sz; i++)
        if (a->bits[i]->id == TRUE_3SAT)
            bool_buf[amod4 + i] = 1;
        else if (a->bits[i]->id == FALSE_3SAT)
            bool_buf[amod4 + i] = 0;
        else
            bool_buf[amod4 + i] = decodable_buf[a->bits[a->sz - 1 - i]->id - 2];


    /*

    // find first nonzero bit and calculate lpad out to a multiple of 4
    int first_nonzero_offs = 0;
    while (first_nonzero_offs < a->sz && a->bits[first_nonzero_offs]->id == FALSE_3SAT &&
        !decodable_buf[a->bits[first_nonzero_offs]->id - 2])
        first_nonzero_offs++;

    int lpad = 4 - (first_nonzero_offs < a->sz ? (a->sz - first_nonzero_offs) % 4 : a->sz % 4);

    // calculate size of the buffer

    int bool_buf_sz = a->sz - first_nonzero_offs + lpad;

    // instantiate boolean buffer

    int* bool_buf = new int[bool_buf_sz];

    // lpad with zeros for multiple of 4
    for (int i = 0; i < lpad; i++)
        bool_buf[i] = 0;

    // copy over boolean bits

    for (int i = 0; i < a->sz - first_nonzero_offs; i++) {
        if (a->bits[first_nonzero_offs + i]->id == TRUE_3SAT)
            bool_buf[lpad + i] = 1;
        else if (a->bits[first_nonzero_offs + i]->id == FALSE_3SAT)
            bool_buf[lpad + i] = 0;
        else
            bool_buf[lpad + i] = decodable_buf[a->bits[first_nonzero_offs + i]->id - 2];
    }

    */

    int num_hex = bool_buf_sz / 4;

    *str_sz = num_hex + 1;
    char* ret_str = new char[*str_sz];

    int hexbits[4];

    // position in return string
    int ret_str_pos = 0;

    for (int i = 0; i < num_hex; i++) {

        hexbits[0] = hexbits[1] = hexbits[2] = hexbits[3] = 0;

        for (int j = 0; j < 4; j++)
            hexbits[3 - j] = bool_buf[bool_buf_sz - 1 - i * 4 - j];

        ret_str[ret_str_pos] = hex_char_from_int(hexbits[3] * 8 + hexbits[2] * 4 + hexbits[1] * 2 + hexbits[0]);
        ret_str_pos++;

    }

    /*

    // do the before-the-decimal part

    int hex_pos = 0;

    while (hex_pos < num_hex) {

        hexbits[0] = hexbits[1] = hexbits[2] = hexbits[3] = 0;

        for (int i = 0; i < 4; i++)
            hexbits[3 - i] = bool_buf[hex_pos * 4 + i];
        ret_str[ret_str_pos] = hex_char_from_int(hexbits[3] * 8 + hexbits[2] * 4 + hexbits[1] * 2 + hexbits[0]);

        hex_pos++;
        ret_str_pos++;
    }
    */

    ret_str[ret_str_pos] = '\0';

    return ret_str;
}

char* dec_get_factors(char* c_str, int c_str_buf_sz, int * len_para) {

    if (c_str == NULL or c_str == "")
        return NULL;

    int num_parm = 2; // TRUE_3SAT = 1 is reserved for true, while FALSE_3SAT = -1 is false

    // get length of c_str
    int strln = 0;
    for (strln = 0; strln < c_str_buf_sz && c_str[strln] != '\0'; strln++)
        ;

    // transform hex input into bool buffer

    int inbuffer_sz = strln * 4;
    bool* inbuffer = new bool[inbuffer_sz];

    for (int i = 0; i < strln; i++) {

        // decode the hex into bits

        int hexbits[4];
        hexbits[0] = hexbits[1] = hexbits[2] = hexbits[3] = 0;

        int hexval = int_from_hex_char ( c_str[i] );

        if (hexval >= 8) {
            hexbits[3] = 1;
            hexval = hexval - 8;
        }
        if (hexval >= 4) {
            hexbits[2] = 1;
            hexval = hexval - 4;
        }
        if (hexval >= 2) {
            hexbits[1] = 1;
            hexval = hexval - 2;
        }
        hexbits[0] = hexval;

        for (int j = 0; j < 4; j++)
            inbuffer[i * 4 + j] = hexbits[3 - j] == 1 ? true : false;
    }

    // count leading zeros

    int leading_zeros = 0;
    for (leading_zeros = 0; !inbuffer[leading_zeros]; leading_zeros++)
        ;

    int c_bit_count = inbuffer_sz - leading_zeros;

    dec_3sat* c_equals = new dec_3sat();
    c_equals->sz = c_bit_count * 2;
    c_equals->ad_sz = 0;
    c_equals->bd_sz = c_bit_count * 2;
    c_equals->bits = new bit_3sat * [c_bit_count * 2];

    c_equals->bits[0] = new bit_3sat();
    c_equals->bits[0]->id = FALSE_3SAT;

    // copy over leading multiply zeros

    for ( int i = 0 ; i < c_bit_count; i++) {
        c_equals->bits[1 + i] = new bit_3sat();
        c_equals->bits[1 + i]->id = FALSE_3SAT;
    }

    // copy over leading c zeros

    for (int i = 0; i < leading_zeros; i++) {
        c_equals->bits[1 + c_bit_count + i] = new bit_3sat();
        c_equals->bits[1 + c_bit_count + i]->id = FALSE_3SAT;
    }

    // transfer over inbuffer

    for (int i = leading_zeros; i < inbuffer_sz; i++) {
        c_equals->bits[1 + c_bit_count + i] = new bit_3sat();
        c_equals->bits[1 + c_bit_count + i]->id = inbuffer[i] ? TRUE_3SAT : FALSE_3SAT;
    }

    delete[] inbuffer;

    dec_3sat* c = NULL;

    dec_3sat* a = new dec_3sat();
    a->sz = c_bit_count;
    a->ad_sz = 0;
    a->bd_sz = c_bit_count;
    a->bits = new bit_3sat * [c_bit_count];

    dec_3sat* b = new dec_3sat();
    b->sz = c_bit_count;
    b->ad_sz = 0;
    b->bd_sz = c_bit_count;
    b->bits = new bit_3sat * [c_bit_count];

    a->bits[0] = new bit_3sat();
    a->bits[0]->id = FALSE_3SAT;

    for (int i = 1; i < c_bit_count; i++)
        a->bits[i] = create_bit(&num_parm);

    b->bits[0] = new bit_3sat();
    b->bits[0]->id = FALSE_3SAT;

    for (int i = 1; i < c_bit_count; i++)
        b->bits[i] = create_bit(&num_parm);

    __int64 mul_str_len = 0;

    char* mul_str = dec_mul(&num_parm, &c, a, b, c_bit_count * 2, 0, & mul_str_len);

    __int64 equals_str_len = 0;

    char* equals_str = dec_equals(&num_parm, c, c_equals, true, & equals_str_len);
    
    int bd_sz = a->bd_sz < b->bd_sz ? a->bd_sz : b->bd_sz;
    int ad_sz = a->ad_sz > b->ad_sz ? a->ad_sz : b->bd_sz;

    __int64 buf_3sat_sz = mul_str_len + equals_str_len + 1;
    char* buf_3sat = new char[buf_3sat_sz];
    strcpy_s(buf_3sat, buf_3sat_sz, mul_str);
    strcpy_s(&(buf_3sat[mul_str_len]), buf_3sat_sz - mul_str_len, equals_str);

    delete[] mul_str;
    delete[] equals_str;

    int k = 0;
    int** input = input_from_char_buf(buf_3sat, buf_3sat_sz, &k, false);
    bool* sln = new bool[num_parm-1];

    delete[] buf_3sat;

    int counted = 0;

    for (int i = 0; i < k; i++) {

        int a = input[i][0] < 0 ? -input[i][0] : input[i][0];
        int b = input[i][0] < 0 ? -input[i][0] : input[i][0];
        int c = input[i][0] < 0 ? -input[i][0] : input[i][0];

        if (a > counted)
            counted = a;
        if (b > counted)
            counted = b;
        if (c > counted)
            counted = c;

    }

    counted = counted - 1;

    SATSolverMaster* master = new SATSolverMaster();
    SATSolverMaster_create(master, input, k, counted , 0);

    char* prime_str = new char[8];
    sprintf_s(prime_str, 8, "prime");

    int search_sz = 1;

    for (int i = 0; i < master->chops; i++)
        search_sz *= 2;

    bool is_sat = false;

    for (int i = 0; i < search_sz; i++) {

        SATSolver* s = new SATSolver();
        SATSolver_create(s, master, input, k, counted, i);

        is_sat = SATSolver_isSat(s, i, sln);
        if (is_sat)
            break;
    }

    if (!is_sat)
        return prime_str;

    int a_str_sz = 0;

    char* a_str = dec_to_str(sln, a, &a_str_sz);
    int b_str_sz = 0;
    
    char* b_str = dec_to_str(sln, b, &b_str_sz);

    int ret_buf_sz = a_str_sz + (int) strnlen_s("\n\n", 4) + b_str_sz + 1;
    char* ret_buf = new char[ret_buf_sz];
    sprintf_s(ret_buf, ret_buf_sz, "%s\n\n%s", a_str, b_str);

    *len_para = ret_buf_sz - 1;

    delete a_str;
    delete b_str;

    return ret_buf;
}

char* nat_get_factors(char* c_str, int c_str_buf_sz, int* len_para) {

    if (c_str == NULL or c_str == "")
        return NULL;

    int num_parm = 2; // TRUE_3SAT = 1 is reserved for true, while FALSE_3SAT = -1 is false

    // get length of c_str
    int strln = 0;
    for (strln = 0; strln < c_str_buf_sz && c_str[strln] != '\0'; strln++)
        ;

    // transform hex input into bool buffer

    int inbuffer_sz = strln * 4;
    bool* inbuffer = new bool[inbuffer_sz];

    for (int i = 0; i < strln; i++) {

        // decode the hex into bits

        int hexbits[4];
        hexbits[0] = hexbits[1] = hexbits[2] = hexbits[3] = 0;

        int hexval = int_from_hex_char(c_str[i]);

        if (hexval >= 8) {
            hexbits[3] = 1;
            hexval = hexval - 8;
        }
        if (hexval >= 4) {
            hexbits[2] = 1;
            hexval = hexval - 4;
        }
        if (hexval >= 2) {
            hexbits[1] = 1;
            hexval = hexval - 2;
        }
        hexbits[0] = hexval;

        for (int j = 0; j < 4; j++)
            inbuffer[i * 4 + j] = hexbits[3 - j] == 1 ? true : false;
    }

    // count leading zeros

    int leading_zeros = 0;
    for (leading_zeros = 0; !inbuffer[leading_zeros]; leading_zeros++)
        ;

    int c_bit_count = inbuffer_sz - leading_zeros;

    nat_3sat* c_equals = new nat_3sat();
    c_equals->sz = (c_bit_count - 1) * 2;
    c_equals->bits = new bit_3sat * [(c_bit_count - 1) * 2];

    // copy over leading multiply zeros

    for (int i = 0; i < (c_bit_count - 1) * 2; i++) {
        c_equals->bits[i] = new bit_3sat();
        c_equals->bits[i]->id = FALSE_3SAT;
    }

    // transfer over inbuffer

    for (int i = 0; i < inbuffer_sz; i++)
        c_equals->bits[c_equals->sz - 1 - i]->id = inbuffer[inbuffer_sz - 1 - i] ? TRUE_3SAT : FALSE_3SAT;

    delete[] inbuffer;

    nat_3sat* c = NULL;

    nat_3sat* a = new nat_3sat();
    a->sz = c_bit_count - 1;
    a->bits = new bit_3sat * [c_bit_count - 1];

    nat_3sat* b = new nat_3sat();
    b->sz = c_bit_count - 1;
    b->bits = new bit_3sat * [c_bit_count - 1];

    for (int i = 0; i < c_bit_count - 1; i++) {
        a->bits[i] = create_bit(&num_parm);
        b->bits[i] = create_bit(&num_parm);
    }

    __int64 mul_str_len = 0;

    char* mul_str = nat_mul(&num_parm, &c, a, b, (c_bit_count - 1) * 2, &mul_str_len);

    __int64 equals_str_len = 0;

    char* equals_str = nat_equals(&num_parm, c, c_equals, true, &equals_str_len);

    __int64 buf_3sat_sz = mul_str_len + equals_str_len + 1;
    char* buf_3sat = new char[buf_3sat_sz];
    strcpy_s(buf_3sat, buf_3sat_sz, mul_str);
    strcpy_s(&(buf_3sat[mul_str_len]), buf_3sat_sz - mul_str_len, equals_str);

    delete[] mul_str;
    delete[] equals_str;

    int k = 0;
    int** input = input_from_char_buf(buf_3sat, buf_3sat_sz, &k, false);
    bool* sln = new bool[num_parm - 1];

    delete[] buf_3sat;

    int counted = 0;

    for (int i = 0; i < k; i++) {

        int a = input[i][0] < 0 ? -input[i][0] : input[i][0];
        int b = input[i][0] < 0 ? -input[i][0] : input[i][0];
        int c = input[i][0] < 0 ? -input[i][0] : input[i][0];

        if (a > counted)
            counted = a;
        if (b > counted)
            counted = b;
        if (c > counted)
            counted = c;

    }

    counted = counted - 1;

    SATSolverMaster* master = new SATSolverMaster();
    SATSolverMaster_create(master, input, k, counted, 0);

    char* prime_str = new char[8];
    sprintf_s(prime_str, 8, "prime");

    int search_sz = 1;

    for (int i = 0; i < master->chops; i++)
        search_sz *= 2;

    bool is_sat = false;

    for (int i = 0; i < search_sz; i++) {

        SATSolver* s = new SATSolver();
        SATSolver_create(s, master, input, k, counted, i);

        is_sat = SATSolver_isSat(s, i, sln);
        if (is_sat)
            break;
    }

    if (!is_sat)
        return prime_str;

    int a_str_sz = 0;

    char* a_str = nat_to_str(sln, a, &a_str_sz);
    int b_str_sz = 0;

    char* b_str = nat_to_str(sln, b, &b_str_sz);

    int ret_buf_sz = a_str_sz + (int)strnlen_s("\n\n", 4) + b_str_sz + 1;
    char* ret_buf = new char[ret_buf_sz];
    sprintf_s(ret_buf, ret_buf_sz, "%s\n\n%s", a_str, b_str);

    *len_para = ret_buf_sz - 1;

    delete [] a_str;
    delete [] b_str;

    return ret_buf;
}


#endif // !__3SATFRAMEWORK_C__
