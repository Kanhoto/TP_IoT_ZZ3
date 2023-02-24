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
const uint8_t key[16]={0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37,0x38, 0x39, 0x65, 0x66, 0x67, 0x68, 0x69, 0x70};

// Counter for AES testing
uint8_t cpt = 225;

const uint8_t* cipheredCounter(int cpt){
  
}

#endif
