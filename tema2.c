/* Calina Cristian Florin 313 CA */
#include <stdio.h>
#include <math.h>
#define MAX 100
#define EPS 0.000001

//functie de citire
void citire (int nr_elevi,int d,int pondere[MAX],double catalog[MAX][MAX]);

//functie ce calculeaza pozitia fiecarui elev la o proba intr-un vector
double pozitie_proba (int nr_elevi,int d,int poz_proba[MAX][MAX],
				  double distincte[MAX],double catalog[MAX][MAX]);

//functie ce calculeaza p1
double p1 (int nr_elevi,int d,double media_notelor[MAX],int pondere[MAX],
		   double catalog[MAX][MAX]);

//functie ce calculeaza p2
double p2 (int nr_elevi,int d,double poz_medie[MAX],double catalog[MAX][MAX],
			int poz_proba[MAX][MAX],double distincte[MAX]);

//functie ce calculeaza punctajul final
double punctaj_final (int nr_elevi,int d,double media_notelor[MAX],
					  int pondere[MAX],double catalog[MAX][MAX],
					  double poz_medie[MAX],int poz_proba[MAX][MAX],
					  double punctaj_final_elev[MAX],double distincte[MAX]);

/*functie ce creeaza un vector in care se pune locul in functie de punctajul final
pentru fiecare elev in parte*/
double vector_ordine (int nr_elevi,int d,double media_notelor[MAX],
					  int pondere[MAX],double catalog[MAX][MAX],
					  double poz_medie[MAX],int poz_proba[MAX][MAX],
					  double punctaj_final_elev[MAX],int ordine[MAX],
					  double distincte[MAX]);

//functie ce calculeaza clasamentul final si il afiseaza 
double afisare_clasament (int nr_elevi,int d,double media_notelor[MAX],
					  int pondere[MAX],double catalog[MAX][MAX],
					  double poz_medie[MAX],int poz_proba[MAX][MAX],
					  double punctaj_final_elev[MAX],int ordine[MAX],
					  double distincte[MAX]);
					  
//functie ce calculeaza si afiseaza perfectionarea pentru fiecare elev
double afisare_perfectionare (int nr_elevi,int d,double media_notelor[MAX],
					  int pondere[MAX],double catalog[MAX][MAX],
					  double poz_medie[MAX],int poz_proba[MAX][MAX],
					  double punctaj_final_elev[MAX],int ordine[MAX],
					  double distincte[MAX]);
					  
int main ()
{	
	//declarare
	int nr_elevi , d , pondere[MAX] ,poz_proba[MAX][MAX],ordine[MAX];
	double catalog[MAX][MAX] , punctaj_final_elev[MAX] , media_notelor[MAX] ,
			poz_medie[MAX],distincte[MAX];
			
	//citire nr_elevi si nr de discipline + apelarea functiei citire
	scanf ("%d %d",&nr_elevi,&d);
    citire(nr_elevi,d,pondere,catalog);
    
    //apelez functia afisare_clasament ce va calcula si afisa clasamentul
	afisare_clasament(nr_elevi,d,media_notelor,pondere,catalog,poz_medie,
					poz_proba,punctaj_final_elev,ordine,distincte);

	//apelez functia afisare_perfectionare ce va calcula si afisa perfectionarea
	afisare_perfectionare(nr_elevi,d,media_notelor,pondere,catalog,poz_medie,
					poz_proba,punctaj_final_elev,ordine,distincte);				
	return 0;
}


void citire (int nr_elevi,int d,int pondere[MAX],double catalog[MAX][MAX])
{
	int i,j;
	for (i=0;i<d;i++)
	{	
		//citesc ponderile notelor pe a 2'a linie
		scanf("%d",&pondere[i]);
	}
	for (i=0;i<nr_elevi;i++)
	{
		for (j=0;j<d;j++) 
		{
			//citesc matricea cu elevi (pe linii) si discipline(pe coloane)
			scanf("%lf",&catalog[i][j]);
		}
	}
}

double pozitie_proba (int nr_elevi,int d,int poz_proba[MAX][MAX],
				  double distincte[MAX],double catalog[MAX][MAX])
{	
	int j,k,l,i,nr_dist;
	for (j=0;j<d;j++)       
	{				
			nr_dist=0; /*variabila ce retine numarul de numere distincte
			             pentru vectorul distincte*/
			distincte[0]=catalog[0][j];/*vectorul distincte va retine
			notele distincte si va fi initializat cu nota primului elev, 
			la materia j, eliminandu-se (in cazul in care exista) restul 
			aparitilor sale in materia respectiva*/  
			for (k=0; k<nr_elevi; k++)
			{
				for (l=0; l<=nr_dist; l++)
				{
					/*compar nota elevului i cu fiecare materie din vectorul
					 cu note distincte si in caz ca gasesc egalitate intre 
					 acestea ies prin break , necrescand variabila l*/
					if (fabs(catalog[k][j]-distincte[l])<EPS)	
						break;	
				}
				if (l==nr_dist+1) 
				{
					/* daca l a ajuns la valoarea nr_dist+1 inseamna ca 
					 nota elevului i este distincta fata de toate notele
					 din vectorul distincte asa ca o adaug in vectorul
					 acesta crescand si nr_dist*/
					nr_dist++;
					distincte[nr_dist]=catalog[k][j];
				}
			}
			for (i=0;i<nr_elevi;i++)
			{
				/*initializez matricea poz_proba (ce va retine pozitiile
				 notelor din matricea catalog) cu 1 */
				poz_proba[i][j]=1; 
				for (k=0; k<=nr_dist; k++) 
				{
					/* verific daca nota elevului i la materia j este
					 mai mica decat oricare dintre notele din vectorul
					 distincte (pt j) si in caz afirmativ ii cresc pozitia */
					if (distincte[k]-catalog[i][j]>=EPS) 
					{
						poz_proba[i][j]++;
					}
				} 
			}
	}
	return 0;
}

double p1 (int nr_elevi,int d,double media_notelor[MAX],int pondere[MAX],
		   double catalog[MAX][MAX])
{			
	int i,j;
	double sum;
	for (i=0;i<nr_elevi;i++)
	{
		/*vectorul media_notelor se foloseste pentru a retine p1 (media
		tuturor notelor elevului i) */
		media_notelor[i]=0;
		sum=0;
		for (j=0;j<d;j++)
		{
			/* media_notelor creste pentru fiecare materie in parte cu 
			 ponderea * nota la materia respectiva */ 
			media_notelor[i]+=(pondere[j]*catalog[i][j]);
			sum+=pondere[j]; //sum retine suma ponderilor
		}
		/*media_notelor se va imparti la sum pentru a retine p1*/ 
		media_notelor[i]=(double)(media_notelor[i])/(sum*10);
	}
	return 0;
}

double p2 (int nr_elevi,int d,double poz_medie[MAX],double catalog[MAX][MAX],
				int poz_proba[MAX][MAX],double distincte[MAX])
{
	int i,j;
	double sum;
	/*apelez functia pozitie_proba pentru matricea poz_proba*/
	pozitie_proba (nr_elevi,d,poz_proba,distincte,catalog);
	for (i=0;i<nr_elevi;i++)
	{
		/*vectorul poz_medie va retine p2*/
		poz_medie[i]=0;
		sum=0;
		for (j=0;j<d;j++)
		{
			/*variabila sum creste cu pozitia la proba respectiva*/
			sum+=poz_proba[i][j];
		}
		/*pentru a afla p2 voi impartii numarul de materii la suma 
		 pozitiilor ocupate de elev la acestea (conform algoritmului) */ 
		poz_medie[i]=d/sum;
	}
	return 0;
}

double punctaj_final (int nr_elevi,int d,double media_notelor[MAX],
					  int pondere[MAX],double catalog[MAX][MAX],
					  double poz_medie[MAX],int poz_proba[MAX][MAX],
					  double punctaj_final_elev[MAX],double distincte[MAX])
{
	int i;
	//apelez functiile p1 si p2
	p1 (nr_elevi,d,media_notelor,pondere,catalog);
	p2 (nr_elevi,d,poz_medie,catalog,poz_proba,distincte);
	for (i=0;i<nr_elevi;i++)
	{
		//adun in vectorul punctaj_final_elev p1 si p2
		punctaj_final_elev[i]=media_notelor[i]+poz_medie[i];
	}
	return 0;
}

double vector_ordine (int nr_elevi,int d,double media_notelor[MAX],
					  int pondere[MAX],double catalog[MAX][MAX],
					  double poz_medie[MAX],int poz_proba[MAX][MAX],
					  double punctaj_final_elev[MAX],int ordine[MAX],
					  double distincte[MAX])
{
	int i,j,counter;
	// apelez functia punctaj_final pentru vectorul punctaj_final_elev
	punctaj_final(nr_elevi,d,media_notelor,pondere,catalog,poz_medie,poz_proba,
					punctaj_final_elev,distincte);
	for (i=0;i<nr_elevi;i++)       
	{
		counter=0;
		for (j=0;j<nr_elevi;j++)
		{
			/*compar toti elevii cu primul apoi toti cu al 2'lea si asa
			 mai departe.Daca elevii j sunt mai mari decat elevul curent (i),
			 variabila counter creste */
			if ((punctaj_final_elev[j]-punctaj_final_elev[i])>EPS)
			{
				counter++;
			}
		}
	//vectorul ordine pentru elevul i va retine poztia lui ca fiind counter+1
		ordine[i]=counter+1;
	}       
	return 0;
}          

double afisare_clasament (int nr_elevi,int d,double media_notelor[MAX],
					  int pondere[MAX],double catalog[MAX][MAX],
					  double poz_medie[MAX],int poz_proba[MAX][MAX],
					  double punctaj_final_elev[MAX],int ordine[MAX],
					  double distincte[MAX])
{
	int counter,i,j;
	//apelez functia vector_ordine pentru vectorul ordine[i]
	vector_ordine (nr_elevi,d,media_notelor,pondere,catalog,poz_medie,poz_proba,
					punctaj_final_elev,ordine,distincte);
	counter=1;          
	printf("Clasament:\n");
	for (i=1;i<=nr_elevi;i++)
	{
		for (j=0;j<nr_elevi;j++)
		{
			/*parcurg tot vectorul ordine si caut elevul de pe prima pozitie 
			afisandu-l , dupa aceea pe urmatorul de pe urmatoarea pozitie si asa
			mai departe*/
			if (ordine[j]==i)
			{
				printf ("%d.elev%d\n",counter,j+1);
				counter++;
			}
		}
	}
	return 0;
}


double afisare_perfectionare (int nr_elevi,int d,double media_notelor[MAX],
					  int pondere[MAX],double catalog[MAX][MAX],
					  double poz_medie[MAX],int poz_proba[MAX][MAX],
					  double punctaj_final_elev[MAX],int ordine[MAX],
					  double distincte[MAX])
{
	int i,j,s,materie,loc1;
	double catalog2[MAX][MAX], max, nota;
	printf("\n");
	printf ("Perfectionare:\n");
	for (i=0;i<nr_elevi;i++)
	{
		for (j=0;j<d;j++)
		{
			/*iau o matrice clona pentru matricea catalog*/
			catalog2[i][j]=catalog[i][j];
		}
	}
	vector_ordine(nr_elevi,d,media_notelor,pondere,catalog2,poz_medie,poz_proba,
				  punctaj_final_elev,ordine,distincte);
	for (i=0;i<nr_elevi;i++)
	{
		/*daca gasesc elevul de pe prima pozitie il retin in variabila loc1
		 si ies din for prin break;*/
		if (ordine[i]==1)
		{
			loc1=i;
			break;
		}
	}
	
	for (i=0;i<nr_elevi;i++)
	{
		/*initializez variabila s (ce va retine numarul de materii minime
		 la care elevul trebuie sa ia 10 pentru a ajunge pe pozitia 1) cu 0
		 pentru fiecare elev in parte*/
		s=0;
		while (ordine[i]>ordine[loc1])
		{
		/*Atat timp cat pozitia elevului i nu a depasit(sau egalat) pozitia 
		 elevului de pe primul loc voi lua o variabila max initializata cu 0
		 ce va retine materia cu influenta maxima si variabila materie
		 pentru a retine pozitia materii(j-ul) cu influenta maxima*/
			max=0;
			materie=0;
			for (j=0;j<d;j++)
			{
				/*daca nota elevului i la materia j este deja 10 trec 
				 la urmatoarea materie*/
				if (catalog2[i][j]==10) 
				{
					continue;
				}
				/*variabila nota va pastra nota elevului i la disciplina j*/
				nota=catalog2[i][j];
				/*ii schimb nota elevului i la materia j cu 10*/
				catalog2[i][j]=10;
				/*apelez functia punctaj_final pentru a calcula punctajul
				 final cu noua nota*/
				punctaj_final(nr_elevi,d,media_notelor,pondere,catalog2,
						poz_medie,poz_proba,punctaj_final_elev,distincte);
				/*daca punctajul final este mai mare ca variabila max atunci
				 ii voi atribui variabilei max valoarea punctajului final
				 si voi retine pozitia acestei materii prin variabila materie*/
				if (punctaj_final_elev[i]>max)
				{
					max=punctaj_final_elev[i];
					materie=j;
				}
				/*ii reatribui nota initiala elevului i la materia j si verific
				pentru urmatoarea materie*/
				catalog2[i][j]=nota;
			}
			/*ii atribui elevului i nota 10 la materia cu cea mai mare
			 influenta si reintru in while in caz ca nu l-a depasit pe cel de pe
			 primul loc. Numarul minim necesar de note (s) pentru a-l depasi  
			 pe elevul de pe primul loc creste cu 1*/
			catalog2[i][materie]=10;
			vector_ordine(nr_elevi,d,media_notelor,pondere,catalog2,
				poz_medie,poz_proba,punctaj_final_elev,ordine,distincte);
			s++;
		}
		/*dupa ce se iese din while ii reatribui notele elevului i din catalogul
		 initial si trec la urmatorul elev */
		printf("elev%d: %d\n",i+1,s);
		for (j=0;j<d;j++)
			{
				catalog2[i][j]=catalog[i][j];      
			}
	}
	return 0;
}
