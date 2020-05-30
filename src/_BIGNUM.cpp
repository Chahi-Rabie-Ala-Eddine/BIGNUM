#include <iostream>
#include "_BIGNUM.h"

using namespace std;

//								//
//	       Initialisation      	//
//								//

/*Set Big number value*/
BIG SetValue(string value)
{
	BIG number;
	mpz_init(number.Number);
	mpz_set_str(number.Number, const_cast<char*>(value.c_str()), 16);

	return number;
}

//								//
//	       Informations      	//
//								//

/*Get Big number size*/
int GetSize(BIG const& number)
{

	return static_cast<int>(mpz_sizeinbase(number.Number, 16));
}

/*Get Big number value*/
string GetValue(BIG const& number)
{
	char* temp = NULL;
	string value(mpz_get_str(temp, 16, number.Number));
	for (auto & character: value) character = toupper(character);
    
    return (string)value;
}

//								//
//	       	   Storage      	//
//								//

/*Initialise a Big number value using another one*/
BIG Equal(BIG Number)
{
	BIG result = SetValue(GetValue(Number));

	return result;
}

//								//
//	     	 Comparaison   		//
//								//

/*Check if the two numbers are equals*/
bool operator==(BIG const& firstNum, BIG const& secondNum)
{

	return (mpz_cmp(firstNum.Number, secondNum.Number)  == 0) ? true : false;
}

/*Check if the two numbers are different*/
bool operator!=(BIG const& firstNum, BIG const& secondNum)
{
	
	return (mpz_cmp(firstNum.Number, secondNum.Number) != 0) ? true : false;
}

/*Check if the first number is greater than the second*/
bool operator>(BIG const& firstNum, BIG const& secondNum)
{

	return (mpz_cmp(firstNum.Number, secondNum.Number) > 0) ? true : false;
}

/*Check if the first number is smaller than the second*/
bool operator<(BIG const& firstNum, BIG const& secondNum)
{

	return (mpz_cmp(firstNum.Number, secondNum.Number) < 0) ? true : false;
}

/*Check if the number is odd*/
bool IsOdd(BIG const& Num)
{

	return (mpz_odd_p (Num.Number) != 0) ? true : false;
}

/*Check if the number is even*/
bool IsEven(BIG const& Num)
{

	return (mpz_even_p (Num.Number) != 0) ? true : false;
}

//								//
//	      	Arithmetic 			//
//								//

/*Addition*/
BIG operator+(BIG const& firstNum, BIG const& secondNum)
{
	BIG result;
	mpz_init(result.Number);
	mpz_add (result.Number , firstNum.Number, secondNum.Number);

	return result;
}

/*Substraction*/
BIG operator-(BIG const& firstNum, BIG const& secondNum)
{
	BIG result;
	mpz_init(result.Number);
	mpz_sub (result.Number , firstNum.Number, secondNum.Number);

	return result;
}

/*Multiplication*/
BIG operator*(BIG const& firstNum, BIG const& secondNum)
{
	BIG result;
	mpz_init(result.Number);
	mpz_mul (result.Number , firstNum.Number, secondNum.Number);

	return result;
}

/*Division*/
BIG operator/(BIG const& firstNum, BIG const& secondNum)
{
	BIG result;
	mpz_init(result.Number);
	mpz_div (result.Number , firstNum.Number, secondNum.Number);

	return result;
}

/*Incrementation*/
void Increment(BIG Num)
{

	mpz_add_ui (Num.Number, Num.Number, 1);
}

/*Decrementation*/
void Decrement(BIG Num)
{
	
	mpz_sub_ui(Num.Number, Num.Number, 1);
}

/*Square*/
BIG Square(BIG const& Num)
{

	return operator*(Num, Num);
}

/*Simple exponentiation : mpz_t power unsigned long*/
BIG SimpleExponentiation(BIG const& base, unsigned long int exponent)
{
	BIG result;
	mpz_init(result.Number);
	mpz_pow_ui (result.Number, base.Number, exponent);

	return result;
}

//								//
//	     Modular Arithmetic 	//
//								//

/*Compute module*/
BIG Mod(BIG const& Num, BIG const& mod)
{
	BIG result;
	mpz_init(result.Number);
	mpz_mod(result.Number, Num.Number, mod.Number);

	return result;
}

/*Modular multiplication*/
BIG ModularMultiplication(BIG const& firstNum, BIG const& secondNum, BIG const& mod)
{

	return Mod(operator*(firstNum, secondNum), mod);
}

/*Modular exponentiation*/
BIG ModularExponentiation(BIG const& Num, BIG const& exp, BIG const& mod)
{
	BIG result;
	mpz_init(result.Number);
	mpz_powm (result.Number, Num.Number, exp.Number, mod.Number);

	return result;
}

//								//
//	     	Cryptography  		//
//								//

/*Montgomery Multiplication*/
BIG MontgomeryMultiplication(BIG const& firstNum, BIG const& secondNum, BIG const& mod)
{

	BIG _2 = SetValue("2"), _1 = SetValue("1");

	BIG size = SimpleExponentiation(mod, GetSize(mod));
	BIG R = Equal(ModularExponentiation(_2, size, _1));

	if(IsOdd(mod))
		throw invalid_argument("Modulo isn't odd !\n");

	if(operator>(mod, size) || operator<(mod, SimpleExponentiation(mod, (GetSize(mod)-1))))
		throw invalid_argument("Modulo's size is out of bounds !\n");

	BIG result;
	mpz_init(result.Number);

	return result;
}

/*Normal fast expnonentiation*/

/*Montgomery fast exponentiation*/

//								//
//	     	  Printing  		//
//								//

/*Print Big number value*/
void PrintBig(BIG number)
{

	gmp_printf("%ZX\n",number.Number);
}
