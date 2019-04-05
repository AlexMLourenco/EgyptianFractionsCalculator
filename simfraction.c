/*******************************************************************************

 Graphical program for simulate the ADT Fraction


*******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "fraction.h"  /* ADT Interface file */

#define MAX_FRACTIONS 12
#define MAX_OPTIONS 9

void Menu (void);
void ReadOption (int *);
void ReadFractionIndex (int *, char *);
int ActiveFraction (PtFraction *, int);
int NotActiveFraction (PtFraction *, int);
void WriteErrorMessage (char *);
void ReadFraction (PtFraction *);
void WriteFraction (PtFraction);
void WriteResult (int, int, int);

int main (void)
{
  PtFraction FractionArray[MAX_FRACTIONS];
  int Option, Index, Fraction1, Fraction2, Fraction3, Equals; char *Str;

  for (Index = 0; Index < MAX_FRACTIONS; Index++) FractionArray[Index] = NULL;
  
  do
  {
    /* cleaning the screen and presenting the menu */
    Menu ();

    /* initializing the error */
    FractionClearError ();

    /* presenting the active fractions */
    for (Index = 0; Index < MAX_FRACTIONS; Index++)
      if (FractionArray[Index] != NULL)
      {
        printf ("\e[1m\e[%d;53f", 5+Index);
		/* WriteFraction (FractionArray[Index]); */
        Str = FractionToString (FractionArray[Index]);
        printf ("%s", Str); printf ("\e[0m");
        free (Str);
      }

    /* read option from the user */
    ReadOption (&Option);

    switch (Option)
    {
        case 1 :  ReadFractionIndex (&Fraction1, "fraction");
                  if (ActiveFraction (FractionArray, Fraction1)) break;
                  ReadFraction (&FractionArray[Fraction1]);
                  if (FractionError ()) WriteErrorMessage ("The creation");
                  break;

        case 2 :  ReadFractionIndex (&Fraction1, "first fraction");
                  ReadFractionIndex (&Fraction2, "second fraction");
                  do
                  {
                    ReadFractionIndex (&Fraction3, "sum fraction");
                  } while (Fraction3 == Fraction1 || Fraction3 == Fraction2);
                  if (ActiveFraction (FractionArray, Fraction3)) break;
                  FractionArray[Fraction3] = FractionAddition (FractionArray[Fraction1], FractionArray[Fraction2]);
                  if (FractionError ()) WriteErrorMessage ("The addition");
                  break;

        case 3 :  ReadFractionIndex (&Fraction1, "first fraction");
                  ReadFractionIndex (&Fraction2, "second fraction");
                  do
                  {
                    ReadFractionIndex (&Fraction3, "difference fraction");
                  } while (Fraction3 == Fraction1 || Fraction3 == Fraction2);
                   if (ActiveFraction (FractionArray, Fraction3)) break;
                   FractionArray[Fraction3] = FractionSubtraction (FractionArray[Fraction1], FractionArray[Fraction2]);
                   if (FractionError ()) WriteErrorMessage ("The subtraction");
                   break;

        case 4 :  ReadFractionIndex (&Fraction1, "first fraction");
                  ReadFractionIndex (&Fraction2, "second fraction");
                  do
                  {
                    ReadFractionIndex (&Fraction3, "product fraction");
                  } while (Fraction3 == Fraction1 || Fraction3 == Fraction2);
                  if (ActiveFraction (FractionArray, Fraction3)) break;
                  FractionArray[Fraction3] = FractionMultiplication (FractionArray[Fraction1], FractionArray[Fraction2]);
                  if (FractionError ()) WriteErrorMessage ("The multiplication");
                  break;

        case 5 :  ReadFractionIndex (&Fraction1, "first fraction");
                  ReadFractionIndex (&Fraction2, "second fraction");
                  do
                  {
                    ReadFractionIndex (&Fraction3, "quotient fraction");
                  } while (Fraction3 == Fraction1 || Fraction3 == Fraction2);
                  if (ActiveFraction (FractionArray, Fraction3)) break;
                  FractionArray[Fraction3] = FractionDivision (FractionArray[Fraction1], FractionArray[Fraction2]);
                  if (FractionError ()) WriteErrorMessage ("The division");
                  break;

        case 6 :  ReadFractionIndex (&Fraction1, "origin fraction");
                  if (NotActiveFraction (FractionArray, Fraction1)) break;
                  do
                  {
                    ReadFractionIndex (&Fraction2, "destination fraction");
                  } while (Fraction2 == Fraction1);
                  if (ActiveFraction (FractionArray, Fraction2)) break;
                  FractionArray[Fraction2] = FractionCopy (FractionArray[Fraction1]);
                  if (FractionError ()) WriteErrorMessage ("The copy");
                  break;
        
        case 7 :  ReadFractionIndex (&Fraction1, "origin fraction");
                  if (NotActiveFraction (FractionArray, Fraction1)) break;
                  do
                  {
                    ReadFractionIndex (&Fraction2, "destination fraction");
                  } while (Fraction2 == Fraction1);
                  if (ActiveFraction (FractionArray, Fraction2)) break;
                  FractionArray[Fraction2] = FractionSymmetrical (FractionArray[Fraction1]);
                  if (FractionError ()) WriteErrorMessage ("The symmetrical");
                  break;
        
        case 8 :  ReadFractionIndex (&Fraction1, "first fraction");
                  if (NotActiveFraction (FractionArray, Fraction1)) break;
                  do
                  {
                    ReadFractionIndex (&Fraction2, "second fraction");
                  } while (Fraction2 == Fraction1);
                  if (NotActiveFraction (FractionArray, Fraction2)) break;
                  Equals = FractionCompareTo (FractionArray[Fraction1], FractionArray[Fraction2]);
                  if (FractionError ()) WriteErrorMessage ("The comparasion");
                  else WriteResult (Fraction1, Fraction2, Equals);
                  break;

        case 9 :  ReadFractionIndex (&Fraction1, "fraction");
                  if (NotActiveFraction (FractionArray, Fraction1)) break;
                  FractionDestroy (&FractionArray[Fraction1]);
                  if (FractionError ()) WriteErrorMessage ("The elimination");
                  break;
    }
  } while (Option != 0);

  for (Index = 0; Index < MAX_FRACTIONS; Index++) 
    if (FractionArray[Index] != NULL) FractionDestroy (&FractionArray[Index]);

  printf ("\e[28;1f");

  return EXIT_SUCCESS;
}

void Menu (void)
{
  system ("clear");

  printf("\e[2;1f~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
  printf("\e[3;1f|           Graphical Program for Simulate Operations with Fractions           |\n");
  printf("\e[4;1f~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
  printf("\e[5;1f| 1 - Create a fraction        | Fraction  0 =                                 |\n");
  printf("\e[6;1f| 2 - Add fractions            | Fraction  1 =                                 |\n");
  printf("\e[7;1f| 3 - Subtract fractions       | Fraction  2 =                                 |\n");
  printf("\e[8;1f| 4 - Multiply fractions       | Fraction  3 =                                 |\n");
  printf("\e[9;1f| 5 - Divide fractions         | Fraction  4 =                                 |\n");
  printf("\e[10;1f| 6 - Copy a fraction          | Fraction  5 =                                 |\n");
  printf("\e[11;1f| 7 - Symmetrical fraction     | Fraction  6 =                                 |\n");  
  printf("\e[12;1f| 8 - Compare fractions        | Fraction  7 =                                 |\n");
  printf("\e[13;1f| 9 - Erase a fraction         | Fraction  8 =                                 |\n");
  printf("\e[14;1f| 0 - Terminate program        | Fraction  9 =                                 |\n");
  printf("\e[15;1f|~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~| Fraction 10 =                                 |\n");
  printf("\e[16;1f| Option->                     | Fraction 11 =                                 |\n");
  printf("\e[17;1f~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~-~\n");
  printf("\e[18;1f|                         Window for Data Acquisition                          |\n");
  printf("\e[19;1f~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
  printf("\e[20;1f|                                                                              |\n");
  printf("\e[21;1f~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
  printf("\e[22;1f|                     Window for Error Messages and Results                    |\n");
  printf("\e[23;1f~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
  printf("\e[24;1f|                                                                              |\n");
  printf("\e[25;1f|                                                                              |\n");
  printf("\e[26;1f|                                                                              |\n");
  printf("\e[27;1f~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
}

void ReadOption (int *poption)
{
  do
  {  
    printf("\e[16;1f| Option ->                    |");
    printf("\e[16;13f"); scanf ("%d", poption);
    scanf ("%*[^\n]"); scanf ("%*c");
  } while (*poption < 0 || *poption > MAX_OPTIONS);
}

void ReadFractionIndex (int *pnf, char *pmsg)
{
  int msglen = strlen (pmsg);

  do
  {
    *pnf = -1;
    printf("\e[20;1f| Index of %s ->                          ", pmsg);
    printf("\e[20;%df", 16+msglen); scanf ("%d", pnf);
    scanf ("%*[^\n]"); scanf ("%*c");
  } while (*pnf < 0 || *pnf >= MAX_FRACTIONS);
}

int ActiveFraction (PtFraction pnfarray[], int pnf)
{
  char car;

  if (pnfarray[pnf] != NULL)
  {
    do
    {
      printf("\e[1m\e[24;1f| The fraction %d already exist!                     ", pnf);
      printf("\e[0m\e[25;1f| Wish to erase it (y/n)? ");
      scanf ("%c", &car); car = tolower (car);
      scanf ("%*[^\n]"); scanf ("%*c");
    } while (car != 'n' && car != 'y');

    if (car == 'y') { FractionDestroy (&pnfarray[pnf]); return 0; }
    else return 1;
  }
  else return 0;
}

int NotActiveFraction (PtFraction pnfarray[], int pnf)
{
  if (pnfarray[pnf] == NULL)
  {
    printf("\e[1m\e[24;1f| The fraction %d does not exist!                     ", pnf);
    printf("\e[0m\e[25;1f| Press a key to continue ");
    scanf ("%*[^\n]"); scanf ("%*c");
    return 1;
  }
  else return 0;
}

void WriteErrorMessage (char *pmsg)
{
  printf("\e[24;1f| %s of fractions was not executed because", pmsg);
  printf("\e[25;1f| \e[1m%s", FractionErrorMessage ());
  printf("\e[0m\e[26;1f| Press a key to continue ");
  scanf ("%*[^\n]"); scanf ("%*c");
}

void ReadFraction (PtFraction *pf)
{
  int VNum, VDen; int Status;

  do
  {
    printf("\e[20;1f| Numerator of fraction ->                      ");
    printf("\e[20;28f"); Status = scanf ("%d", &VNum);
    scanf ("%*[^\n]"); scanf ("%*c");
  } while (!Status);

  do
  {
    printf("\e[20;1f| Denominator of fraction ->                ");
    printf("\e[20;30f"); Status = scanf ("%d", &VDen);
    scanf ("%*[^\n]"); scanf ("%*c");
  } while (!Status || VDen == 0);

  *pf = FractionCreate (VNum, VDen);
}

void WriteFraction (PtFraction pf)
{
  if (pf != NULL) printf ("%d / %d", FractionGetNumerator (pf),  FractionGetDenominator (pf));
}

void WriteResult (int pfrac1, int pfrac2, int pres)
{
/*
  if (pres) printf("\e[24;1f| \e[1mequal fractions \e[0m");
  else printf("\e[24;1f| \e[1mdifferent fractions \e[0m");
 */
  if (pres < 0) printf("\e[24;1f| \e[1mfraction %d is smaller than fraction %d \e[0m", pfrac1, pfrac2);
  else if (pres > 0) printf("\e[24;1f| \e[1mfraction %d is bigger than fraction %d \e[0m", pfrac1, pfrac2);
       else printf("\e[24;1f| \e[1mequal fractions %d and %d \e[0m", pfrac1, pfrac2);
  printf("\e[0m\e[25;1f| Press a key to continue ");
  scanf ("%*[^\n]"); scanf ("%*c");
}