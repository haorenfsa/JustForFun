// Base64code table
// value 	code
// 0 	A 	16 	Q 	32 	g 	48 	w
// 1 	B 	17 	R 	33 	h 	49 	x
// 2 	C 	18 	S 	34 	i 	50 	y
// 3 	D 	19 	T 	35 	j 	51 	z
// 4 	E 	20 	U 	36 	k 	52 	0
// 5 	F 	21 	V 	37 	l 	53 	1
// 6 	G 	22 	W 	38 	m 	54 	2
// 7 	H 	23 	X 	39 	n 	55 	3
// 8 	I 	24 	Y 	40 	o 	56 	4
// 9 	J 	25 	Z 	41 	p 	57 	5
// 10 	K 	26 	a 	42 	q 	58 	6
// 11 	L 	27 	b 	43 	r 	59 	7
// 12 	M 	28 	c 	44 	s 	60 	8
// 13 	N 	29 	d 	45 	t 	61 	9
// 14 	O 	30 	e 	46 	u 	62 	+
// 15 	P 	31 	f 	47 	v 	63 	/

//define function types
typedef int RETVAL;
const int OK = 0;
const int FAIL = 1;
const int GROUPSIZE = 3;
const char* tag = "BASE64";

#define BASE64_API  RETVAL
#define BIG_FUNC static RETVAL
#define TOOL_FUNC static inline RETVAL

//if failed,return FAIL
#define TOOL_CALL(x) \
if(x){\
printf("[" tag "]error exit in file: %s line:%d\n", __FILE__, __LINE__)\
return FAIL;\
}

TOOL_FUNC NewCharArray(char *outStr, unsigned int inSize);

//align as Base64, may add length 1 or 2 bytes, return new length
TOOL_FUNC AlignBase64(char* inStr, size_t originLength, char* outStr, size_t &outLength);

TOOL_FUNC CodeSwitch(void* inVoid, size_t inLength, void* outVoid, size_t &outLength);

TOOL_FUNC AddBytes(char* inStr, size_t inBytes, char* outStr);

BASE64_API Base64Encoder(void* inVoid, size_t inLength, void* outVoid, size_t &outLength);
{
	//handle as char*
	char* inStr = (char*) inVoid;
	char* outStr = NULL;
	//align as Base64, return new length;
	TOOL_CALL( AlignBase64(inStr, inLength, outLength) );
	
	//transcode 6 bit as unit, 4 unit as a group
	TOOL_CALL( CodeSwitch(inStr, outStr) );
}

TOOL_FUNC NewCharArray(char *outStr, unsigned int inSize)
{
	outStr = (char*) malloc(inSize);
	if(NULL != outStr)
		return OK;
	else
		return FAIL;
}

TOOL_FUNC AlignBase64(char* inStr, size_t originLength, char* outStr, size_t &outLength)
{
	if( originLength%GROUPSIZE == 1)
	{
		TOOL_CALL( AddBytes(inStr, 2, outStr) );
		outLength += 2;
	}
	else if( originLength%GROUPSIZE == 2)
	{
		TOOL_CALL( AddBytes(inStr, 1, outStr) );
		outLength += 1;
	}
	return OK;
}