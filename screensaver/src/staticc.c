#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define _MAX_WIDTH 25
#define _MAX_HEIGHT 25
#define _SCREEN_HEIGHT 24
#define _SCREEN_WIDTH 80

// mettre un random pour lancer une image au pif
typedef struct imgPBM imgPBM;
struct imgPBM
{

	int width;
	int height;
	char pixels[_MAX_HEIGHT][_MAX_WIDTH];
	int aleatoir;

};

imgPBM getImgFromFile(char *path);
void showImg(imgPBM img);
void ascii();
void printToXy(int x, int y, char text);

void staticc(){
	char c;
	imgPBM img;
	system("clear");
	
	srand(time(NULL));
	int aleatoir = rand() % (5-1+1) + 1;
	if(aleatoir == 1)
	{	
		img = getImgFromFile("/home/vincent/Documents/screensaver/img/static/1.pbm");
	}

	if(aleatoir == 2)
	{	
		img= getImgFromFile("/home/vincent/Documents/screensaver/img/static/2.pbm");
	}

	if(aleatoir == 3)
	{
		img= getImgFromFile("/home/vincent/Documents/screensaver/img/static/3.pbm");
	}
	
	if(aleatoir == 4)
	{
		img= getImgFromFile("/home/vincent/Documents/screensaver/img/static/4.pbm");
	}
	
	if(aleatoir == 5)
	{
		img= getImgFromFile("/home/vincent/Documents/screensaver/img/static/5.pbm");
	}


	
	showImg(img);	
	scanf("%c", &c);
	system("clear");

	
}

imgPBM getImgFromFile(char *path){
	FILE* file = NULL;
	int i = 0;
	char lue[_MAX_WIDTH] = "";
	int width = 0;
	int height = 0;
	imgPBM img;
	int numLigne = 0;
	char c;
	

	
	file = fopen(path,"r");
	if(file != NULL ){
		while(fgets(lue, _MAX_WIDTH, file) != NULL){
			if(i == 1){
				
				sscanf(lue,"%d %d",&width,&height);

				img.width = width;
				img.height = height;


				
			}
			else if(i > 1 ){			
				
				int j;
				for(j = 0 ; j < img.width ; j++){				

					img.pixels[i-2][j] = lue[j];
				}
				

				
			}
			i++;	
		}
		
	}else{
		printf("Impossible d'ouvir le fichier !\n");
	}

	return img;
}


void showImg(imgPBM img){
	int j = 0;
	int i = 0;
	

	int posY = _SCREEN_WIDTH / 2 - img.width / 2;
	int posX = _SCREEN_HEIGHT / 2 - img.height / 2;




	for(j = 0; j < img.height ; j ++){
		for(i = 0 ; i < img.width ; i++){
			char pix = img.pixels[j][i];

			if(pix == '0'){


				printToXy(posX + j, posY + i, ' ');
			}else if(pix == '1'){


				printToXy(posX + j, posY + i, 'X');
			}else{
				
						
			}
			
		}
		printf(" \n");
			
	}
}


void ascii(){
	int i = 0;
	for(i = 0; i < 256 ;i ++){
		printf("%d = %c\n", i, (char)i);
	}

}




void printToXy(int x, int y, char text)
{
  printf("\033[%d;%dH%c\n", x, y, text);
}

