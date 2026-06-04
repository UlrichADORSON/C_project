#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define NBCHIFFRES 5
#define NBESSAIS 10

/* prototypes à définir */
int entree(int essai[], int dim);
void tirage(int ref[], int dim);
void analyse(int ref[], int essai[], int dim, int *NbPos, int *NbChif);/*Tous les prototypes definis ici sont globals*/

main() /*1er partie du code*/
{
    int ref[NBCHIFFRES], essai[NBCHIFFRES]; /*Definition des tableaux de comparaison des chiffres proposés et chiffres à deviner*/
    int NbPos, NbChif, Nbcoup, i, status;

    status = 0;
    tirage(ref, NBCHIFFRES);

    for (i = 1; i <= NBESSAIS; i++) /*Debut de la boucle pour calculer le nombre d'essai effectuer*/
    {
        Nbcoup = i;
        printf("\nNombre d'Essai: %d/%d\n", Nbcoup, NBESSAIS);

        entree(essai, NBCHIFFRES);
        if (entree == 0)
            continue;

        analyse(ref, essai, NBCHIFFRES, &NbPos, &NbChif); /*&NbPos et NbChif sont les coordonnées de l'element dans le tableau*/

        printf("Nombre de chiffres exacts bien places : %d\n", NbPos);
        printf("Nombre de chiffres exacts mal places  : %d\n", NbChif);

        if (NbPos == NBCHIFFRES) /*Comparaison des chiffres proposés par l'utilisateur et des chiffres générés*/
        {
            status = 1; /*Si les chifffres sont tous bien placés status = 1 qui veut dire vrai*/
            printf("\nBravo Boss! Vous avez trouve la combinaison MasterMind.\n"); /*%Message de reussite*/
            break;
        }
    }

    if (status != 1) /*Initialisation du message d'erreur en cas de defaite*/
    {
        printf("Vous n'avez pas trouve la bonne combinaison en %d essai\n", NBESSAIS); /*Message de defaite avec le nombre*/
        printf("La bonne combinaison etait : ");
        for (i = 0; i < NBCHIFFRES; i++)
            printf("%d", ref[i]);
        printf("\n");
    }
    getchar;
    return 0;
}

void tirage(int ref[], int dim) /*2ème partie du code*/
{
    int NbSec, vali, i;
    double valf;

    NbSec = time(NULL); /* nombre de secondes écoulées depuis le 1/1/70 */
    srand(NbSec); /* initialisation du générateur pseudo-aléatoire */
    vali = rand(); /* un coup pour rien. Le premier n'est pas aléatoire */

    for (i = 0; i < dim; i++)
    {
        valf = rand() / (RAND_MAX + 1.0); /* nombre flottant compris entre 0.0 et 0.9999999 */
        vali = (int)(valf * 10); /* nombre entier compris entre 0 et 9 */
        ref[i] = vali;
    }
}

int entree(int essai[], int dim) /*3ème partie du code*/
{
    unsigned int x, limite;
    int i;

    limite = pow(10, dim); /*Utilisation de la fonction puissance pour definir la limite de chiffre à proposer*/

    do{
    printf("\nEntrez votre combinaison de 5 chiffres : ", dim);
    scanf("%d", &x); /*Les chiffres proposés sont analyser grace à scanf dans x*/

    if(x >= limite){
        printf("Veuillez verifier que le nombre de chiffre saisie est de 5\n"); /*Message d'erreur en cas d'excès du nombre de chiffres entrés*/
    }
}
    while(x >= limite);
    for (i = dim - 1; i >= 0; i--)
    {
        essai[i] = x % 10;
        x = x / 10;
    }
    return 1;
}

void analyse(int ref[], int essai[], int dim, int *NbPos, int *NbChif) /*4ème partie du code*/
{
    int i, j, RefTmp[NBCHIFFRES];
    int EssaiTmp[NBCHIFFRES];

    *NbPos = 0;
    *NbChif = 0;

    for (i = 0; i < dim; i++)
    {
        RefTmp[i] = ref[i];
        EssaiTmp[i] = essai[i];
    }

    for (i = 0; i < dim; i++)
    {
        if (EssaiTmp[i] == RefTmp[i])
        {
            (*NbPos)++;
            RefTmp[i] = -1;
            EssaiTmp[i] = -2;
        }
    }

    for (i = 0; i < dim; i++)
    {
        for (j = 0; j < dim; j++)
        {
            if (EssaiTmp[i] == RefTmp[j])
            {
                (*NbChif)++;
                RefTmp[j] = -1;
                break;
            }
        }
    }
}

