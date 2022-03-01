#include <iostream>
#include <string>
#include <bits/stdc++.h>

typedef unsigned long long u64;

using namespace std;

u64 read_u64_hex(const char *data)
{
    u64 ret=0;
    for(;;++data)//read left
    {
        u64 dec=*data -'0';
        if(dec<10)
            ret=ret<<4|dec;
        else {
            u64 upper=(*data&0xDF) -'A';
            if(upper>5)
                break;
            ret=ret<<4|upper+10;
            }
    }
    return ret;
}



//*********KEY FUNCTIONS********//
void left_circular_shift_pkey(u64 &left, u64 &right ,u64 keyIndex){

    int arr[16] = {1, 1, 2, 2, 2, 2, 2 ,2 ,1 ,2 ,2 ,2 ,2 ,2 ,2 ,1};
    if(arr[keyIndex-1] == 1)
    {
       left = (left << 1) | (left >> 27);
       right = (right << 1) | (right >> 27);
    }
    else
    {
        left = (left << 2) | (left >> 26);
        right = (right << 2) | (right >> 26);
    }
}



u64 permutation_1(u64 plainKey){

    int arr[56] = {57,49,41,33,25,17,9,\
                   1,58,50,42,34,26,18,\
                   10,2,59,51,43,35,27,\
                   19,11,3,60,52,44,36,\
                   63,55,47,39,31,23,15,\
                   7,62,54,46,38,30,22,\
                   14,6,61,53,45,37,29,\
                   21,13,5,28,20,12,4};
    u64 out=0;
    for(int i=0;i<56;++i)
              out|=(plainKey>>(64-arr[56-1-i])&1)<<i;
    return out;
}


u64 permutation_2(u64 key){
    int arr[48] = {14,17,11,24,1,5,\
                   3,28,15,6,21,10,\
                   23,19,12,4,26,8,\
                   16,7,27,20,13,2,\
                   41,52,31,37,47,55,\
                   30,40,51,45,33,48,\
                   44,49,39,56,34,53,\
                   46,42,50,36,29,32};
    u64 out = 0;
    for(int i=0;i<48;++i)
              out|=(key>>(56-arr[48-1-i])&1)<<i;
    return out;
}



//*********Data FUNCTIONS********//
u64 initial_data_permutation(u64 plainData){
    int arr[64] = {58,50,42,34,26,18,10,2,\
                   60,52,44,36,28,20,12,4,\
                   62,54,46,38,30,22,14,6,\
                   64,56,48,40,32,24,16,8,\
                   57,49,41,33,25,17,9,1,\
                   59,51,43,35,27,19,11,3,\
                   61,53,45,37,29,21,13,5,\
                   63,55,47,39,31,23,15,7};

    u64 out = 0;
    for(int i=0; i<64; ++i)
          out|=(plainData >>(64 - arr[64-1-i]) & 1)<<i;
    return out;

}

u64 expansion(u64 rightData){
    int arr[48] = {32,1,2,3,4,5,\
                   4,5,6,7,8,9,\
                   8,9,10,11,12,13,\
                   12,13,14,15,16,17,\
                   16,17,18,19,20,21,\
                   20,21,22,23,24,25,\
                   24,25,26,27,28,29,\
                   28,29,30,31,32,1};
    u64 out = 0;
    for(int i=0; i<48; ++i)
          out|=(rightData >>(32 - arr[48-1-i]) & 1)<<i;
    return out;
}


u64 sBox1(u64 row, u64 colomn){
    u64 arr[4][16] = {{14,4,13,1,2,15,11,8,3,10,6,12,5,9,0,7},\
                        {0,15,7,4,14,2,13,1,10,6,12,11,9,5,3,8},\
                        {4,1,14,8,13,6,2,11,15,12,9,7,3,10,5,0},\
                        {15,12,8,2,4,9,1,7,5,11,3,14,10,0,6,13}};

    return arr[row][colomn];
}

u64 sBox2(u64 row, u64 colomn){
    u64 arr[4][16] = {{15,1,8,14,6,11,3,4,9,7,2,13,12,0,5,10},\
                        {3,13,4,7,15,2,8,14,12,0,1,10,6,9,11,5},\
                        {0,14,7,11,10,4,13,1,5,8,12,6,9,3,2,15},\
                        {13,8,10,1,3,15,4,2,11,6,7,12,0,5,14,9}};

    return arr[row][colomn];
}

u64 sBox3(u64 row, u64 colomn){
    u64 arr[4][16] = {{10,0,9,14,6,3,15,5,1,13,12,7,11,4,2,8},\
                       {13,7,0,9,3,4,6,10,2,8,5,14,12,11,15,1},\
                       {13,6,4,9,8,15,3,0,11,1,2,12,5,10,14,7},\
                       {1,10,13,0,6,9,8,7,4,15,14,3,11,5,2,12}};

    return arr[row][colomn];
}

u64 sBox4(u64 row, u64 colomn){
    u64 arr[4][16] = {{7,13,14,3,0,6,9,10,1,2,8,5,11,12,4,15},\
                       {13,8,11,5,6,15,0,3,4,7,2,12,1,10,14,9},\
                       {10,6,9,0,12,11,7,13,15,1,3,14,5,2,8,4},\
                       {3,15,0,6,10,1,13,8,9,4,5,11,12,7,2,14}};

    return arr[row][colomn];
}

u64 sBox5(u64 row, u64 colomn){
    u64 arr[4][16] = {{2,12,4,1,7,10,11,6,8,5,3,15,13,0,14,9},\
                       {14,11,2,12,4,7,13,1,5,0,15,10,3,9,8,6},\
                       {4,2,1,11,10,13,7,8,15,9,12,5,6,3,0,14},\
                       {11,8,12,7,1,14,2,13,6,15,0,9,10,4,5,3}};

    return arr[row][colomn];
}

u64 sBox6(u64 row, u64 colomn){
    u64 arr[4][16] = {{12,1,10,15,9,2,6,8,0,13,3,4,14,7,5,11},\
                       {10,15,4,2,7,12,9,5,6,1,13,14,0,11,3,8},\
                       {9,14,15,5,2,8,12,3,7,0,4,10,1,13,11,6},\
                       {4,3,2,12,9,5,15,10,11,14,1,7,6,0,8,13}};

    return arr[row][colomn];
}

u64 sBox7(u64 row, u64 colomn){
    u64 arr[4][16] = {{4,11,2,14,15,0,8,13,3,12,9,7,5,10,6,1},\
                       {13,0,11,7,4,9,1,10,14,3,5,12,2,15,8,6},\
                       {1,4,11,13,12,3,7,14,10,15,6,8,0,5,9,2},\
                       {6,11,13,8,1,4,10,7,9,5,0,15,14,2,3,12}};

    return arr[row][colomn];
}

u64 sBox8(u64 row, u64 colomn){
    u64 arr[4][16] = {{13,2,8,4,6,15,11,1,10,9,3,14,5,0,12,7},\
                       {1,15,13,8,10,3,7,4,12,5,6,11,0,14,9,2},\
                       {7,11,4,1,9,12,14,2,0,6,10,13,15,3,5,8},\
                       {2,1,14,7,4,10,8,13,15,12,9,0,3,5,6,11}};

    return arr[row][colomn];
}

u64 sbox(u64 rightData){
    int g1 = rightData >> 42;
    int g2 = rightData >> 36 & 0x003F;
    int g3 = rightData >> 30 & 0x003F;
    int g4 = rightData >> 24 & 0x003F;
    int g5 = rightData >> 18 & 0x003F;
    int g6 = rightData >> 12 & 0x003F;
    int g7 = rightData >> 6 & 0x003F;
    int g8 = rightData & 0x003F;

    int r1 = ((g1 >> 4) & 0x2)|(g1 & 1);
    int r2 = ((g2 >> 4) & 0x2)|(g2 & 1);
    int r3 = ((g3 >> 4) & 0x2)|(g3 & 1);
    int r4 = ((g4 >> 4) & 0x2)|(g4 & 1);
    int r5 = ((g5 >> 4) & 0x2)|(g5 & 1);
    int r6 = ((g6 >> 4) & 0x2)|(g6 & 1);
    int r7 = ((g7 >> 4) & 0x2)|(g7 & 1);
    int r8 = ((g8 >> 4) & 0x2)|(g8 & 1);

    int c1 = (g1 & 0b011110) >>1;
    int c2 = (g2 & 0b011110) >>1;
    int c3 = (g3 & 0b011110) >>1;
    int c4 = (g4 & 0b011110) >>1;
    int c5 = (g5 & 0b011110) >>1;
    int c6 = (g6 & 0b011110) >>1;
    int c7 = (g7 & 0b011110) >>1;
    int c8 = (g8 & 0b011110) >>1;

    u64 total = sBox1(r1,c1) << 28\
                                | (sBox2(r2,c2) << 24)\
                                |sBox3(r3,c3) << 20\
                                |sBox4(r4,c4)<< 16\
                                |sBox5(r5,c5)<< 12\
                                |sBox6(r6,c6)<< 8\
                                |sBox7(r7,c7)<< 4\
                                |sBox8(r8,c8);

    return total;
}

u64 permutation_in_FBlock(u64 rightData){
    int arr[32] = {16,7,20,21,\
                   29,12,28,17,\
                   1,15,23,26,\
                   5,18,31,10,\
                   2,8,24,14,\
                   32,27,3,9,\
                   19,13,30,6,\
                   22,11,4,25,};
    u64 out = 0;
    for(int i=0; i<32; ++i)
          out|=(rightData >>(32 - arr[32-1-i]) & 1)<<i;
    return out;
}

u64 fBlock(u64 rightData, u64 key){
    //expansion
    rightData = expansion(rightData);

    //xorring
    rightData = rightData ^ key;

    //sbox
    rightData = sbox(rightData);

    //permutaion in fblock
    rightData = permutation_in_FBlock(rightData);

    return rightData;
}

u64 final_data_permutation(u64 roundsOutput){

    int arr[64] = {40,8,48,16,56,24,64,32,\
                   39,7,47,15,55,23,63,31,\
                   38,6,46,14,54,22,62,30,\
                   37,5,45,13,53,21,61,29,\
                   36,4,44,12,52,20,60,28,\
                   35,3,43,11,51,19,59,27,\
                   34,2,42,10,50,18,58,26,\
                   33,1,41,9,49,17,57,25};

    u64 out = 0;
    for(int i=0; i<64; ++i)
          out|=(roundsOutput >>(64 - arr[64-1-i]) & 1)<<i;
    return out;
}



//**************MAIN**************//
int main(int argc, char* argv[]){
//    string operation = "decrypt";
//    string message = "7DB033DD14D6F975";
//    string key = "1323445A6D788381";

    string operation = argv[1];
    string message = argv[2];
    string key = argv[3];


    //*********KEYS SECTION********//

    //read input string to hexa
    u64 plainKey = read_u64_hex(&key[0]);

    //applying permutation1
    u64 p1key = permutation_1(plainKey);

    //splitting 56-bit key
    u64 right = p1key & 0xFFFFFFF;
    u64 left = p1key>>28;

    //generating keys
    u64 keysArr[16];
    for(int i=0; i < 16 ; i++){

        //applying shift left
        left_circular_shift_pkey(left,right,i+1);

        //updating pkey
        p1key = (( (left<<28) & 0x00FFFFFFFFFFFFFF) | (right & 0x000000000FFFFFFF)) & 0x00FFFFFFFFFFFFFF ;

        //applying second permutation
        u64 key = permutation_2(p1key);

        //adding the key to the array
        keysArr[i] = key;
    }

    //*********MESSAGE SECTION********//

    //read input string to hexa
    u64 plainMessage = read_u64_hex(&message[0]);


    //cycles calculation
    #ifdef _GNUC_
    # define __rdtsc __builtin_ia32_rdtsc
    #else
    # include<intrin.h>
    #endif
    long long t1=__rdtsc();
    //code under benchmark...

    //applying initial permutation
    u64 IP = initial_data_permutation(plainMessage);

    //splitting 64-bit data
    u64 r0 = IP & 0xFFFFFFFF;
    u64 l0 = IP>>32;

    //applying the 16 rounds
    u64 rData;
    u64 lData;

    if(operation == "encrypt"){
        for(int i = 0; i < 16; i++){
            rData = l0 ^ fBlock(r0,keysArr[i]);
            lData = r0;
            r0 = rData;
            l0 = lData;

        }
    }
    else{
        for(int i = 0; i < 16; i++){
            rData = l0 ^ fBlock(r0,keysArr[16-i-1]);
            lData = r0;
            r0 = rData;
            l0 = lData;

        }
    }

    //reverse the data
    u64 dataResultReversed = (rData << 32)|(lData);

    //applying final permutation
    u64 finalResult = final_data_permutation(dataResultReversed);

    long long t2=__rdtsc();


    //****PRINTING SECTION*********//
    if(operation == "encrypt"){
        cout << "cipher: ";
    }
    else{
        cout << "plain: ";
    }
    printf("%016llX\n", finalResult);
    printf("Cycles: %lld\n", t2-t1);


}
