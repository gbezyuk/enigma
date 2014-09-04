//
//  main.c
//  enigma
//
//  Created by Grigoriy Beziuk on 04.09.14.
//  Copyright (c) 2014 Grigoriy Beziuk. All rights reserved.
//

#include <stdio.h>

const int BUFFER_SIZE = 5;
const char BITSHIFT_VALUE = 1;
const char CHAR_BIT = 8;
const unsigned char DBG = 1;

int inverse_coder(unsigned char* input, unsigned char* output, int buffer_length);
int bitshift_coder(unsigned char* input, unsigned char* output, int buffer_length, unsigned char shift);
int caesar_coder(unsigned char* input, unsigned char* output, int buffer_length, char shift);
unsigned char circular_bitshift(unsigned char value, unsigned char shift);
unsigned char circular_shift(unsigned char value, unsigned char shift);
unsigned char *bit_representation(unsigned char value, unsigned char* result);

int main(int argc, const char * argv[]) {
    unsigned char test[BUFFER_SIZE] = "abcd";
    unsigned char output[BUFFER_SIZE] = "";
    unsigned char back_to_origin[BUFFER_SIZE] = "";

//    unsigned char buf1[9] = "", buf2[9] = "";
//    
//    for (unsigned char i=0; i<16; i++) {
//        printf("%d = %s; ~%d = %s = %d\n", i, bit_representation(i, buf1), i, bit_representation(~i, buf2), ~i);
//    }
    
//    bitshift_coder(test, output, BUFFER_SIZE, BITSHIFT_VALUE);
//    bitshift_coder(output, back_to_origin, BUFFER_SIZE, 8 - BITSHIFT_VALUE);

//    inverse_coder(test, output, BUFFER_SIZE);
//    inverse_coder(output, back_to_origin, BUFFER_SIZE);
    
    caesar_coder(test, output, BUFFER_SIZE, 1);
    caesar_coder(output, back_to_origin, BUFFER_SIZE, -1);

    printf("%s -> %s -> %s\n", test, output, back_to_origin);
    return 0;
}

unsigned char *bit_representation(unsigned char value, unsigned char* result) {
    for (int i=7; i >= 0; i--) {
        result[i] = (value % 2) ? '1' : '0';
//        printf("\t%d %d %s\n", value, value % 2, result);
        value /= 2;
    }
    result[8] = '\0';
    return result;
}

unsigned char circular_bitshift(unsigned char value, unsigned char shift) {
    // NOTE: proven to work only with positive shifts
    return (value << shift) | (value >> (sizeof(value) * CHAR_BIT - shift));
}

unsigned char circular_shift(unsigned char value, unsigned char shift) {
    return (value + shift < 256) ? value + shift : value + shift - 256;
}


int inverse_coder(unsigned char* input, unsigned char* output, int buffer_length) {
    unsigned char *read = input;
    unsigned char *write = output;
    unsigned char buf1[9] = "", buf2[9] = "";
    while (read < input + buffer_length - 1) {
        unsigned char in = *read++;
        unsigned char out = ~in;
        *write ++ = out;
        if (DBG) {
            printf("%c %s -> %c %s\n",
                   in, bit_representation(in, buf1),
                   out, bit_representation(out, buf2));
        }
    }
    return 0;
}

int bitshift_coder(unsigned char* input, unsigned char* output, int buffer_length, unsigned char shift) {
    unsigned char *read = input;
    unsigned char *write = output;
    unsigned char buf1[9] = "", buf2[9] = "";
    while (read < input + buffer_length - 1) {
        unsigned char in = *read++;
        unsigned char out = circular_bitshift(in, shift);
        *write ++ = out;
        if (DBG) {
            printf("%c %s -> %c %s\n",
                   in, bit_representation(in, buf1),
                   out, bit_representation(out, buf2));
        }
    }
    return 0;
}

int caesar_coder(unsigned char* input, unsigned char* output, int buffer_length, char shift) {
    unsigned char *read = input;
    unsigned char *write = output;
    unsigned char buf1[9] = "", buf2[9] = "";
    while (read < input + buffer_length - 1) {
        unsigned char in = *read++;
        unsigned char out = circular_shift(in, shift);
        *write ++ = out;
        if (DBG) {
            printf("%c %d %s -> %c %d %s\n",
                   in, in, bit_representation(in, buf1),
                   out, out, bit_representation(out, buf2));
        }
    }
    return 0;
}

