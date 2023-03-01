#ifndef BYTE_MANAGER_H
#define BYTE_MANAGER_H

/*
---------------------------------------------
                Byte Manager
---------------------------------------------

-----------------------------------------------------------------------------------
**Functions**
void displayByteArray(const uint8_t* array) :
uint8_t* XORs(const uint8_t* b1, const uint8_t* b2) :
-----------------------------------------------------------------------------------
*/

// Don't use on arduino
// This code was made in case user is lazy (as me) to generate random Keys
void displayByteArray(const uint8_t* array){
  const int size = sizeof(array)/sizeof(uint8_t);
    
  printf("{");
  for(int i=0; i<size; ++i){
      printf("0x%X", array[i]);
      if(i < size-1)
        printf(",");
  }
  printf("}\n");
}

// XOR operand between two byte array
// (Do not verify error, so don't try impossible things (^w^))
void XORs(const uint8_t* src, const uint8_t* dest){
  int len = sizeof(src)/sizeof(uint8_t);

  for(int i=0; i<len; ++i){
    dest[i] = src[i] ^ dst[i];
  }

  return result;
}

#endif