#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "afficheur.h"


int main(int argc, char *argv[])
{
	char exiasaver[15] = {0}; //variable de type caractère qui fait la taille de 15 caractères
	FILE* statique = NULL;
	FILE* dynamique = NULL;
	scanf("%s",exiasaver);
	


	if(strcmp(exiasaver, "exiasaver") == 0)//Si on tape exiasaver
	{

		printf("lancer exiasaver"); //Lancer l'éxecutable ExiaSaver
		srand(time(NULL));
		int nbgen=rand()%3+1;    //générer un nombre random entre 1 et 3
		printf("%d\n",nbgen); // afficher le nombre random

		if(nbgen == 1)
		{
			statique = fopen("/home/vincent/Documents/screensaver/src/staticc.c","r");
			staticc();
		}

		if(nbgen ==2)
		{
			printf("dynamique");
			//dynamique = fopen("/home/vincent/Documents/screensaver/src/dynamic.c","r");
			//dynamic();
		}
		
		if(nbgen ==3)
		{
			printf("interactif");
		}
	}


	else if(strcmp(exiasaver, "-stat") == 0)  //Si commande ExiaSaver stats
	{
		printf("lancer historique");// lancer historique
	}

return 0;
}
