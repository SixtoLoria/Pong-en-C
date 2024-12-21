// Juego del pong.

#include <stdio.h>
#include <windows.h>
#define V 21 // Dimensiones del campo
#define H 75


// prototipos de las funciones 

void inicio ( char campo[V][H]  ,int  pelX, int pelY,int  inijug, int finjug, int  iniia, int finia );
void borde (char campo[V][H]);
void raqueta_jug ( char campo[V][H], int inijug, int finjug );
void raqueta_ia (char campo[V][H], int iniia, int finia);
void pelota (  char campo[V][H], int pelX, int pelY );
void gameloop (char campo[V][H]  ,int  pelX, int pelY,int  inijug, int finjug, int  iniia, int finia, int modX, int modY, int modia);
void draw (char campo[V][H]);
void input(char campo[V][H]  ,int  *pelX, int *pelY,int  *inijug, int *finjug, int  *iniia, int *finia, int *modX, int *modY, int *modia, int *goal);
void update ( char campo[V][H]  ,int  pelX, int pelY,int  inijug, int finjug, int  iniia, int finia );

int main (){
	
	int pelX, pelY, inijug, finjug, iniia,finia; // Variables de posicion
	int modX, modY, modia;  // variables de movimiento de la pelota y la raqueta de la ia
	char campo[V][H];
	
	
	// --------------------- Posicion ----------------------------------
	pelX = 37;
	pelY = 10;
	
	
	// tamano de raqueta del jugador.
	inijug = 8;
	finjug = 12;
	
	// Tamano de raqueta de la ia
	iniia = 5;
	finia = 18;
	
	// -------------- Modificacion -----------------------
	
	modX = -1;
	modY = -1;
	modia = -1;
	
	
	
	inicio (campo,pelX,pelY, inijug,finjug, iniia, finia);
	
	gameloop (campo, pelX,pelY, inijug,finjug, iniia, finia, modX,modY,modia);        // Bucle del juego.
	
	
	system ("pause");
	return 0;
}




void inicio ( char campo[V][H]  ,int  pelX, int pelY,int  inijug, int finjug, int  iniia, int finia ){
	
	borde (campo); // Funcion que crea el campo de juego
	
	raqueta_jug ( campo, inijug,finjug ); // funcion que crea la raqueta del jugador
	
	raqueta_ia (campo, iniia, finia); // funcion que crea la raqueta de la ia
	
	pelota (campo, pelX,pelY);
	
}

void borde (char campo[V][H]){
	
	int i, j;
	
	for (i = 0; i < V ; i++){
		for (j = 0; j<H ; j++){
			
			if (i == 0 || i == V-1){
				campo[i][j] = '-';
			}
			else if (j == 0 || j == H-1){
				campo[i][j] = '|';
			}
			else{
				campo[i][j] = ' ';
			}
		}
	}
}

void raqueta_jug ( char campo[V][H], int inijug, int finjug ){
	
	int i, j;
	
	for (i = inijug; i < finjug; i++){
		for (j = 2; j <=3; j++){
			
			campo[i][j] = 'X';
		}
	}
}


void raqueta_ia (char campo[V][H], int iniia, int finia){
	
	int i, j;
	
	for (i = iniia; i < finia; i++){
		for (j = H - 4; j <= H -3; j++){
			
			campo[i][j] = 'X';
		}
	}
		
}

void pelota (  char campo[V][H], int pelX, int pelY ){
	
	campo[pelY][pelX] = 'O';
}


void leercamp(char campo[V][H]){
	int i,j;
	
	for (i = 0; i< V; i++){
		for (j = 0; j < H; j++){
			printf("%c", campo[i][j]);
		}printf("\n");
	}
	
}

void gameloop (char campo[V][H]  ,int  pelX, int pelY,int  inijug, int finjug, int  iniia, int finia, int modX, int modY, int modia){
	int goal;
	goal = 0;
	
	do{
		
		draw (campo); // Dibujar en pantalla
		input (campo, &pelX, &pelY, &inijug, &finjug, &iniia, &finia, &modX, &modY, &modia, &goal); // verificar y modificar las posiciones
		update (campo,pelX,pelY, inijug,finjug, iniia, finia); // actualizar a matriz campo
		Sleep (10);  // Velocidad del juego
		 
	}while (goal == 0);
	
	
	
	
}



void draw (char campo[V][H]){
	system ("cls");       // en linux = system("clear) para recargar la pantalla
	leercamp (campo);
}


void input(char campo[V][H]  ,int  *pelX, int *pelY,int  *inijug, int *finjug, int  *iniia, int *finia, int *modX, int *modY, int *modia, int *goal){
	
	// ---------------------Verificacion --------------
	
	// verificando si choca en la pared
	if (*pelY == 1 || *pelY == V-2){
		
		// Multiplicando la modificacion la direccion vertical de la pelota por -1
		*modY *= -1;	
	}
	
	// verificando si se hace un goal
	
	if (*pelX == 1 || *pelX == H -2){
		* goal = 1; // acabdndo el juego
	}
	
	// choque con la raqueta del jugador
	int i;
	char key; // reconocedor de tecla
	
	if (*pelX == 4){
		for (i = (*inijug); i<= (*finjug); i++){
			if (i == (*pelY)){
				*modX *= -1;
			}
		}
	}
	// choque con raqueta de la ia
	if (*pelX == H-5){
		for (i = (*iniia); i<= (*finia); i++){
			if (i == (*pelY)){
				*modX *= -1;
			}
		}
	}
	
	//  posicion de la raqueta de la ia
	
	if (*iniia == 1 || *finia == V-1){
		*modia *= -1;
	}
	
	
	// ----------- Modificacion ----------------
	
	if (*goal == 0){
		// Movimiento de la pelota
	
		*pelX += (*modX);
		*pelY += (*modY);
		
		// movimiento de la raqueta de la ia
		
		*iniia += (*modia);
		*finia += (*modia);
		
		// movimiento de la raqueta del jugador
		
		if (kbhit() == 1){ // provisional
			key = getch(); // es como scanf solo que no hay que presionar enter
			
			if (key == 'w'){
				if (*inijug != 1){
					*inijug -= 1;
					*finjug -= 1;
				}
			}
			
			if (key == 's'){
				if (*finjug != V-2){
					*inijug += 1;
					*finjug += 1;
				}
			}
			
		}

	}
	
}


void update ( char campo[V][H]  ,int  pelX, int pelY,int  inijug, int finjug, int  iniia, int finia ){
	
	borde (campo); // Funcion que crea el campo de juego
	
	raqueta_jug ( campo, inijug,finjug ); // funcion que crea la raqueta del jugador
	
	raqueta_ia (campo, iniia, finia); // funcion que crea la raqueta de la ia
	
	pelota (campo, pelX,pelY);
}










