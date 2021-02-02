#include <iostream>

int strlen(char *string)
{
    int string_length;

    for (string_length = 0; string[string_length]; string_length++);

    return string_length;
}

void reverse(char *string)
{
    int start;
    int end = strlen(string);
    char temp;

    for (start = 0; start < end/2; start++)
    {
	temp = string[start];
	string[start] = string[end - start - 1];
	string[end - start - 1] = temp;
    }
}

void to_binary(int decimal)
{
    char binary[32]; // 32 is size of intgeer
    int number;
    int i;
    int carry;

    if (decimal < 0)
    {
	for (i = 0, number = decimal; number != 0; number /= 2, i++)
	{
	    binary[i] = -1 * (number) % 2 + '0';
	}
	
	binary[i] = '\0';

	// invert the number
	for (i = 0; binary[i]; i++)
	{
	    if (binary[i] == '1')
	    {
		binary[i] = '0';
	    }
	    else
	    {
		binary[i] = '1';
	    }			    
	}

	for (i = 0, carry = 1; carry != 0; i++)
	{
	    if (binary[i] == '1' && carry == 1)
	    {
		binary[i] = '0';
	    }
	    else if (binary[i] == '0' && carry == 1)
	    {
		binary[i] = '1';
		carry = 0;
	    }
	}
	

	reverse(binary);
    }
    else
    {
	for (i = 0, number = decimal; number != 0; number /= 2, i++)
	{
	    binary[i] = (number) % 2 + '0';
	}
	
	binary[i] = '\0';
    
	reverse(binary);
    }
    
    std::cout << "Representation of decimal number " << decimal << " is " << binary << std::endl;
}

int main(int argc, char **argv)
{

    int a = 45;
    int b = -45;

    to_binary(a);
    to_binary(b);
    return 0;
}
