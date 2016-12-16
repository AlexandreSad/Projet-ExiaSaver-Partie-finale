#include <stdio.h>
#include <stdlib.h>
#include <time.h>


int main(int argc, char *argv[])
{
    int c;
    int NombreDeFoisStatique = 0;
    int NombreDeFoisDynamque = 0;
    int NombreDeFoisInteractif = 0;
    int ExiaTermsaver_aleatoir = 0;
    int imagestatic;
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);

    FILE* fichier = NULL;
    fichier = fopen("Historique.txt", "a"); //fichier "Historique" ouvert en mode ajout


    if (fichier != NULL)// si fichier existe bien
    {




            srand(time(NULL));
            ExiaTermsaver_aleatoir = rand() % (3-1+1) + 1;// génère un nombre aléatoie entre 1 et 3 et l'affecte à la variable la variable



            if(ExiaTermsaver_aleatoir == 1) // si le nombre générer =1
            {



                 srand(time(NULL));
                 imagestatic = rand() % (5-1+1) + 1; // génère un nombre aléatoire entre 1 et 5
                 if(imagestatic == 1)
                        {
                          fprintf(fichier,"%d/%d/%d %d:%d:%d;1;ex1.pbm\n", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
                        }

                 if(imagestatic == 2)
                        {
                          fprintf(fichier,"%d/%d/%d %d:%d:%d;1;ex2.pbm\n", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
                        }

                 if(imagestatic == 3)
                        {
                          fprintf(fichier,"%d/%d/%d %d:%d:%d;1;ex3.pbm\n", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
                 }

                 if(imagestatic == 4)
                        {
                          fprintf(fichier,"%d/%d/%d %d:%d:%d;1;ex4.pbm\n", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
                        }

                 if(imagestatic == 5)
                        {
                          fprintf(fichier,"%d/%d/%d %d:%d:%d;1;ex5.pbm\n", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
                        }




                }
            if (ExiaTermsaver_aleatoir == 2)
                {
                    fprintf(fichier,"%d/%d/%d %d:%d:%d;2;3x5\n", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);


                }
            if (ExiaTermsaver_aleatoir == 3)
                {
                fprintf(fichier,"%d/%d/%d %d:%d:%d;3;20x20\n", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);


                }





            }

            fclose(fichier);
            fichier = fopen("Historique.txt", "r"); // fichier "Historique ouvert en mode lecture
            int etatlecture = 0;



            if (fichier != NULL) // si le fichier éxiste
            {
                do
                {                                     //Parcour le fichier caractère par caractère
                        c = fgetc (fichier);


                        if(etatlecture == 1) // si etatlecture = 1
                        {
                            if(c == '1')
                            {
                                NombreDeFoisStatique++;
                            }
                            if(c == '2')
                            {
                                NombreDeFoisDynamque++;
                            }
                            if(c == '3');
                            {
                                NombreDeFoisInteractif++;
                            }
                            if(c == ';')
                            {
                                etatlecture = 0;
                            }
                        }
                        if(c == ';') //si le caractère ";" est lu
                        {
                            etatlecture = 1; // affecte la valeur 1 à etatlecture
                        }


                }while (c != EOF); //On continue tant que fgetc n'a pas retourné EOF (fin de fichier)


                    printf("Ecran statique executer %d fois\n",NombreDeFoisStatique);
                    printf("Ecran dynamique executer %d fois\n",NombreDeFoisDynamque);      // Affiche la valeur des variables
                    printf("Ecran interactif executer %d fois\n",NombreDeFoisInteractif);



            }




    return 0;
    }
