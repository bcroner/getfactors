#ifndef __BTC3SAT_H__
#define __BTC3SAT_H__
#include "3SAT_framework.hpp"
#include "btc3sat.hpp"
#include "3SATBaseConsole.hpp"

#include <iostream>
#include <stdio.h>

// Tseytin transformations being employed here to convert operations to 3-CNF

// c = a and b: (~a or ~b or c) (a or ~c) (b or ~c)

void and_b3(int* num_parm, int** lst, bit_3sat** c, bit_3sat* a, bit_3sat* b) {

    // 3

    *c = create_bit(num_parm);

    lst[0][0] = -a->id;
    lst[0][1] = -b->id;
    lst[0][2] = (*c)->id;

    lst[1][0] = a->id;
    lst[1][1] = -(*c)->id;
    lst[1][2] = FALSE_3SAT;

    lst[2][0] = b->id;
    lst[2][1] = -(*c)->id;
    lst[2][2] = FALSE_3SAT;
}

// c = a nand b: (~a or ~b or ~c) (a or c) (b or c)

void nand_b3(int* num_parm, int** lst, bit_3sat** c, bit_3sat* a, bit_3sat* b) {

    // 3

    *c = create_bit(num_parm);

    lst[0][0] = -a->id;
    lst[0][1] = -b->id;
    lst[0][2] =  - (*c)->id;

    lst[1][0] = a->id;
    lst[1][1] = (*c)->id;
    lst[1][2] = FALSE_3SAT;

    lst[2][0] = b->id;
    lst[2][1] = (*c)->id;
    lst[2][2] = FALSE_3SAT;
}

// c = a or b: (a or b or ~c) (~a or c) (~b or c)

void or_b3(int* num_parm, int** lst, bit_3sat** c, bit_3sat* a, bit_3sat* b) {

    // 3

    *c = create_bit(num_parm);

    lst[0][0] = a->id;
    lst[0][1] = b->id;
    lst[0][2] = - (*c)->id;

    lst[1][0] = -a->id;
    lst[1][1] = (*c)->id;
    lst[1][2] = FALSE_3SAT;

    lst[2][0] = -b->id;
    lst[2][1] = (*c)->id;
    lst[2][1] = FALSE_3SAT;
}

// c = a nor b: (a or b or c) (~a or ~c) (~b or ~c)

void nor_b3(int* num_parm, int** lst, bit_3sat** c, bit_3sat* a, bit_3sat* b) {

    // 3

    *c = create_bit(num_parm);

    lst[0][0] = a->id;
    lst[0][1] = b->id;
    lst[0][2] = (*c)->id;

    lst[1][0] = -a->id;
    lst[1][1] = -(*c)->id;
    lst[1][0] = FALSE_3SAT;

    lst[2][0] = -b->id;
    lst[2][1] = -(*c)->id;
    lst[2][2] = FALSE_3SAT;
}

// c = not a: (~a or ~c) (a or c)

void not_b3(int* num_parm, int** lst, bit_3sat** c, bit_3sat* a) {

    // 2

    *c = create_bit(num_parm);

    lst[0][0] = -a->id;
    lst[0][1] = -(*c)->id;
    lst[0][2] = FALSE_3SAT;

    lst[1][0] = a->id;
    lst[1][1] = (*c)->id;
    lst[1][2] = FALSE_3SAT;
}

// c = a xor b: (~a or ~b or ~c) (a or b or ~c) (a or ~b or c) (~a or b or c)

void xor_b3(int* num_parm, int** lst, bit_3sat** c, bit_3sat* a, bit_3sat* b) {

    // 4

    *c = create_bit(num_parm);

    lst[0][0] = -a->id;
    lst[0][1] = -b->id;
    lst[0][2] = -(*c)->id;

    lst[1][0] = a->id;
    lst[1][1] = b->id;
    lst[1][2] = - (*c)->id;

    lst[2][0] = a->id;
    lst[2][1] = -b->id;
    lst[2][2] = (*c)->id;

    lst[3][0] = -a->id;
    lst[3][1] = b->id;
    lst[3][2] = (*c)->id;
}

// c = a xnor b: (~a or ~b or c) (a or b or c) (a or ~b or ~c) (~a or b or ~c)

void xnor_b3(int* num_parm, int** lst, bit_3sat** c, bit_3sat* a, bit_3sat* b) {

    *c = create_bit(num_parm);

    lst[0][0] = -a->id;
    lst[0][1] = -b->id;
    lst[0][2] = (*c)->id;

    lst[1][0] = a->id;
    lst[1][1] = b->id;
    lst[1][2] = (*c)->id;

    lst[2][0] = a->id;
    lst[2][1] = -b->id;
    lst[2][2] = - (*c)->id;

    lst[3][0] = -a->id;
    lst[3][1] = b->id;
    lst[3][2] = - (*c)->id;
}

// bitadd = a + b + cin: cin xor (a xor b) = (~a or ~b or ~c) (a or b or ~c) (a or ~b or c) (~a or b or c)

void bitaddsum_b3(int* num_parm, int** lst, bit_3sat** sum, bit_3sat* c_in, bit_3sat* a, bit_3sat* b) {

    // 8

    bit_3sat* c;

    int** x1 = new int* [4];
    for (int i = 0; i < 4; i++)
        x1[i] = new int[3];

    int x1_len = 0;
    xor_b3(num_parm, x1, &c, a, b, &x1_len);

    int** x2 = new int* [4];
    for (int i = 0; i < 4; i++)
        x2[i] = new int[3];

    int x2_len = 0;
    xor_b3(num_parm, x2, sum, c_in, c, &x2_len);

    for (int i = 0; i < x1_len; i++)
        for (int j = 0; j < 3; j++)
            lst [i][j] = x1[i][j];

    for (int i = 0; i < x2_len; i++)
        for (int j = 0; j < 3; j++)
            lst [x1_len + i][j] = x1[i][j];

    delete c;

    for (int i = 0; i < 3; i++) {
        delete[] x1[i];
        delete[] x2[i];
    }

    delete[] x1;
    delete[] x2;
}

// bitcout = a + b + cin: (a and b) or (b and cin) or (a and cin):

void bitaddcout_b3(int* num_parm, int** lst, bit_3sat** c_out, bit_3sat* c_in, bit_3sat* a, bit_3sat* b) {

    // 15

    bit_3sat* a1;
    bit_3sat* a2;
    bit_3sat* a3;
    bit_3sat* o1;

    int** l1 = new int* [3];
    for (int i = 0; i < 3; i++)
        l1[i] = new int[3];

    and_b3(num_parm, l1, &a1, a, b);

    int** l2 = new int* [3];
    for (int i = 0; i < 3; i++)
        l2[i] = new int[3];

    and_b3(num_parm, l2, &a2, b, c_in);

    int** l3 = new int* [3];
    for (int i = 0; i < 3; i++)
        l3[i] = new int[3];

    and_b3(num_parm, l3, &a3, a, c_in);

    int** p1 = new int* [3];
    for (int i = 0; i < 3; i++)
        p1[i] = new int[3];

    or_b3(num_parm, p1, &o1, a1, a2);

    int** p2 = new int* [3];
    for (int i = 0; i < 3; i++)
        p2[i] = new int[3];

    or_b3(num_parm, p2, c_out, a3, o1);

    int ret_len = 15;

    for (int i = 0; i < 3; i++) {
        lst[i][0] = l1[i][0];
        lst[i][1] = l1[i][1];
        lst[i][2] = l1[i][2];
    }

    for (int i = 0; i < 3; i++) {
        lst[3 * 1 + i][0] = l2[i][0];
        lst[3 * 1 + i][1] = l2[i][1];
        lst[3 * 1 + i][2] = l2[i][2];
    }


    for (int i = 0; i < 3; i++) {
        lst[3 * 2 + i][0] = l3[i][0];
        lst[3 * 2 + i][1] = l3[i][1];
        lst[3 * 2 + i][2] = l3[i][2];
    }


    for (int i = 0; i < 3; i++) {
        lst[3 * 3 + i][0] = p1[i][0];
        lst[3 * 3 + i][1] = p1[i][1];
        lst[3 * 3 + i][2] = p1[i][2];
    }

    for (int i = 0; i < 3; i++) {
        lst[3 * 4 + i][0] = p2[i][0];
        lst[3 * 4 + i][1] = p2[i][1];
        lst[3 * 4 + i][2] = p2[i][2];
    }

    for (int i = 0; i < 3; i++) {
        delete[] l1[i];
        delete[] l2[i];
        delete[] l3[i];
        delete[] p1[i];
        delete[] p2[i];
    }

    delete l1;
    delete l2;
    delete l3;
    delete p1;
    delete p2;
}

// implies = a->b: (~a or b)

void implies_b3(int* num_parm, int ** lst, bit_3sat** c, bit_3sat* a, bit_3sat* b) {

    // 5

    int pos = 0;

    // invert a

    int** not_a_lst = new int* [2];
    for (int i = 0; i < 2; i++)
        not_a_lst[i] = new int[3];

    bit_3sat* a_inv = NULL;
    not_b3(num_parm, not_a_lst, &a_inv, a);

    // or with b

    int** or_lst = new int* [3];
    for (int i = 0; i < 3; i++)
        or_lst[i] = new int[3];

    or_b3(num_parm, or_lst, c, a_inv, b);

    int ret_len = 5;

    for (int i = 0; i < 2; i++) {
        lst[i][0] = not_a_lst[i][0];
        lst[i][1] = not_a_lst[i][1];
        lst[i][2] = not_a_lst[i][2];
    }

    for (int i = 0; i < 3; i++) {
        lst[2 + i][0] = not_a_lst[i][0];
        lst[2 + i][1] = not_a_lst[i][1];
        lst[2 + i][2] = not_a_lst[i][2];
    }

    for ( int i = 0 ; i < 2; i++)
        delete[] not_a_lst[i];

    delete not_a_lst[i];

    for ( int i = 0 ; i < 3; i++)
        delete[] or_lst[i];

    delete or_lst;
}

// force equals

int** equals_b3(int* num_parm, int *** lst , dec_3sat* a, dec_3sat* b, bool eq, __int64* len_para) {

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

    // xnor them all together

    int** xnor_lst = new int*[bd_sz + ad_sz];
    for (int i = 0; i < bd_sz + ad_sz; i++)
        xnor_lst[i] = new int [3];

    dec_3sat* c = create_dec(num_parm, bd_sz, ad_sz);
    for (int i = 0; i < bd_sz + ad_sz; i++)
        xnor_b3(num_parm, &(xnor_lst[i]), & c->bits[i], a_mod->bits[i], b_mod->bits[i]);

    // and all those xnors together

    int** and_lst = new int*[c->sz];
    for (int i = 0; i < c->sz; i++)
        and_lst[i] = new int[3];

    int id = c->bits[0]->id;

    bit_3sat* d = new bit_3sat();
    d->id = id;

    for (int i = 1; i < c->sz; i++) {
        bit_3sat* temp = NULL;
        and_b3(num_parm, &and_lst[i], &temp, d, c->bits[i]);
        bit_3sat* dump = d;
        d = temp;
        delete dump;
    }

    // verify that d xnors with eq (set to either true or false)

    int** xnor_lst = new int*[4];
    for (int i = 0; i < 4; i++)
        xnor_lst[i] = new int[3];

    bit_3sat* eq_bit = new bit_3sat();
    eq_bit->id = eq ? TRUE_3SAT : FALSE_3SAT;

    bit_3sat* f = NULL;
    xnor_b3(num_parm, xnor_lst, &f, d, eq_bit);

    *len_para = bd_sz + ad_sz + c->sz + 4;
    *lst = new int* [*len_para];
    for (int i = 0; i < *len_para; i++)
        *lst[i] = new int[3];

    for (int i = 0; i < bd_sz + ad_sz; i++) {
        *lst[i][0] = xnor_lst[i][0];
        *lst[i][1] = xnor_lst[i][1];
        *lst[i][2] = xnor_lst[i][2];
    }

    for (int i = 0; i < c->sz; i++) {
        *lst[bd_sz + ad_sz + i][0] = and_lst[i][0];
        *lst[bd_sz + ad_sz + i][1] = and_lst[i][1];
        *lst[bd_sz + ad_sz + i][2] = and_lst[i][2];
    }

    for (int i = 0; i < 4; i++) {
        *lst[bd_sz + ad_sz + c->sz + i][0] = xnor_lst[i][0];
        *lst[bd_sz + ad_sz + c->sz + i][1] = xnor_lst[i][1];
        *lst[bd_sz + ad_sz + c->sz + i][2] = xnor_lst[i][2];
    }

    for (int i = 0; i < bd_sz + ad_sz; i++)
        delete[] xnor_lst[i];
    delete xnor_lst;

    for (int i = 0; i < c->sz; i++)
        delete[] and_lst[i];
    delete and_lst;

    for (int i = 0; i < 4; i++)
        delete[] xnor_lst[i];
    delete xnor_lst;
}

// force not equals

int** not_equals_b3(int* num_parm, int *** lst, dec_3sat* a, dec_3sat* b, __int64* len_para) {

    return equals_b3(num_parm, lst, a, b, false, len_para);

}

bit_3sat ** pre_processing_b3(int * num_parm, bit_3sat ** input, uint64_t input_len, int * output_len) {

    int modulus = (int) input_len % 512;

    *output_len = input_len + 1;

    if (modulus > 512 - 64)
        *output_len += 512 - (modulus - (512 - 64));
    else
        *output_len += 512 - modulus;

    bit_3sat** ret = new bit_3sat*[*output_len];

    for (int i = 0; i < input_len; i++) {
        ret[i] = new bit_3sat();
        ret[i]->id = input[i]->id;
    }

    ret[input_len + 1] = new bit_3sat();
    ret[input_len + 1]->id = TRUE_3SAT;

    int output_pos = input_len + 1;

    if (modulus > 512 - 64) {
        for (int i = 0; i < 512 - modulus; i++) {
            ret[input_len + 1 + i] = new bit_3sat();
            ret[input_len + 1 + i]->id = FALSE_3SAT;
        }

        for (int i = 0 ; i < 512-64; i++) {
            ret[input_len + 1 + 512 - modulus + i] = new bit_3sat();
            ret[input_len + 1 + 512 - modulus + i]->id = FALSE_3SAT;
        }
        output_pos += 512 - modulus + 512 - 64;
    }
    else {
        for (int i = 0; i < 512 - 64 - modulus; i++) {
            ret[input_len + 1 + i] = new bit_3sat();
            ret[input_len + 1 + i]->id = FALSE_3SAT;
        }
        output_pos += 512 - 64 - modulus;
    }

    for (int i = 63; i >= 0; i--) {
        uint64_t base_num = 1;
        for (int j = 0; j < i; j++)
            base_num *= 2;
        if (base_num >= input_len) {
            input_len -= base_num;
            ret[output_pos] = new bit_3sat();
            ret[output_pos]->id = TRUE_3SAT;
            output_pos++;
        }
        else {
            ret[output_pos] = new bit_3sat();
            ret[output_pos]->id = FALSE_3SAT;
            output_pos++;
        }

    }

    return ret;
}

bit_3sat ** Ch_b3 (int * num_parm, int ** lst, bit_3sat ** x, bit_3sat ** y, bit_3sat ** z) {

    // ((x & (y ^ z)) ^ z)

    // 32 * 4 * 2 + 32 * 3

    int** xor_yz_lst = new int* [32 * 4];
    for (int i = 0; i < 32 * 4; i++)
        xor_yz_lst[i] = new int[3];

    int** and_x_yxorz_lst = new int* [32 * 3];
    for (int i = 0; i < 32 * 3; i++)
        and_x_yxorz_lst [i] = new int[3];

    int** xor_lr_lst = new int* [32 * 4];
    for (int i = 0; i < 32 * 4; i++)
        xor_lr_lst[i] = new int[3];

    bit_3sat ** xor_yz_c = new bit_3sat * [32];
    bit_3sat ** and_x_yxorz_c = new bit_3sat * [32];
    bit_3sat ** res_c = new bit_3sat * [32];

    for (int i = 0; i < 32; i++)
        xor_b3(num_parm, xor_yz_lst, &xor_yz_c[i], y[i], z[i]);

    for (int i = 0; i < 32; i++)
        and_b3(num_parm, and_x_yxorz_lst, &and_x_yxorz_c[i], xor_yz_c[i], x[i]);

    for (int i = 0; i < 32; i++)
        xor_b3(num_parm, xor_lr_lst, &res_c[i], and_x_yxorz_c[i], z[i]);

    for (int i = 0; i < 32 * 4; i++) {
        delete[] xor_yz_lst[i];
        delete[] xor_lr_lst[i];
    }

    delete xor_yz_lst;
    delete xor_lr_lst;

    for (int i = 0; i < 32 * 3; i++)
        delete[] and_x_yxorz_lst[i];

    delete and_x_yxorz_lst;

    for (int i = 0; i < 32; i++) {
        delete[] xor_yz_c[i];
        delete[] and_x_yxorz_c[i];
    }

    delete xor_yz_c;
    delete and_x_yxorz_c;

    return res_c;
}
bit_3sat** Maj_b3 (int* num_parm, int ** lst, bit_3sat** x, bit_3sat** y, bit_3sat** z) {

    // ((x& (y | z)) | (y & z))

    // 3 * 32 * 4

    bit_3sat** yorz_c = new bit_3sat * [32];
    bit_3sat** yandz_c = new bit_3sat * [32];
    bit_3sat** xandyorz_c = new bit_3sat * [32];
    bit_3sat** ret_c = new bit_3sat * [32];

    int** yorz_lst = new int* [3*32];
    for (int i = 0; i < 3 * 32; i++)
        yorz_lst[i] = new int[3];

    int** yandz_lst = new int* [3 * 32];
    for (int i = 0; i < 3 * 32; i++)
        yandz_lst[i] = new int[3];

    int** xandyorz_lst = new int* [3 * 32];
    for (int i = 0; i < 3 * 32; i++)
        xandyorz_lst[i] = new int[3];

    int** ret_lst = new int* [3 * 32];
    for (int i = 0; i < 3 * 32; i++)
        ret_lst[i] = new int[3];

    for (int i = 0; i < 32; i++) {
        or_b3(num_parm, yorz_lst, &(yorz_c[i * 3 + 0]), y[i], z[i]);
        or_b3(num_parm, yorz_lst, &(yorz_c[i * 3 + 1]), y[i], z[i]);
        or_b3(num_parm, yorz_lst, &(yorz_c[i * 3 + 2]), y[i], z[i]);
    }

    for (int i = 0; i < 32; i++) {
        and_b3(num_parm, yandz_lst, &(yandz_c[i * 3 + 0]), y[i], z[i]);
        and_b3(num_parm, yandz_lst, &(yandz_c[i * 3 + 1]), y[i], z[i]);
        and_b3(num_parm, yandz_lst, &(yandz_c[i * 3 + 2]), y[i], z[i]);
    }

    for (int i = 0; i < 32; i++) {
        and_b3(num_parm, xandyorz_lst, &(xandyorz_c[i * 3 + 0]), x[i], yorz_c[i]);
        and_b3(num_parm, xandyorz_lst, &(xandyorz_c[i * 3 + 1]), x[i], yorz_c[i]);
        and_b3(num_parm, xandyorz_lst, &(xandyorz_c[i * 3 + 2]), x[i], yorz_c[i]);
    }

    for (int i = 0; i < 32; i++) {
        and_b3(num_parm, ret_lst, &(ret_c[i * 3 + 0]), yandz_c[i], xandyorz_c[i]);
        and_b3(num_parm, ret_lst, &(ret_c[i * 3 + 1]), yandz_c[i], xandyorz_c[i]);
        and_b3(num_parm, ret_lst, &(ret_c[i * 3 + 2]), yandz_c[i], xandyorz_c[i]);
    }

    for (int i = 0; i < 32; i++) {
        lst[i][0] = yorz_lst[i][0];
        lst[i][1] = yorz_lst[i][1];
        lst[i][2] = yorz_lst[i][2];
    }

    for (int i = 0; i < 32; i++) {
        lst[32 + i][0] = yandz_lst[i][0];
        lst[32 + i][1] = yandz_lst[i][1];
        lst[32 + i][2] = yandz_lst[i][2];
    }

    for (int i = 0; i < 32; i++) {
        lst[32 + 32 + i][0] = xandyorz_lst[i][0];
        lst[32 + 32 + i][1] = xandyorz_lst[i][1];
        lst[32 + 32 + i][2] = xandyorz_lst[i][2];
    }

    for (int i = 0; i < 32; i++) {
        lst[32 + 32 + 32 + i][0] = ret_lst[i][0];
        lst[32 + 32 + 32 + i][1] = ret_lst[i][1];
        lst[32 + 32 + 32 + i][2] = ret_lst[i][2];
    }

    for (int i = 0; i < 32; i++) {

        delete[] yorz_c [i];
        delete[] yandz_c[i];
        delete[] xandyorz_c [i];

        delete [] yorz_lst [i];
        delete [] yandz_lst [i];
        delete [] xandyorz_lst [i];

    }

    delete yorz_c;
    delete yandz_c;
    delete xandyorz_c;
    delete yorz_lst;
    delete yandz_lst;
    delete xandyorz_lst;

    return ret_c;
}
bit_3sat** ROTR_b3(int* num_parm, int **lst, bit_3sat** x, int n) {

    // ((x >> n) | (x << (32 - n)))

    // 32 * 3

    bit_3sat** x_rr_n_c = new bit_3sat * [32];
    bit_3sat** x_ll_n_c = new bit_3sat * [32];
    bit_3sat** res_c = new bit_3sat * [32];

    int** res_lst = new int* [32];
    for (int i = 0; i < 32; i++)
        res_lst[i] = new int[3];

    for (int i = 0; i < 32; i++) {
        x_rr_n_c[i] = new bit_3sat();
        x_rr_n_c[i]->id = x[(i + n) % 32]->id;
    }

    for (int i = 0; i < 32 - n; i++) {
        x_ll_n_c[i] = new bit_3sat();
        x_ll_n_c[i]->id = x[(i + (32 - n)) % 32]->id;
    }

    for (int i = 0; i < 32; i++)
        or_b3(num_parm, &(res_lst[i]), &res_c[i], x_rr_n_c[i], x_ll_n_c[i]);

    for (int i = 0; i < 32; i++) {
        delete[] x_rr_n_c[i];
        delete[] x_ll_n_c[i];
    }

    delete x_rr_n_c;
    delete x_ll_n_c;

    return res_c;
}
bit_3sat** S0_b3(int* num_parm, int ** lst, bit_3sat** x) {

    // (ROTR(x, 2) ^ ROTR(x, 13) ^ ROTR(x, 22))

    // 32 * 3 * 3 + 32 * 4 * 2

    int** rotrx2_lst = new int* [32 * 3];
    for (int i = 0; i < 32 * 3; i++)
        rotrx2_lst[i] = new int[3];

    int** rotrx13_lst = new int* [32 * 3];
    for (int i = 0; i < 32 * 3; i++)
        rotrx13_lst[i] = new int[3];

    int** rotrx22_lst = new int* [32 * 3];
    for (int i = 0; i < 32 * 3; i++)
        rotrx22_lst[i] = new int[3];

    int** xor_213_lst = new int* [32 * 4];
    for (int i = 0; i < 32 * 4; i++)
        xor_213_lst[i] = new int[3];

    int** xor_lr_lst = new int* [32 * 4];
    for (int i = 0; i < 32 * 4; i++)
        xor_lr_lst[i] = new int[3];


    bit_3sat** rotrx2_c = ROTR_b3(num_parm, rotrx2_lst, x, 2);
    bit_3sat** rotrx13_c = ROTR_b3(num_parm, rotrx13_lst, x, 13);
    bit_3sat** rotrx22_c = ROTR_b3(num_parm, rotrx22_lst, x, 22);
    bit_3sat** xor_213_c = new bit_3sat * [32];

    for (int i = 0; i < 32; i++)
        xor_b3(num_parm, &(xor_213_lst[i * 4]), &xor_213_c[i], rotrx2_c[i], rotrx13_c[i]);

    bit_3sat** res_c = new bit_3sat * [32];

    for (int i = 0; i < 32; i++)
        xor_b3(num_parm, &(xor_lr_lst[i * 4]), &res_c[i], xor_213_c[i], rotrx22_c[i]);

    for (int i = 0; i < 32 * 3; i++) {
        lst[i][0] = rotrx2_lst[i][0];
        lst[i][1] = rotrx2_lst[i][1];
        lst[i][2] = rotrx2_lst[i][2];
    }

    for (int i = 0; i < 32 * 3; i++) {
        lst[32 * 3 * 1 + i][0] = rotrx13_lst[i][0];
        lst[32 * 3 * 1 + i][1] = rotrx13_lst[i][1];
        lst[32 * 3 * 1 + i][2] = rotrx13_lst[i][2];
    }

    for (int i = 0; i < 32 * 3; i++) {
        lst[32 * 3 * 2 + i][0] = rotrx22_lst[i][0];
        lst[32 * 3 * 2 + i][1] = rotrx22_lst[i][1];
        lst[32 * 3 * 2 + i][2] = rotrx22_lst[i][2];
    }

    for (int i = 0; i < 32 * 4; i++) {
        lst[32 * 3 * 3 + i][0] = xor_213_lst[i][0];
        lst[32 * 3 * 3 + i][1] = xor_213_lst[i][1];
        lst[32 * 3 * 3 + i][2] = xor_213_lst[i][2];
    }

    for (int i = 0; i < 32 * 4; i++) {
        lst[32 * 3 * 3 + 32 * 4 + i][0] = xor_lr_lst[i][0];
        lst[32 * 3 * 3 + 32 * 4 + i][1] = xor_lr_lst[i][1];
        lst[32 * 3 * 3 + 32 * 4 + i][2] = xor_lr_lst[i][2];
    }

    for (int i = 0; i < 32 * 3; i++) {
        delete[] rotrx2_lst[i];
        delete[] rotrx13_lst[i];
        delete[] rotrx22_lst[i];
    }

    delete rotrx2_lst;
    delete rotrx13_lst;
    delete rotrx22_lst;


    for (int i = 0; i < 32 * 4; i++) {
        delete[] xor_213_lst [i];
        delete[] xor_lr_lst[i];
    }

    delete xor_213_lst;
    delete xor_lr_lst;

    for (int i = 0; i < 32; i++) {
        delete[] rotrx2_c[i];
        delete[] rotrx13_c[i];
        delete[] rotrx22_c[i];
    }

    delete rotrx2_c;
    delete rotrx13_c;
    delete rotrx22_c;

    for (int i = 0; i < 32 * 4; i++)
        delete[] xor_213_c[i];

    delete xor_213_c;

    return res_c;
}
bit_3sat** S1_b3(int* num_parm, int ** lst, bit_3sat** x) {

    // (ROTR(x, 6) ^ ROTR(x, 11) ^ ROTR(x, 25))

    // 32 * 3 * 3 + 32 * 4 * 2

    int** rotrx6_lst = new int* [32 * 3];
    for (int i = 0; i < 32 * 3; i++)
        rotrx6_lst[i] = new int[3];

    int** rotrx11_lst = new int* [32 * 3];
    for (int i = 0; i < 32 * 3; i++)
        rotrx11_lst[i] = new int[3];

    int** rotrx25_lst = new int* [32 * 3];
    for (int i = 0; i < 32 * 3; i++)
        rotrx25_lst[i] = new int[3];

    int** xor_611_lst = new int* [32 * 4];
    for (int i = 0; i < 32 * 4; i++)
        xor_611_lst[i] = new int[3];

    int** xor_lr_lst = new int* [32 * 4];
    for (int i = 0; i < 32 * 4; i++)
        xor_lr_lst[i] = new int[3];


    bit_3sat** rotrx6_c = ROTR_b3(num_parm, rotrx6_lst, x, 6);
    bit_3sat** rotrx11_c = ROTR_b3(num_parm, rotrx11_lst, x, 11);
    bit_3sat** rotrx25_c = ROTR_b3(num_parm, rotrx25_lst, x, 25);
    bit_3sat** xor_611_c = new bit_3sat * [32];

    for (int i = 0; i < 32; i++)
        xor_b3(num_parm, &(xor_611_lst[i * 4]), &xor_611_c[i], rotrx6_c[i], rotrx11_c[i]);

    bit_3sat** res_c = new bit_3sat * [32];

    for (int i = 0; i < 32; i++)
        xor_b3(num_parm, &(xor_lr_lst[i * 4]), &res_c[i], xor_611_c[i], rotrx25_c[i]);

    for (int i = 0; i < 32 * 3; i++) {
        lst[i][0] = rotrx6_lst[i][0];
        lst[i][1] = rotrx6_lst[i][1];
        lst[i][2] = rotrx6_lst[i][2];
    }

    for (int i = 0; i < 32 * 3; i++) {
        lst[32 * 3 * 1 + i][0] = rotrx11_lst[i][0];
        lst[32 * 3 * 1 + i][1] = rotrx11_lst[i][1];
        lst[32 * 3 * 1 + i][2] = rotrx11_lst[i][2];
    }

    for (int i = 0; i < 32 * 3; i++) {
        lst[32 * 3 * 2 + i][0] = rotrx25_lst[i][0];
        lst[32 * 3 * 2 + i][1] = rotrx25_lst[i][1];
        lst[32 * 3 * 2 + i][2] = rotrx25_lst[i][2];
    }

    for (int i = 0; i < 32 * 4; i++) {
        lst[32 * 3 * 3 + i][0] = xor_611_lst[i][0];
        lst[32 * 3 * 3 + i][1] = xor_611_lst[i][1];
        lst[32 * 3 * 3 + i][2] = xor_611_lst[i][2];
    }

    for (int i = 0; i < 32 * 4; i++) {
        lst[32 * 3 * 3 + 32 * 4 + i][0] = xor_lr_lst[i][0];
        lst[32 * 3 * 3 + 32 * 4 + i][1] = xor_lr_lst[i][1];
        lst[32 * 3 * 3 + 32 * 4 + i][2] = xor_lr_lst[i][2];
    }

    for (int i = 0; i < 32 * 3; i++) {
        delete[] rotrx6_lst[i];
        delete[] rotrx11_lst[i];
        delete[] rotrx25_lst[i];
    }

    delete rotrx6_lst;
    delete rotrx11_lst;
    delete rotrx25_lst;


    for (int i = 0; i < 32 * 4; i++) {
        delete[] xor_611_lst[i];
        delete[] xor_lr_lst[i];
    }

    delete xor_611_lst;
    delete xor_lr_lst;

    for (int i = 0; i < 32; i++) {
        delete[] rotrx6_c[i];
        delete[] rotrx11_c[i];
        delete[] rotrx25_c[i];
    }

    delete rotrx6_c;
    delete rotrx11_c;
    delete rotrx25_c;

    for (int i = 0; i < 32 * 4; i++)
        delete[] xor_611_c[i];

    delete xor_611_c;

    return res_c;

}
bit_3sat** s0_b3(int* num_parm, int ** lst, bit_3sat** x) {

    // (ROTR(x, 7) ^ ROTR(x, 18) ^ (x >> 3))

    // 32 * 3 * 2 + 32 * 4 * 2

    bit_3sat** x_rr_3_c = new bit_3sat * [32];

    for (int i = 0; i < 32; i++) {
        x_rr_3_c[i] = new bit_3sat();
        x_rr_3_c[i]->id = x[(i + 3) % 32]->id;
    }

    int** rotrx7_lst = new int* [32 * 3];
    for (int i = 0; i < 32 * 3; i++)
        rotrx7_lst[i] = new int[3];
    
    int** rotrx18_lst = new int* [32 * 3];
    for (int i = 0; i < 32 * 3; i++)
        rotrx18_lst[i] = new int[3];

    int** xor_x7x18_lst = new int* [4 * 32];
    for (int i = 0; i < 3 * 32; i++)
        xor_x7x18_lst[i] = new int[3];

    int** xor_lr_lst = new int* [4 * 32];
    for (int i = 0; i < 3 * 32; i++)
        xor_lr_lst[i] = new int[3];

    bit_3sat** rotrx7_c = ROTR_b3(num_parm, rotrx7_lst, x, 22);
    bit_3sat** rotrx18_c = ROTR_b3(num_parm, rotrx18_lst, x, 22);
    bit_3sat** xor_x7x18_c = new bit_3sat * [32];
    bit_3sat** res_c = new bit_3sat * [32];

    for (int i = 0; i < 32; i++)
        xor_b3(num_parm, &(xor_x7x18_lst[i * 4]), &xor_x7x18_c[i], rotrx7_c[i], rotrx18_c[i]);

    for (int i = 0; i < 32; i++)
        xor_b3(num_parm, &(xor_lr_lst[i * 4]), &res_c[i], x_rr_3_c[i], xor_x7x18_c[i]);

    for (int i = 0; i < 32 * 3; i++) {
        lst[i][0] = rotrx7_lst[i][0];
        lst[i][1] = rotrx7_lst[i][1];
        lst[i][2] = rotrx7_lst[i][2];
    }

    for (int i = 0; i < 32 * 3; i++) {
        lst[32 * 3 * 1 + i][0] = rotrx18_lst[i][0];
        lst[32 * 3 * 1 + i][1] = rotrx18_lst[i][1];
        lst[32 * 3 * 1 + i][2] = rotrx18_lst[i][2];
    }

    for (int i = 0; i < 32 * 4; i++) {
        lst[32 * 3 * 2 + i][0] = xor_x7x18_lst[i][0];
        lst[32 * 3 * 2 + i][1] = xor_x7x18_lst[i][1];
        lst[32 * 3 * 2 + i][2] = xor_x7x18_lst[i][2];
    }

    for (int i = 0; i < 32 * 4; i++) {
        lst[32 * 3 * 2 + 32 * 4 * 1 + i][0] = xor_lr_lst[i][0];
        lst[32 * 3 * 2 + 32 * 4 * 1 + i][1] = xor_lr_lst[i][1];
        lst[32 * 3 * 2 + 32 * 4 * 1 + i][2] = xor_lr_lst[i][2];
    }

    for (int i = 0; i < 32 * 3; i++) {
        delete[] rotrx7_lst[i];
        delete[] rotrx18_lst[i];
    }
    delete rotrx7_lst;
    delete rotrx18_lst;

    for (int i = 0; i < 32 * 4; i++) {
        delete[] xor_x7x18_lst[i];
        delete[] xor_lr_lst[i];
    }

    delete xor_x7x18_lst;
    delete xor_lr_lst;

    for (int i = 0; i < 32; i++) {
        delete[] rotrx7_c[i];
        delete[] rotrx18_c[i];
        delete[] xor_x7x18_c[i];
    }

    delete rotrx7_c;
    delete rotrx18_c;
    delete xor_x7x18_c;

    return res_c;
}
bit_3sat** s1_b3(int* num_parm, int ** lst, bit_3sat** x) {

    // (ROTR(x, 17) ^ ROTR(x, 19) ^ (x >> 10))

    // 32 * 3 * 2 + 32 * 4 * 2

    bit_3sat** x_rr_10_c = new bit_3sat * [32];

    for (int i = 0; i < 32; i++) {
        x_rr_10_c[i] = new bit_3sat();
        x_rr_10_c[i]->id = x[(i + 3) % 32]->id;
    }

    int** rotrx17_lst = new int* [32 * 3];
    for (int i = 0; i < 32 * 3; i++)
        rotrx17_lst[i] = new int[3];

    int** rotrx19_lst = new int* [32 * 3];
    for (int i = 0; i < 32 * 3; i++)
        rotrx19_lst[i] = new int[3];

    int** xor_x17x19_lst = new int* [4 * 32];
    for (int i = 0; i < 3 * 32; i++)
        xor_x17x19_lst[i] = new int[3];

    int** xor_lr_lst = new int* [4 * 32];
    for (int i = 0; i < 3 * 32; i++)
        xor_lr_lst[i] = new int[3];

    bit_3sat** rotrx17_c = ROTR_b3(num_parm, rotrx17_lst, x, 22);
    bit_3sat** rotrx19_c = ROTR_b3(num_parm, rotrx19_lst, x, 22);
    bit_3sat** xor_x17x19_c = new bit_3sat * [32];
    bit_3sat** res_c = new bit_3sat * [32];

    for (int i = 0; i < 32; i++)
        xor_b3(num_parm, &(xor_x17x19_lst[i * 4]), &xor_x17x19_c[i], rotrx17_c[i], rotrx19_c[i]);

    for (int i = 0; i < 32; i++)
        xor_b3(num_parm, &(xor_lr_lst[i * 4]), &res_c[i], x_rr_10_c[i], xor_x17x19_c[i]);

    for (int i = 0; i < 32 * 3; i++) {
        lst[i][0] = rotrx17_lst[i][0];
        lst[i][1] = rotrx17_lst[i][1];
        lst[i][2] = rotrx17_lst[i][2];
    }

    for (int i = 0; i < 32 * 3; i++) {
        lst[32 * 3 * 1 + i][0] = rotrx19_lst[i][0];
        lst[32 * 3 * 1 + i][1] = rotrx19_lst[i][1];
        lst[32 * 3 * 1 + i][2] = rotrx19_lst[i][2];
    }

    for (int i = 0; i < 32 * 4; i++) {
        lst[32 * 3 * 2 + i][0] = xor_x17x19_lst[i][0];
        lst[32 * 3 * 2 + i][1] = xor_x17x19_lst[i][1];
        lst[32 * 3 * 2 + i][2] = xor_x17x19_lst[i][2];
    }

    for (int i = 0; i < 32 * 4; i++) {
        lst[32 * 3 * 2 + 32 * 4 * 1 + i][0] = xor_lr_lst[i][0];
        lst[32 * 3 * 2 + 32 * 4 * 1 + i][1] = xor_lr_lst[i][1];
        lst[32 * 3 * 2 + 32 * 4 * 1 + i][2] = xor_lr_lst[i][2];
    }

    for (int i = 0; i < 32 * 3; i++) {
        delete[] rotrx17_lst[i];
        delete[] rotrx19_lst[i];
    }
    delete rotrx17_lst;
    delete rotrx19_lst;

    for (int i = 0; i < 32 * 4; i++) {
        delete[] xor_x17x19_lst[i];
        delete[] xor_lr_lst[i];
    }

    delete xor_x17x19_lst;
    delete xor_lr_lst;

    for (int i = 0; i < 32; i++) {
        delete[] rotrx17_c[i];
        delete[] rotrx19_c[i];
        delete[] xor_x17x19_c[i];
    }

    delete rotrx17_c;
    delete rotrx19_c;
    delete xor_x17x19_c;

    return res_c;
}

/* SHA256 round function */
bit_3sat ** RND_b3 (a, b, c, d, e, f, g, h, k) {
		t0 = h + S1(e) + Ch(e, f, g) + k; \
		t1 = S0(a) + Maj(a, b, c); \
		d += t0; \
		h  = t0 + t1; \
} 

/* Adjusted round function for rotating state */
bit_3sat** RNDr_b3(S, W, i) {
    RND(S[(64 - i) % 8], S[(65 - i) % 8], \
        S[(66 - i) % 8], S[(67 - i) % 8], \
        S[(68 - i) % 8], S[(69 - i) % 8], \
        S[(70 - i) % 8], S[(71 - i) % 8], \
        W[i] + sha256_k[i])
}

/*
 * SHA256 block compression function.  The 256-bit state is transformed via
 * the 512-bit input block to produce a new state.
 */
void sha256_transform_b3 (uint32_t* state, const uint32_t* block, int swap)
{
    uint32_t W[64];
    uint32_t S[8];
    uint32_t t0, t1;
    int i;

    /* 1. Prepare message schedule W. */
    if (swap) {
        for (i = 0; i < 16; i++)
            W[i] = swab32(block[i]);
    }
    else
        memcpy(W, block, 64);
    for (i = 16; i < 64; i += 2) {
        W[i] = s1(W[i - 2]) + W[i - 7] + s0(W[i - 15]) + W[i - 16];
        W[i + 1] = s1(W[i - 1]) + W[i - 6] + s0(W[i - 14]) + W[i - 15];
    }

    /* 2. Initialize working variables. */
    memcpy(S, state, 32);

    /* 3. Mix. */
    RNDr(S, W, 0);
    RNDr(S, W, 1);
    RNDr(S, W, 2);
    RNDr(S, W, 3);
    RNDr(S, W, 4);
    RNDr(S, W, 5);
    RNDr(S, W, 6);
    RNDr(S, W, 7);
    RNDr(S, W, 8);
    RNDr(S, W, 9);
    RNDr(S, W, 10);
    RNDr(S, W, 11);
    RNDr(S, W, 12);
    RNDr(S, W, 13);
    RNDr(S, W, 14);
    RNDr(S, W, 15);
    RNDr(S, W, 16);
    RNDr(S, W, 17);
    RNDr(S, W, 18);
    RNDr(S, W, 19);
    RNDr(S, W, 20);
    RNDr(S, W, 21);
    RNDr(S, W, 22);
    RNDr(S, W, 23);
    RNDr(S, W, 24);
    RNDr(S, W, 25);
    RNDr(S, W, 26);
    RNDr(S, W, 27);
    RNDr(S, W, 28);
    RNDr(S, W, 29);
    RNDr(S, W, 30);
    RNDr(S, W, 31);
    RNDr(S, W, 32);
    RNDr(S, W, 33);
    RNDr(S, W, 34);
    RNDr(S, W, 35);
    RNDr(S, W, 36);
    RNDr(S, W, 37);
    RNDr(S, W, 38);
    RNDr(S, W, 39);
    RNDr(S, W, 40);
    RNDr(S, W, 41);
    RNDr(S, W, 42);
    RNDr(S, W, 43);
    RNDr(S, W, 44);
    RNDr(S, W, 45);
    RNDr(S, W, 46);
    RNDr(S, W, 47);
    RNDr(S, W, 48);
    RNDr(S, W, 49);
    RNDr(S, W, 50);
    RNDr(S, W, 51);
    RNDr(S, W, 52);
    RNDr(S, W, 53);
    RNDr(S, W, 54);
    RNDr(S, W, 55);
    RNDr(S, W, 56);
    RNDr(S, W, 57);
    RNDr(S, W, 58);
    RNDr(S, W, 59);
    RNDr(S, W, 60);
    RNDr(S, W, 61);
    RNDr(S, W, 62);
    RNDr(S, W, 63);

    /* 4. Mix local working variables into global state */
    for (i = 0; i < 8; i++)
        state[i] += S[i];
}

static const uint32_t sha256d_hash1[16] = {
    0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x80000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000100
};

static void sha256d_80_swap_b3(uint32_t* hash, const uint32_t* data)
{
    uint32_t S[16];
    int i;

    sha256_init(S);
    sha256_transform(S, data, 0);
    sha256_transform(S, data + 16, 0);
    memcpy(S + 8, sha256d_hash1 + 8, 32);
    sha256_init(hash);
    sha256_transform(hash, S, 0);
    for (i = 0; i < 8; i++)
        hash[i] = swab32(hash[i]);
}

void sha256d_b3(unsigned char* hash, const unsigned char* data, int len)
{
    uint32_t S[16], T[16];
    int i, r;

    sha256_init(S);
    for (r = len; r > -9; r -= 64) {
        if (r < 64)
            memset(T, 0, 64);
        memcpy(T, data + len - r, r > 64 ? 64 : (r < 0 ? 0 : r));
        if (r >= 0 && r < 64)
            ((unsigned char*)T)[r] = 0x80;
        for (i = 0; i < 16; i++)
            T[i] = be32dec(T + i);
        if (r < 56)
            T[15] = 8 * len;
        sha256_transform(S, T, 0);
    }
    memcpy(S + 8, sha256d_hash1 + 8, 32);
    sha256_init(T);
    sha256_transform(T, S, 0);
    for (i = 0; i < 8; i++)
        be32enc((uint32_t*)hash + i, T[i]);
}

static inline void sha256d_preextend_b3(uint32_t* W)
{
    W[16] = s1(W[14]) + W[9] + s0(W[1]) + W[0];
    W[17] = s1(W[15]) + W[10] + s0(W[2]) + W[1];
    W[18] = s1(W[16]) + W[11] + W[2];
    W[19] = s1(W[17]) + W[12] + s0(W[4]);
    W[20] = W[13] + s0(W[5]) + W[4];
    W[21] = W[14] + s0(W[6]) + W[5];
    W[22] = W[15] + s0(W[7]) + W[6];
    W[23] = W[16] + s0(W[8]) + W[7];
    W[24] = W[17] + s0(W[9]) + W[8];
    W[25] = s0(W[10]) + W[9];
    W[26] = s0(W[11]) + W[10];
    W[27] = s0(W[12]) + W[11];
    W[28] = s0(W[13]) + W[12];
    W[29] = s0(W[14]) + W[13];
    W[30] = s0(W[15]) + W[14];
    W[31] = s0(W[16]) + W[15];
}

static inline void sha256d_prehash_b3(uint32_t* S, const uint32_t* W)
{
    uint32_t t0, t1;
    RNDr(S, W, 0);
    RNDr(S, W, 1);
    RNDr(S, W, 2);
}

void sha256d_ms_b3(uint32_t* hash, uint32_t* W,
    const uint32_t* midstate, const uint32_t* prehash);

static inline void sha256d_ms_b3(uint32_t* hash, uint32_t* W,
    const uint32_t* midstate, const uint32_t* prehash)
{
    uint32_t S[64];
    uint32_t t0, t1;
    int i;

    S[18] = W[18];
    S[19] = W[19];
    S[20] = W[20];
    S[22] = W[22];
    S[23] = W[23];
    S[24] = W[24];
    S[30] = W[30];
    S[31] = W[31];

    W[18] += s0(W[3]);
    W[19] += W[3];
    W[20] += s1(W[18]);
    W[21] = s1(W[19]);
    W[22] += s1(W[20]);
    W[23] += s1(W[21]);
    W[24] += s1(W[22]);
    W[25] = s1(W[23]) + W[18];
    W[26] = s1(W[24]) + W[19];
    W[27] = s1(W[25]) + W[20];
    W[28] = s1(W[26]) + W[21];
    W[29] = s1(W[27]) + W[22];
    W[30] += s1(W[28]) + W[23];
    W[31] += s1(W[29]) + W[24];
    for (i = 32; i < 64; i += 2) {
        W[i] = s1(W[i - 2]) + W[i - 7] + s0(W[i - 15]) + W[i - 16];
        W[i + 1] = s1(W[i - 1]) + W[i - 6] + s0(W[i - 14]) + W[i - 15];
    }

    memcpy(S, prehash, 32);

    RNDr(S, W, 3);
    RNDr(S, W, 4);
    RNDr(S, W, 5);
    RNDr(S, W, 6);
    RNDr(S, W, 7);
    RNDr(S, W, 8);
    RNDr(S, W, 9);
    RNDr(S, W, 10);
    RNDr(S, W, 11);
    RNDr(S, W, 12);
    RNDr(S, W, 13);
    RNDr(S, W, 14);
    RNDr(S, W, 15);
    RNDr(S, W, 16);
    RNDr(S, W, 17);
    RNDr(S, W, 18);
    RNDr(S, W, 19);
    RNDr(S, W, 20);
    RNDr(S, W, 21);
    RNDr(S, W, 22);
    RNDr(S, W, 23);
    RNDr(S, W, 24);
    RNDr(S, W, 25);
    RNDr(S, W, 26);
    RNDr(S, W, 27);
    RNDr(S, W, 28);
    RNDr(S, W, 29);
    RNDr(S, W, 30);
    RNDr(S, W, 31);
    RNDr(S, W, 32);
    RNDr(S, W, 33);
    RNDr(S, W, 34);
    RNDr(S, W, 35);
    RNDr(S, W, 36);
    RNDr(S, W, 37);
    RNDr(S, W, 38);
    RNDr(S, W, 39);
    RNDr(S, W, 40);
    RNDr(S, W, 41);
    RNDr(S, W, 42);
    RNDr(S, W, 43);
    RNDr(S, W, 44);
    RNDr(S, W, 45);
    RNDr(S, W, 46);
    RNDr(S, W, 47);
    RNDr(S, W, 48);
    RNDr(S, W, 49);
    RNDr(S, W, 50);
    RNDr(S, W, 51);
    RNDr(S, W, 52);
    RNDr(S, W, 53);
    RNDr(S, W, 54);
    RNDr(S, W, 55);
    RNDr(S, W, 56);
    RNDr(S, W, 57);
    RNDr(S, W, 58);
    RNDr(S, W, 59);
    RNDr(S, W, 60);
    RNDr(S, W, 61);
    RNDr(S, W, 62);
    RNDr(S, W, 63);

    for (i = 0; i < 8; i++)
        S[i] += midstate[i];

    W[18] = S[18];
    W[19] = S[19];
    W[20] = S[20];
    W[22] = S[22];
    W[23] = S[23];
    W[24] = S[24];
    W[30] = S[30];
    W[31] = S[31];

    memcpy(S + 8, sha256d_hash1 + 8, 32);
    S[16] = s1(sha256d_hash1[14]) + sha256d_hash1[9] + s0(S[1]) + S[0];
    S[17] = s1(sha256d_hash1[15]) + sha256d_hash1[10] + s0(S[2]) + S[1];
    S[18] = s1(S[16]) + sha256d_hash1[11] + s0(S[3]) + S[2];
    S[19] = s1(S[17]) + sha256d_hash1[12] + s0(S[4]) + S[3];
    S[20] = s1(S[18]) + sha256d_hash1[13] + s0(S[5]) + S[4];
    S[21] = s1(S[19]) + sha256d_hash1[14] + s0(S[6]) + S[5];
    S[22] = s1(S[20]) + sha256d_hash1[15] + s0(S[7]) + S[6];
    S[23] = s1(S[21]) + S[16] + s0(sha256d_hash1[8]) + S[7];
    S[24] = s1(S[22]) + S[17] + s0(sha256d_hash1[9]) + sha256d_hash1[8];
    S[25] = s1(S[23]) + S[18] + s0(sha256d_hash1[10]) + sha256d_hash1[9];
    S[26] = s1(S[24]) + S[19] + s0(sha256d_hash1[11]) + sha256d_hash1[10];
    S[27] = s1(S[25]) + S[20] + s0(sha256d_hash1[12]) + sha256d_hash1[11];
    S[28] = s1(S[26]) + S[21] + s0(sha256d_hash1[13]) + sha256d_hash1[12];
    S[29] = s1(S[27]) + S[22] + s0(sha256d_hash1[14]) + sha256d_hash1[13];
    S[30] = s1(S[28]) + S[23] + s0(sha256d_hash1[15]) + sha256d_hash1[14];
    S[31] = s1(S[29]) + S[24] + s0(S[16]) + sha256d_hash1[15];
    for (i = 32; i < 60; i += 2) {
        S[i] = s1(S[i - 2]) + S[i - 7] + s0(S[i - 15]) + S[i - 16];
        S[i + 1] = s1(S[i - 1]) + S[i - 6] + s0(S[i - 14]) + S[i - 15];
    }
    S[60] = s1(S[58]) + S[53] + s0(S[45]) + S[44];

    sha256_init(hash);

    RNDr(hash, S, 0);
    RNDr(hash, S, 1);
    RNDr(hash, S, 2);
    RNDr(hash, S, 3);
    RNDr(hash, S, 4);
    RNDr(hash, S, 5);
    RNDr(hash, S, 6);
    RNDr(hash, S, 7);
    RNDr(hash, S, 8);
    RNDr(hash, S, 9);
    RNDr(hash, S, 10);
    RNDr(hash, S, 11);
    RNDr(hash, S, 12);
    RNDr(hash, S, 13);
    RNDr(hash, S, 14);
    RNDr(hash, S, 15);
    RNDr(hash, S, 16);
    RNDr(hash, S, 17);
    RNDr(hash, S, 18);
    RNDr(hash, S, 19);
    RNDr(hash, S, 20);
    RNDr(hash, S, 21);
    RNDr(hash, S, 22);
    RNDr(hash, S, 23);
    RNDr(hash, S, 24);
    RNDr(hash, S, 25);
    RNDr(hash, S, 26);
    RNDr(hash, S, 27);
    RNDr(hash, S, 28);
    RNDr(hash, S, 29);
    RNDr(hash, S, 30);
    RNDr(hash, S, 31);
    RNDr(hash, S, 32);
    RNDr(hash, S, 33);
    RNDr(hash, S, 34);
    RNDr(hash, S, 35);
    RNDr(hash, S, 36);
    RNDr(hash, S, 37);
    RNDr(hash, S, 38);
    RNDr(hash, S, 39);
    RNDr(hash, S, 40);
    RNDr(hash, S, 41);
    RNDr(hash, S, 42);
    RNDr(hash, S, 43);
    RNDr(hash, S, 44);
    RNDr(hash, S, 45);
    RNDr(hash, S, 46);
    RNDr(hash, S, 47);
    RNDr(hash, S, 48);
    RNDr(hash, S, 49);
    RNDr(hash, S, 50);
    RNDr(hash, S, 51);
    RNDr(hash, S, 52);
    RNDr(hash, S, 53);
    RNDr(hash, S, 54);
    RNDr(hash, S, 55);
    RNDr(hash, S, 56);

    hash[2] += hash[6] + S1(hash[3]) + Ch(hash[3], hash[4], hash[5])
        + S[57] + sha256_k[57];
    hash[1] += hash[5] + S1(hash[2]) + Ch(hash[2], hash[3], hash[4])
        + S[58] + sha256_k[58];
    hash[0] += hash[4] + S1(hash[1]) + Ch(hash[1], hash[2], hash[3])
        + S[59] + sha256_k[59];
    hash[7] += hash[3] + S1(hash[0]) + Ch(hash[0], hash[1], hash[2])
        + S[60] + sha256_k[60]
        + sha256_h[7];
}

bit_3sat** uint32_to_bit3sat_b3(__int64 parm) {

    bit_3sat** ret = new bit_3sat * [32];
    for (int i = 0; i < 32; i++)
        ret[i] = new bit_3sat();

    for (int i = 0; i < 32; i++) {
        __int64 val = 1;
        for (int pow = 0; pow <= 31 - i; pow++)
            val *= 2;
        if (parm >= val) {
            parm -= val;
            ret[31 - i]->id = TRUE_3SAT;
        }
        else
            ret[31 - i]->id = FALSE_3SAT;
    }
    return ret;
}


bit_3sat ** sha_256_b3(int* num_parm, bit_3sat** input, int intput_len) {

    __int64 h[8] = {
        0x6a09e667, 0xbb67ae85, 0x3c6ef372, 0xa54ff53a, 0x510e527f, 0x9b05688c, 0x1f83d9ab, 0x5be0cd19,
    };
    __int64 k[64] = {
        0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5, 0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
        0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3, 0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
        0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc, 0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
        0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7, 0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
        0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13, 0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
        0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3, 0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
        0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5, 0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
        0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208, 0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2,
    };

    bit_3sat*** h_b3 = new bit_3sat ** [8];
    bit_3sat*** k_b3 = new bit_3sat ** [64];

    for (int i = 0; i < 8; i++)
        h_b3[i] = uint32_to_bit3sat_b3(h[i]);

    for (int i = 0; i < 64; i++)
        k_b3[i] = uint32_to_bit3sat_b3(k[i]);
}

#endif