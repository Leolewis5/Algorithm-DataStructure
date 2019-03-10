#include <stdio.h>
#include <stdint.h>
#include <iostream>
using namespace std;
/*
int is_big_endian(void)
{
    union {
        uint32_t i;
        char c[4];
    } e = { 0x01000000 };
	
    return e.c[0];
}

int main(void)
{
    printf("System is %s-endian.\n",
        is_big_endian() ? "big" : "little");

    return 0;
}
*/

int main() {
    int a = 0x12345678;
    // 0x12, 0x34, 0x56, 0x78
	//  ^ big endian
	
	// 0x12, 0x34, 0x56, 0x78
	//                    ^ little endian
    char *ptr = (char *)&a;
    cout<<ptr<<" "<<*ptr<<endl;
    if (*ptr == 0x12)
        printf("Big Endian\n");
    else
        printf("Little Endian\n");
    return 0;
}
