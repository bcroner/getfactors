// get_factors_base.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#ifndef __GET_FACTORS_BASE_CPP__
#define __GET_FACTORS_BASE_CPP__

#include <iostream>
#include <stdio.h>

#include "3SATBaseConsole.hpp"
#include "3SAT_framework.hpp"

using namespace std;

int main()
{
    int num_parm = 2;
    int len_para = 0;
    //bit* a = create_bit(&num_parm);
    //bit* b = create_bit(&num_parm);
    //bit* c = NULL;
    //char bitc_name[15];
    //strcpy_s(bitc_name, 15, "bitc");
    //printf("%s\n", and_3sat(&num_parm, bitc_name, c, a, b, &len_para));
    //char c_str[5];
    char c_str[2000];
    /*
    strcpy_s(c_str, 2000,
        "BE88B9A8CA71030100C1798F81149B6F\
        5687B7EB3E218554D6608D4528914571\
        A54AE074E604863A0AA37302F1ED9DA3\
        A7EDCB8BB05ACE317D289A6E62A56888\
        A4BE324087C5A5BA67731FCFCE9EFD52\
        50FAABC5447D6DBDF6FCA97F4F370913\
        384EBC8A814063CA5151B0667394EABB\
        9ECE59C4191EFA3C67BA5022FC169BD6\
        08D1E14262E7D3EB8E61E66B70F720C9\
        4CD16BBEE0AA918992BE202C34F2901B\
        BE971780AC9DC4284C350DACBEFF7A2F\
        5543B9851BFC95A03081496AFC99466F\
        D31393574E5655A9C3AF13A5E98E2A11\
        59D6AD59EC1AAF2A7EF65F40D8C282B3\
        CA90A2C1788723C9B226D84545356A2F\
        4DF3F73A85483E8C08D5855055E7BE4D");
    */
    /*
    strcpy_s(c_str, 2000,
        "04898102f980b7d6f2a263692d1dad\
        7355c722bd52bc5615facfe9b7a5b2\
        d615b9d2da021a9b3b86f659909fc1\
        6ffff83445962c809d95dadf4daa8a\
        8304d84267"); // https://gmail.com
    */
    strcpy_s(c_str, 2000, "6");
    //strcpy_s(c_str, 2000, "F");
    //strcpy_s(c_str, 2000, "8F");
    //char * factors = get_factors(c_str, 2000, & len_para);
    //printf_s("%s\n", factors);
    /*
    int str_sz = 0;
    bool decodable_buf[] = {true, false, true, true, false, false, true, false , false};
    dec_3sat * numa = new dec_3sat();
    numa->ad_sz = 0;
    numa->bd_sz = 5;
    numa->sz = 5;
    strcpy_s(numa->name, 17, "numa_test");
    numa->bits = new bit * [5];
    int tf = FALSE_3SAT;
    numa->bits[0] = create_bit(&tf);
    numa->bits[1] = create_bit(&num_parm);
    numa->bits[2] = create_bit(&num_parm);
    numa->bits[3] = create_bit(&num_parm);
    numa->bits[4] = create_bit(&num_parm);
    char* dec_str = dec_to_str(decodable_buf, numa, &str_sz);
    */
    dec_3sat* c;
    dec_3sat* a = new dec_3sat();
    a->bd_sz = 4;
    a->ad_sz = 0;
    a->sz = 2;
    a->bits = new bit_3sat*[4];
    a->bits[0] = new bit_3sat();
    a->bits[0]->id = FALSE_3SAT;
    a->bits[1] = create_bit(&num_parm);
    a->bits[2] = create_bit(&num_parm);
    a->bits[3] = create_bit(&num_parm);


    dec_3sat* b = new dec_3sat();
    b->bd_sz = 4;
    b->ad_sz = 0;
    b->sz = 2;
    b->bits = new bit_3sat * [4];
    b->bits[0] = new bit_3sat();
    b->bits[0]->id = FALSE_3SAT;
    b->bits[1] = create_bit(&num_parm);
    b->bits[2] = create_bit(&num_parm);
    b->bits[3] = create_bit(&num_parm);

    char* sum_str = dec_add(&num_parm, &c, a, b, false, &len_para);

    printf_s("%s", sum_str);

    return 0;
}

#endif

/*
*
* mit.edu website security certificate

Modulus (2048 bits):
BE88B9A8CA71030100C1798F81149B6F
5687B7EB3E218554D6608D4528914571
A54AE074E604863A0AA37302F1ED9DA3
A7EDCB8BB05ACE317D289A6E62A56888
A4BE324087C5A5BA67731FCFCE9EFD52
50FAABC5447D6DBDF6FCA97F4F370913
384EBC8A814063CA5151B0667394EABB
9ECE59C4191EFA3C67BA5022FC169BD6
08D1E14262E7D3EB8E61E66B70F720C9
4CD16BBEE0AA918992BE202C34F2901B
BE971780AC9DC4284C350DACBEFF7A2F
5543B9851BFC95A03081496AFC99466F
D31393574E5655A9C3AF13A5E98E2A11
59D6AD59EC1AAF2A7EF65F40D8C282B3
CA90A2C1788723C9B226D84545356A2F
4DF3F73A85483E8C08D5855055E7BE4D

  Public Exponent (17 bits):
  01 00 01

*/

/*
* 
* mail.google.com

04:89:81:02:f9:80:b7:d6:f2:a2:63:69:2d:1d:ad:
73:55:c7:22:bd:52:bc:56:15:fa:cf:e9:b7:a5:b2:
d6:15:b9:d2:da:02:1a:9b:3b:86:f6:59:90:9f:c1:
6f:ff:f8:34:45:96:2c:80:9d:95:da:df:4d:aa:8a:
83:04:d8:42:67

*/


// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
