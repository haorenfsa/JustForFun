
#define unsigned int uint

uint human_multiply(uint num1, uint num2)
{
	uint human_num1[10];
	uint human_num2[10];
	GetHumanNum(num1, human_num1);
	GetHumanNum(num2, human_num2);
	
	multiplies
	for()
	{
		for()
		{
			
		}
	}
	addall
	
}

void GetHumanNum(uint num, uint human_num[])
{
	uint bits1 = count_decimal_bits(num1);
	uint bits2 = count_decimal_bits(num2);
	for(uint bits)
}

//count bits in decimal
uint count_decimal_bits(uint num_in)
{
	uint bits = 0;
	do{
		uint num_in /= 10;
		bits ++;
	}
	while( 0 != num_in );
	return bits;
}

//from 0x0 to 9x9
uint simple_multiply(uint num1, uint num2)
{
	return num1*num2;
}