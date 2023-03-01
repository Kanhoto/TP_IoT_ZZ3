#ifndef AES_CREDENTIALS_H
#define AES_CREDENTIALS_H

/*
---------------------------------------------
              AES credentials
---------------------------------------------

-----------------------------------------------------------------------------------
**Variables**
key : AES key in 16 bytes, to cypher our counter intro counter prims
cpt : initial counter (could evolve as running programm)

**Functions**
cipheredCounter(int) : returned the ciphered counter (oblivious)
-----------------------------------------------------------------------------------
*/

//key[16] cotain 16 byte key(128 bit) for encryption
const uint8_t key[16]={0xa3, 0x97, 0xa2, 0x55, 0x53, 0xbe, 0xf1, 0xfc, 0xf9, 0x79, 0x6b, 0x52, 0x14, 0x13, 0xe9, 0xe2};

// Counter for AES testing
uint8_t cpt = 225;

const uint8_t* cipheredCounter(int cpt){
  
}

#endif
