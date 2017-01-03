#include <stdlib.h>
#include <stdio.h>

struct TestStruct
{
	int		iNum1; //64bit - 16hex
	double	dNum2; //16hex
	char	str[11]; //8bit*11 = 88 bit = 44hex ,last 2 is 00
	const char*	pStr; //
};

// format:
// 00 00 00 00 00 00 00 00
// note there may be paddings
// in this test case:
// 8  7  6  5  4  3  2  1 byte
//
// 00 00 00 00 00 40 07 DE : const char* pStr = 0x4007DE
// 00 00 00 00 00 00 64 6C : 1~3:char str[11], 4~8 are padding
// 72 6F 77 6F 6C 6C 65 68 : char str[11] = "helloworld"
// 40 09 21 FB 54 2F E9 38 :3.141592653
// 00 00 00 00 00 00 80 01 :32769

//about double:
//-1.7E308—1.7E308
//````````符号位 阶码 尾数 长度
//float    1     8    23   32
//double   1    11    52   64
//临时数   1    15    64   80 ?
//400921FB542FE938
//double:3141592653
// 1|2-12|13|64
// 40 09 21 FB 54 2F E9 38
// <=>
// 1|           12|13
// 0100 0000  0000 1001 :40 09
// 0010 0001  1111 1011 :21 FB 
// 0101 0100  0010 1111 :54 2F
// 1110 1001  0011 1000 :E9 38
//0 10000000000 1001001000011111101101010100001011111110100100111000 
//0 2^1	 (1+ 0.5 + 0.0625 +.... ) ~=1.57.... x2 = 3.14...
//+| 2^10 = 1024|  (1 + 2^-1 +2^-4) * 1024
void PrintStruct(unsigned char* pStruct, size_t size)
{
	for(int i = size - 1 ; i >= 0 ; i--)
	{
		printf("%02X ", *( pStruct + i ) );
		if( i%8 == 0)
		{
			printf("\n");
		}
	}
}

//test
int main(int argc, char* argv[])
{
	const char* pStr = "helloworld";
	struct TestStruct STestInstance = 
	{
		32769, 3.141592653, "helloworld", pStr
	};
	printf("%lf\n", 3.141592653);
	PrintStruct( (unsigned char*)&STestInstance, sizeof(STestInstance) );
	return 0;
}