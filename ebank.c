#include "headers.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

#ifdef _WIN32
#define strcasecmp _stricmp
#endif

/* ===================== DATE & HEURE ===================== */

DATETIME getCurrentDateTime()
{
    DATETIME dt;
    time_t t = time(NULL);
    struct tm *tm_info = localtime(&t);

    if (tm_info == NULL)
    {
        printf("Erreur recuperation date.\n");
        exit(1);
    }

    dt.jour    = tm_info->tm_mday;
    dt.mois    = tm_info->tm_mon + 1;
    dt.annee   = tm_info->tm_year + 1900;
    dt.heure   = tm_info->tm_hour;
    dt.minute  = tm_info->tm_min;
    dt.seconde = tm_info->tm_sec;

    return dt;
}

void afficherDateTime(DATETIME dt)
{
    printf("%02d/%02d/%04d %02d:%02d:%02d\n",
           dt.jour,
           dt.mois,
           dt.annee,
           dt.heure,
           dt.minute,
           dt.seconde);
}

/* ===================== GENERATION NUMEROS ===================== */

char *generateNumeroCompte()
{
    char *numero = (char *)malloc(20);
    if (numero == NULL)
    {
        printf("Erreur allocation memoire.\n");
        exit(1);
    }

    long taille = getFileSize(FILE_ACCOUNTS);

    int nb = (taille <= 0)
             ? 1
             : (int)(taille / sizeof(ACCOUNT)) + 1;

    sprintf(numero, "CPT-%03d", nb);

    return numero;
}

char *generateNumeroOperation()
{
    char *numero = (char *)malloc(20);
    if (numero == NULL)
    {
        printf("Erreur allocation memoire.\n");
        exit(1);
    }

    long taille = getFileSize(FILE_OPERATIONS);

    int nb = (taille <= 0)
             ? 1
             : (int)(taille / sizeof(OPERATION)) + 1;

    sprintf(numero, "OP-%03d", nb);

    return numero;
}
