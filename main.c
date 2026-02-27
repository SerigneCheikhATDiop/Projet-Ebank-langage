#include "headers.h"

int main()
{
    int choice, nb;
    char numero[20];
    float montant;
    ACCOUNT *account;

    do
    {
        printf("\n========================================\n");
        printf("         BANQUE ELECTRONIQUE            \n");
        printf("========================================\n");
        printf("1.  Creation compte (Nouveau/Existant)\n");
        printf("2.  Liste de tous les comptes\n");
        printf("3.  Recherche compte par numero\n");
        printf("4.  Depot\n");
        printf("5.  Retrait\n");
        printf("6.  Liste de toutes les operations\n");
        printf("7.  Nombre total de comptes\n");
        printf("8.  Nombre total de clients\n");
        printf("9.  Liste des comptes par client\n");
        printf("10. Liste des operations par compte\n");
        printf("11. Liste des operations par type\n");
        printf("12. Nombre d'operations par compte\n");
        printf("13. Nombre d'operations par type\n");
        printf("14. Fermer un compte\n");
        printf("15. Quitter\n");
        printf("16. Generer PDF operations\n");
        printf("17. Generer PDF statistiques\n");
        printf("========================================\n");

        do {
            printf("Faites un choix (1-17) : ");
            scanf("%d", &choice);
        } while(choice < 1 || choice > 17);

        while(getchar() != '\n'); // nettoyage buffer

        printf("\n");

        switch(choice)
        {
        case 1:
            creerCompte();
            break;

        case 2:
            printf("=== LISTE DES COMPTES ===\n");
            listerComptes();
            break;

        case 3:
            printf("Numero de compte a rechercher : ");
            fgets(numero, sizeof(numero), stdin);
            numero[strcspn(numero, "\n")] = 0;

            account = rechercherCompteParNumero(numero);

            if(account != NULL) {
                printf("\n=== COMPTE TROUVE ===\n");
                printf("Numero : %s\n", account->numero);
                printf("Proprietaire : %s %s\n",
                       account->customer.firstname,
                       account->customer.lastname);
                printf("Telephone : %s\n", account->customer.phone);
                printf("Solde : %.2f\n", account->balance);
                printf("Statut : %s\n",
                       account->isClosed ? "FERME" : "ACTIF");

                free(account);
            } else {
                printf("Compte introuvable.\n");
            }
            break;

        case 4:
            printf("Numero de compte pour depot : ");
            fgets(numero, sizeof(numero), stdin);
            numero[strcspn(numero, "\n")] = 0;

            do {
                printf("Montant a deposer : ");
                scanf("%f", &montant);
                if(montant <= 0)
                    printf("Montant invalide.\n");
            } while(montant <= 0);

            while(getchar() != '\n');

            depot(numero, montant);
            break;

        case 5:
            printf("Numero de compte pour retrait : ");
            fgets(numero, sizeof(numero), stdin);
            numero[strcspn(numero, "\n")] = 0;

            do {
                printf("Montant a retirer : ");
                scanf("%f", &montant);
                if(montant <= 0)
                    printf("Montant invalide.\n");
            } while(montant <= 0);

            while(getchar() != '\n');

            retrait(numero, montant);
            break;

        case 6:
            listerOperations();
            break;

        case 7:
            nb = nombreComptes();
            if(nb != 0)
                printf("Nombre total de comptes : %d\n", nb);
            else
                printf("Aucun compte.\n");
            break;

        case 8:
            nb = nombreClients();
            if(nb != 0)
                printf("Nombre total de clients : %d\n", nb);
            else
                printf("Aucun client.\n");
            break;

        case 9:
            listerComptesParClient();
            break;

        case 10:
            listerOperationsParCompte();
            break;

        case 11:
            listerOperationsParType();
            break;

        case 12:
            nombreOperationsParCompte();
            break;

        case 13:
            nombreOperationsParType();
            break;

        case 14:
            fermerCompte();
            break;

        case 15:
            quitterApplication();
            return 0;

        case 16:
            printf("=== GENERATION PDF : OPERATIONS ===\n");
            listerOperationsParComptePDF();
            break;

        case 17:
            printf("=== GENERATION PDF : STATISTIQUES ===\n");
            nombreOperationsParComptePDF();
            break;
        }

        PAUSE
        CLEAR

    } while(1);

    return 0;
}
