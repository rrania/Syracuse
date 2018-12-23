#include <stdio.h>
#include <stdlib.h>

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

}
