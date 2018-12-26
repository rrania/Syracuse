#include <stdio.h>

#define tailleTableau 6

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

char div2Char(char c, int retenu){
    static char base16 []={'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};
    int pos=recherchePosDansTableau(base16,16,c);
    int resInt=((pos + retenu*16)/2)%16;
    return ( base16[resInt] );
}

//divise le nombre pair en hexadecimal qui se trouve dans le tableau par 2
//return un tableau de char avec le resultat de devision par 2 en hexadecimal
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

char mult3Char(char c, int* retenu){
    static char base16[]={'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};
    int pos=recherchePosDansTableau(base16,16,c);
    int produit=pos*3;
    int resInt=((produit%16)+ *retenu)%16;
    *retenu =produit/16;
    return base16[resInt];
}
void mult3(char tableau[]){
    int i;
    int retenu=0;
    for (i=tailleTableau-1 ; i>=0;i--){
        tableau[i]=mult3Char(tableau[i], &retenu);
    }
}
char ajout1Char(char c , int* retenu){
    static char base16[]={'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};
    int pos=recherchePosDansTableau(base16,16,c);
    int preRes=pos+ *retenu;
    *retenu=preRes/16;
    return (base16[preRes%16]);
}

void ajout1(char tableau[]){
    int i=tailleTableau-1;
    int retenu=1;
    while(i>0 && retenu ){
            tableau[i]=ajout1Char(tableau[i] , &retenu);
            i--;
    }
}
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

int main(){
    char t[]={'0','0','6','A','9','3','\0'};
    printf("%s",t);
    printf("////////////////////");
    int res=unTour(t);
    printf("************");
    printf("%c %c %c %c %c %c",t[0],t[1],t[2],t[3],t[4],t[5]);
    printf("le res est %d",res);
    return 0;
}

