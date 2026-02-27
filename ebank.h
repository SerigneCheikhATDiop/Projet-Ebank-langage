#ifndef HEADERS_H
#define HEADERS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// ================= STRUCTURES =================

typedef struct
{
    int jour;
    int mois;
    int annee;
    int heure;
    int minute;
    int seconde;
} DATETIME;


// ========== STRUCTURE CUSTOMER ==========
typedef struct
{
    char lastname[50];
    char firstname[50];
    char phone[20];
} CUSTOMER;


// ========== STRUCTURE ACCOUNT ==========
typedef struct
{
    char numero[45];
    CUSTOMER customer;
    float balance;
    int isClosed;
    DATETIME createdAt;
} ACCOUNT;


// ========== STRUCTURE OPERATION ==========
typedef struct
{
    char numero[45];
    char type[50];
    float amount;
    ACCOUNT account;
    DATETIME operationDate;
} OPERATION;


// ================= PROTOTYPES =================

// Fonctions generales
DATETIME getCurrentDateTime();
void afficherDateTime(DATETIME dt);
char *generateNumeroCompte();
char *generateNumeroOperation();

// Comptes
void creerCompte();
void creerCompteNouveauClient();
void creerCompteClientExistant();
void listerComptes();
ACCOUNT *rechercherCompteParNumero(char numero[]);
void afficherCompte(ACCOUNT acc);
void fermerCompte();
int nombreComptes();

// Clients
void saveCustomerInFile(char filename[], CUSTOMER customer);
CUSTOMER *rechercherClientParTelephone(char telephone[]);
CUSTOMER saisirNouveauClient();
void afficherClient(CUSTOMER client);
int nombreClients();

// Operations
void depot(char numeroCompte[], float montant);
void retrait(char numeroCompte[], float montant);
void listerOperations();
void listerOperationsParCompte();
void listerOperationsParType();
void nombreOperationsParCompte();
void nombreOperationsParType();
void afficherOperation(OPERATION op);

// Fichiers
long getFileSize(char filename[]);
void saveAccountInFile(char filename[], ACCOUNT acc);
void saveOperationInFile(char filename[], OPERATION op);

// PDF
void listerOperationsParComptePDF();
void nombreOperationsParComptePDF();

// Application
int quitterApplication();

#endif
