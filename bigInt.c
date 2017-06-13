
#include <stdio.h>
#include <string.h>

#define N 40

typedef struct {
    int num[N];
    int isNegative;
} Number;

void add(int num1[], int num2[], int ans[])
{
    for (int i = 0; i < N; i++) {
        int sum = num1[i] + num2[i];
        ans[i + 1] += sum / 10;
        ans[i] += sum % 10;
    }

    for (int i = 0; i < N; i++) {
        ans[i + 1] += ans[i] / 10;
        ans[i] %= 10;
    }
}

void subtract(int num1[], int num2[], int ans[])
{
    int borrow[N + 1] = {0};
    for (int i = 0; i < N; i++) {
        int diff = borrow[i] + (num1[i] - num2[i]);

        if (diff < 0) {
            borrow[i + 1] = -1;
            diff += 10;
        }

        ans[i] = diff;
    }
}

void multiply(int num1[], int num2[], int ans[])
{
    for (int i = 0; i < N; i++) {   /* num2 */
        for (int j = 0; j < N; j++) { /* num1 */
            int product = num1[j] * num2[i];
            ans[i + j] += product;
        }
    }

    for (int i = 0; i < 2 * N - 1; i++) {
        ans[i + 1] += ans[i] / 10;
        ans[i] %= 10;
    }
}

void printNumber(int ans[])
{
    int notZero = 0;
    for (int i = 2 * N - 1; i >= 0; i--) {
        if (ans[i] == 0)
            continue;
        else {
            notZero = i;
            break;
        }
    }

    for (int i = notZero; i >= 0; i--)
        printf("%d", ans[i]);
    printf("\n");
}

void convertFromStringToNumberArray(char str[], int num[])
{
    int len = strlen(str);
    for (int i = 0; i < len; i++)
        num[i] = str[len - i - 1] - '0';
}

int main()
{
    char number1[2 * N], number2[2 * N];
    while (scanf("%s %s", number1, number2) != EOF) {
        int num1[2 * N] = {0}, num2[2 * N] = {0};
        convertFromStringToNumberArray(number1, num1);
        convertFromStringToNumberArray(number2, num2);

        for (int i = 2 * N - 1; i >= 0; i--)
            printf("%d", num1[i]);
        printf("\n");

        for (int i = 2 * N - 1; i >= 0; i--)
            printf("%d", num2[i]);
        printf("\n");

        int ans[2 * N] = {0}; /* no more overflow issue */
        add(num1, num2, ans);
        printNumber(ans);

        memset(ans, 0, sizeof(ans));
        subtract(num1, num2, ans);
        printNumber(ans);

        memset(ans, 0, sizeof(ans));
        multiply(num1, num2, ans);
        printNumber(ans);
    }

    return 0;
}
