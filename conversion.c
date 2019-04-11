#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


#define MILLION 1000000
#define MILLE 1000
#define MAX_CHAR_CONV 1024

static char unite[10][16] = {"zero", "un", "deux", "trois", "quatre", "cinq", "six", "sept", "huit", "neuf"};
static char dizaine[10][16] = {"", "", "vingt", "trente", "quarante", "cinquante", "soixante", ""/*on utilise soixante */, "quatre-vingt", ""/*on utilise quatre-vingt*/};
static char dix[10][16] = {"dix", "onze", "douze", "treize", "quatorze", "quinze", "seize", "dix-sept", "dix-huit", "dix-neuf"};


typedef struct _nmbre{

	char entier[256];
	int neg;
	int virg;
} nbre;


//fonction de vonversion (nombre -> letter 0 ==> 999)
static char *centaine(long nombre){

	char *str_centaine = malloc(MAX_CHAR_CONV/2*sizeof(char));
		if (str_centaine==NULL){

			printf("Error \n");
			return NULL;
		}

		memset(str_centaine,0,sizeof(str_centaine));
		int c,d,u;
		c = nombre/100;
		d = (nombre-c*100)/10;
		u = (nombre-c*100-d*10);

		//les centaines

		if (c==1)
			strcat(str_centaine, "centt");

		else if (c>0){

			strcat(str_centaine,unite[c]);//le nombre de cent
			strcat(str_centaine, "cent");

			if ((d==0) && (c==0))
				strcat(str_centaine, "s");//si apres le test il n'ya pas de nombre on ajoute le S
			else 
				strcat(str_centaine, " ");//sinon on ajoute un espace
		}

//on fait les dizaines et les unites !!!

if (d==0){  //si les dizaines valent 0 no ecrit directement les unites 
	if (u>0)
		strcat(str_centaine,unite[u]);
}

else if (d==1){
	strcat(str_centaine, dix[u]);

}

//cas particulier des vingts
else if (d==2)
{
	if (u==0) //si 0 on ecrit "vingt"
		strcat(str_centaine, dizaine[d]);
	
	else if (u==1)
	{
		strcat(str_centaine, dizaine[d]);
		strcat(str_centaine, "et un");//si egale a 1, on ecrit vingt et un
	}

	else{
		strcat(str_centaine, dizaine[d]);
		strcat(str_centaine, "-");
		strcat(str_centaine, unite[u]);
	}
}

else if (d==8) // de meme pour vingt
{
	if (u==0){

		strcat(str_centaine, dizaine[d]);//pour l'accord du pluriel
		strcat(str_centaine, "s");
	}
	else if (u==1){
		strcat(str_centaine, dizaine[d]);
		strcat(str_centaine, "-un");
	}

	else
    {
        strcat(str_centaine, dizaine[d]); //l'accord du pluriel
        strcat(str_centaine, "s ");
        strcat(str_centaine, unite[u]);
    }
}

//cas particulier (70 90)
else if ((d==9) || (d==7))
{
	strcat(str_centaine, dizaine[d-1]);// 73=60+13    98 = 80+18
	strcat(str_centaine, "-");
    strcat(str_centaine, dix[u]);
}

else {

	if (u==0)
		strcat(str_centaine, dizaine[d]);
	else if (u==1){

		strcat(str_centaine, dizaine[d]);
		strcat(str_centaine, "et un");
	}

	else {

		strcat(str_centaine, dizaine[d]);
		strcat(str_centaine, "-");
		strcat(str_centaine, unite[u]);
	}
}
return str_centaine;
}

//fct return chiane de characteres 		conversions nomber->lettre

static char *CnvLettreChiffres(long nombre){

	char *str_lettre = malloc(MAX_CHAR_CONV * sizeof(char));

	if (str_lettre==NULL)
	{
		printf("Error\n");
		return NULL;
	}

	memset(str_lettre,0,sizeof(str_lettre));

	if (labs(nombre)<1000000)
	{
		if (nombre!=0)
		{
			while(nombre!=0)
			{
				if (nombre>MILLION)
				{
					long nb = nombre/MILLION;
					strcat(str_letter, centaine(nb));

					if (nb == 1)
						strcat(str_lettre, "Million");
					else
						strcat(str_lettre, "Millions");

					nombre %= (nb*MILLION);

					if (nombre > 0)
								
					strcat(str_lettre, " ");
				}

				else if (nombre>MILLE)
				{
					long nb = nombre/MILLE;
					if (nb == 1)
						strcat(str_lettre, "mille");					
					else
					{
						strcat(str_lettre, centaine(nb));
						strcat(str_lettre, "lettre");
					}

					nombre %= (nb*MILLE);

					if (nombre > 0)
						strcat(str_lettre, " ");	
					
				}
				else 
				 {
				 	strcat(str_lettre, centaine(nombre));
				 	nombre = 0;
				 }
			}
		}

		//cas exeptionnel du 0

		else if (nombre==0)
		{
			strcat(str_lettre, "zero");
		}

		return str_lettre;
	}

	else
	{
		printf("Veuillez saisir un nombre inferieur a un milliard !!\n");
		return NULL;
	}

	return str_lettre;

}

static nbre convStr(char *orig)
{


	size_t i,j, ent=0, virg=0;
	int virgule = 0; //pour la virgule
	int debut = 0; //si on a deja commence a trouver des chiffres: utile pour les tests negatifs
	nbre number;

	number.str = malloc(strlen(orig)*sizeof(char));

	if (number,str==NULL)
	{
		printf("Error\n");

		return number;
	}

	memset(nombre.str,0,sizeof(nombre.str));
    memset(nombre.entier,0,sizeof(nombre.entier));
    memset(nombre.virgule,0,sizeof(nombre.virgule));

    for (i=0; j=0; i<strlen(orig) ; i++)
    {
    	if ((orig[i]=='-') && (debut==0))
    		number.neg = 1;//si on trouve le signe '-' donc le nombre est negatif!!!
    	if ((orig[i]==',') || (orig[i]=='.'))//on prend en compte la premiere virgule ou le premier point
    	{
    		if (virgule==0)
    		{
    			debut=1;//on peut commence meme si on a pas trouve la partie entiere .9 = 0.9
    			number.virg=1;
    			number.str[j]='.';
    			virgule=1;
    			j++;
    		}
    	}

    	else if (isdigit(org[i]))
    	{
    		debut=1;
    		if (virgule==0) //si on a pas trouve la virgule
    		{
    			number.entier[ent]=org[i];
    			virg++; 
    		}
    	}
    }
}