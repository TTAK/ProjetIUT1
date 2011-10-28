#include "stdafx.h"
#include "stdlib.h"
#include "string.h"
#define Maxtrain 8
#define Maxprov 12

typedef char CH15[16];


typedef struct strTrain strTrain;
struct strTrain // Structure affichage des trains
{
	int num;
	int i_prov;
	int heure; // Heure d'arrivée en minutes
	char quai;
};

typedef struct strProv strProv;
struct strProv // Structure affichage des trains
{
	CH15 nom;
	int nbtraintot; // Nombre de trains total de cette provenance depuis le début de l'execution du programme
	int nbtrainact; // Nombre de trains total de cette provenance actuelement affiché
};


int main()
{
    int affichage_ecran(strTrain Tab_Train[],strProv Tab_Provenance[], int NbTrainGare);
    int s_quai();
    int s_prov(strProv Tab_prov[Maxprov]);
    int code_A(strTrain Tab_Train[], strProv Tab_Provenance[], int* p_NbTrain, int nbQuai);
	int code_R(strTrain Tab_Train[],strProv Tab_Provenance[], int nbTrain, int nbQuai);
	int code_Q(strTrain Tab_Train[],strProv Tab_Provenance[], int nbTrain, int nbQuai);
	int code_D(strTrain Tab_Train[], int* nbTrainP);

    strTrain Tab_Train[Maxtrain];
    strProv Tab_Provenance[Maxprov];

    int nbTrain =0, nbQuai;
    int *p_nbTrain = &nbTrain;
    char code;

    int nbProv=s_prov(Tab_Provenance);
    if(nbProv < 0)
    {
        return -2;
    }

    nbQuai=s_quai();
	if(nbQuai < 0)
	{
		return -3;
	}

    affichage_ecran(Tab_Train, Tab_Provenance, nbTrain);
	do
	{
		printf("Veuillez entrer un code de mise … jour : ");
		code=getchar();
		fflush(stdin);
		switch(code)
		{
			case 'A':
				code_A(Tab_Train, Tab_Provenance, p_nbTrain, nbQuai);
				affichage_ecran(Tab_Train, Tab_Provenance, nbTrain);
				fflush(stdin);
				break;

			case 'R':
				code_R(Tab_Train, Tab_Provenance, *p_nbTrain, nbQuai);
				affichage_ecran(Tab_Train, Tab_Provenance, nbTrain);
				fflush(stdin);
				break;

			case 'Q':
				code_Q(Tab_Train, Tab_Provenance, *p_nbTrain, nbQuai);
				affichage_ecran(Tab_Train, Tab_Provenance, nbTrain);
				fflush(stdin);
				break;
			case 'D':
				code_D(Tab_Train,&nbTrain);
				affichage_ecran(Tab_Train, Tab_Provenance, nbTrain);
				fflush(stdin);
				break;

			default:
				if (code !='F') printf("Erreur : Les codes disponibles sont A, R, Q, D, V, P, F");
				break;
		}
	}while(code !='F');


	system("PAUSE");
    return 0;
}

int affichage_ecran(strTrain Tab_Train[],strProv Tab_Provenance[], int nbTrainGare)
{
    system("cls");//Netoyage dee l'écran avant l'affichage
    int i;
    //Carractère de Tableau mal affiché par l'éditeur, ils ont été choisit en police Teminal pour une compatibilitée avec tout les systèmes windows.
    printf("ÉÍÍÍÍÍÍÍÍÍËÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍËÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍËÍÍÍÍÍ»\n");//Haut du Tableau d'affichage
    printf("ºTrain Nø ºEn provenance deºHeure d'arriv‚eºQuai º\n");//Nom des champ du Tableau
    printf("ÌÍÍÍÍÍÍÍÍÍÎÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÎÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÎÍÍÍÍÍ¹\n");//Separation horizontale

    for(i=0; i<nbTrainGare; i++)
    {
        //Affiche les trains, 1 train par ligne, jusqu'à NbTrainGare
        printf("º-- %03d --º%-16sº---- %02dh%02d ----º- %c -º\n",Tab_Train[i].num, Tab_Provenance[Tab_Train[i].i_prov].nom, Tab_Train[i].heure/60, Tab_Train[i].heure%60, Tab_Train[i].quai);
    }
    printf("ÈÍÍÍÍÍÍÍÍÍÊÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÊÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÊÍÍÍÍÍ¼\n");//Bas du Tableau d'affichage

	return 0;
}

int s_quai()
{
    int nbQuai;
    printf("Veuillez entrer le nombre de quai : ");
    scanf("%d",&nbQuai);
    fflush(stdin);
    if(nbQuai>6 || nbQuai<1)
    {
        printf("Erreur : Le nombre de quais doit etre compris entre 1 et 6 \nla valeur %d ne convient donc pas\n\n\n\n\n",nbQuai);
		system("pause");
        nbQuai=-1;
    }
	return nbQuai;
}

int s_prov(strProv Tab_Provenance[Maxprov])
{
    int i, j;
    int nbProv;
    int t_inTabProv(strProv Tab_Provenance[], int max, CH15 prov);

    printf("Entrer le nombre total de provenances : ");
    scanf("%d",&nbProv);
    fflush(stdin);
    CH15 prov;

    if(nbProv<1 || nbProv > Maxprov)
    {
        printf("Erreur : Le nombre de provenances doit etre compris entre 1 et 12 \nla valeur %d ne convient donc pas\n\n\n\n\n",nbProv);
        return -1;
    }
    printf("Entrez la provenance nø1 : ");
    gets(Tab_Provenance[0].nom);
    for(i=1;i<nbProv;i++)
    {
        printf("Entrer la provenance nø%d : ",i+1);
        gets(prov);
        j=i;

        while(t_inTabProv(Tab_Provenance, i, prov) == 0)
		{
			printf("Erreur : La provenance existe déjà dans le tableau");
			printf("Entrer la provenance nø%d : ",i+1);
			gets(prov);
		}


		while(strcmp(prov, Tab_Provenance[j-1].nom)<0 && j>0)
		{
			strcpy(Tab_Provenance[j].nom, Tab_Provenance[j-1].nom);
			j=j-1;
		}
		strcpy(Tab_Provenance[j].nom, prov);

    }
    return nbProv;
}


int code_A(strTrain Tab_Train[],strProv Tab_Provenance[], int* p_nbTrain, int nbQuai)
{
	int t_errmin_code_A(strTrain Tab_Train[], int nbTrain, char quai, int heure);
	int t_code_A_errquai(int quai, int nbQuai);

    int num, hh, mm, i=0;
    CH15 prov;
    char quai;

    if (*p_nbTrain == Maxtrain)
    {
        printf("Erreur : Le nombre maximum de trains est d‚jà atteint");
		return -1;
    }

    printf("Veuillez saisir le num‚ro du train : ");
    scanf("%d", &num);
    for (i=0; i<Maxtrain; i++)
    {
        if (Tab_Train[i].num == num)
        {
			printf("Erreur : Le num‚ro du train entr‚ existe d‚j…");
			printf("Veuillez saisir le numéro du train : ");
			scanf("%d", &num);
            i = 0;
        }
    }
    fflush(stdin);

    printf("Veuillez saisir le libell‚ de sa provenance : ");
    gets(prov);
    i=0;
    while(strcmp(Tab_Provenance[i].nom, prov) != 0) // Tant que la provenance tapée est absente du tableau de provenances
    {
        i++; // Incrémenter i pour avancer dans le tableau de provenances
        if (i==Maxprov) // Si i atteint le maximum de provenances
        {
			printf("Erreur : La provenance est inconnue"); // Alors la provenance tapée n'est pas dans le tableau
     	    printf("Veuillez saisir le libell‚ de sa provenance : ");
            gets(prov);// On redemande la provenance
			i=0;// On remet i zéro pour relancer le parcours du tableau
        }
    } // On sort du while avec la confirmation que la provenance tapée est dans le tableau de provenances

    printf("Veuillez saisir l'heure d'arriv‚e du train : ");
    scanf("%d", &hh);
	printf("Veuillez saisir les minutes : ");
	scanf("%d", &mm);
    fflush(stdin);

    printf("Veuillez saisir la lettre du quai correspondant au train : ");
    quai=getchar();

	if (t_code_A_errquai(quai, nbQuai) || t_errmin_code_A(Tab_Train, *p_nbTrain, quai, (hh*60 + mm)))
	{
		quai=' ';
	}

	// *p_Nbtrain correspond à la position à laquelle nous allons affectez le nouveau train

    Tab_Train[(*p_nbTrain)].num = num;
    Tab_Train[(*p_nbTrain)].i_prov = i;
    Tab_Train[(*p_nbTrain)].heure = hh*60 + mm; // On remet les heures en minutes et on les ajoute aux minutes contenu dans mm entré par l'utilisateur
    Tab_Train[(*p_nbTrain)].quai = quai;

    *p_nbTrain = *p_nbTrain + 1;

	Tab_Provenance[i].nbtrainact++; // On incrémente le nombre trains actuellement prévu pour cette provenance
	Tab_Provenance[i].nbtraintot++; // On incrémente le nombre trains passés par cette provenance

    return 0;
}

int code_R(strTrain Tab_Train[],strProv Tab_Provenance[], int nbTrain, int nbQuai)
{
	int t_errmin_code_R(strTrain Tab_Train[], int nbTrain, char quai, int heure, int numtrainmodif);

	int num, hh, mm, i;

	printf("Veuillez saisir le num‚ro du train : ");
    scanf("%d", &num);
    for (i=0; i<Maxtrain; i++)
    {
        if (Tab_Train[i].num == num)
        {
			break;
		}
		if (i==(Maxtrain-1))
		{
			printf("Erreur : Le num‚ro du train entr‚ n'existe pas");
			printf("Veuillez saisir le num‚ro du train : ");
			scanf("%d", &num);
			i = 0;
		}
    }

	printf("Veuillez saisir l'heure d'arriv‚e du train : ");
    scanf("%d", &hh);
	printf("Veuillez saisir les minutes : ");
	scanf("%d", &mm);
    fflush(stdin);

	if (t_errmin_code_R(Tab_Train, nbTrain, Tab_Train[i].quai, (hh*60 + mm), i))
	{
		Tab_Train[i].quai=' ';
	}

	Tab_Train[i].heure = hh*60 + mm; // On remet les heures en minutes et on les ajoute aux minutes contenu dans mm entré par l'utilisateur

	return 0;
}

int code_Q(strTrain Tab_Train[],strProv Tab_Provenance[], int nbTrain, int nbQuai)
{
	int t_errmin_code_Q(strTrain Tab_Train[], int nbTrain, char quai, int heure);
	int t_errquai_code_Q(int quai, int nbQuai);

	int num, i;
	char quai;

	printf("Veuillez saisir le num‚ro du train : ");
    scanf("%d", &num);
    fflush(stdin);
    for (i=0; i<Maxtrain; i++)
    {
        if (Tab_Train[i].num == num)
        {
			break;
		}
		if (i==(Maxtrain-1))
		{
			printf("Erreur : Le num‚ro du train entr‚ n'existe pas");
			printf("Veuillez saisir le num‚ro du train : ");
			scanf("%d", &num);
			i = 0;
		}
    }

	printf("Veuillez saisir la lettre du quai correspondant au train : ");
    quai=getchar();

	if (t_errquai_code_Q(quai, nbQuai) || t_errmin_code_Q(Tab_Train, nbTrain, quai, Tab_Train[i].heure))
	{
		quai=' ';
	}

	Tab_Train[i].quai= quai;

	return 0;
}

int code_D(strTrain Tab_Train[], int* nbTrainP)
{
    int i,j;//Initialisation compteurs
    int numTrain;//Variable numero du train rechercher
    printf("Entrez le numero du train au depart : ");
    scanf("%d",numTrain);//Récuperation de numTrain

    for(i=0;i<*nbTrainP;i++)//on balaye tout le tableau d'affichage de train
    {
        if(Tab_Train[i].num==numTrain)//On regarde si la case i contien le train numero numTrain
        {
            *nbTrainP=*nbTrainP - 1;//Si le train est trouvée on enlève 1 au nombre de train
            for(j=i;j<(*nbTrainP);j++)//on decale ensuite les trains
            {
                Tab_Train[i]=Tab_Train[i+1];//pas de problème avec la taille du tableau on s'arrete à i=(nbTrain-1)
            }
            return 0;//si tout c'est bien passé, on renvoi 0
        }
    }
    return -1;//sinon on renvoi 1
}


int t_inTabProv(strProv Tab_Provenance[], int max, CH15 prov)
{
    int a=1, k;
    for(k=0; strcmp(prov, Tab_Provenance[k].nom)>0 && k<=max; k++)
    {
        if(strcmp(prov, Tab_Provenance[k].nom)==0)
        {
            a=0;
        }
    }
    return a;
}


int t_errmin_code_A(strTrain Tab_Train[], int nbTrain, char quai, int heure)
{
	int j;

	for (j=0; j < nbTrain; j++)
	{
		if (Tab_Train[j].quai == quai)
		{
			if ((Tab_Train[j].heure - (heure)) < 30)
			{
				printf("Erreur : Le d‚lai de 30 minutes n'est pas respect‚\n");
				return 1;
			}
		}
	}
	return 0;
}

int t_errmin_code_R(strTrain Tab_Train[], int nbTrain, char quai, int heure, int numtrainmodif)
{
	int j;

	for (j=0; j < nbTrain; j++)
	{
		if (Tab_Train[j].quai == quai && numtrainmodif != j)
		{
			if ((Tab_Train[j].heure - (heure)) < 30)
			{
				printf("Erreur : Le d‚lai de 30 minutes n'est pas respect‚\n");
				return 1;
			}
		}
	}
	return 0;
}

int t_errmin_code_Q(strTrain Tab_Train[], int nbTrain, char quai, int heure)
{
	int j;

	for (j=0; j < nbTrain; j++)
	{
		if (Tab_Train[j].quai == quai)
		{
			if ((Tab_Train[j].heure - (heure)) < 30)
			{
				printf("Erreur : Le d‚lai de 30 minutes n'est pas respect‚\n");
				return 1;
			}
		}
	}
	return 0;
}


int t_errquai_code_Q(int quai, int nbQuai)
{
	if (('A' > quai) || (quai >= ('A'+ nbQuai)))
	{
		printf("Erreur : Le num‚ro de quai entr‚ est en dehors des quais disponibles\n");
		return 1;
	}
	return 0;
}

int t_code_A_errquai(int quai, int nbQuai)//Nom pas homogène avec le reste
{
	if (('A' > quai) || (quai >= ('A'+ nbQuai)))
	{
		printf("Erreur : Le num‚ro de quai entr‚ est en dehors des quais disponibles\n");
		return 1;
	}
	return 0;
}

