// get_factors_base.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#ifndef __GET_FACTORS_BASE_CPP__
#define __GET_FACTORS_BASE_CPP__

#include <iostream>
#include <cmath>
#include <stdio.h>

#include "I:/My Drive/products/3SAT AI/3SATAI/3SATBaseConsole.hpp"
#include "I:/My Drive/products/3SAT AI/3SAT_Framework/3SAT_Framework/3SAT_framework.hpp"

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
    //strcpy_s(c_str, 5, "6");
    //strcpy_s(c_str, 5, "F");
    //strcpy_s(c_str, 5, "8F");
    //char * factors = get_factors(c_str, 5, & len_para);
    int str_sz = 0;
    bool decodable_buf[] = {true, false, true, true, false, false, true, false , false};
    dec* numa = new dec();
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
    return 0;
}

#endif

/*
*
* mit.edu website security certificate

Modulus (2048 bits):
  BE 88 B9 A8 CA 71 03 01 00 C1 79 8F 81 14 9B 6F
56 87 B7 EB 3E 21 85 54 D6 60 8D 45 28 91 45 71
A5 4A E0 74 E6 04 86 3A 0A A3 73 02 F1 ED 9D A3
A7 ED CB 8B B0 5A CE 31 7D 28 9A 6E 62 A5 68 88
A4 BE 32 40 87 C5 A5 BA 67 73 1F CF CE 9E FD 52
50 FA AB C5 44 7D 6D BD F6 FC A9 7F 4F 37 09 13
38 4E BC 8A 81 40 63 CA 51 51 B0 66 73 94 EA BB
9E CE 59 C4 19 1E FA 3C 67 BA 50 22 FC 16 9B D6
08 D1 E1 42 62 E7 D3 EB 8E 61 E6 6B 70 F7 20 C9
4C D1 6B BE E0 AA 91 89 92 BE 20 2C 34 F2 90 1B
BE 97 17 80 AC 9D C4 28 4C 35 0D AC BE FF 7A 2F
55 43 B9 85 1B FC 95 A0 30 81 49 6A FC 99 46 6F
D3 13 93 57 4E 56 55 A9 C3 AF 13 A5 E9 8E 2A 11
59 D6 AD 59 EC 1A AF 2A 7E F6 5F 40 D8 C2 82 B3
CA 90 A2 C1 78 87 23 C9 B2 26 D8 45 45 35 6A 2F
4D F3 F7 3A 85 48 3E 8C 08 D5 85 50 55 E7 BE 4D

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
