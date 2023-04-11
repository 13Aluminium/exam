// #include <stdio.h>
// #include <conio.h>

// int main()
// {
//     int numInDec, convertBase, i, divisorNum, base, somevar, array[10], num, decimalNumber;

//     printf("This is a code to convert any base to any base\n\n");

//     printf("Enter any base: ");
//     scanf("%d", &base);

//     printf("Enter a base you want to convert to: ");
//     scanf("%d", &convertBase);

//     printf("Enter a %d base number: ", base);
//     scanf("%d", &num);

//     switch (base)
//     {
//     case 10:
//         if (convertBase == 2)
//         {
//             for (i = 0; num > 0; i++)
//             {
//                 array[i] = num % base;
//                 num /= base;
//             }

//             for (i = i - 1; i >= 0; i--)
//             {
//                 // printf("Hello");
//                 printf("%d", array[i]);
//             }

//             decimalNumber = array[0] * 1 + array[1] * 2 + array[2] * 4 + array[3] * 8;
//             printf("Decimal number is: %d", decimalNumber);
//         }

//         else if (convertBase == 8)
//         {
//         }

//         break;

//     default:
//         break;
//     }

//     return 0;
// }

#include <stdio.h>
#include <string.h>
void baseconversion(char s[20], int, int);
int main()
{
    char s[20];
    int base1, base2;
    printf("Enter the number and base:");
    scanf("%s%d", s, &base1);
    printf("Enter the base to be converted:");
    scanf("%d", &base2);
    baseconversion(s, base1, base2);
}

void baseconversion(char s[20], int b1, int b2)
{
    int count = 0, r, digit, i, n = 0, b = 1;
    for (i = strlen(s) - 1; i >= 0; i--)
    {
        if (s[i] >= 'A' && s[i] <= 'Z')
        {
            digit = s[i] - '0' - 7;
        }
        else
        {
            digit = s[i] - '0';
        }
        n = digit * b + n;
        b = b * b1;
    }
    while (n != 0)
    {
        r = n % b2;
        digit = '0' + r;
        if (digit > '9')
        {
            digit += 7;
        }
        s[count] = digit;
        count++;
        n = n / b2;
    }
    for (i = count - 1; i >= 0; i--)
    {
        printf("%c", s[i]);
    }
    printf("\n");
}
