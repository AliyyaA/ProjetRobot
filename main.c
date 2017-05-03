/*Algorithmic Project : Sudoku by Aliyya Adira and Alzahra Hassanein*/

/*Polytech 2016/2017*/

#include <stdlib.h>
#include <stdio.h>

/* --Le--nommage--de--certaines--valeurs----------------- */

#define VALUE 0

#define COUNT ( Size + 1 )

/* --Les--constantes--de--compilation------------------- */

#define Max_size_bloc 5
#define Max_size ( Max_size_bloc * Max_size_bloc )
#define Size ( Size_bloc * Size_bloc )

/* --Les--variables--globales----------------------------- */

int Size_bloc ;

int Sudoku[ Max_size + 1 ][ Max_size + 1 ][ Max_size + 2 ] ;

int * Lines[ Max_size + 1 ][ Max_size + 1 ] ;
int * Columns[ Max_size + 1 ][ Max_size + 1 ] ;
int * Blocs[ Max_size + 1 ][ Max_size + 1 ] ;

int Optimise_one , Optimise_two ;

char Transcode[ 16 + 1 ]
= { ' ' , '1' , '2' , '3' , '4' , '5' , '6' , '7' , '8' , '9' ,
    'A' , 'B' , 'C' , 'D' , 'E' , 'F' , 'G' } ;

char Transcode_ext[ 25 + 1 ]
= { ' ' , 'A' , 'B' , 'C' , 'D' , 'E' , 'F' , 'G' , 'H' , 'I' , 'J' , 'K' , 'L' ,
    'M' , 'N' , 'O' , 'P' , 'Q' , 'R' , 'S' , 'T' , 'U' , 'V' , 'W' , 'X' , 'Y' } ;

/* --Quelques--exemples--pour--le--test------------------- */

#include "grids.c"

/* --Les--prototypes--des--fonctions--fournies------------------ */

void setup_Lines_Columns_Blocs ( void ) ;
void fill_squares_line ( int * squares[ ] , int li ) ;
void fill_squares_column ( int * squares[ ] , int co ) ;
void fill_squares_bloc ( int * squares[ ] , int base_li , int base_co ) ;

void optimise ( void ) ;

int fill_and_count_squares_Sudoku ( int value_list[ ] ) ;
int main ( void ) ;

/* --Les--prototypes--des--fonctions--a--fournir-------- */

void print_Sudoku ( void ) ;
void fill_possibilities ( void ) ;
int quel_bloc(int li, int co);
int optimise_possibilities ( int * squares[ ] ) ;
int back_track ( int squares_filled ) ;

/*Structure nécessaire pour l'optimisation */

typedef struct{
  int res;
  int ind;
}onlyone;


/* --Les--fonctions--fournies--------------------- */

void setup_Lines_Columns_Blocs ( void )
     {int i ;
      for ( i = 1 ; i <= Size ; i++ )
          {fill_squares_line( Lines[ i ] , i ) ;
           fill_squares_column( Columns[ i ] , i ) ;
           fill_squares_bloc( Blocs[ i ] ,
                              1 + ( i - 1 ) / Size_bloc * Size_bloc ,
                              1 + ( i - 1 ) % Size_bloc * Size_bloc ) ;
          }
     }

void fill_squares_line ( int * squares[ ] , int li )
     {int co , index = 1 ;
      for ( co = 1 ; co <= Size ; co++ )
          squares[ index++ ] = Sudoku[ li ][ co ] ;
     }

void fill_squares_column ( int * squares[ ] , int co )
     {int li , index = 1 ;
      for ( li = 1 ; li <= Size ; li++ )
          squares[ index++ ] = Sudoku[ li ][ co ] ;
     }

void fill_squares_bloc ( int * squares[ ] , int base_li , int base_co )
     {int offset_li , offset_co , index = 1 ;
      for ( offset_li = 0 ; offset_li < Size_bloc ; offset_li++ )
          for ( offset_co = 0 ; offset_co < Size_bloc ; offset_co++ )
              squares[ index++ ] = Sudoku[ base_li + offset_li ][ base_co + offset_co ] ;
     }

void optimise ( void )
     {int i , iterate ;
      do {iterate = 0 ;
          for ( i = 1 ; i <= Size ; i++ )
              {iterate = optimise_possibilities ( Lines[ i ] ) ;
               iterate = optimise_possibilities ( Columns[ i ] ) || iterate ;
               iterate = optimise_possibilities ( Blocs[ i ] ) || iterate ;
              }
         }
      while ( iterate ) ;
     }

int fill_and_count_squares_Sudoku ( int value_list[ ] )
    {int li , co , value , index = 0 , sum = 0 ;
     for ( li = 1 ; li <= Size ; li++ )
         for ( co = 1 ; co <= Size ; co++ )
             {value = value_list[ index ++ ] ;
              Sudoku[ li ][ co ][ VALUE ] = value ;
              if ( value )
                 sum++ ;
             }
     return( sum ) ;
    }

int main ( void )
    {int solution_found , number_squares ;
     Size_bloc = 5;
     setup_Lines_Columns_Blocs( ) ;
     Optimise_one = 1 ;
     Optimise_two = 1 ;
     number_squares = fill_and_count_squares_Sudoku(Grid_twenty_five_1) ;
     print_Sudoku( ) ;
     solution_found = back_track( number_squares ) ;
     if ( solution_found )
        {(void)printf( "\nNous avons trouvé la solution :\n\n" ) ;
         print_Sudoku( ) ;
        }
     else
        (void)printf( "\nNous n'avons pas trouvé de solution.\n" ) ;
     (void)printf( "Bye !" ) ;
     return( 0 ) ;
    }

/* --Les--autres--prototypes----------------------- */

/* Ce sont les proptotypes des autres fonctions que vous introduisez. */

/* Les fonctions auxiliaires de print_Sudoku */
void affiche_chaine(int nbre)
{
    int i ;
    for (i = 1; i <= nbre; i++) {
        printf("*") ;
    }
    printf("\n") ;
}

/* --La--fonction--d--impression-------------------------- */
void print_Sudoku ( void )
     {
            
        int li, co ;
        
        /* on déssine un bord supérieur de la grille avec des étoiles */
        li=1;
        printf(" ") ;
        for( co=1 ; co<= Size ; co++ ){
            printf("*******") ;
        } 
   printf("\n") ;
        printf("*") ;

        /* pour chaque colonne de la première ligne */
        for( co=1 ; co<=Size ; co++ ){

            /* si le numéro de la colonne n'est pas multiple de la taille du bloc*/
            if (co % (Size_bloc)) {

                /* si la valeur de la case est supérieure à 10 */
                /* on ajoute deux espaces de part et d'autre de la valeur */
                if (Sudoku[li][co][VALUE] >= 10) {
                    printf("  %d  |", Sudoku[li][co][VALUE]) ;
                }

                /* si la valeur de la case est inférieur à 10 */
                /* on ajoute trois espaces à gauche de la valeur */
                /* et deux espaces à droite de la valeur */
                /* afin de bien aligner la grille */
                else {
                    printf("   %d  |", Sudoku[li][co][VALUE]) ;
                }
            }

            /* si le numéro de la colonne est multiple de la taille du bloc */
            /* on fait la même chose que précédemment, à la seule différence */
            /* que l'on va écrire '*' à la place de '|' */
            /* pour séparer les blocs de taille Size_bloc */
            else {
                if (Sudoku[li][co][VALUE] >= 10) {
                    printf("  %d  *", Sudoku[li][co][VALUE]) ;
                }
                else {
                    printf("   %d  *", Sudoku[li][co][VALUE]) ;
                }
            }
        }
        printf("\n") ;

        /* maintenant on fait la même chose pour chaque ligne */
        for( li=2 ; li<=Size ; li++ ){
            printf(" ") ;
            
            /* on rajoute la fonction qui sépare les lignes et les blocs */
            /* si la ligne précedente n'est pas multiple de size bloc */
            /* on dessine une ligne de traits */
            if ((li-1)%(Size_bloc) != 0) {
                for( co=1 ; co<= Size ; co++ ){
                    printf("-------") ;
                }
            }
    
            /* si la ligne précedente est multiple de size bloc */
            /* on dessine une ligne d'étoiles */
            else {
                for( co=1 ; co<= Size ; co++ ){
                    printf("*******") ;
                }
            }

            
       printf("\n") ;
            printf("*") ;
            for( co=1 ; co<=Size ; co++ ){
                if (co % (Size_bloc)) {
                    if (Sudoku[li][co][VALUE] >= 10) {
                        printf("  %d  |", Sudoku[li][co][VALUE]) ;
                    }
                    else {
                        printf("   %d  |", Sudoku[li][co][VALUE]) ;
                    }
                }
                else {
                    if (Sudoku[li][co][VALUE] >= 10) {
                        printf("  %d  *", Sudoku[li][co][VALUE]) ;
                    }
                    else {
                        printf("   %d  *", Sudoku[li][co][VALUE]) ;
                    }
                }
            }
            printf("\n") ;
        }

        /* on dessine le bord inférieur de la grille avec des étoiles */
        printf (" ");
        for( co=1 ; co<= Size ; co++ ){
                printf("*******") ;
        } 
        printf("\n\n") ; 
        return ;    
     }





/* Les fonctions auxiliaires de fill_possibilities */

int quel_bloc ( int li, int co ){
    int l, c;
    /*Determine le bloc selon les lignes et les colonnes ou l'on se trouve*/
    l = ((li - 1)/Size_bloc)*Size_bloc ;
    c = ((co - 1)/Size_bloc) + 1 ;
 	
    return (l+c) ; 
}

/* --Le--raisonnement--au--niveau--zero------------------------ */

void fill_possibilities ( void )
{
      int li,co,count,v,tco,tli, blok,caze;
      
      for (li=1; li<=Size ; li++){
      	for (co=1; co<=Size;co++){
      		if(Sudoku[li][co][VALUE] == 0){
      			v=1;
      			count = Size;
      			while (v<=Size){
      				Sudoku[li][co][v] = 1;
      				tco=1;
      				while (tco<=Size){
      					if (Lines[li][tco][VALUE] == v){
      	/*Si la valeur à la (tco)ième case de la (li)ème ligne vaut v*/
      						Sudoku[li][co][v] = 0; 
      	//v n'est pas une possibilité
      						count = count - 1;      
      					}
      					tco=tco+1;
      				}
      				tli =1;
      				while(tli<=Size){
      					if(Sudoku[li][co][v]!=0 && Columns[co][tli][VALUE]==v ){
      	/*Si la valeur de co ième case de la tli ème colonne vaut v et que v est une possibilité*/
      						Sudoku[li][co][v]=0;
      						count=count-1;
      					}
      					tli = tli+1;
      				}
/*On définit la présence dans le bloc */
					caze = 1 ;
      				blok = quel_bloc(li, co); 
           		 	
           			while(caze<=Size){
             			if (Sudoku[li][co][v]!=0 && Blocs[blok][caze][VALUE] == v ){
	/*Si la valeur de la caze ième case du blok ième bloc vaut v et qu'il est encore une possibilité */
               				Sudoku[li][co][v] = 0 ;
		           			count = count-1 ;  
	            		}
/*On fait le test sur toutes les cases d'un bloc*/
              		caze = caze+1 ; 
            	   }
	          v = v+1 ;   
        	  }
        	  
          Sudoku[li][co][COUNT] = count ; 
      /*    printf("li= %d co= %d count= %d \n ", li, co, Sudoku[li][co][COUNT]) ;      */		
        }	
      }
    }
    return ; 
}


/* --Une--valeur--proposee--une--seule--fois------------ */

onlyone uneval(int v ,int *squares[]){
  int cpt=0 ,i, ind = 0;
  onlyone ans;
  for(i = 1; i < Size+1; i++){
    if(squares[i][VALUE]==0){ //Si la case est vide
      if(squares[i][v]){ //Si la case propose cette possibilité v
        cpt++; //compteur d'occurence de la possibilité
        ind = i; //mémorisation de l'indice de la case la proposant
      }
    }
  }
  
  if(cpt==1)
  {//si l'occurence est unique
    ans.res = 1;
    ans.ind = ind;
  }
  else
  { //si elle n'est pas unique
    ans.res = 0;
    ans.ind = -1; //indice incorrect 
  }
  return ans; //retour à la fonction optimise_possibilities
}
/* --Les--optimisations--------------------------- */

int optimise_possibilities ( int * squares[ ] )
{
  onlyone test ;
  int poss = 0,j,a;
  for(j = 1; j <= Size; j++){
    test = uneval(j, squares); //appel de la fonction retournant l'unicité
    							// pour la case d'indice j
    if (test.res && squares[test.ind][COUNT] > 1){
    /*si l'occurence présente dans le champ test.res vaut 1 <=> occurence unique alors on vide les autres possibilités qu'offraient cette case
    en laissant celle de test.ind */ 
      for (a = 1; a <= Size; a++){
        if (a!=j){
          squares[test.ind][a] = 0;
        }
        squares[test.ind][COUNT] = 1;//on remet le compteur de possibilité à 1
      }
      poss++; //compteur pour savoir si on est passé dans la boucle ou pas
    }
  }
  if(poss > 0) //si on est passé dans la boucle alors une optimisation a été faite
    return 1;
  else //sinon aucune n'a été possible on renvoie 0  
    return 0;
}

/* --Le--back--track-------------------------------------- */

int back_track ( int squares_filled )
{
    	int cpt, li, co;
    	int p, testback, tli, tco;
     if (squares_filled == Size*Size)
     /* Si toutes les cases sont remplies */
  	    	return 1 ; 
  	else {	
  	/* on cherche la case vide avec le moins de possibilités */
  		fill_possibilities();
  		cpt = Size; 
  		for (li=1; li<=Size; li++){
	  		for (co=1; co<=Size; co++){
	  			if (Sudoku[li][co][VALUE] == 0){
	  				if (Sudoku[li][co][COUNT]<cpt){
	  					cpt = Sudoku[li][co][COUNT];
	  					tli = li;
	  					tco = co; 
	  				}
	  			}	
  			}		
  		}	
  		/* on regarde toutes les valeurs de p */
  		for (p=1; p<=Size; p++){
  			/* si p est une possibilité */
	  		if (Sudoku[tli][tco][p] == 1){
	  			Sudoku[tli][tco][VALUE] = p;
	  			testback = back_track(squares_filled + 1);
	  			/* si le choix effectué est mauvais, on vide la case et on test p+1*/
	  			if (testback == 0)	  			
	  				Sudoku[tli][tco][VALUE]= 0;
	  			/* sinon le choix est bon */
	  			else
	  				return 1;
	  		}			
  		}
  		return 0;
    }
}


/* ------------------------------------------------------------- */
