#include <stdio.h> // I/O
#include <stdlib.h> //
#include <string.h> // gestion chaine de caractères
#include <time.h> // gestion heure
#include <unistd.h> //processus
/* Pour perror() et errno */
#include <errno.h>
/* Pour le type pid_t */
#include <sys/types.h>

//taille écran
#define _SCREEN_HEIGHT 24
#define _SCREEN_WIDTH 80

//taille max tableaux
#define _MAX_WIDTH 28
#define _MAX_HEIGHT 25

//taille max img heure
#define _TIME_WIDTH 28
#define _TIME_HEIGHT 5

//taille du msg
#define _MSG 48

//nombres de secondes
#define _NBSEC 5

typedef struct localTime localTime;
struct localTime
{
	int hour;
	int minute;
	int second;
};


typedef struct imgPBM imgPBM;
struct imgPBM
{

	int width;
	int height;
	char pixels[_MAX_HEIGHT][_MAX_WIDTH];
};

//var glocale pour le msg
char msg[] = "Cet ecran sera actualise dans quelques secondes\0";

//prototypes fonctions

//lit l' et creer une img (struct)
imgPBM getImgFromTime(int hour, int min, int sec);
//lit un fichier et créer une img (struct)
imgPBM getImgFromFile(char *path);
//donne l'img du chiffre donné en paramètre
imgPBM getImgChiffre(int value);
//affiche l'img dans la console
void showImg(imgPBM img);
//affiche un caractère au corrd XY
void printToXy(int x, int y, char text);
//recupère l'heure
localTime getTime();

/* La fonction create_process duplique le processus appelant et retourne
   le PID du processus fils ainsi créé */
pid_t create_process(void)
{
    /* On crée une nouvelle valeur de type pid_t */
    pid_t pid;

    /* On fork() tant que l'erreur est EAGAIN */
    do {
		pid = fork();
    } while ((pid == -1) && (errno == EAGAIN));

    /* On retourne le PID du processus ainsi créé */
    return pid;
}

/* La fonction child_process effectue les actions du processus fils :
	Affiche les points après le msg.
*/
void child_process(void)

{
	
	int posX = _SCREEN_HEIGHT - 2;
	int posYT = _SCREEN_WIDTH / 2 - _MSG / 2 + _MSG ;
	//affiche le point
	int i = -1;

	while(1){
		i++;

		printToXy(posX, posYT+i, '.');
		sleep(1);
		//réinsisalise la position du point
		if(i == _NBSEC - 1){
			i = -1;
		}
		
	}
	
	
}


/* La fonction father_process effectue les actions du processus père:
	Affiche l'heure et le msg.
*/

void father_process(int child_pid)

{
	//calcul postion de départ pour le msg
	int posY = _SCREEN_WIDTH / 2 - _MSG / 2;
	int posX = _SCREEN_HEIGHT - 2;
	int l = 0;
	
	
	while(1){
		
	    //recupère l'heure
		localTime myTime = getTime();
		//creer une imgPBM de l'heure
		imgPBM timeImg = getImgFromTime(myTime.hour,myTime.minute,myTime.second);

		//affiche l'img
		showImg(timeImg);

		//affiche le msg
		for(l = 0 ; l < _MSG; l++){
		
			printToXy(posX, posY + l ,msg[l]);
		}

		//met le processus en pause pour N secondes
		sleep(_NBSEC);

		//efface la console
		system("clear");
	}	
}




int main(int argc, char *argv[]){


	//créer les processus
	pid_t pid = create_process();

	//test sur le pid renvoyé
    switch (pid) {

	    //Si on a une erreur irrémédiable (ENOMEM dans notre cas) 
	    case -1:
	    	perror("fork");
	    	return EXIT_FAILURE;
	    break;

	    //Si on est dans le fils 
	    case 0:
	    	child_process();
	    break;

	    // Si on est dans le père 
	    default:
	    	father_process(pid);
	    break;

    }
   

return 0;

}

/*
Fonction qui retourne une imgPBM du chiffre donné en paramètre
On appelle la fonction qui va lire le bon fichier et créer (et remplir) la structure imgPBM
*/
imgPBM getImgChiffre(int value){
	
	imgPBM imgChiffre;
	
	//remplit la struct avec le bon chiffre ( à partir du bon fichier )
	switch(value){
		case -1: // cprrespond au ":"
			
			imgChiffre = getImgFromFile("../img/dynamique/point.pbm");
			break;		
		case 0:

			imgChiffre = getImgFromFile("../img/dynamique/zero.pbm");
			break;
		case 1:

			imgChiffre = getImgFromFile("../img/dynamique/un.pbm");
			break;
		case 2:

			imgChiffre = getImgFromFile("../img/dynamique/deux.pbm");
			break;
		case 3:
			
			imgChiffre = getImgFromFile("../img/dynamique/trois.pbm");
			break;
		
		case 4:	
			imgChiffre = getImgFromFile("../img/dynamique/quatre.pbm");			
			break;

		case 5:

			imgChiffre = getImgFromFile("../img/dynamique/cinq.pbm");		
			break;

		case 6:
		
			imgChiffre = getImgFromFile("../img/dynamique/six.pbm");			
			break;

		case 7:
			imgChiffre = getImgFromFile("../img/dynamique/sept.pbm");
			
			break;

		case 8:
			
			imgChiffre = getImgFromFile("../img/dynamique/huit.pbm");		
			break;
		case 9:
			
			imgChiffre = getImgFromFile("../img/dynamique/neuf.pbm");
			break;
		}//fin switch

	return imgChiffre;
}

/*
Fonction qui crée et rempli la structure imgPBM à partir d'un fichier .pbm.
On lit le fichier ligne par ligne et on remplie le tableau de pixels case par case.
On lit également la deuxième ligne pour connaitre la taille de l'img.
*/
imgPBM getImgFromFile(char *path){
	
	FILE* file = NULL;
	int i = 0;
	char lue[_MAX_WIDTH] = "";
	int width = 0;
	int height = 0;
	imgPBM img;
	int j;
	
	//ouvre le fichier en lecture
	file = fopen(path,"r");
	//si on réussit à ouvrir le fichier
	if(file != NULL ){
		//lecture ligne par ligne
		while(fgets(lue, _MAX_WIDTH, file) != NULL){
			//lecture de la ligne contenant la taille
			if(i == 1){
				//recherche de la largeur et de la hauteur dans la chaine de caractère
				sscanf(lue,"%d %d",&width,&height);
				//enregistre dans la structure la largeur et la hauteur
				img.width = width;
				img.height = height;
				
			}
			//lecture des lignes suivantes du fichier
			else if(i > 1 ){			
				
				//remplissage de la structure
				for(j = 0 ; j < img.width ; j++){				
					img.pixels[i-2][j] = lue[j]; //i - 2 car pour la case 0, i vaut 2 à cause des 2 premières lignes du fichierS
				}
				
			}else{
				//ligne 0 avec le P1
			}
			i++;	
		}
		
	}else{
		printf("Impossible d'ouvir le fichier %s !\n", path);
	}

	//fermeture du fichier
	fclose(file);

	return img;
}


/*
Fonction qui retourne une struct imgPBM remlit de l'heure.
*/
imgPBM getImgFromTime(int hour, int min, int sec){

	//calcul des dizaines et des unités pour les heures, les minutes et les secondes
	int dizainesH = hour/10;
	int unitesH = hour%10;

	int dizainesM = min/10;
	int unitesM = min%10;

	int dizainesS = sec/10;
	int unitesS = sec%10;

	//création et remplissage de la struct pour les chiffres correspondant	
	imgPBM dh = getImgChiffre(dizainesH);
	imgPBM uh = getImgChiffre(unitesH);
	
	imgPBM dm = getImgChiffre(dizainesM);
	imgPBM um = getImgChiffre(unitesM);
	
	imgPBM ds = getImgChiffre(dizainesS);
	imgPBM us = getImgChiffre(unitesS);
	
	//création et remplissage de la struct pour les ":"
	imgPBM point = getImgChiffre(-1);
	
	//variables pour les boucles for
	int j = 0;
	int k = 0;
	int pos = 0;//indicateur de position dans le tableau de l'heure

	//déclaration structure img pour l'heure
	imgPBM imgTime;
	imgTime.width = _TIME_WIDTH;
	imgTime.height = us.height;//hauteur de l'heure = hauteur d'un chiffre

	//remplit la struct img de l'heure avec les img des chiffres lignes par lignes
	for(j = 0; j < imgTime.height ; j ++){
		
		//remplit la ligne j avec la dizaine des heures dans la ligne j de la structure de l'heure
		for(k = 0; k < dh.width ; k++){
			imgTime.pixels[j][pos] = dh.pixels[j][k];
			pos ++;
		}
		
		//on ajoute un espace ( un zero ) entre 2 chiffres
		pos++;
		imgTime.pixels[j][ pos ] = '0';
		
		//remplit la ligne j avec les unites des heures
		for(k = 0; k < uh.width ; k++){
			imgTime.pixels[j][pos] = uh.pixels[j][k];
			pos++;
		}
		
		//remplit la ligne j avec les ":" 
		for(k = 0; k < point.width ; k++){
			imgTime.pixels[j][pos] = point.pixels[j][k];
			pos++;
		}

		//remplit la ligne avec la dizaine des minutes
		for(k = 0; k < dm.width ; k++){
			imgTime.pixels[j][pos] = dm.pixels[j][k];
			pos++;
		}

		//on ajoute un espace ( un zero ) entre 2 chiffres
		pos++;
		imgTime.pixels[j][ pos ] = '0';

		//remplit la ligne avec l'unité des minutes
		for(k = 0; k < um.width ; k++){
			imgTime.pixels[j][pos] = um.pixels[j][k];
			pos++;
		}

		//remplit la ligne j avec les ":" 
		for(k = 0; k < point.width ; k++){
			imgTime.pixels[j][pos] = point.pixels[j][k];
			pos++;
		}

		//remplit la ligne avec la dizaine des secondes
		for(k = 0; k < ds.width ; k++){
			imgTime.pixels[j][pos] = ds.pixels[j][k];
			pos++;
		}

		//on ajoute un espace ( un zero ) entre 2 chiffres
		pos++;
		imgTime.pixels[j][ pos ] = '0';	

		//remplit la ligne avec les unités des secondes
		for(k = 0; k < us.width ; k++){
			imgTime.pixels[j][pos] = us.pixels[j][k];
			pos++;
		}

		//reinitiallise le curseur pour la ligne suivante
		pos = 0;	
		
			
	}

	return imgTime;
}


/*
	Fonction qui calcul l'heure et la retourne dans la structure localTime
*/
localTime getTime(){


	//recupère lh courante
	time_t dt = time(NULL);

	//convertion heure locale
	struct tm tm_now = *localtime(&dt);

	//créer une chaine de car pour l'afficher
	char s_now[sizeof "HH:MM:SS"];

	strftime(s_now, sizeof s_now, "%H:%M:%S", &tm_now);

	int hour, min, sec;
	
	// extraction sur la chaine de caracère de l'h
	sscanf(s_now,"%d:%d:%d",&hour, &min, &sec);

	localTime myTime;
	myTime.hour = hour;
	myTime.minute = min;
	myTime.second = sec;

	return myTime;
}


/*
	Fonction qui affiche l'img dans la console
*/
void showImg(imgPBM img){
	//variables pour les boucles for
	int j = 0;
	int i = 0;
	
	//calcul de la position initiale pour centrer l'heure
	int posY = _SCREEN_WIDTH / 2 - img.width / 2;
	int posX = _SCREEN_HEIGHT / 2 - img.height / 2;

	//efface la console
	system("clear");

	//parcours du tableau de pixels à double dimension
	//On affiche:
	//	 un espace si on trouve un 0
	//   un X si on trouve un 1
	for(j = 0; j < img.height ; j ++){
		for(i = 0 ; i < img.width ; i++){
			
			char pix = img.pixels[j][i];
			
			if(pix == '0'){
				printToXy(posX + j, posY + i, ' ');
			}else if(pix == '1'){
				printToXy(posX + j, posY + i, 'X');
			}else{
				//on ignore si on trouve autre chose
			}
			
		}
		printf(" \n");//saut de ligne
			
	}
	
}


/*
	Fonction qui affiche un caractère a la position x y
*/
void printToXy(int x, int y, char text)
{
  printf("\033[%d;%dH%c\n", x, y, text);
}
