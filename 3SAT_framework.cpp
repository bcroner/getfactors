// 3SAT_framework.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#ifndef __3SATFRAMEWORK_C__
#define __3SATFRAMEWORK_C__

#include "3SAT_framework.hpp"
#include "../../3SATAI/3SATBaseConsole.hpp"

#include <iostream>
#include <stdio.h>

// Tseytin transformations being employed here to convert operations to 3-CNF

bit* create_bit(int* num_parm) {

    bit* ret = new bit();
    
    ret->id = *num_parm;

    if ( *num_parm != FALSE_3SAT && *num_parm != TRUE_3SAT)
        (*num_parm)++;

    return ret;

}

dec* create_dec(int * num_parm, char* name_parm, int bd_sz_parm, int ad_sz_parm) {

    dec* ret = new dec();
    strcpy_s(ret->name, name_parm);
    ret->bd_sz = bd_sz_parm;
    ret->ad_sz = ad_sz_parm;
    ret->sz = bd_sz_parm + ad_sz_parm;
    ret->bits = new bit * [ret->sz];
    for (int i = 0; i < ret->sz; i++)
        ret->bits[i] = create_bit(num_parm);
    return ret;

}

// c = a and b: (~a or ~b or c) (a or ~c) (b or ~c)

char* and_3sat(int * num_parm, char* name, bit* c, bit* a, bit* b, int *len_para) {

    c = create_bit(num_parm);
    char* ret = new char[128];
    char** lst = new char* [3];
    for (int i = 0; i < 3; i++)
        lst[i] = new char[32];

    /*
    sprintf_s(lst[0], "-%d -%d %d", a->id, b->id, c->id);
    sprintf_s(lst[1], "%d -%d", a->id, c->id);
    sprintf_s(lst[2], "%d -%d", b->id, c->id);
    */

    sprintf_s(lst[0], 32, "-%d -%d %d", a->id, b->id, c->id);
    sprintf_s(lst[1], 32, "%d -%d %d", a->id, c->id, FALSE_3SAT);
    sprintf_s(lst[2], 32, "%d -%d %d", b->id, c->id, FALSE_3SAT);

    int len = 0;
    for (int i = 0; i < 3; i++) {
        sprintf_s(&(ret[len]), 128-len, "%s\n", lst[i]);
        len += (int) strnlen_s(lst[i], 32) + (int) strnlen_s("\n", 2);
        delete [] lst[i];
    }

    *len_para = len;

    delete [] lst;

    return ret;

}

// c = a nand b: (~a or ~b or ~c) (a or c) (b or c)

char* nand_3sat(int * num_parm, char* name, bit* c, bit* a, bit* b, int *len_para) {

    c = create_bit(num_parm);
    char* ret = new char[128];
    char** lst = new char* [3];
    for (int i = 0; i < 3; i++)
        lst[i] = new char[32];

    /*
    sprintf_s(lst[0], "-%d -%d -%d", a->id, b->id, c->id);
    sprintf_s(lst[1], "%d %d", a->id, c->id);
    sprintf_s(lst[2], "%d %d", b->id, c->id);
    */

    sprintf_s(lst[0], 32, "-%d -%d -%d", a->id, b->id, c->id);
    sprintf_s(lst[1], 32, "%d %d %d", a->id, c->id, FALSE_3SAT);
    sprintf_s(lst[2], 32, "%d %d %d", b->id, c->id, FALSE_3SAT);

    int len = 0;
    for (int i = 0; i < 3; i++) {
        sprintf_s(&ret[len], 128-len, "%s\n", lst[i]);
        len += (int) strnlen_s(lst[i], 32) + (int) strnlen_s("\n", 2);
        delete [] lst[i];
    }

    *len_para = len;

    delete [] lst;

    return ret;

}

// c = a or b: (a or b or ~c) (~a or c) (~b or c)

char* or_3sat(int * num_parm , char* name, bit* c, bit *a, bit* b, int *len_para) {

    c = create_bit(num_parm);
    char* ret = new char[128];
    char** lst = new char* [3];
    for (int i = 0; i < 3; i++)
        lst[i] = new char[32];

    /*
    sprintf_s(lst[0], "%d %d -%d", a->id, b->id, c->id);
    sprintf_s(lst[1], "-%d %d", a->id, c->id);
    sprintf_s(lst[2], "-%d %d", b->id, c->id);
    */

    sprintf_s(lst[0], 32, "%d %d -%d", a->id, b->id, c->id);
    sprintf_s(lst[1], 32, "-%d %d %d", a->id, c->id, FALSE_3SAT);
    sprintf_s(lst[2], 32, "-%d %d %d", b->id, c->id, FALSE_3SAT);

    int len = 0;
    for (int i = 0; i < 3; i++) {
        sprintf_s(&ret[len], 128-len, "%s\n", lst[i]);
        len += (int) strnlen_s(lst[i], 32) + (int) strnlen_s("\n", 2);
        delete [] lst[i];
    }

    *len_para = len;

    delete [] lst;

    return ret;

}

// c = a nor b: (a or b or c) (~a or ~c) (~b or ~c)

char* nor_3sat(int* num_parm, char* name, bit* c, bit* a, bit* b, int* len_para) {

    c = create_bit(num_parm);
    char* ret = new char[128];
    char** lst = new char* [3];
    for (int i = 0; i < 3; i++)
        lst[i] = new char[32];

    /*
    sprintf_s(lst[0], "%d %d %d", a->id, b->id, c->id);
    sprintf_s(lst[1], "-%d -%d", a->id, c->id);
    sprintf_s(lst[2], "-%d -%d", b->id, c->id);
    */

    sprintf_s(lst[0], 32, "%d %d %d", a->id, b->id, c->id);
    sprintf_s(lst[1], 32, "-%d -%d -%d", a->id, c->id, FALSE_3SAT);
    sprintf_s(lst[2], 32, "-%d -%d -%d", b->id, c->id, FALSE_3SAT);

    int len = 0;
    for (int i = 0; i < 3; i++) {
        sprintf_s(&(ret[len]), 128-len, "%s\n", lst[i]);
        len += (int) strnlen_s(lst[i], 32) + (int) strnlen_s("\n", 2);
        delete [] lst[i];
    }

    *len_para = len;

    delete [] lst;

    return ret;

}

// c = not a: (~a or ~c) (a or c)

char* not_3sat(int * num_parm, char* name, bit* c, bit* a, int *len_para) {

    c = create_bit(num_parm);
    char* ret = new char[64];
    char** lst = new char* [4];
    for (int i = 0; i < 2; i++)
        lst[i] = new char[32];

    /*
    sprintf_s(lst[0], "-%d -%d", a->id, c->id);
    sprintf_s(lst[1], "%d %d", a->id, c->id);
    */

    sprintf_s(lst[0], 32, "-%d -%d -%d", a->id, c->id, FALSE_3SAT);
    sprintf_s(lst[1], 32, "%d %d %d", a->id, c->id, FALSE_3SAT);

    int len = 0;
    for (int i = 0; i < 2; i++) {
        sprintf_s(&ret[len], 64-len, "%s\n", lst[i]);
        len += (int) strnlen_s(lst[i], 32) + (int) strnlen_s("\n", 2);
        delete [] lst[i];
    }

    *len_para = len;

    delete [] lst;

    return ret;

}

// c = a xor b: (~a or ~b or ~c) (a or b or ~c) (a or ~b or c) (~a or b or c)

char* xor_3sat(int * num_parm, char* name, bit* c, bit* a, bit* b, int *len_para) {

    c = create_bit(num_parm);
    char* ret = new char[128];
    char** lst = new char* [4];
    for (int i = 0; i < 4; i++)
        lst[i] = new char[32];

    sprintf_s(lst[0], 32, "-%d -%d -%d", a->id, b->id, c->id);
    sprintf_s(lst[1], 32, "%d %d -%d", a->id, b->id, c->id);
    sprintf_s(lst[2], 32, "%d -%d %d", a->id, b->id, c->id);
    sprintf_s(lst[3], 32, "-%d %d %d", a->id, b->id, c->id);

    int len = 0;
    for (int i = 0; i < 4; i++) {
        sprintf_s(&(ret[len]), 128-len, "%s\n", lst[i]);
        len += (int) strnlen_s(lst[i], 32) + (int) strnlen_s("\n", 2);
        delete [] lst[i];
    }

    *len_para = len;

    delete [] lst;

    return ret;

}

// c = a xnor b: (~a or ~b or c) (a or b or c) (a or ~b or ~c) (~a or b or ~c)

char* xnor_3sat(int * num_parm, char* name, bit* c, bit* a, bit* b, int *len_para) {

    c = create_bit(num_parm);
    char* ret = new char[128];
    char** lst = new char* [4];
    for (int i = 0; i < 4; i++)
        lst[i] = new char[32];

    sprintf_s(lst[0], 32, "-%d -%d %d", a->id, b->id, c->id);
    sprintf_s(lst[1], 32, "%d %d %d", a->id, b->id, c->id);
    sprintf_s(lst[2], 32, "%d -%d -%d", a->id, b->id, c->id);
    sprintf_s(lst[3], 32, "-%d %d -%d", a->id, b->id, c->id);

    int len = 0;
    for (int i = 0; i < 4; i++) {
        sprintf_s(&(ret[len]), 128-len, "%s\n", lst[i]);
        len += (int) strnlen_s(lst[i], 32) + (int) strnlen_s("\n", 2);
        delete [] lst[i];
    }

    *len_para = len;

    delete [] lst;

    return ret;

}

// bitadd = a + b + cin: cin xor (a xor b) = (~a or ~b or ~c) (a or b or ~c) (a or ~b or c) (~a or b or c)
// d = cin xor c: (~cin or ~c or ~d) (cin or c or ~d) (cin or ~c or d) (~cin or c or d)

char* bitaddsum_3sat(int * num_parm, char* name, bit* sum, bit* c_in, bit* a, bit* b, int *len_para) {

    sum = create_bit(num_parm);
    bit * c = create_bit(num_parm);
    bit* d = create_bit(num_parm);;
    char* ret = new char[256];
    char** lst = new char* [8];
    for (int i = 0; i < 8; i++)
        lst[i] = new char[32];

    sprintf_s(lst[0], 32, "-%d -%d -%d", a->id, b->id, c->id);
    sprintf_s(lst[1], 32, "%d %d -%d", a->id, b->id, c->id);
    sprintf_s(lst[2], 32, "%d -%d %d", a->id, b->id, c->id);
    sprintf_s(lst[3], 32, "-%d %d %d", a->id, b->id, c->id);
    sprintf_s(lst[4], 32, "-%d -%d -%d", c_in->id, c->id, d->id);
    sprintf_s(lst[5], 32, "%d %d -%d", c_in->id, c->id, d->id);
    sprintf_s(lst[6], 32, "%d -%d %d", c_in->id, c->id, d->id);
    sprintf_s(lst[7], 32, "-%d %d %d", c_in->id, c->id, d->id);

    int len = 0;
    for (int i = 0; i < 8; i++) {
        sprintf_s(&(ret[len]), 256-len, "%s\n", lst[i]);
        len += (int) strnlen_s(lst[i], 32) + (int) strnlen_s("\n", 2);
        delete [] lst[i];
    }

    *len_para = len;

    delete [] lst;

    return ret;

}

// bitcout = a + b + cin: (a and b) or (b and cin) or (a and cin):
// (a and b): (~a or ~b or c) (a or ~c) (b or ~c)
// (b and cin): (~b or ~cin or d) (b or ~d) (cin or ~c)
// (a and cin): (~a or ~cin or e) (a or ~e) (cin or ~e)
// (a and b) or (b and cin) = c or d: (c or d or ~f) (~c or f) (~d or f)
// ((a and b) or (b and cin)) or (a and cin) = f or e: (f or e or ~g) (~f or g) (~e or g)

char* bitaddcout_3sat(int * num_parm, char* name, bit* c_out, bit* c_in, bit* a, bit* b, int *len_para) {

    c_out = create_bit(num_parm);
    bit * c = create_bit(num_parm);
    bit * d = create_bit(num_parm);
    bit * e = create_bit(num_parm);
    bit * f = create_bit(num_parm);
    bit * g = create_bit(num_parm);
    
    char* ret = new char[512];
    char** lst = new char* [15];
    for (int i = 0; i < 15; i++)
        lst[i] = new char[32];

    /*
    sprintf_s(lst[0], "-%d -%d %d", a->id, b->id, c.id);
    sprintf_s(lst[1], "%d -%d", a->id, c->id);
    sprintf_s(lst[2], "%d -%d", b->id, c->id);
    sprintf_s(lst[3], "-%d -%d %d", b->id, c_in->id, d->id);
    sprintf_s(lst[4], "%d -%d", b->id, d->id);
    sprintf_s(lst[5], "%d -%d", c_in->id, c->id);
    sprintf_s(lst[6], "-%d -%d %d", a->id, c_in->id, e->id);
    sprintf_s(lst[7], "%d -%d", a->id, e->id);
    sprintf_s(lst[8], "%d -%d", c_in->id, e->id);
    sprintf_s(lst[9], "%d %d -%d", c->id, d->id, f->id);
    sprintf_s(lst[10], "-%d %d", c->id, f->id);
    sprintf_s(lst[11], "-%d %d", d->id, f->id);
    sprintf_s(lst[12], "%d %d -%d", f->id, e->id, g->id);
    sprintf_s(lst[13], "-%d %d", f->id, g->id);
    sprintf_s(lst[14], "-%d %d", e->id, g->id);
    */

    sprintf_s(lst[0], 32, "-%d -%d %d", a->id, b->id, c->id);
    sprintf_s(lst[1], 32, "%d -%d -%d", a->id, c->id, FALSE_3SAT);
    sprintf_s(lst[2], 32, "%d -%d -%d", b->id, c->id, FALSE_3SAT);
    sprintf_s(lst[3], 32, "-%d -%d %d", b->id, c_in->id, d->id);
    sprintf_s(lst[4], 32, "%d -%d -%d", b->id, d->id, FALSE_3SAT);
    sprintf_s(lst[5], 32, "%d -%d -%d", c_in->id, c->id, FALSE_3SAT);
    sprintf_s(lst[6], 32, "-%d -%d %d", a->id, c_in->id, e->id);
    sprintf_s(lst[7], 32, "%d -%d -%d", a->id, e->id, FALSE_3SAT);
    sprintf_s(lst[8], 32, "%d -%d -%d", c_in->id, e->id, FALSE_3SAT);
    sprintf_s(lst[9], 32, "%d %d -%d", c->id, d->id, f->id);
    sprintf_s(lst[10], 32, "-%d %d %d", c->id, f->id, FALSE_3SAT);
    sprintf_s(lst[11], 32, "-%d %d %d", d->id, f->id, FALSE_3SAT);
    sprintf_s(lst[12], 32, "%d %d -%d", f->id, e->id, g->id);
    sprintf_s(lst[13], 32, "-%d %d %d", f->id, g->id, FALSE_3SAT);
    sprintf_s(lst[14], 32, "-%d %d %d", e->id, g->id, FALSE_3SAT);

    int len = 0;
    for (int i = 0; i < 15; i++) {
        sprintf_s(&(ret[len]), 512-len, "%s\n", lst[i]);
        len += (int) strnlen_s(lst[i], 32) + (int) strnlen_s("\n", 2);
        delete [] lst[i];
    }

    *len_para = len;

    delete [] lst;

    return ret;

}

// implies = a->b: (~a or b)

char* implies_3sat(int * num_parm, char* name, bit* c, bit* a, bit* b, int *len_para) {

    char* ret = new char[256];
    int pos = 0;

    // invert a

    int not_len = 0;

    bit* a_inv = NULL;
    char* not_a_str = not_3sat(num_parm, name, a_inv , a , &not_len);
    strcpy_s(&(ret[pos]), 256-pos, not_a_str);
    pos += not_len;

    delete [] not_a_str;

    // or with b

    int or_len = 0;

    char* or_str = or_3sat(num_parm, name, c, a_inv, b, &or_len);
    strcpy_s(&(ret[pos]), 256-pos, or_str);
    pos += or_len;

    delete [] or_str;

    *len_para = not_len + or_len;

    return ret;

}

// dec_add c = a + b

char* dec_add(int * num_parm, char* name, dec* c, dec* a, dec* b, bool discard_final_c_out, int *len_para) {

    // find the largest number of bits

    int bd_bits = a->bd_sz > b->bd_sz ? a->bd_sz : b->bd_sz;
    int ad_bits = a->ad_sz > b->ad_sz ? a->ad_sz : a->bd_sz;
    int tt_bits = bd_bits + ad_bits;

    // create modified a and b

    dec* a_mod = new dec();
    dec* b_mod = new dec();

    a_mod->ad_sz = ad_bits;
    b_mod->ad_sz = ad_bits;
    a_mod->bd_sz = bd_bits;
    b_mod->bd_sz = bd_bits;
    a_mod->sz = tt_bits;
    b_mod->sz = tt_bits;

    a_mod->bits = new bit * [tt_bits];
    b_mod->bits = new bit * [tt_bits];

    // populate a_mod and b_mod

    int a_ad_extra = ad_bits - a->ad_sz;
    int b_ad_extra = ad_bits - b->ad_sz;
    int a_bd_extra = bd_bits - a->bd_sz;
    int b_bd_extra = bd_bits - b->bd_sz;

    // extend with 0 bits

    for (int i = 0; i < a_ad_extra; i++) {
        int neg_one = FALSE_3SAT;
        a_mod->bits[i] = create_bit(&neg_one);
    }

    for (int i = 0; i < b_ad_extra; i++) {
        int neg_one = FALSE_3SAT;
        b_mod->bits[i] = create_bit(&neg_one);
    }

    // copy for after decimal point

    for (int i = 0; i + a->ad_sz; i++) {
        int id = a->bits[i]->id;
        a_mod->bits[i + a_ad_extra] = create_bit(&id);
    }

    for (int i = 0; i + b->ad_sz; i++) {
        int id = b->bits[i]->id;
        b_mod->bits[i + b_ad_extra] = create_bit(&id);
    }

    // copy for before decimal point

    for (int i = 0; i + a->bd_sz; i++) {
        int id = a->bits[i]->id;
        a_mod->bits[i + a_ad_extra + a->ad_sz] = create_bit(&id);
    }

    for (int i = 0; i + b->bd_sz; i++) {
        int id = b->bits[i]->id;
        b_mod->bits[i + b_ad_extra + b->ad_sz] = create_bit(&id);
    }

    // sign-extend

    for (int i = 0; i + a->bd_sz < bd_bits; i++) {
        int id = a->bits[a->bd_sz - 1]->id;
        a_mod->bits[i + a_ad_extra + a->ad_sz + a->bd_sz] = create_bit(&id);
    }

    for (int i = 0; i + b->bd_sz < bd_bits; i++) {
        int id = b->bits[b->bd_sz - 1]->id;
        a_mod->bits[i + b_ad_extra + b->ad_sz + b->bd_sz] = create_bit(&id);
    }

    // instantiate c

    c = new dec();
    c->bd_sz = bd_bits + 1;
    c->ad_sz = ad_bits;
    c->sz = tt_bits + (discard_final_c_out ? 0 : 1);
    c->bits = new bit * [c->sz]();

    int neg_one = FALSE_3SAT;

    bit* c_in = create_bit(&neg_one);
    bit* c_out = NULL;

    int buf_sz = 768 * c->sz;
    char* ret = new char[buf_sz];
    int pos = 0;

    // perform the first addition with a zero for carry_in

    int bitaddsum_3sat_0_len = 0;
    char* sum_str = bitaddsum_3sat(num_parm, name, c->bits [0], c_in, a_mod->bits[0], b_mod->bits[0], &bitaddsum_3sat_0_len);
    strcpy_s(&(ret[pos]), buf_sz-pos, sum_str);
    pos += bitaddsum_3sat_0_len;

    int bitaddcout_3sat_0_len = 0;
    char* c_out_str = bitaddcout_3sat(num_parm, name, c_out, c_in, a_mod->bits[0], b_mod->bits[0], &bitaddcout_3sat_0_len);
    strcpy_s(&(ret[pos]), buf_sz-pos, c_out_str);
    pos += bitaddcout_3sat_0_len;
    delete c_in;
    c_in = c_out;

    // perform all the rest of the additions

    int *bitaddsum_3sat_tt_bits = new int [tt_bits - 1];
    int *bitaddcout_3sat_tt_bits = new int [tt_bits - 1];

    for (int i = 1; i < tt_bits; i++) {

        bitaddsum_3sat_tt_bits [ i - 1 ] = 0;
        bitaddcout_3sat_tt_bits[ i - 1 ] = 0;

    }

    for (int i = 1; i < tt_bits; i++) {
        sum_str = bitaddsum_3sat(num_parm, name, c->bits [i], c_in , a_mod->bits[i], b_mod->bits[i], &(bitaddsum_3sat_tt_bits[i - 1]));
        strcpy_s(&(ret[pos]), 256-pos, sum_str);
        pos += bitaddsum_3sat_tt_bits[i - 1];
        c_out_str = bitaddcout_3sat(num_parm, name, c_out , c_in, a_mod->bits[i], b_mod->bits[i], &(bitaddcout_3sat_tt_bits[i - 1]));
        strcpy_s(&(ret[pos]), 256-pos, c_out_str);
        pos += bitaddcout_3sat_tt_bits[i - 1];
        delete (c_in);
        c_in = c_out;
    }

    *len_para = pos;

    delete [] bitaddcout_3sat_tt_bits;
    delete [] bitaddsum_3sat_tt_bits;

    // set the msb of c as the final carry_out value

    if (! discard_final_c_out)
        c->bits[c->sz - 1] = c_in;

    // return the buffer of 3-CNF

    return ret;

}

// twos_complement = -a

char* twos_comp_3sat(int* num_parm, char* name, dec* c, dec* a, int *len_para) {

    char* ret = new char[(64 + 768) * a->sz];
    int pos = 0;

    // create not_3sat_len
    int* not_3sat_len = new int[a->sz];
    for (int i = 0; i < a->sz; i++)
        not_3sat_len[i] = 0;

    // invert a

    dec* a_inv = new dec();
    a_inv->sz = a->sz;
    a_inv->ad_sz = a->ad_sz;
    a_inv->bd_sz = a->bd_sz;
    a_inv->bits = new bit * [a_inv->sz]();
    sprintf_s(a_inv->name, "%s_inv", name);
    for (int i = 0; i < a_inv->sz; i++) {
        char * not_str = not_3sat(num_parm, a_inv->name, a_inv->bits[i], a->bits[i], &(not_3sat_len[i]));
        strcpy_s(&(ret[pos]), (64+768) * a->sz - pos, not_str);
        pos += not_3sat_len[i];
    }

    // create one, adjusting for any fractions

    dec* b = new dec();
    b->sz = a->sz;
    b->bd_sz = a->bd_sz;
    b->ad_sz = a->ad_sz;
    b->bits = new bit * [b->sz];
    int pos_one = TRUE_3SAT;
    b->bits[0] = create_bit(&pos_one);
    for (int i = 1; i < b->sz; i++) {
        int neg_one = FALSE_3SAT;
        b->bits[i] = create_bit(&neg_one);
    }

    // perform the addition discarding the final carry

    int add_str_len = 0;

    char* add_str = dec_add(num_parm, name, c, b, a_inv, true, &add_str_len);

    strcpy_s(&(ret[pos]), add_str_len, add_str);

    delete [] add_str;
    delete [] not_3sat_len;

    *len_para = pos + add_str_len;

    // return 3sat source

    return ret;
}

// dec_sub c = a + -b

char* dec_sub(int* num_parm, char* name, dec* c, dec* a, dec* b, int *len_para) {

    int buf_sz = (64 + 768) * b->sz + 768 * (a->sz > b->sz ? a->sz : b->sz);
    char* ret = new char[buf_sz];
    int pos = 0;

    dec* twos_b = NULL;
    char twos_name[15];
    sprintf_s(twos_name, "%s_twos", b->name);

    int twos_str_len = 0;
    char* twos_str = twos_comp_3sat(num_parm, twos_name, twos_b, b, &twos_str_len);
    strcpy_s(&(ret[pos]), twos_str_len, twos_str);
    pos += twos_str_len;

    int add_str_len = 0;
    char* add_str = dec_add(num_parm, name, c, a, twos_b, false, &add_str_len);
    strcpy_s(&(ret[pos]), add_str_len, add_str);
    pos += add_str_len;

    *len_para = twos_str_len + add_str_len;

    delete [] twos_str;
    delete [] add_str;

    return ret;

}

// force equals

char* equals(int * num_parm, char* name, dec* a, dec* b, bool eq, int * len_para) {

    // c = a xnor b
    // d = and all c bits together
    // d must be equal to T

    // create modified a and b for comparison purposes

    dec* a_mod;
    dec* b_mod;

    int bd_sz = a->bd_sz < b->bd_sz ? a->bd_sz : b->bd_sz;
    int a_start = bd_sz < a->bd_sz ? a->bd_sz - bd_sz : a->bd_sz;
    int b_start = bd_sz < b->bd_sz ? b->bd_sz - bd_sz : b->bd_sz;

    // sign-extend, if necessary

    int ad_sz = a->ad_sz > b->ad_sz ? a->ad_sz : b->bd_sz;
    int a_sign_ext = ad_sz - a->ad_sz;
    int b_sign_ext = ad_sz - b->ad_sz;

    // instantiate a_mod and b_mod
    char a_mod_name[15];
    sprintf_s(a_mod_name, "%s_mod", a->name);
    a_mod = create_dec(NULL, a_mod_name, bd_sz, ad_sz);

    char b_mod_name[15];
    sprintf_s(b_mod_name, "%s_mod", b->name);
    b_mod = create_dec(NULL, b_mod_name, bd_sz, ad_sz);

    // copy over data for a
    for (int i = 0; i < bd_sz + a->ad_sz; i++)
        a_mod->bits[i]->id = a->bits[a_start + i]->id;

    // sign-extend a
    for (int i = 0; i < a_sign_ext; i++)
        a_mod->bits[bd_sz + a->ad_sz + i]->id = a->bits[a->sz - 1]->id;

    // copy over data for b
    for (int i = 0; i < bd_sz + b->ad_sz; i++)
        b_mod->bits[i]->id = b->bits[b_start + i]->id;

    // sign-extend b
    for (int i = 0; i < b_sign_ext; i++)
        b_mod->bits[bd_sz + b->ad_sz + i]->id, b->bits[b->sz - 1]->id;

    // create return buffer

    int buf_sz = (bd_sz + ad_sz) * (128 + 128) + 128;
    char* ret = new char[buf_sz];
    int pos = 0;

    // xnor them all together

    int* xnor_str_len = new int[bd_sz + ad_sz];
    for (int i = 0; i < bd_sz + ad_sz; i++)
        xnor_str_len[i] = 0;

    char c_name[15];
    sprintf_s(c_name, "%s_c", name);
    dec* c = create_dec(num_parm, c_name, bd_sz, ad_sz);
    for (int i = 0; i < bd_sz + ad_sz; i++) {
        char* xnor_str = xnor_3sat(num_parm, name, c->bits[i], a_mod->bits[i], b_mod->bits[i], &(xnor_str_len[i]));
        strcpy_s(&(ret[pos]), buf_sz - pos, xnor_str);
        pos += xnor_str_len[i];
    }

    // and all those xnors together

    int* and_str_len = new int[c->sz];
    for (int i = 0; i < c->sz; i++)
        and_str_len[i] = 0;

    int id = c->bits[0]->id;

    bit* d = create_bit(&id);
    for (int i = 1; i < c->sz; i++) {
        bit* temp = NULL;
        char* and_str = and_3sat(num_parm, name, temp, d, c->bits[i], &(and_str_len[i]));
        strcpy_s(&(ret[pos]), buf_sz - pos, and_str);
        pos += and_str_len[i];
        bit* dump = d;
        d = temp;
        delete dump;
    }

    // verify that d xnors with eq (set to either true or false)

    int final_xnor_str_len = 0;

    int eq_bit_id = eq ? TRUE_3SAT : FALSE_3SAT;

    bit* eq_bit = create_bit(&eq_bit_id);

    bit* f = NULL;
    char* final_xnor_str = xnor_3sat(num_parm, name, f, d, eq_bit, &final_xnor_str_len);
    strcpy_s(&(ret[pos]), buf_sz - pos, final_xnor_str);
    pos += final_xnor_str_len;

    *len_para = pos;

    delete [] xnor_str_len;
    delete [] and_str_len;

    return ret;

}

// force not equals

char* not_equals(int* num_parm, char* name, dec* a, dec* b, int *len_para) {

    return equals(num_parm, name, a, b, false, len_para);

}

// dec_mul c = a * b

char* dec_mul(int* num_parm, char* name, dec* c, dec* a, dec* b, int bd_sz, int ad_sz, int *len_para) {

    // create the buffer to collect the 3CNF

    int buf_sz = (768 + 128) * a->sz * b->sz;
    char* ret = new char[buf_sz];
    int pos = 0;

    // create the first intermediate number

    dec* itmd_c = new dec();
    itmd_c->bits = new bit * [a->sz + b->sz]();
    itmd_c->sz = a->sz + b->sz;
    itmd_c->bd_sz = a->bd_sz + b->bd_sz;
    itmd_c->ad_sz = a->ad_sz + b->ad_sz;
    sprintf_s(itmd_c->name, "%s_itmd_c_%x", name, 0);

    int* and_str_itmd_c = new int[a->sz];
    for (int i = 0; i < a->sz; i++)
        and_str_itmd_c[i] = 0;

    char bitname[15];

    for (int j = 0; j < a->sz; j++) {
        sprintf_s(bitname, "%s_itmd_c_%x_%x", name, 0, j);
        char* and_str = and_3sat(num_parm, bitname, itmd_c->bits[j], a->bits[j], b->bits[j], &(and_str_itmd_c[j]));
        strcpy_s(&(ret[pos]), buf_sz - pos, and_str);
        pos += and_str_itmd_c[j];
    }

    int** and_str_itmd_ab = new int* [b->sz];
    for (int i = 0; i < b->sz; i++) {
        and_str_itmd_ab[i] = new int[a->sz];
        for (int j = 0; j < a->sz; a++)
            and_str_itmd_ab[i][j] = 0;
    }
    int* sum_str_len = new int[b->sz];
    for (int i = 0; i < b->sz; i++)
        sum_str_len[i] = 0;

    for (int i = 1; i < b->sz; i++) {
        dec* itmd_b = itmd_c;
        dec* itmd_a = new dec();
        itmd_a->bits = new bit * [a->sz + i]();
        itmd_a->sz = a->sz + i;
        itmd_a->bd_sz = a->bd_sz;
        itmd_a->ad_sz = a->ad_sz + i;
        sprintf_s(itmd_a->name, "%s_itmd_a_%x", name, i);
        for (int j = 0; j < i; j++) {
            itmd_a->bits[j] = new bit();
            itmd_a->bits[j]->id = FALSE_3SAT;
        }
        for (int j = i; j < a->sz + i; j++) {
            sprintf_s(bitname, "%s_itmd_%x_%x", name, i, j);
            char* and_str = and_3sat(num_parm, bitname, itmd_a->bits[j], a->bits[j], b->bits[j], &(and_str_itmd_ab[i][j-i]));
            strcpy_s(&(ret[pos]), buf_sz - pos, and_str);
            pos += and_str_itmd_ab[i][j-i];
        }
        char decname[15];
        sprintf_s(decname, "%s_itmd_s_%x", name, i);
        char* sum_str = dec_add(num_parm, decname, itmd_c, itmd_a, itmd_b, false, &(sum_str_len[i]));
        strcpy_s(&(ret[pos]), buf_sz - pos, sum_str);
        pos += sum_str_len[i];
    }

    // copy itmd_c to c truncated according to bd_sz and ad_sz

    char decname[15];
    sprintf_s(decname, 15, "%s_c", name);
    c = create_dec(num_parm, decname, bd_sz, ad_sz);

    // first take care of lowest-order starting at index 0

    int itmd_c_ad_start = 0;
    int c_ad_start = 0;

    if (c->ad_sz > itmd_c->ad_sz) {
        // fill with neg_one
        for (int c_ad_start = 0; c_ad_start < c->ad_sz - itmd_c->ad_sz; c_ad_start++) {
            int neg_one = FALSE_3SAT;
            c->bits[c_ad_start] = create_bit(&neg_one);
        }
    }
    else
        itmd_c_ad_start = itmd_c->ad_sz - c->ad_sz;

    // copy over bits after decimal

    for (int i = 0; i < c->ad_sz; i++) {
        int idx = itmd_c->bits[itmd_c_ad_start + i]->id;
        c->bits[c_ad_start + i] = create_bit(&idx);
    }

    // now work on bits before decimal

    if (c->bd_sz <= itmd_c->bd_sz) {

        // copy over bits one by one until c is full
        for (int i = 0; i < c->bd_sz - 1; i++) {
            int idx = itmd_c->bits[itmd_c_ad_start + itmd_c->ad_sz + i]->id;
            c->bits[c->ad_sz + i] = create_bit(&idx);
        }

        // sign-extend truncation
        int idx = itmd_c->bits[itmd_c->bd_sz + itmd_c->ad_sz - 1]->id;
        c->bits[c->ad_sz + c->bd_sz - 1] = create_bit(&idx);
    }
    else {

        // copy over bits one by one until itmd_c is exhausted
        for (int i = 0; i < itmd_c->bd_sz; i++) {
            int idx = itmd_c->bits[itmd_c_ad_start + itmd_c->ad_sz + i]->id;
            c->bits[c->ad_sz + i] = create_bit(&idx);
        }

        // sign-extend until c is full
        for (int i = 0; i < c->bd_sz - itmd_c->bd_sz; i++) {
            int idx = itmd_c->bits[itmd_c_ad_start + itmd_c->ad_sz + itmd_c->bd_sz - 1]->id;
            c->bits[c->ad_sz + itmd_c->bd_sz + i] = create_bit(&idx);
        }
    }

    delete [] and_str_itmd_c;
    for (int i = 0; i < b->sz; i++)
        delete [] and_str_itmd_ab[i];
    delete [] and_str_itmd_ab;
    delete [] sum_str_len;

    *len_para = pos;

    return ret;

}

// dec_div: b = c/a; a*b = c

char* dec_div(int* num_parm, char* name, dec* c, dec* a, dec* b, int *len_para) {

    // calculate sizes after decimal and before decimal

    int ad_sz = (c->ad_sz > a->ad_sz ? c->ad_sz : a->ad_sz) + 1;
    int bd_sz = c->bd_sz > a->bd_sz ? c->bd_sz - a->bd_sz : a->bd_sz - c->bd_sz;
    int sz = ad_sz + bd_sz;

    char calc_b_name[15];
    sprintf_s(calc_b_name, 15, "%s_div_b", name);

    b = create_dec(num_parm, calc_b_name, bd_sz, ad_sz);

    char calc_name[15];
    sprintf_s(calc_b_name, 15, "%s_div", name);

    int dec_mul_str_len = 0;

    dec* itmd_c = create_dec(num_parm, calc_name, c->bd_sz, c->ad_sz);
    char* dec_mul_str = dec_mul(num_parm, calc_name, itmd_c, a, b, bd_sz, ad_sz, & dec_mul_str_len);

    char calc_eq_name[15];
    sprintf_s(calc_b_name, 15, "%s_div_eq", calc_eq_name);

    int equals_str_len = 0;

    char * equals_str = equals(num_parm, calc_eq_name, c, itmd_c, true, &equals_str_len);

    char* ret = new char[dec_mul_str_len + equals_str_len];
    strcpy_s(&(ret[0]), dec_mul_str_len, dec_mul_str);
    strcpy_s(&(ret[dec_mul_str_len]), equals_str_len, equals_str);

    *len_para = dec_mul_str_len + equals_str_len;

    delete [] dec_mul_str;
    delete [] equals_str;

    return ret;
}

// dec_sqrt: a = sqrt(c); a*a = c

char* dec_sqrt(int* num_parm, char* name, dec* c, dec* a, int *len_para) {
    // calculate sizes after decimal and before decimal

    int ad_sz = c->ad_sz + c->sz;
    int bd_sz = c->bd_sz / 2 + c->bd_sz % 2;
    int sz = ad_sz + bd_sz;

    char calc_a_name[15];
    sprintf_s(calc_a_name, 15, "%s_sqrt_c", name);

    a = create_dec(num_parm, calc_a_name, bd_sz, ad_sz);

    char calc_c_name[15];
    sprintf_s(calc_a_name, 15, "%s_sqrt", name);

    int dec_mul_str_len = 0;

    dec* itmd_c = create_dec(num_parm, calc_a_name, c->bd_sz, c->ad_sz);
    char* dec_mul_str = dec_mul(num_parm, calc_c_name, itmd_c, a, a, bd_sz, ad_sz, &dec_mul_str_len);

    char calc_eq_name[15];
    sprintf_s(calc_eq_name, 15, "%s_sqrt_eq", calc_eq_name);

    int equals_str_len = 0;

    char * equals_str = equals(num_parm, calc_eq_name, c, itmd_c, true, & equals_str_len);

    char* ret = new char[dec_mul_str_len + equals_str_len];
    strcpy_s(&(ret[0]), dec_mul_str_len, dec_mul_str);
    strcpy_s(&(ret[dec_mul_str_len]), equals_str_len, equals_str);

    *len_para = dec_mul_str_len + equals_str_len;

    delete [] dec_mul_str;
    delete [] equals_str;

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

int** input_from_char_buf(int * num_parm, char * buf_3sat, int buf_3sat_sz, int * k) {

    // count the newlines for k

    for (int i = 0; i < strnlen_s(buf_3sat, buf_3sat_sz); i++)
        if (buf_3sat[i] == '\n')
            (*k)++;

    int** ret = new int* [*k];

    int pos = 0;

    for (int i = 0; i < *k; i++) {

        char temp[128];

        int t_pos = 0;

        while (buf_3sat[pos] != '\n') {
            temp[t_pos] = buf_3sat[pos];
            t_pos++;
            pos++;
        }
        char nullchar = '\0';
        temp[t_pos] = nullchar;

        ret[i] = new int[3];

        sscanf_s(temp, "%d %d %d", &(ret[i][0]), &(ret[i][1]), &(ret[i][2]));
    }

    return ret;

}

char* dec_to_str(bool * decodable_buf, dec * a, int * str_sz) {

    // rtrim trailing zeros and calculate rpad out to a multiple of 4
    int last_nonzero_offs = 0;
    while (last_nonzero_offs < a->ad_sz && a->bits[a->sz - last_nonzero_offs - 1]->id == FALSE_3SAT)
        last_nonzero_offs++;
    while (last_nonzero_offs < a->ad_sz && !decodable_buf [a->bits[a->sz - last_nonzero_offs - 1]->id - 2])
        last_nonzero_offs++;

    int rpad = last_nonzero_offs < a->ad_sz - 1 ? 4 - (a->ad_sz - last_nonzero_offs - 1) % 4 : 0;

    // find first nonzero bit and calculate lpad out to a multiple of 4
    int first_nonzero_offs = 0;
    while (first_nonzero_offs < a->bd_sz && a->bits[first_nonzero_offs]->id == FALSE_3SAT)
        first_nonzero_offs++;
    while (first_nonzero_offs < a->bd_sz && !decodable_buf[a->bits[first_nonzero_offs]->id - 2])
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

char* get_factors(char* c_str, int c_str_buf_sz, int* len_para) {

    char retme[15];
    strcpy_s(retme, 15, "\0");

    if (c_str == NULL or c_str == "")
        return NULL;

    int num_parm = 2; // TRUE_3SAT = 1 is reserved for true, while FALSE_3SAT = -1 is false

    // get length of c_str
    int strln = 0;
    for (strln = 0; strln < c_str_buf_sz && c_str[strln] != '\0'; strln++)
        ;

    printf("c_str: %s c_str_buf_sz: %d strln: %d\n", c_str, c_str_buf_sz, strln);

    int c_bit_count = strln * 4;

    dec* c_equals = new dec();
    c_equals->sz = c_bit_count + 1;
    c_equals->ad_sz = 0;
    c_equals->bd_sz = c_bit_count + 1;
    c_equals->bits = new bit * [c_bit_count + 1];

    int tf = FALSE_3SAT;
    c_equals->bits[0] = create_bit(&tf);

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

        for (int j = 0; j < 4; j++) {
            tf = hexbits[3 - j] == 1 ? TRUE_3SAT : FALSE_3SAT;
            c_equals->bits[1 + i*4 + j] = create_bit(&tf);
        }
    }

    int ab_bit_count = c_bit_count - 1;

    dec* c = NULL;

    dec* a = new dec();
    a->sz = ab_bit_count + 1;
    a->ad_sz = 0;
    a->bd_sz = ab_bit_count + 1;
    a->bits = new bit * [ab_bit_count+1];

    dec* b = new dec();
    b->sz = ab_bit_count + 1;
    b->ad_sz = 0;
    b->bd_sz = ab_bit_count + 1;
    b->bits = new bit * [ab_bit_count+1];

    tf = FALSE_3SAT;
    a->bits[0] = create_bit(&tf);

    for (int i = 0; i < ab_bit_count; i++)
        a->bits[i+1] = create_bit(&num_parm);

    tf = FALSE_3SAT;
    b->bits[0] = create_bit(&tf);

    for (int i = 0; i < ab_bit_count; i++)
        b->bits[i+1] = create_bit(&num_parm);

    char mp_str[15];
    sprintf_s(mp_str, 15, "mp");

    char mp_eq_str[15];
    sprintf_s(mp_eq_str, 15, "mpeq");

    int mul_str_len = 0;

    char* mul_str = dec_mul(&num_parm, mp_str, c, a, b, c_bit_count + 1, 0, & mul_str_len);

    int equals_str_len = 0;

    char* equals_str = equals(&num_parm, mp_eq_str, c, c_equals, true, & equals_str_len);
    
    int bd_sz = a->bd_sz < b->bd_sz ? a->bd_sz : b->bd_sz;
    int ad_sz = a->ad_sz > b->ad_sz ? a->ad_sz : b->bd_sz;

    int buf_3sat_sz = mul_str_len + equals_str_len;
    char* buf_3sat = new char[buf_3sat_sz];
    strcpy_s(buf_3sat, buf_3sat_sz, mul_str);
    strcpy_s(&(buf_3sat[mul_str_len]), equals_str_len, equals_str);

    int k = 0;
    int** input = input_from_char_buf(&num_parm, buf_3sat, buf_3sat_sz, &k);
    bool* sln = new bool[num_parm-1];

    SATSolverMaster* master = new SATSolverMaster();
    SATSolverMaster_create(master, input, k, num_parm);

    SATSolver* s = new SATSolver();
    SATSolver_create(s, master, input, k, num_parm, 0, 0);

    char* prime_str = new char[8];
    sprintf_s(prime_str, 8, "prime");
    
    if (!SATSolver_isSat(s, sln))
        return prime_str;

    int a_str_sz = 0;

    char* a_str = dec_to_str(sln, a, &a_str_sz);
    int b_str_sz = 0;
    
    char* b_str = dec_to_str(sln, b, &b_str_sz);

    int ret_buf_sz = a_str_sz + (int) strnlen_s("\n\n", 4) + b_str_sz;
    char* ret_buf = new char[ret_buf_sz];
    sprintf_s(ret_buf, ret_buf_sz, "%s\n\n%s", a_str, b_str);

    delete mul_str;
    delete equals_str;
    delete a_str;
    delete b_str;

    return ret_buf;
}

#endif // !__3SATFRAMEWORK_C__

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
