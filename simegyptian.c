/*******************************************************************************

 Graphical program for simulate the ADT Egyptian Fraction


*******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "fraction.h"  /* ADT Fraction Interface file */
#include "egyptianfraction.h"   /* ADT Egyptian Fraction Interface file */

#define MAX_FRACTIONS 9
#define MAX_OPTIONS 6

void Menu (void);
void ReadOption (int *);
void ReadFractionIndex (int *, char *);
int ActiveFraction (PtEgyptianFraction *, int);
int NotActiveFraction (PtEgyptianFraction *, int);
void WriteFractionErrorMessage (char *);
void WriteEgyptianErrorMessage (char *);
void ReadFraction (char *, PtFraction *);
void WriteEgyptianFraction (PtEgyptianFraction);
void WriteResult (int, int, int);
void WriteFraction (PtFraction);
void WriteResultExist (PtFraction, int, int);

int main (void)
{
  PtEgyptianFraction FractionArray[MAX_FRACTIONS]; PtFraction InputFraction, OutputFraction;
  int Option, Index, Fraction1, Fraction2, Equals, Exist;

  for (Index = 0; Index < MAX_FRACTIONS; Index++) FractionArray[Index] = NULL;
  
  do
  {
    /* cleaning the screen and presenting the menu */
    Menu ();

    /* initializing the error */
    FractionClearError ();

    /* presenting the active egyptian fractions */
    for (Index = 0; Index < MAX_FRACTIONS; Index++)
      if (FractionArray[Index] != NULL)
      {
        printf ("\e[1m\e[%d;43f", 5+Index);
		WriteEgyptianFraction (FractionArray[Index]);
        printf ("\e[0m");
      }

    /* read option from the user */
    ReadOption (&Option);

    switch (Option)
    {
        case 1 :  ReadFractionIndex (&Fraction1, "egyptian fraction");
                  if (ActiveFraction (FractionArray, Fraction1)) break;
                  ReadFraction ("conversion to egyptian", &InputFraction);
                  if (FractionError ()) { WriteFractionErrorMessage ("The fraction input"); break; }
                  FractionArray[Fraction1] = EgyptianFractionCreate (InputFraction);
                  if (EgyptianFractionError ()) WriteEgyptianErrorMessage ("The creation");
                  FractionDestroy (&InputFraction);
                  break;

        case 2 :  ReadFractionIndex (&Fraction1, "origin egyptian fraction");
                  if (NotActiveFraction (FractionArray, Fraction1)) break;
                  do
                  {
                    ReadFractionIndex (&Fraction2, "destination egyptian fraction");
                  } while (Fraction2 == Fraction1);
                  if (ActiveFraction (FractionArray, Fraction2)) break;
                  FractionArray[Fraction2] = EgyptianFractionCopy (FractionArray[Fraction1]);
                  if (EgyptianFractionError ()) WriteEgyptianErrorMessage ("The copy");
                  break;

        case 3 :  ReadFractionIndex (&Fraction1, "egyptian fraction");
                  if (NotActiveFraction (FractionArray, Fraction1)) break;
                  OutputFraction = EgyptianFractionToFraction (FractionArray[Fraction1]);
                  if (EgyptianFractionError ()) WriteEgyptianErrorMessage ("The deconversion");
                  else
				  {
				  	WriteFraction (OutputFraction);
				  	FractionDestroy (&OutputFraction);
				  }
                  break;

        case 4 :  ReadFractionIndex (&Fraction1, "first egyptian fraction");
                  if (NotActiveFraction (FractionArray, Fraction1)) break;
                  do
                  {
                    ReadFractionIndex (&Fraction2, "second egyptian fraction");
                  } while (Fraction2 == Fraction1);
                  if (NotActiveFraction (FractionArray, Fraction2)) break;
                  Equals = EgyptianFractionEquals (FractionArray[Fraction1], FractionArray[Fraction2]);
                  if (EgyptianFractionError ()) WriteEgyptianErrorMessage ("The comparasion");
                  else WriteResult (Fraction1, Fraction2, Equals);
                  break;

        case 5 :  ReadFractionIndex (&Fraction1, "egyptian fraction");
                  if (NotActiveFraction (FractionArray, Fraction1)) break;
                  ReadFraction ("existence verification", &InputFraction);
                  if (FractionError ()) { WriteFractionErrorMessage ("The fraction input"); break; }
                  Exist = EgyptianFractionBelongs (FractionArray[Fraction1], InputFraction);
                  if (EgyptianFractionError ()) WriteEgyptianErrorMessage ("The existence");
                  WriteResultExist (InputFraction, Fraction1, Exist);
                  FractionDestroy (&InputFraction);
                  break;

        case 6 :  ReadFractionIndex (&Fraction1, "egyptian fraction");
                  if (NotActiveFraction (FractionArray, Fraction1)) break;
                  EgyptianFractionDestroy (&FractionArray[Fraction1]);
                  if (EgyptianFractionError ()) WriteEgyptianErrorMessage ("The elimination");
                  break;
    }
  } while (Option != 0);

  for (Index = 0; Index < MAX_FRACTIONS; Index++) 
    if (FractionArray[Index] != NULL) EgyptianFractionDestroy (&FractionArray[Index]);

  printf ("\e[26;1f");

  return EXIT_SUCCESS;
}

void Menu (void)
{
  system ("clear");

  printf("\e[2;1f~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
  printf("\e[3;1f|           Graphical Program for Simulate Operations with Egyptian Fractions           |\n");
  printf("\e[4;1f~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
  printf("\e[5;1f| 1 - Create an egyptian fraction | F 0 =                                               |\n");
  printf("\e[6;1f| 2 - Copy an egyptian fraction   | F 1 =                                               |\n");
  printf("\e[7;1f| 3 - Deconverte to fraction      | F 2 =                                               |\n");
  printf("\e[8;1f| 4 - Compare egyptian fractions  | F 3 =                                               |\n");
  printf("\e[9;1f| 5 - Exist in egyptian fraction  | F 4 =                                               |\n");
  printf("\e[10;1f| 6 - Erase an egyptian fraction  | F 5 =                                               |\n");
  printf("\e[11;1f| 0 - Terminate program           | F 6 =                                               |\n");
  printf("\e[12;1f|~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~| F 7 =                                               |\n");
  printf("\e[13;1f| Option ->                       | F 8 =                                               |\n");
  printf("\e[14;1f~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
  printf("\e[15;1f|                             Window for Data Acquisition                               |\n");
  printf("\e[16;1f~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
  printf("\e[17;1f|                                                                                       |\n");
  printf("\e[18;1f~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
  printf("\e[19;1f|                         Window for Error Messages and Results                         |\n");
  printf("\e[20;1f~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
  printf("\e[21;1f|                                                                                       |\n");
  printf("\e[22;1f|                                                                                       |\n");
  printf("\e[23;1f|                                                                                       |\n");
  printf("\e[24;1f~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
}

void ReadOption (int *poption)
{
  do
  {  
    printf("\e[13;1f| Option ->                       |");
    printf("\e[13;13f"); scanf ("%d", poption);
    scanf ("%*[^\n]"); scanf ("%*c");
  } while (*poption < 0 || *poption > MAX_OPTIONS);
}

void ReadFractionIndex (int *pnf, char *pmsg)
{
  int msglen = strlen (pmsg);

  do
  {
    *pnf = -1;
    printf("\e[17;1f| Index of %s ->                          ", pmsg);
    printf("\e[17;%df", 16+msglen); scanf ("%d", pnf);
    scanf ("%*[^\n]"); scanf ("%*c");
  } while (*pnf < 0 || *pnf >= MAX_FRACTIONS);
}

int ActiveFraction (PtEgyptianFraction pnfarray[], int pnf)
{
  char car;

  if (pnfarray[pnf] != NULL)
  {
    do
    {
      printf("\e[1m\e[21;1f| The fraction %d already exist!                    ", pnf);
      printf("\e[0m\e[22;1f| Wish to erase it (y/n)? ");
      scanf ("%c", &car); car = tolower (car);
      scanf ("%*[^\n]"); scanf ("%*c");
    } while (car != 'n' && car != 's');

    if (car == 's') { EgyptianFractionDestroy (&pnfarray[pnf]); return 0; }
    else return 1;
  }
  else return 0;
}

int NotActiveFraction (PtEgyptianFraction pnfarray[], int pnf)
{
  if (pnfarray[pnf] == NULL)
  {
    printf("\e[1m\e[21;1f| The fraction %d does not exist!                     ", pnf);
    printf("\e[0m\e[22;1f| Press a key to continue ");
    scanf ("%*[^\n]"); scanf ("%*c");
    return 1;
  }
  else return 0;
}

void WriteFractionErrorMessage (char *pmsg)
{
  printf("\e[21;1f| %s of fractions was not executed because", pmsg);
  printf("\e[22;1f| \e[1m%s", FractionErrorMessage ());
  printf("\e[0m\e[23;1f| Press a key to continue ");
  scanf ("%*[^\n]"); scanf ("%*c");
}

void WriteEgyptianErrorMessage (char *pmsg)
{
  printf("\e[21;1f| %s of fractions was not executed because", pmsg);
  printf("\e[22;1f| \e[1m%s", EgyptianFractionErrorMessage ());
  printf("\e[0m\e[23;1f| Press a key to continue ");
  scanf ("%*[^\n]"); scanf ("%*c");
}

void ReadFraction (char *msg, PtFraction *pf)
{
  int VNum, VDen; int Status;

  printf("\e[1m\e[21;1f| Fraction reading for %s \e[0m", msg);

  do
  {
    printf("\e[17;1f| Numerator of fraction ->                      ");
    printf("\e[17;28f"); Status = scanf ("%d", &VNum);
    scanf ("%*[^\n]"); scanf ("%*c");
  } while (!Status);

  do
  {
    printf("\e[17;1f| Denominator of fraction ->                ");
    printf("\e[17;30f"); Status = scanf ("%d", &VDen);
    scanf ("%*[^\n]"); scanf ("%*c");
  } while (!Status || VDen == 0);

  *pf = FractionCreate (VNum, VDen);
}

void WriteEgyptianFraction (PtEgyptianFraction pegyptian)
{
  PtFraction fraction; char *Str;
  int n = EgyptianFractionGetSize (pegyptian);
	
  for (int i = 0; i < n-1; i++)
    {
      fraction = EgyptianFractionGetPos (pegyptian, i);
      Str = FractionToString (fraction);
      printf ("%s + ", Str);
      free (Str);
	}
  fraction = EgyptianFractionGetPos (pegyptian, n-1);
  Str = FractionToString (fraction);
  printf ("%s", Str);
  free (Str);
  if (!EgyptianFractionIsComplete (pegyptian)) printf (" + ...");
}

void WriteResult (int pfrac1, int pfrac2, int pres)
{
  if (pres) printf("\e[21;1f| \e[1megyptian fractions %d and %d are qual ", pfrac1, pfrac2);
  else printf("\e[21;1f| \e[1megyptian fractions %d and %d are different ", pfrac1, pfrac2);
  printf("\e[0m\e[22;1f| Press a key to continue ");
  scanf ("%*[^\n]"); scanf ("%*c");
}

void WriteFraction (PtFraction pfraction)
{
  char * Str = FractionToString (pfraction);
  printf("\e[21;1f| \e[1mfraction result = %s", Str);
  printf("\e[0m\e[22;1f| Press a key to continue ");
  scanf ("%*[^\n]"); scanf ("%*c");
  free (Str);
}

void WriteResultExist (PtFraction pfraction, int pfrac1, int pexist)
{
  char * Str = FractionToString (pfraction);
  if (pexist) printf("\e[21;1f| \e[1mthe fraction %s exist in egyptian fraction %d              ", Str, pfrac1);
  else printf("\e[21;1f| \e[1mthe fraction %s does not exist in egyptian fraction %d            ", Str, pfrac1);
  printf("\e[0m\e[22;1f| Press a key to continue ");
  scanf ("%*[^\n]"); scanf ("%*c");
  free (Str);
}