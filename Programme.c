#include <stdio.h>
#include <stdlib.h>

/*On initialise la taille du tableau qui recevra la dernière ligne du fichier texte*/
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
     /*On initialise le tableau, puis on alloue l'espace nécessaire*/
     char *str;
    /*Attention, en C on peut pas juste retourner un tableau, on a besoin de cette ligne*/
    str = (char*)malloc(sizeof(char)*MAXCHAR);

    /*Ouvrir le fichier*/
    fp = fopen("C:\\Users\\marjo\\OneDrive - De Vinci\\Documents\\ESILV\\Cours\\S5\\Structures_Données_Algo\\Projet_C\\bin\\Debug\\FichierResult.txt","r");

   /*Fonction qui retourne dans str la dernière ligne de fp*/
    fgets(str, MAXCHAR,fp);

    fclose(fp);

    return  str;
}


int main()
{

   Write(13);
   Write(14);
   Write(15);
   char  *last = Read_Last() ;
   printf("%s", last);
  /*On ne doit pas oublier de libérer l'espace mémoire après l'avoir utilisé*/
   free(last);

}
