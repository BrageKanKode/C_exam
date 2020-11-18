#include "include/main.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <stdint.h>
#include <time.h>

typedef struct _CCD
{
    char digit[5];
    int convert;
    struct _CCD *p;
} CCD;

int ProcessCreditcardPaymentFIXED(int a, char *c, char *e, char *n, int printforloop);
int ProcessCreditcardPayment(int a, char *c, char *e, char *n);

int Backendprocesspayment(int a, int64_t c, CCD *p, const char *n, int b);

int main()
{
    printf("Check that 123x can be any number");
    ProcessCreditcardPaymentFIXED(11, "4242123014121991", "12/20", "dokf", 0);
    ProcessCreditcardPaymentFIXED(11, "4242123114121991", "12/20", "dokf", 0);
    ProcessCreditcardPaymentFIXED(11, "4242123214121991", "12/20", "dokf", 0);
    ProcessCreditcardPaymentFIXED(11, "4242123314121991", "12/20", "dokf", 0);
    ProcessCreditcardPaymentFIXED(11, "4242123414121991", "12/20", "dokf", 0);
    ProcessCreditcardPaymentFIXED(11, "4242123514121991", "12/20", "dokf", 0);
    ProcessCreditcardPaymentFIXED(11, "4242123614121991", "12/20", "dokf", 0);
    ProcessCreditcardPaymentFIXED(11, "4242123714121991", "12/20", "dokf", 0);
    ProcessCreditcardPaymentFIXED(11, "4242123814121991", "12/20", "dokf", 0);
    ProcessCreditcardPaymentFIXED(11, "4242123914121991", "12/20", "dokf", 0);
    printf("\n");

    printf("\nCheck that for loop i fixed ");
    ProcessCreditcardPaymentFIXED(11, "4242123914121991", "12/21", "dokf", 1);

    // Check dates
    printf("\n\nCheck that dates work \n12/21: ");
    ProcessCreditcardPaymentFIXED(11, "4242123914121991", "12/21", "dokf", 0);
    printf("\n12/19: ");
    ProcessCreditcardPaymentFIXED(11, "4242321114121991", "12/19", "dokf", 0);
    printf("01/20: ");
    ProcessCreditcardPaymentFIXED(11, "4242321114121991", "01/20", "dokf", 0);

    printf("\n\nOriginal \n");

    // original
    ProcessCreditcardPayment(11, "4242123914121991", "12/20", "dokf");
}

int ProcessCreditcardPaymentFIXED(int a, char *cardNumber, char *expireDate, char *n, int printforloop)
{

    int64_t llCreditcard = 0; /* C99 type, our compiler supports this... */
    char *piCardNumber = (char *)cardNumber;
    int j = 0;
    CCD *pc, *cc = (CCD *)malloc(sizeof(CCD));
    // Expire date function
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);

    time(&t);

    char buffer[50];
    char *buffer2;
    strcpy(buffer, expireDate);

    strtok_r(buffer, "/", &buffer2);

    int imonth = atoi(buffer);
    int iyear = atoi(buffer2);
    int icurrentyear = tm.tm_year - 100;
    int icurrentmonth = tm.tm_mon;

    if (iyear <= icurrentyear)
    {
        if (imonth < icurrentmonth || iyear < icurrentyear)
        {
            printf("Card is expired!\n");
            return 1;
        }
    }

    printf("\n");
    // Expiration function complete.

    if (!cc)
    {
        exit(1);
    }
    else
    {
        pc = cc;
    }
    memset(cc, 0, sizeof(CCD));

    /* Create 4 linked structures that holds one 4 digit
    segment of cardnumber: */
    while (piCardNumber[0])
    {
        pc->digit[j++] = piCardNumber++[0];

        if (strlen(pc->digit) == 4)
        {

            pc->p = (CCD *)malloc(sizeof(CCD));

            if (!pc->p)
            {
                exit(1);
            }
            else
            {
                memset(pc->p, 0, sizeof(CCD));
                pc = pc->p;
                j = 0;
            }
        }
    }
    /* Check that card starts with 4242, if not card is from
    another bank so we fail: */
    if (strcmp(cc->digit, "4242") != 0)
    {
        free(cc);
        return 6;
    }

    /* Calculate the cardnumber as a 64 bit integer: */
    for (j = 12, pc = cc; pc->p; pc = pc->p, j -= 4)
    {
        if (printforloop == 1)
        {
            printf("for loop: %d\n", j);
        }

        pc->convert = atoi(pc->digit);

        llCreditcard += ((int64_t)pc->convert) * pow(10, j);
    }

    /* If next section is 123x it is a bonus card with cash-back, we
    send type (x) to backend below: Set j to the type of bonus card */
    if (strncmp(cc->p->digit, "123", 3) == 0)
    {

        j = (cc->p->digit[3] - '0') % 10;
        printf("x = %d", j);
    }

    /* Call backend function: */
    Backendprocesspayment(a, llCreditcard, cc, n, j);

    free(cc);

    return 0;
}

// Tredje feil er at denne ikke fungerte. Måtte ha kode kropp
int Backendprocesspayment(int a, int64_t c, CCD *p, const char *n, int b)
{
    return 0;
}

int ProcessCreditcardPayment(int a, char *c, char *e, char *n)
{
    int64_t llCreditcard = 0; /* C99 type, our compiler supports this... */
    char *i = (char *)c;
    int j = 0;
    CCD *pc, *cc = (CCD *)malloc(sizeof(CCD));
    if (!cc)
        exit(1);
    else
        pc = cc;
    memset(cc, 0, sizeof(CCD));
    /* Create 4 linked structures that holds one 4 digit
 segment of cardnumber: */
    while (i[0])
    {
        pc->digit[j++] = i++[0];
        if (strlen(pc->digit) == 4)
        {
            pc->p = (CCD *)malloc(sizeof(CCD));
            if (!pc->p)
                exit(1);
            else
            {
                memset(pc->p, 0, sizeof(CCD));
                pc = pc->p;
                j = 0;
            }
        }
    }
    /* Check that card starts with 4242, if not card is from
 another bank so we fail: */
    if (strcmp(cc->digit, "4242") != 0)
    {
        free(cc);
        return 6;
    }
    //              ERROR
    /* Calculate the cardnumber as a 64 bit integer: */
    for (j = 12, pc = cc; pc; pc = pc->p, j -= 4)
    {
        printf("for loop: %d \n", j);
        pc->convert = atoi(pc->digit);
        llCreditcard += ((int64_t)pc->convert) * pow(10, j);
    }
    /* If next section is 123x it is a bonus card with cash-back, we
 send type (x) to backend below: Set j to the type of bonus card */
    if (strncmp(cc->p->digit, "123", 3) == 0)
    {
        j = cc->p->digit[cc->p->digit[3] / ((cc->p->digit[3] - '0') % 9)];
        printf("x = %d", j);
    }
    /* Call backend function: */
    Backendprocesspayment(a, llCreditcard, cc, n, j);
    free(cc);
    return 0;
}
