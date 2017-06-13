
#include <stdio.h>
#include <string.h>

#define N 40

typedef struct {
    int num[2 * N];
    int isNegative;
} Number;

void add(Number *num1, Number *num2, Number *ans)
{
    for (int i = 0; i < N; i++) {
        int sum = num1->num[i] + num2->num[i];
        ans->num[i + 1] += sum / 10;
        ans->num[i] += sum % 10;
    }

    for (int i = 0; i < N; i++) {
        ans->num[i + 1] += ans->num[i] / 10;
        ans->num[i] %= 10;
    }
}

void subtract(Number *num1, Number *num2, Number *ans)
{
    int borrow[N + 1] = {0};
    for (int i = 0; i < N; i++) {
        int diff = borrow[i] + (num1->num[i] - num2->num[i]);

        if (diff < 0) {
            borrow[i + 1] = -1;
            diff += 10;
        }

        ans->num[i] = diff;
    }
}

void multiply(Number *num1, Number *num2, Number *ans)
{
    for (int i = 0; i < N; i++) {   /* num2 */
        for (int j = 0; j < N; j++) { /* num1 */
            int product = num1->num[j] * num2->num[i];
            ans->num[i + j] += product;
        }
    }

    for (int i = 0; i < 2 * N - 1; i++) {
        ans->num[i + 1] += ans->num[i] / 10;
        ans->num[i] %= 10;
    }
}

void printNumber(Number ans)
{
    int notZero = 0;
    for (int i = 2 * N - 1; i >= 0; i--) {
        if (ans.num[i] == 0)
            continue;
        else {
            notZero = i;
            break;
        }
    }

    if (ans.isNegative == 1)
        printf("-");
    for (int i = notZero; i >= 0; i--)
        printf("%d", ans.num[i]);
    printf("\n");
}

void convertFromStringToNumber(char str[], Number *num)
{
    int len = strlen(str);
    if (str[0] == '-')
        num->isNegative = 1;
    else
        num->isNegative = 0;

    // -1234
    for (int i = 0; i < len - num->isNegative; i++)
        num->num[i] = str[len - i - 1] - '0';
}

int main()
{
    char number1[2 * N], number2[2 * N];
    while (scanf("%s %s", number1, number2) != EOF) {
        Number num1, num2, ans;
        convertFromStringToNumber(number1, &num1);
        convertFromStringToNumber(number2, &num2);

        printNumber(num1);
        printNumber(num2);

        printf("\nAddition\n");
        ans.isNegative = 0;
        memset(ans.num, 0, sizeof(ans.num));
        add(&num1, &num2, &ans);
        printNumber(ans);

        printf("\nSubtraction\n");
        ans.isNegative = 0;
        memset(ans.num, 0, sizeof(ans.num));
        subtract(&num1, &num2, &ans);
        printNumber(ans);

        printf("\nMultiplication\n");
        ans.isNegative = 0;
        memset(ans.num, 0, sizeof(ans.num));
        multiply(&num1, &num2, &ans);
        printNumber(ans);
    }

    return 0;
}
