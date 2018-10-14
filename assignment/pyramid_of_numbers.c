/*----------------------------------------------------------
 *				HTBLA-Leonding / Class: 2DHIF
 * ---------------------------------------------------------
 * Exercise Number: 3
 * Title:			Pyramid of Numbers
 * Author:			David Kraus
 * ----------------------------------------------------------
 * Description:
 * Calculates a pyramid of numbers, i.e., it multiplies a big
 * integer by the number 2, its result by 3, etc. and then
 * returns to the original value by subsequently dividing,
 * again starting by 2, 3, etc.
 * ----------------------------------------------------------
 */
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

/// The maximum number of digits allowed in a big int.
#define MAX_DIGITS 80

/** BigInt represents an integer number which can have MAX_DIGITS digits
*** @see MAX_DIGITS
*/
struct BigInt {
	/** number of digits of the big int. */
	int digits_count;

	/** array of digits of big int. */
	unsigned int the_int[MAX_DIGITS];
};

/** strtobig_int converts a string into a BigInt. If strtobig_int runs
*** against a character not between '0' and '9' the conversion stops
*** at this point.
*** @param *str The string to be converted.
*** @param len Number of characters in string to be converted.
*** @param *big_int The converted string now as BigInt.
* @return The number of characters converted.
*/
int strtobig_int(const char *str, int len, struct BigInt *big_int);

/** print_big_int() prints a BigInt.
*** @param *big_int The BigInt to be printed.
*/
void print_big_int(const struct BigInt *big_int);

/** multiply() multiplies a BigInt by an int.
*** @param big_int The BigInt to be multiplied.
*** @param factor The int value which is multiplied by BigInt.
*** @param *big_result The result of the multiplication.
*/
void multiply(const struct BigInt *big_int, int factor, struct BigInt *big_result);

/** divide() multiplies a BigInt by an int.
*** @param big_int The BigInt to be divided.
*** @param divisor The int value by which we want to devide big_int.
*** @param *big_result The result of the division.
*/
void divide(const struct BigInt *big_int, int divisor, struct BigInt *big_result);

/** copy_big_int() copies a BigInt to another BigInt.
*** @param from The source where we want to copy from.
*** @param *to The target where we want to copy to.
*/
void copy_big_int(const struct BigInt *from, struct BigInt *to);


/**
*** Reverses a BigInt by each digit
**/
void reverse_big_int(struct BigInt *big_int);

/**
*** main() reads the base number from which the pyramid has to be calculated
*** into an array of char. The max. length of this number is MAX_DIGITS.
*** The number is checked to contain only digits. If not the program exits.
*** Then the inputted number is converted into a big int by calling the
*** function strtobig_int().
*** After the conversion the tower is calculated by calling the functions
*** multiply(), print_big_int(), and copy_big_int() consecutively from 2 to
*** 9 and then again with divide() instead of multiply() from 2 to 9.
***
*/
int main(int argc, char *argv[])
{
	struct BigInt number;
	char userInput[MAX_DIGITS];

	printf("Pyramid of numbers\n\n");
	printf("Please enter a number: ");
	scanf("%s", userInput);

	strtobig_int(userInput, strlen(userInput), &number);

	//multiply
	struct BigInt result;
	int multiplicationFactor = 2;

	for (int i = 0; i < 8; i++)
	{
		print_big_int(&number);
		printf(" * %d = ", multiplicationFactor);
		multiply(&number, multiplicationFactor, &result);

		print_big_int(&result);
		printf("\n");

		number = result;
		multiplicationFactor++;
	}

	//divide
	int divisionFactor = 2;
	for (int i = 0; i < 8; i++)
	{
		divide(&number, divisionFactor, &result);
		print_big_int(&number);
		printf(" / %d = ", divisionFactor);

		print_big_int(&result);
		printf("\n");

		number = result;
		divisionFactor++;
	}

	return 0;
}

void reverse_big_int(struct BigInt *big_int)
{
	for (int i = 0; i < big_int->digits_count - 1; i++)
	{
		int tempOne = big_int->the_int[big_int->digits_count - i - 1];
		int tempTwo = big_int->the_int[i];
		big_int->the_int[i] = tempOne;
		big_int->the_int[big_int->digits_count - i - 1] = tempTwo;
	}
}

int strtobig_int(const char *str, int len, struct BigInt *big_int)
{
	int convertedDigits = 0;
	for (int i = 0; i < len; i++)
	{
		if (str[i] >= '0' && str[i] <= '9')
		{
			(*big_int).the_int[convertedDigits] = str[len - i - 1] - 48;
			convertedDigits++;
		}
	}

	big_int->digits_count = convertedDigits;
	return convertedDigits;
}

void copy_big_int(const struct BigInt *from, struct BigInt *to)
{
	*to = *from;
}

void multiply(const struct BigInt *big_int, int factor, struct BigInt *big_result)
{
	int overflow = 0;
	big_result->digits_count = big_int->digits_count;

	for (int i = big_int->digits_count - 1; i >= 0 && i < big_result->digits_count; i--)
	{
		int result = big_int->the_int[i] * factor + overflow;

		if (result > 9)
		{
			int temp = result / 10;
			if (i == 0)
			{
				big_result->the_int[i] = result % 10;
				big_result->digits_count++;

				//Swap digits
				for (int i = big_result->digits_count - 1 ; i > 0; i--) {
					big_result->the_int[i] = big_result->the_int[i - 1];
				}

				big_result->the_int[i] = temp;
			}
			else
			{
				big_result->the_int[i] = result % 10;
			}
			overflow = temp;
		}
		else
		{
			big_result->the_int[i] = result % 10;
			overflow = 0;
		}
	}
}

void divide(const struct BigInt *big_int, int divisor, struct BigInt *big_result)
{
	bool numberSet = false;
	int digits = 0;
    int overflow = 0;

    for(int i = 0; i < big_int->digits_count; i++)
	{
        int result = (big_int->the_int[i] + overflow) / divisor;

		if (result == 0 && numberSet)
		{
            big_result->the_int[digits] = result;
            digits++;
        }
		else if (result != 0)
		{
	    	numberSet = true;
	    	big_result->the_int[digits] = result;
	    	digits++;
        }

        overflow = (big_int->the_int[i] + overflow) % divisor;
        overflow *= 10;
    }

    big_result->digits_count = digits;
}

void print_big_int(const struct BigInt *big_int)
{
	char numberString[big_int->digits_count];

	for (int i = 0; i < big_int->digits_count; i++)
	{
		numberString[big_int->digits_count - i - 1] = ('0' + big_int->the_int[i]);
	}

	numberString[big_int->digits_count] = 0;

	printf("%s", numberString);
}
