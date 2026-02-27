#ifndef HEADERS_H
#define HEADERS_H
#include "ebank.h"
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define FILE_ACCOUNTS "accounts.txt"
#define FILE_OPERATIONS "operations.txt"
#define FILE_CUSTOMERS "customers.txt"
#define CLEAR system("cls");
#define PAUSE system("pause");

/* ===== PROTOTYPES DES FONCTIONS ===== */

void creerCompte();
void listerComptes();
void listerComptesParClient();
void listerOperations();
void listerOperationsParCompte();
void listerOperationsParType();
void nombreOperationsParCompte();
void nombreOperationsParType();
void fermerCompte();
void quitterApplication();

void listerOperationsParComptePDF();
void nombreOperationsParComptePDF();

DATETIME getCurrentDateTime();
void afficherDateTime(DATETIME dt);

char *generateNumeroCompte();
char *generateNumeroOperation();

#endif
