#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 40

typedef struct {
    int num[2 * N];
    int isNegative;
} Number;

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
    if (notZero == 0 && ans.num[0] == 0)
        ans.isNegative = 0;

    if (ans.isNegative == 1)
        printf("-");
    for (int i = notZero; i >= 0; i--)
        printf("%d", ans.num[i]);
    printf("\n");
}

void isZero(Number *ans)
{
    int notZero = 0;
    for (int i = 2 * N - 1; i >= 0; i--) {
        if (ans->num[i] == 0)
            continue;
        else {
            notZero = i;
            break;
        }
    }
    if (notZero == 0 && ans->num[0] == 0)
        ans->isNegative = 0;
}

void subtract(Number *num1, Number *num2, Number *ans);

void add(Number *num1, Number *num2, Number *ans)
{
    if (num1->isNegative == num2->isNegative) {
        // 5 + 5, -5 + -5 -> -(5 + 5)

        for (int i = 0; i < N; i++) {
            int sum = num1->num[i] + num2->num[i] + ans->num[i];
            ans->num[i + 1] = sum / 10;
            ans->num[i] = sum % 10;
        }

        // for (int i = 0; i < N; i++) {
        //     ans->num[i + 1] += ans->num[i] / 10;
        //     ans->num[i] %= 10;
        // }

        if (num1->isNegative == 1) {
            ans->isNegative = (ans->isNegative + 1) % 2;
        }
    } else {
        if (num1->isNegative) {
            // -7 + 5 = 5 + -7 = 5 - +7
            num1->isNegative = (num1->isNegative + 1) % 2;
            subtract(num2, num1, ans);
        } else {
            // 5 + -7 = 5 - +7
            num2->isNegative = (num2->isNegative + 1) % 2;
            subtract(num1, num2, ans);
        }
    }

    isZero(ans);
}

int isLessThan(Number num1, Number num2)
{
    int notZero1 = 0;
    for (int i = 2 * N - 1; i >= 0; i--) {
        if (num1.num[i] == 0)
            continue;
        else {
            notZero1 = i;
            break;
        }
    }

    int notZero2 = 0;
    for (int i = 2 * N - 1; i >= 0; i--) {
        if (num2.num[i] == 0)
            continue;
        else {
            notZero2 = i;
            break;
        }
    }

    if (notZero1 < notZero2) {
        return 1;
    } else if (notZero1 > notZero2) {
        return 0;
    } else {
        for (int i = notZero1; i >= 0; i--) {
            if (num1.num[i] != num2.num[i]) {
                if (num1.num[i] < num2.num[i])
                    return 1;
                else
                    return 0;
            }
        }
        return 0;
    }

    return 0;
}

void subtract(Number *num1, Number *num2, Number *ans)
{
    // printNumber(*num1);
    // printNumber(*num2);

    if (num1->isNegative == num2->isNegative) {
        if (isLessThan(*num1, *num2) == 1) {
            // printf("Swap\n");
            ans->isNegative = (ans->isNegative + 1) % 2;
            subtract(num2, num1, ans);
            return;
        }

        // 7 - 5
        // -7 - -5 = -(7 - 5)
        int borrow[N + 1] = {0};
        for (int i = 0; i < N; i++) {
            int diff = borrow[i] + (num1->num[i] - num2->num[i]);

            if (diff < 0) {
                borrow[i + 1] = -1;
                diff += 10;
            }

            ans->num[i] = diff;
        }

        if (num1->isNegative == 1)
            ans->isNegative = (ans->isNegative + 1) % 2;
    } else {
        if (num1->isNegative == 1) {
            // -7 - 5 = -(7 + 5)
            ans->isNegative = (ans->isNegative + 1) % 2;
            num1->isNegative = 0;
            add(num1, num2, ans);
        } else {
            // 7 - -5 = 7 + 5
            num2->isNegative = 0;
            add(num1, num2, ans);
        }
    }

    isZero(ans);
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

    if (num1->isNegative != num2->isNegative)
        ans->isNegative = (ans->isNegative + 1) % 2;

    isZero(ans);
}

void convertFromStringToNumber(char str[], Number *num)
{
    int len = strlen(str);
    memset(num, 0, sizeof(int) * 2 * N);

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

        printf("\nAddition\n");
        convertFromStringToNumber(number1, &num1);
        convertFromStringToNumber(number2, &num2);

        ans.isNegative = 0;
        memset(ans.num, 0, sizeof(ans.num));
        add(&num1, &num2, &ans);
        printNumber(ans);

        printf("\nSubtraction\n");
        convertFromStringToNumber(number1, &num1);
        convertFromStringToNumber(number2, &num2);
        ans.isNegative = 0;
        memset(ans.num, 0, sizeof(ans.num));
        subtract(&num1, &num2, &ans);
        printNumber(ans);

        printf("\nMultiplication\n");
        convertFromStringToNumber(number1, &num1);
        convertFromStringToNumber(number2, &num2);
        ans.isNegative = 0;
        memset(ans.num, 0, sizeof(ans.num));
        multiply(&num1, &num2, &ans);
        printNumber(ans);
    }

    return 0;
}
