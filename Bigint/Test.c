#include <assert.h>
#include "Bigint.h"

void Bigint_Compare_Test1()
{
	uint8_t bigint1[] = { 0xff, 0x14, 0x45, 0x67 };
	uint8_t bigint2[] = { 0xf1, 0x14, 0x45, 0x67 };

	assert(Bigint_Compare(bigint1, bigint2, 4, 4) == 1);
}

void Bigint_Compare_Test2()
{
	uint8_t bigint1[] = { 0xf0, 0x14, 0x45, 0x67 };
	uint8_t bigint2[] = { 0xff, 0x14, 0x45, 0x67 };

	assert(Bigint_Compare(bigint1, bigint2, 4, 4) == 2);
}

void Bigint_Compare_Test3()
{
	uint8_t bigint1[] = { 0xff, 0x14, 0x45, 0x67 };
	uint8_t bigint2[] = { 0xff, 0x14, 0x45, 0x67 };

	assert(Bigint_Compare(bigint1, bigint2, 4, 4) == 0);
}

void Bigint_Add_Test1()
{
	uint8_t bigint1[]    = { 0xff, 0x14, 0x45, 0x67 };
	uint8_t bigint2[]    = { 0xe4, 0x78, 0x90, 0x94 };
	unsigned long *x1    = (unsigned long *)bigint1;
	unsigned long *x2    = (unsigned long *)bigint2;
	unsigned long y1     = *x1 + *x2;
	unsigned long result = 0u;

	Bigint_Add(bigint1, bigint2, (uint8_t*)&result, sizeof(bigint1), sizeof(bigint2));

	assert(result == y1);
}

void Bigint_Add_Test2()
{
	uint8_t bigint1[]    = { 0xff, 0x14, 0x45, 0x67 };
	uint8_t bigint2[]    = { 0x00, 0x00, 0x00, 0x00 };
	unsigned long *x1    = (unsigned long *)bigint1;
	unsigned long *x2    = (unsigned long *)bigint2;
	unsigned long y1     = *x1 + *x2;
	unsigned long result = 0u;

	Bigint_Add(bigint1, bigint2, (uint8_t*)&result, sizeof(bigint1), sizeof(bigint2));

	assert(result == y1);

}

void Bigint_Add_Test3()
{
	uint8_t bigint1[]    = { 0xff, 0x14, 0x45, 0x67 };
	uint8_t bigint2[]    = { 0x00 };
	unsigned long *x1    = (unsigned long *)bigint1;
	unsigned long result = 0u;

	Bigint_Add(bigint1, bigint2, (uint8_t*)&result, sizeof(bigint1), sizeof(bigint2));

	assert(result == *x1);
}


void Bigint_Add_Test4()
{
	uint8_t bigint1[]    = { 0xff, 0x14, 0x45, 0x67 };
	uint8_t bigint2[]    = { 0x00, 0x67, 0x89, 0x89 };
	unsigned long *x1    = (unsigned long *)bigint1;
	unsigned long *x2    = (unsigned long *)bigint2;
	unsigned long y1     = *x1 + *x2;
	unsigned long result = 0u;

	Bigint_Add(bigint1, bigint2, (uint8_t*)&result, sizeof(bigint1), sizeof(bigint2));

	assert(result == y1);
}


void Bigint_Add_Test5()
{
	uint8_t bigint1[]    = { 0xff, 0xff, 0xff, 0xff };
	uint8_t bigint2[]    = { 0x01, 0x00, 0x00, 0x00 };
	unsigned long *x1    = (unsigned long *)bigint1;
	unsigned long *x2    = (unsigned long *)bigint2;
	unsigned long y1     = *x1 + *x2;
	unsigned long long result = 0u;
	unsigned long      *result1 = 0u;

	Bigint_Add(bigint1, bigint2, (uint8_t*)&result, sizeof(bigint1), sizeof(bigint2));

	result1 = (unsigned long*)&result;

	assert(*result1 == y1);
}


void Bigint_Substract_Test1()
{
	uint8_t bigint1[] = { 0xff, 0x14, 0x45, 0x67 };
	uint8_t bigint2[] = { 0x00, 0x67, 0x89, 0x89 };
	unsigned long *x1 = (unsigned long *)bigint1;
	unsigned long *x2 = (unsigned long *)bigint2;
	unsigned long y1 = *x1 - *x2;
	unsigned long result1 = 0u;

	Bigint_Substract(bigint1, bigint2, &result1, sizeof(bigint1), sizeof(bigint2));

	assert(result1 == y1);
}


void Bigint_Substract_Test2()
{
	uint8_t bigint1[] = { 0xff, 0x14, 0x45, 0x67 };
	uint8_t bigint2[] = { 0x00, 0x00, 0x00, 0x00 };
	unsigned long *x1 = (unsigned long *)bigint1;
	unsigned long *x2 = (unsigned long *)bigint2;
	unsigned long y1 = *x1 - *x2;
	unsigned long result1 = 0u;

	Bigint_Substract(bigint1, bigint2, &result1, sizeof(bigint1), sizeof(bigint2));

	assert(result1 == y1);
}


void Bigint_Substract_Test3()
{
	uint8_t bigint1[] = { 0xff, 0x14, 0x45, 0x67 };
	uint8_t bigint2[] = { 0x11, 0xdd };
	unsigned long *x1 = (unsigned long *)bigint1;
	unsigned long  x2 = 0xdd11;
	unsigned long y1 = *x1 - x2;
	unsigned long result1 = 0u;

	Bigint_Substract(bigint1, bigint2, &result1, sizeof(bigint1), sizeof(bigint2));

	assert(result1 == y1);
}

void Bigint_ReadBit_Test1()
{
	uint8_t bigint1[] = { 0xff, 0x14, 0x45, 0x67 };
	unsigned long *x1 = (unsigned long *)bigint1;
	unsigned long y1 = (*x1 & (1 << 13))>>13 ;
	unsigned long result1 = Bigint_ReadBit(bigint1, 13);

	assert(result1 == y1);
}

void Bigint_ReadBit_Test2()
{
	uint8_t bigint1[] = { 0xff, 0x14, 0x45, 0x67 };
	unsigned long *x1 = (unsigned long *)bigint1;
	unsigned long y1 = (*x1 & (1 << 12)) >> 12;
	unsigned long result1 = Bigint_ReadBit(bigint1, 12);

	assert(result1 == y1);
}

void Bigint_WriteBit_Test1()
{
	uint8_t bigint1[] = { 0xff, 0x14, 0x45, 0x67 };
	unsigned long *x1 = (unsigned long *)bigint1;
	unsigned long y1  = (*x1 | (1 << 13));

	Bigint_WriteBit(bigint1, 13, 1);

	assert(*x1 == y1);
}

void Bigint_WriteBit_Test2()
{
	uint8_t bigint1[] = { 0xff, 0x14, 0x45, 0x67 };
	unsigned long *x1 = (unsigned long *)bigint1;
	unsigned long y1 = (*x1 & ~(1 << 12));

	Bigint_WriteBit(bigint1, 12, 0);

	assert(*x1 == y1);
}

void Bigint_ShiftLeft_Test1()
{
	uint8_t bigint1[] = { 0xff, 0x14, 0x45, 0x67 };
	unsigned long *x1 = (unsigned long *)bigint1;
	unsigned long y1   = *x1 << 7;
	unsigned long result =0;

	Bigint_ShiftLeft(bigint1, &result, 7, sizeof(bigint1));

	assert(result == y1);
}

void Bigint_ShiftLeft_Test2()
{
	uint8_t bigint1[] = { 0xff, 0x14, 0x45, 0x67 };
	unsigned long *x1 = (unsigned long *)bigint1;
	unsigned long y1 = *x1 << 13;
	unsigned long result = 0;

	Bigint_ShiftLeft(bigint1, &result, 13, sizeof(bigint1));

	assert(result == y1);
}

void Bigint_ShiftRight_Test1()
{
	uint8_t bigint1[] = { 0xff, 0x14, 0x45, 0x67 };
	unsigned long *x1 = (unsigned long *)bigint1;
	unsigned long y1 = *x1 >> 13;
	unsigned long result = 0;

	Bigint_ShiftRight(bigint1, &result, 13, sizeof(bigint1));

	assert(result == y1);
}

void Bigint_ShiftRight_Test2()
{
	uint8_t bigint1[] = { 0xff, 0x14, 0x45, 0x67 };
	unsigned long *x1 = (unsigned long *)bigint1;
	unsigned long y1 = *x1 >> 7;
	unsigned long result = 0;

	Bigint_ShiftRight(bigint1, &result, 7, sizeof(bigint1));

	assert(result == y1);
}

void Bigint_And_Test1()
{
	uint8_t bigint1[] = { 0xff, 0x14, 0x45, 0x67 };
	uint8_t bigint2[] = { 0x11, 0xdd, 0x00, 0x89 };
	unsigned long *x1 = (unsigned long *)bigint1;
	unsigned long *x2 = (unsigned long *)bigint2;
	unsigned long y1 = *x1 & *x2;
	unsigned long result1 = 0u;

	Bigint_And(bigint1, bigint2, &result1, sizeof(bigint1), sizeof(bigint2));

	assert(result1 == y1);
}

void Bigint_Or_Test1()
{
	uint8_t bigint1[] = { 0xff, 0x14, 0x45, 0x67 };
	uint8_t bigint2[] = { 0x11, 0xdd, 0x00, 0x89 };
	unsigned long *x1 = (unsigned long *)bigint1;
	unsigned long *x2 = (unsigned long *)bigint2;
	unsigned long y1 = *x1 | *x2;
	unsigned long result1 = 0u;

	Bigint_Or(bigint1, bigint2, &result1, sizeof(bigint1), sizeof(bigint2));

	assert(result1 == y1);
}

void Bigint_Xor_Test1()
{
	uint8_t bigint1[] = { 0xff, 0x14, 0x45, 0x67 };
	uint8_t bigint2[] = { 0x11, 0xdd, 0x00, 0x89 };
	unsigned long *x1 = (unsigned long *)bigint1;
	unsigned long *x2 = (unsigned long *)bigint2;
	unsigned long y1 = *x1 ^ *x2;
	unsigned long result1 = 0u;

	Bigint_Xor(bigint1, bigint2, &result1, sizeof(bigint1), sizeof(bigint2));

	assert(result1 == y1);
}

void Bigint_Multiply_Test1()
{
	uint8_t bigint1[] = { 0xff, 0x14, 0x00, 0x00 };
	uint8_t bigint2[] = { 0x11, 0xdd, 0x00, 0x00 };
	unsigned long *x1 = (unsigned long *)bigint1;
	unsigned long *x2 = (unsigned long *)bigint2;
	unsigned long y1 = *x1 * *x2;
	unsigned long result1 = 0u;

	Bigint_Multiply(bigint1, bigint2, &result1, 2, 2);

	assert(result1 == y1);
}

void Bigint_Multiply_Test2()
{
	uint8_t bigint1[] = { 0xff, 0x14, 0xe4, 0x11 };
	uint8_t bigint2[] = { 0x00, 0x00, 0x00, 0x00 };
	unsigned long *x1 = (unsigned long *)bigint1;
	unsigned long *x2 = (unsigned long *)bigint2;
	unsigned long y1 = *x1 * *x2;
	unsigned long long result1 = 0u;

	Bigint_Multiply(bigint1, bigint2, &result1, 4, 2);

	assert(result1 == y1);
}


void Bigint_Multiply_Test3()
{
	uint8_t bigint1[] = { 0xff, 0x14, 0xe4, 0x11 };
	uint8_t bigint2[] = { 0x01, 0x00, 0x00, 0x00 };
	unsigned long *x1 = (unsigned long *)bigint1;
	unsigned long *x2 = (unsigned long *)bigint2;
	unsigned long y1 = *x1 * *x2;
	unsigned long long result1 = 0u;

	Bigint_Multiply(bigint1, bigint2, &result1, 4, 1);

	assert(result1 == y1);
}


void Bigint_Multiply_Test4()
{
	uint8_t bigint1[] = { 0xff, 0x14, 0xe4, 0x11 };
	uint8_t bigint2[] = { 0x01, 0x5a, 0xf7, 0x99 };
	unsigned long *x1 = (unsigned long *)bigint1;
	unsigned long *x2 = (unsigned long *)bigint2;
	unsigned long long y1 = (unsigned long long)*x1 * (unsigned long long)*x2;
	unsigned long long result1 = 0u;

	Bigint_Multiply(bigint1, bigint2, &result1, 4, 4);

	assert(result1 == y1);
}

void Bigint_Divide_Test1()
{
	uint8_t bigint1[] = { 0xff, 0x14, 0xe4, 0xff };
	uint8_t bigint2[] = { 0x01, 0x5a, 0x00, 0x00 };
	unsigned long *x1 = (unsigned long *)bigint1;
	unsigned long *x2 = (unsigned long *)bigint2;
	unsigned long y1  = (unsigned long)*x1 / (unsigned long)*x2;
	unsigned long y2  = (unsigned long)*x1 % (unsigned long)*x2;
	unsigned long result1 = 0u;
	unsigned long result2 = 0u;

	Bigint_Divide(&bigint1, &bigint2, &result1, &result2, 4, 4);

	assert(result1 == y1);
	assert(result2 == y2);
}

void Bigint_Divide_Test2()
{
	uint8_t bigint1[] = { 0xff, 0x14, 0xe4, 0xff };
	uint8_t bigint2[] = { 0x01, 0x00, 0x00, 0x00 };
	unsigned long *x1 = (unsigned long *)bigint1;
	unsigned long *x2 = (unsigned long *)bigint2;
	unsigned long y1 = (unsigned long)*x1 / (unsigned long)*x2;
	unsigned long y2 = (unsigned long)*x1 % (unsigned long)*x2;
	unsigned long result1 = 0u;
	unsigned long result2 = 0u;

	Bigint_Divide(&bigint1, &bigint2, &result1, &result2, 4, 1);

	assert(result1 == y1);
	assert(result2 == y2);
}

void Bigint_Divide_Test3()
{
	uint8_t bigint1[] = { 0xff, 0x14, 0xe4, 0xff };
	uint8_t bigint2[] = { 0x01, 0x00, 0x00, 0x00 };
	unsigned long *x1 = (unsigned long *)bigint1;
	unsigned long *x2 = (unsigned long *)bigint2;
	unsigned long y1 = (unsigned long)*x1 / (unsigned long)*x2;
	unsigned long y2 = (unsigned long)*x1 % (unsigned long)*x2;
	unsigned long result1 = 0u;
	unsigned long result2 = 0u;

	Bigint_Divide(&bigint1, &bigint2, &result1, &result2, 4, 4);

	assert(result1 == y1);
	assert(result2 == y2);
}

void Bigint_Divide_Test4()
{
	uint8_t bigint1[] = { 0xff, 0x14, 0xe4, 0xff };
	uint8_t bigint2[] = { 0x00, 0x00, 0x00, 0x00 };
	unsigned long y1 = 0;
	unsigned long y2 = 0;
	unsigned long result1 = 0u;
	unsigned long result2 = 0u;

	Bigint_Divide(&bigint1, &bigint2, &result1, &result2, 4, 4);

	assert(result1 == y1);
	assert(result2 == y2);
}


void Bigint_ModularExponentiation_Test1()
{
	uint8_t base[]     = { 0xff, 0x14, 0xe4, 0xff };
	uint8_t exponent[] = { 0x11, 0x24, 0x00, 0x00 };
	uint8_t modulus[]  = { 0x42, 0x15, 0xcf, 0xe5 };
	uint8_t reponseBuff[4];
	unsigned long correctrResult = 0xdd25f2f9;
	unsigned long *response = (unsigned long *)reponseBuff;

	memset(reponseBuff, 0 ,4);

	Bigint_ModularExponentiation(base, exponent, modulus, reponseBuff, 4);

	assert(correctrResult == *response);
}


void Bigint_ModularExponentiation_Test2()
{
	uint8_t base[]     = { 0xff, 0x14, 0xe4, 0xff, 0x11, 0x24, 0x90, 0x45 };
	uint8_t exponent[] = { 0x11, 0x24, 0x00, 0x00, 0x78, 0x49, 0x56, 0x32 };
	uint8_t modulus[]  = { 0x42, 0x15, 0xcf, 0xe5, 0x11, 0x24, 0xff, 0x14 };
	uint8_t reponseBuff[8];
	unsigned long long correctrResult = 0xbf8a8d9f5db6ffd;
	unsigned long long *response = (unsigned long *)reponseBuff;

	memset(reponseBuff, 0, 8);

	Bigint_ModularExponentiation(base, exponent, modulus, reponseBuff, 8);

	assert(correctrResult == *response);
}


void Bigint_ModularExponentiation_Test3()
{
	uint8_t base[]     = { 0x11, 0x14, 0xe4, 0xff, 0x11, 0x24, 0x90, 0x45 };
	uint8_t exponent[] = { 0x00, 0x00, 0x11, 0x00, 0xf5, 0x49, 0x56, 0x77 };
	uint8_t modulus[]  = { 0x22, 0x15, 0xcf, 0xe1, 0x11, 0x22, 0xf1, 0x14 };
	uint8_t reponseBuff[8];
	unsigned long long correctrResult = 0x128202935cde2bc5;
	unsigned long long *response = (unsigned long *)reponseBuff;

	memset(reponseBuff, 0, 8);

	Bigint_ModularExponentiation(base, exponent, modulus, reponseBuff, 8);

	assert(correctrResult == *response);
}


void Bigint_ModularExponentiation_Test4()
{
	uint8_t base[]     = { 0x11, 0x14, 0xe4, 0xff, 0x11, 0x24, 0x90, 0x45, 0x11, 0x14, 0xe4, 0xff, 0x11, 0x24, 0x90, 0x45 };
	uint8_t exponent[] = { 0x00, 0x00, 0x11, 0x00, 0xf5, 0x49, 0x56, 0x77, 0x11, 0x14, 0xe4, 0xff, 0x11, 0x24, 0x90, 0x45 };
	uint8_t modulus[]  = { 0x22, 0x15, 0xcf, 0xe1, 0x11, 0x22, 0xf1, 0x14, 0x11, 0x14, 0xe4, 0xff, 0x11, 0x24, 0x90, 0x45 };
	uint8_t reponseBuff[16];
	uint8_t const result[] = { 0x6d, 0xff, 0x76, 0x4f, 0xc2, 0xa1, 0xb4, 0x12, 0x51, 0xc3, 0x2d, 0x77, 0x5e, 0xe8, 0x85, 0x2b };

	memset(reponseBuff, 0, 16);

	Bigint_ModularExponentiation(base, exponent, modulus, reponseBuff, 16);

	for (int i = 0; i < 16; i++)
	{
		assert(reponseBuff[i] == result[i]);
	}
}

void Bigint_VerifyPrime_Test1()
{
	uint8_t bigint1[] = { 0x81, 0x3d, 0x66 };

	uint8_t response = Bigint_VerifyPrime(bigint1, 3, 3);

	assert(response == 1);
}

void Bigint_VerifyPrime_Test2()
{
	uint8_t bigint1[] = { 0x80, 0x3d, 0x66 };

	uint8_t response = Bigint_VerifyPrime(bigint1, 3, 3);

	assert(response == 0);
}

void Bigint_VerifyPrime_Test3()
{
	uint8_t bigint1[] = { 0xff, 0xff, 0xff, 0x7f };

	uint8_t response = Bigint_VerifyPrime(bigint1, 3, 4);

	assert(response == 1);
}

void Bigint_VerifyPrime_Test4()
{
	uint8_t bigint1[] = { 0xff, 0xff, 0xff, 0x6f };

	uint8_t response = Bigint_VerifyPrime(bigint1, 3, 4);

	assert(response == 0);
}

void Bigint_VerifyPrime_Test5()
{
	uint8_t bigint1[] = { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x7F };

	uint8_t response = Bigint_VerifyPrime(bigint1, 3, sizeof(bigint1));

	assert(response == 1);
}

void Bigint_VerifyPrime_Test6()
{
	uint8_t bigint1[] = { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xF5, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x7F };

	uint8_t response = Bigint_VerifyPrime(bigint1, 3, sizeof(bigint1));

	assert(response == 0);
}

void main()
{
	Bigint_Compare_Test1();
	Bigint_Compare_Test2();
	Bigint_Compare_Test3();

	Bigint_Add_Test1();
	Bigint_Add_Test2();
	Bigint_Add_Test3();
	Bigint_Add_Test4();
	Bigint_Add_Test5();

	Bigint_Substract_Test1();
	Bigint_Substract_Test2();
	Bigint_Substract_Test3();

	Bigint_ReadBit_Test1();
	Bigint_ReadBit_Test2();

	Bigint_WriteBit_Test1();
	Bigint_WriteBit_Test2();

	Bigint_ShiftLeft_Test1();
	Bigint_ShiftLeft_Test2();

	Bigint_ShiftRight_Test1();
	Bigint_ShiftRight_Test2();

	Bigint_And_Test1();

	Bigint_Or_Test1();

	Bigint_Xor_Test1();

	Bigint_Multiply_Test1();
	Bigint_Multiply_Test2();
	Bigint_Multiply_Test3();
	Bigint_Multiply_Test4();

	Bigint_Divide_Test1();
	Bigint_Divide_Test2();
	Bigint_Divide_Test3();
	Bigint_Divide_Test4();

	Bigint_ModularExponentiation_Test1();
	Bigint_ModularExponentiation_Test2();
	Bigint_ModularExponentiation_Test3();
	Bigint_ModularExponentiation_Test4();

	Bigint_VerifyPrime_Test1();
	Bigint_VerifyPrime_Test2();
	Bigint_VerifyPrime_Test3();
	Bigint_VerifyPrime_Test4();
	Bigint_VerifyPrime_Test5();
	Bigint_VerifyPrime_Test6();
}
