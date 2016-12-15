#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define TAILLE_MAX 3

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
    fichier = fopen("Historique.txt", "a");


    if (fichier != NULL)
    {




            srand(time(NULL));
            ExiaTermsaver_aleatoir = rand() % (3-1+1) + 1;



            if(ExiaTermsaver_aleatoir == 1)
            {



                 srand(time(NULL));
                 imagestatic = rand() % (5-1+1) + 1;
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
            fichier = fopen("Historique.txt", "r");
            int etatlecture = 0;



            if (fichier != NULL)
            {
                do
                {
                        c = fgetc (fichier);


                        if(etatlecture == 1)
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
                        if(c == ';')
                        {
                            etatlecture = 1;
                        }


                }while (c != EOF);


                    printf("Ecran statique executer %d fois\n",NombreDeFoisStatique);
                    printf("Ecran dynamique executer %d fois\n",NombreDeFoisDynamque);
                    printf("Ecran interactif executer %d fois\n",NombreDeFoisInteractif);



            }




    return 0;
    }
