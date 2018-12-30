#include <stdio.h>
#include <stdlib.h>

//on définit la taille du tableau ou on stocke le nombre en hexadecimal
//exemple 1
#define tailleTableau 3
/*
//exemple 2
#define tailleTableau 20
*/

/*On crée une méthode qui va écrire dans un fichier le nombre qui vérifie la suite de Syracuse*/
/*Il prend en méthode un nombre à écrire dans le fichier*/
void Write(unsigned long nombre)
{
    /*On définit le fichier*/
    FILE * fp;

    /*On ouvre le fichier, le a+ permet de lire et écrire à partir de la fin du fichier*/
    fp = fopen("FichierResult.txt","a+");

    /*On écrit dans le fichier : on précise le fichier dans lequel on écrit puis ce qu'on écrit*/
    fprintf(fp,"%d\n", nombre);

    /*Puis on ferme le fichier*/
    fclose(fp);

}

void Write_Char(char nombre[])
{
    /*On définit le fichier*/
    FILE * fp;

    /*On ouvre le fichier, le a+ permet de lire et écrire à partir de la fin du fichier*/
    fp = fopen("FichierResult.txt","a+");

    fprintf(fp,"%s", nombre);

    fprintf(fp,"\n");
    /*Puis on ferme le fichier*/
    fclose(fp);

}

/*1ere méthode Syracuse 'Classique' prenant un long en argument car logn a une plage de valeurs plus grande que int*/
int Syracuse(unsigned long n)
{
    unsigned long avant_dernier = 0;
    unsigned long dernier = n;
    unsigned long avant_avant_dernier = 0;
    unsigned long calcul = 0;

    /*Tant que le nombre n'est pas 1, on continue les opérations*/
    while(avant_avant_dernier !=4 || avant_dernier!=2 || dernier !=1)
    {
        /*Si le nombre est pair, alors on le divise par 2*/
        if(dernier %2 ==0) calcul = dernier/2;

        /*Sinon, on le multiplie par 3 et on ajoute 1*/
        else  calcul = 3*dernier+1;

        avant_avant_dernier = avant_dernier;
        avant_dernier = dernier;
        dernier = calcul;
        printf("%d\n", avant_avant_dernier);
        printf("%d\n", avant_dernier);

       printf("%d\n", dernier);

    }

    /*On retourne n, le nombre en argument, =1 si ça vérifie Syracuse*/
    return dernier;

}

/*2e méthode : Récurcive qui prend en argument le même long que dans la 1ere méthode*/
int SyracuseRecurcif(unsigned long avant_avant_dernier, unsigned long avant_dernier, unsigned long dernier)
{

    /*Si le nombre est 1 on retourne 1 ça vérifie Syracuse*/
  if(avant_avant_dernier !=4 || avant_dernier!=2 || dernier !=1) return 1;

  /*Sinon, on retourne la même méthode avec en argument le nombre divisé par deux s'il est pair, ou le nombre x3+1 s'il est impair*/
  if(dernier%2==0) return SyracuseRecurcif( avant_dernier, dernier, dernier/2);
  else return SyracuseRecurcif(avant_dernier, dernier, 3*dernier+1);

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
//return la retenu finale
int mult3(char tableau[]){
    int i;
    int retenu=0;
    for (i=tailleTableau-1 ; i>=0;i--){
        tableau[i]=mult3Char(tableau[i], &retenu);
    }
    return retenu;
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
//return la retenu finale
int ajout1(char tableau[]){
    int i=tailleTableau-1;
    int retenu=1;
    while(i>=0 && retenu ){
            tableau[i]=ajoutChar(tableau[i] , &retenu);
            i--;
    }
    return retenu;
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
//return 1 si l'hypothese est validee pour le tour
//0 si l'hypothèse n'est pas validee ou on a plus de place dans le tableau pour faire le calcule
int unTour(char tableau[]){
    int trouve4=0;
    int trouve2=0;
    int trouve1=0;
    while ( !trouve4 || !trouve2 || !trouve1){
        trouve4= est(tableau,'4')?1:trouve4;
        trouve2= (est(tableau,'2') && trouve4) ?1:trouve2 ;
        trouve1= (est(tableau,'1') && trouve4 && trouve2 )?1:trouve1;
        if (estPair(tableau[tailleTableau-1])){
            div2(tableau);
        } else{
            if (mult3(tableau)){
                return 0;
            }
            if (ajout1(tableau)){
                return 0;
            }
        }
        //printf("%s\n",tableau);
    }
    return 1;
}

//copier le rableau tab dans le tableau tabCopie
void copierTab(char tab[] , char tabCopie[]){
    for (int i=0; i<tailleTableau+1;i++){
        tabCopie[i]=tab[i];
    }
}


int main()
{
    //Partie 1
    //exemple1
    printf("Partie 1 : en cours\n");
    unsigned long i=1;
    while(i<30)
    {
        Write(i);
        SyracuseRecurcif(0,0,i);
        i++;
    }
  /*
  //exemple 2
     //On a pris la valeur du plus grand long puis -1 et /3 : on a testé mais pour tester les 2 boucles, on prend une valeur du
    //nombre max plus petit
    unsigned long i=1;
    while(i<3074457345618258602)
    {
        Write(i);
        SyracuseRecurcif(0,0,i);
        i++;
    }
*/
    printf("Partie 1 : finie\n");
    //Partie 2
    printf("Partie 2 : en cours\n");

    //exemple 1 avec tailleTableau = 3
    char tab[tailleTableau+1];
    tab[3]='\0';
    tab[2]='1';
    tab[1]='0';
    tab[0]='0';

    /*
    //exemple 2 avec tailleTableau = 20
    //Le tableau est rempli de la valeur max des long -1 /3 en base 16
    char tab[tailleTableau+1];
    for (int i=0; i<tailleTableau+1;i++){
        tab[i]='0';
    }
    tab[tailleTableau]='\0';
    tab[tailleTableau-1]='0';
    tab[tailleTableau-2]='0';
    tab[tailleTableau-3]='A';
    tab[tailleTableau-4]='A';
    tab[tailleTableau-5]='A';
    tab[tailleTableau-6]='A';
    tab[tailleTableau-7]='A';
    tab[tailleTableau-8]='A';
    tab[tailleTableau-9]='A';
    tab[tailleTableau-10]='A';
    tab[tailleTableau-11]='A';
    tab[tailleTableau-12]='A';
    tab[tailleTableau-13]='A';
    tab[tailleTableau-14]='A';
    tab[tailleTableau-15]='A';
    tab[tailleTableau-16]='2';
    */
    Write_Char(tab);
    char tab2[tailleTableau+1];
    copierTab(tab,tab2);
    ajout1(tab2);
    while( 1 )
    {
        copierTab(tab2,tab);
        Write_Char(tab);
        if ( !unTour(tab)){
            printf("retenu differente de 0 donc on s'arrete puisqu'on n'a plus d'espace dans le tableau");
            return 0;
        }
        ajout1(tab2);
    }
    return 1;

}
