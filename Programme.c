#include <stdio.h>

#define tailleTableau 6
#define MAXCHAR 1000

void Write(int nombre)
{
    FILE * fp;

    /*Ouvrir le fichier, le a+ permet de lire et écrire à partir de la fin du fichier*/
    fp = fopen("C:\\Users\\marjo\\OneDrive - De Vinci\\Documents\\ESILV\\Cours\\S5\\Structures_Données_Algo\\Projet_C\\bin\\Debug\\FichierResult.txt","a+");

    /*Ecrire dans le fichier*/
    fprintf(fp,"%d\n", nombre);

    /*Puis on ferme le fichier*/
    fclose(fp);

}

char *Read_Last()
{
     FILE * fp;
     char *str;
    str = (char*)malloc(sizeof(char)*MAXCHAR);

    /*Ouvrir le fichier*/
    fp = fopen("C:\\Users\\marjo\\OneDrive - De Vinci\\Documents\\ESILV\\Cours\\S5\\Structures_Données_Algo\\Projet_C\\bin\\Debug\\FichierResult.txt","r");

    /*Ici, on veut la denrière ligne donc tant que ce n'est pas null, on parcourt la ligne suivante*/
    while(fgets(str, MAXCHAR,fp)!=NULL)
    {
      fgets(str, MAXCHAR,fp);
    }

    fclose(fp);

    return  str;
}

/*On teste deux méthodes qui retournent 0 ou 1 (vrai ou faux)*/
int Syracuse(long n)
{
    while(n !=1)
    {
        if(n %2 ==0) n = n/2;

        else  n = 3*n +1;

    }

    return n;

}

int SyracuseRecurcif(long n)
{
  if(n==1) return 1;

  if(n%2==0) return SyracuseRecurcif(n/2);
  else return SyracuseRecurcif(3*n+1);

}

//partie 2 avec le tableau de caractères

//return 1 si le caractere c est pair , 0 sinon
int estPair(char c){
    return ( c=='A' || c =='C' || c== 'E' || c%2 == 0);
}

//chercher la position du caractere cRecherche dans le tableau tab
// return -1 si le caractere recherche n'existe pas , sinon sa position dans le tableau
int recherchePosDansTableau(char tab[] , int taille , char cRecherche ){
    int pos=-1;
    int i=0;
    while (i<taille && pos==-1 ){
        if (tab[i]==cRecherche){
            pos=i;
        }
        i++;
    }
    return pos;
}

//return la division du caractere c par 2 en tenant compte de la retenu
//le resultat est la representation en caractere du calcul
char div2Char(char c, int retenu){
    static char base16 []={'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};
    int pos=recherchePosDansTableau(base16,16,c);
    int resInt=((pos + retenu*16)/2)%16;
    return ( base16[resInt] );
}

//divise le nombre pair en hexadecimal qui se trouve dans le tableau par 2
//le resultat de devision par 2 en hexadecimal est stocke directement dans le meme tableau
void div2(char tableau[]){
    int i;
    int retenu=0;
    for(i=0;i<tailleTableau;i++){
            int ancienneVal=tableau[i];
            tableau[i]=div2Char(ancienneVal, retenu);
        if(estPair(ancienneVal)){
            retenu='0';
        }else {
            retenu='1';
        }
    }
}

//return la multiplicatn du caractere c par 3 en tenant compte de la retenu
//et on change la valeur de la retenu grace a l'adresse de la retenu
//le resultat est la representation en caractere du calcul
char mult3Char(char c, int* retenu){
    static char base16[]={'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};
    int pos=recherchePosDansTableau(base16,16,c);
    int produit=pos*3;
    int resInt=((produit%16)+ *retenu)%16;
    *retenu =produit/16;
    return base16[resInt];
}

//multiple le nombre impair en hexadecimal qui se trouve dans le tableau par 3
//le resultat de la multiplication par 3 en hexadecimal est stocke directement dans le meme tableau
void mult3(char tableau[]){
    int i;
    int retenu=0;
    for (i=tailleTableau-1 ; i>=0;i--){
        tableau[i]=mult3Char(tableau[i], &retenu);
    }
}
//return l'ajout de la retenu au caractere c
//et on change la valeur de la retenu grace a l'adresse de la retenu
//le resultat est la representation en caractere du calcul
char ajoutChar(char c , int* retenu){
    static char base16[]={'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};
    int pos=recherchePosDansTableau(base16,16,c);
    int preRes=pos+ *retenu;
    *retenu=preRes/16;
    return (base16[preRes%16]);
}

//l'ajout de un au nombre en hexadecimal qui se trouve dans le tableau
//le resultat en hexadecimal est stocke directement dans le meme tableau

void ajout1(char tableau[]){
    int i=tailleTableau-1;
    int retenu=1;
    while(i>0 && retenu ){
            tableau[i]=ajoutChar(tableau[i] , &retenu);
            i--;
    }
}

//return 1 si le contenu du tableau est egale au caractere c , 0 sinon
int est(char tableau[] , char c){
    if (tableau[tailleTableau-1] != c){
        return 0;
    }
    int i;
    for(i=tailleTableau-2;i>=0;i--){
        if (tableau[i] != '0' ){
            return 0;
        }
    }
    return 1;
}

//un tour de Syracuse avec un nombre en Hexadecimal stocke dans le tableau
int unTour(char tableau[]){
    int trouve4=0;
    int trouve2=0;
    int trouve1=0;
    while ( !trouve4 || !trouve2 || !trouve1){
        trouve4= est(tableau,'4')?1:trouve4;
        trouve2= est(tableau,'2')?1:trouve2;
        trouve1= est(tableau,'1')?1:trouve1;
        if (estPair(tableau[tailleTableau-1])){
            div2(tableau);
        } else{
            mult3(tableau);
            ajout1(tableau);
        }
    }
    return 1;
}


int main()
{
   Write(13);
   Write(14);
   /*Write(15);
   char  *last  =Read_Last() ;
   printf("%s", last);
   free(last); */

   long a_test = 250;
   int n = Syracuse(a_test);
    /*Si le nombre vérifie l'hypothèse, on l'écrit dans le fichier*/
   if(n==1)
   {
       Write(a_test);
   }
   char  *last  =Read_Last() ;
    /*Ici, on affiche 250*/
   printf("%s", last);
   free(last);
    /*char t[]={'0','0','6','A','9','3','\0'};
    printf("%s",t);
    printf("////////////////////");
    int res=unTour(t);
    printf("************");
    printf("%c %c %c %c %c %c",t[0],t[1],t[2],t[3],t[4],t[5]);
    printf("le res est %d",res);
    return 0; */

}
