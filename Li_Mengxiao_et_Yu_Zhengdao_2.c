
#include <stdio.h>
#include <stdlib.h>

/*************************************************/
/*                                               */
/*                sucre syntaxique               */
/*                                               */
/*************************************************/

#define AND &&
#define OR ||
#define ISNOT !=
#define NOT !
#define then

typedef enum { FALSE, TRUE} bool;
int cpt;

/*************************************************/
/*                                               */
/*          definition type liste                */
/*                                               */
/*************************************************/

typedef struct Bloc
{
    int nombre;
    struct Bloc *suivant;
} Bloc;

typedef Bloc *Liste ;

/*************************************************/
/*                                               */
/*                predeclarations                */
/*                                               */
/*************************************************/

/* initialise une Liste � vide */
void initVide(Liste *L);

/* renvoie 1 si la Liste en parametre est vide, 0 sinon */
bool estVide(Liste l);

/* renvoie le premier element de la Liste en parametre */
int premier(Liste l);

/* renvoie une nouvelle Liste correspondant a celle en parametre, avec l'element x ajoute en haut de la pile */
Liste ajoute(int x, Liste l);

/* modifie la Liste en parametre: x est ajoute comme premier element */
void empile(int x, Liste* L);

/* renvoie une nouvelle Liste correspondant a celle en parametre sans son premier element */
Liste suite(Liste l);

/* modifie la Liste en parametre: le premier element est retire */
void depile(Liste* l);

/* affichage simple en recursif et en iteratif */
void affiche_rec(Liste l);
void affiche_iter(Liste l);

/* longueur en recursif et en iteratif */
int longueur_rec (Liste l);
int longueur_iter (Liste l);

/*  Elimination du dernier element en recursif et en iteratif  */
/*  VD est la sousprocedure utilitaire de la version recursive */
void VD (Liste *L);
void VireDernier_rec (Liste *L);
void VireDernier_iter (Liste *L);


/*************************************************/
/*                                               */
/*                briques de base                */
/*                                               */
/*************************************************/


void initVide( Liste *L)
{
    *L = NULL ;
}

bool estVide(Liste l)
{
    return l == NULL ;
}

int premier(Liste l)
{
    return l->nombre ; 
}

Liste ajoute(int x, Liste l)
{
    Liste tmp = (Liste) malloc(sizeof(Bloc)) ;
    cpt++;
    tmp->nombre = x ;
    tmp->suivant = l ;
    return tmp ;
}

void empile(int x, Liste *L)
{
      *L = ajoute(x,*L) ; 
}

Liste suite(Liste l)
{
    return l->suivant ;
}


void depile(Liste *L)
{
    Liste tmp = *L ;
    *L = suite(*L) ;
    free(tmp) ;
}

/*************************************************/
/*                                               */
/*     Affiche, avec les briques de base         */
/*                                               */
/*************************************************/

void affiche_rec(Liste l)
{
    if(estVide(l))
        printf("\n");
    else
    {
        printf("%d ", premier(l));
        affiche_rec(suite(l));
    }
}


void affiche_iter(Liste l)
{
    Liste L2 = l;
    while(!estVide(L2))
    {
        printf("%d ", premier(L2));
        L2 = suite(L2);
    }
    printf("\n");
}
void affiche_iter1(Liste l)
{
    Liste L2 = l;
    while(!estVide(L2))
    {
        printf("%d ", premier(L2));
        L2 = suite(L2);
    }
 
}

/*************************************************/
/*                                               */
/*     Longueur, sans les briques de base        */
/*                                               */
/*************************************************/

int longueur_rec (Liste l)
{
    if (l == NULL)
         return 0 ;
    else return (1 + longueur_rec(l->suivant)) ;
}


int longueur_iter (Liste l)
{
    Liste P = l;
    int cpt = 0 ;
    while (P ISNOT NULL)
    {   P = P->suivant ;
        cpt++ ;
    }
    return cpt ;
}

/*************************************************/
/*                                               */
/*       VireDernier,                            */
/*               sans les briques de base,       */
/*               ni le "->"                      */
/*                                               */
/*************************************************/

void VD (Liste *L)
          // *L non NULL ie liste non vide
{
     if ( ((**L).suivant) == NULL )
            depile(L) ;   // moralement : depile(& (*L)) ;
     else VD (& ( (**L).suivant )) ;
}

void VireDernier_rec (Liste *L)
{
     if ( (*L) ISNOT NULL )
          VD(L);        // moralement : VD(& (*L)) ;
}

void VireDernier_iter (Liste *L)
{
    if ( (*L) ISNOT NULL)
    {
        while ( ((**L).suivant) ISNOT NULL )
                 L = & ( (**L).suivant ) ;
        free(*L) ;
        *L = NULL ;
     }
}


/*************************************************/
/*                                               */
/*       Libere la memoire                       */
/*                                               */
/*************************************************/

void VideListe(Liste *L)
{
    if(NOT(estVide(*L)))
    {
        depile(L);
        VideListe(L);
    }
      
}

/*************************************************/
/*                                               */
/*           Projet                               */
/*                                               */
/*************************************************/


/*************************************************/
/*      Q1 ZeroEnPositionUnOuDeuxOuTrois         */
/*************************************************/
bool aux(Liste l,int i){
    if(estVide(l)||i>=3)
        return FALSE;
    if(i<3 && premier(l)==0){
        return TRUE;
    }
    i++;
    return aux(suite(l),i);
}
bool ZeroEnPositionUnOuDeuxOuTrois(Liste l){
    return aux(l,0);    
}

/*************************************************/
/*               Q2 Pluscourte                   */
/*************************************************/
bool Pluscourte(Liste l1,Liste l2){
    if(estVide(l1) && l2 != NULL){
        return TRUE;
    }else if(estVide(l2)){
        return FALSE;
    }else{
        return Pluscourte(suite(l1),suite(l2));
    }
}

/*************************************************/
/*          Q3 NombreDe0AvantPositionK           */
/*************************************************/
//Une version recursive sans sous-fonctionnalite
int NombreDe0AvantPositionK(Liste l,int k){
    if(k==0 || estVide(l)){
        return 0;
    }else if(premier(l)==0){       
        return 1+NombreDe0AvantPositionK(suite(l),k-1);
    }else{       
        return NombreDe0AvantPositionK(suite(l),k-1);
    }
}
//Une version iterative 
int NombreDe0AvantPositionK1(Liste l,int k){
    int r=0;
    if(estVide(l)){
        return r;
    }else{
        while(k!=0 && NOT(estVide(l))){
            if(premier(l)==0){
                r++;
            }
            l=suite(l);
            k--;
        }
        return r;
    }
}
//Une version qui utilise une sous-fonction recursive terminale avec argument(s) supplementaire(s). 
int aux_NombreDe0AvantPositionK2(Liste l,int k,int r){
    if(k==0 || estVide(l)){
        return r;
    }else{
        if(premier(l)==0){
            r++;
        }
        return aux_NombreDe0AvantPositionK2(suite(l),k-1,r);
    }
}
int NombreDe0AvantPositionK2(Liste l,int k){
     return aux_NombreDe0AvantPositionK2(l,k,0);
}

//Une version qui utilise une sous-procedure recursive terminale avec argument(s) supplementaire(s).
void aux_NombreDe0AvantPositionK3(Liste l,int k,int *r){
    if(k!=0 && NOT(estVide(l))){
        if(premier(l)==0){
            *r=*r+1;
        }
        aux_NombreDe0AvantPositionK3(suite(l),k-1,r);
    }
}
int NombreDe0AvantPositionK3(Liste l,int k){
    int r=0;
    aux_NombreDe0AvantPositionK3(l,k,&r);
    return r;
}
/*************************************************/
/*         Q4 NombreDe0ApresRetroPositionK       */
/*************************************************/

void aux_NombreDe0ApresRetroPositionK(Liste l,int k,int *cpt,int *r){
    if(estVide(l)){
        *r=0;
        *cpt=0;
    }else{
        aux_NombreDe0ApresRetroPositionK(suite(l),k,cpt,r);
        *r=*r+1;
        if((*r)<=k && premier(l)==0){
            *cpt=*cpt+1;
        }
    }       
    
}
int NombreDe0ApresRetroPositionK(Liste l,int k){
    int cpt,r;
    aux_NombreDe0ApresRetroPositionK(l,k,&cpt,&r);
    return cpt;
}
/*************************************************/
/*                Q5 FctBegaye                   */
/*************************************************/
//une fonction recursive simple sans sous-fonctionnalit
Liste FctBegaye(Liste l){
    if(estVide(l)){
        Liste l1;
        initVide (&l1);
        return l1;
    }else{
        Liste l2=FctBegaye(suite(l));
        if(premier(l)>0){
            empile(premier(l), &l2);
            empile(premier(l), &l2);
        }
        return l2;
    }   
}
//une fonction recursive terminale
void aux_FctBegaye1(Liste l1,Liste *l2){
    if(estVide(l1)){
        initVide (l2);
        
    }else{
        aux_FctBegaye1(suite(l1),l2);
        if(premier(l1)>0){
            empile(premier(l1), l2);
            empile(premier(l1), l2);
        }
        
    }

}
Liste FctBegaye1(Liste l){
    Liste l1;
    aux_FctBegaye1(l,&l1);
    return l1;
}
//iterative
Liste FctBegaye2(Liste l){
    Liste l1;
    initVide (&l1);
    while (NOT(estVide(l)))
    {
        if(premier(l)>0){
            empile(premier(l),&l1);
            empile(premier(l),&l1);
        }
        l=suite(l);
    }
    Liste l2;
    initVide (&l2);
    while (NOT(estVide(l1)))
    {
        empile(premier(l1),&l2);
        l1=suite(l1);
    }
    return l2;
    
    
}

/*************************************************/
/*                Q6 ProcBegaye                  */
/*************************************************/
/*************************************************/
/*                                               */
/*       PointeurSuite                           */
/*                                               */
/*************************************************/

Liste* PointeurSuite(Liste *l)
{
    return (&((**l).suivant));
}
//Question6
void aux_ProcBegaye(Liste *l){
    if(NOT(estVide(*l))){
       
       if(premier(*l)>0){
            empile(premier(*l),l);
            aux_ProcBegaye(PointeurSuite(PointeurSuite(l)));
       }else{
            depile(l);
            aux_ProcBegaye(l);
       }
        
    }

}
void ProcBegaye(Liste l){

    aux_ProcBegaye(&l);
    affiche_iter(l);
    
}
/*************************************************/
/*              Q7 Permutations                  */
/*************************************************/
/*************************************************/
/*                                               */
/*     definition type liste de liste            */
/*               Permutations                    */
/*************************************************/

typedef struct BlocListL
{
    Liste liste;
    struct BlocListL *suivant;
} BlocListL;

typedef BlocListL *ListeL;

void initVideListL( ListeL *LL)
{
    *LL = NULL ;
}
bool estVideListL(ListeL ll)
{
    return ll == NULL ;
}

Liste premierListL(ListeL ll)
{
    return ll->liste ; 
}
ListeL suiteListL(ListeL ll){
    return ll->suivant;
}

ListeL ajouteListL(Liste l, ListeL ll)
{
    ListeL tmp = (ListeL) malloc(sizeof(BlocListL)) ;
    tmp->liste = l ;
    tmp->suivant = ll ;
    cpt++;
    return tmp ;
}
void empileListL(Liste l, ListeL *LL)
{
      *LL = ajouteListL(l,*LL) ; 
}
void affiche_iterListL(ListeL ll)
{
    ListeL L2 = ll;
    while(!estVideListL(L2))
    {
        printf("[");
        affiche_iter1(premierListL(L2));
        printf("]");
        L2 = suiteListL(L2);
    }
    printf("");
}

/*************************************************/
/*               Permutations                    */
/*************************************************/
ListeL Concat(ListeL l1,ListeL l2){
    if(estVideListL(l1)){
        return l2;
    }else{
        return ajouteListL(premierListL(l1),Concat(suiteListL(l1),l2));
    }
}
ListeL AETTL(int x,ListeL ll){
    if(estVideListL(ll)){
        return ll;
    }else{
        return ajouteListL(ajoute(x,premierListL(ll)),AETTL(x,suiteListL(ll)));
    }

} 
ListeL ATP(int x, Liste l){
    if(estVide(l)){
        ListeL ll;
        initVideListL(&ll);
        empile(x, &l);
        return ajouteListL(l,ll);
    }else{
        return ajouteListL(ajoute(x,l),AETTL(premier(l),ATP(x,suite(l))));
    }
}
ListeL ATLTP(int x,ListeL ll){//
    if(estVideListL(ll)){
        return ll;//
    }else{
        return Concat(ATP(x,premierListL(ll)),ATLTP(x,suiteListL(ll)));
    }
}
ListeL Permutations(int n){
    if(n==0){
        ListeL ll;
        initVideListL(&ll);
        Liste l;
        initVide(&l);
        return ajouteListL(l,ll);//
    }else{
        return ATLTP(n,Permutations(n-1));
    }       
}


/*************************************************/
/*                Q8 ListesBis                   */
/*************************************************/
typedef struct Blocp
{
    int nombre;
    struct Blocp *suivant;
    struct Blocp *pred;
    
    
} Blocp;

typedef Blocp *ListesBis ;


void initVideListB( ListesBis *L)
{
    *L=(ListesBis)malloc(sizeof(Blocp));
    (*L)->suivant=NULL;
    (*L)->pred=NULL;
    
} 
bool estVideListB(ListesBis ll)
{
    return ll == NULL ;
}

int premierListB(ListesBis l)
{
    return l->suivant->nombre; 
}
ListesBis suiteListB(ListesBis l)
{
    return l->suivant ;
}
ListesBis pred(ListesBis l)
{
    return l->pred ;
}
ListesBis ajouteListB(int x, ListesBis l)
{   
    ListesBis tmp = (ListesBis) malloc(sizeof(Blocp)) ;
    tmp->nombre = x ;
    tmp->suivant = l->suivant;
    tmp->pred=l;
    if(suiteListB(l)){
        l->suivant->pred=tmp;
        l->suivant=tmp;

    }else{
        l->suivant=tmp;
    } 
      
    return l ;
}

void affiche_iterListB(ListesBis l)
{
    ListesBis L2 = l->suivant;
    while(!estVideListB(L2))
    {
        printf("%d ", L2->nombre);
        L2 = suiteListB(L2);
    }
    printf("\n");
}

void depileListB(ListesBis *L)
{
    ListesBis tmp = *L ;
    *L = suiteListB(*L) ;
    free(tmp) ;
}

void retireP(int *pointe,ListesBis *l){   
    ListesBis p=suiteListB(*l);
    while (!estVideListB(p))
    {
        if((p->nombre)==*pointe){
            p->pred->suivant=suiteListB(p);
            if(suiteListB(p)){
                p->suivant->pred=p->pred;
            }       
            free(p); 
            break;
            
                      
        }else{
            p=suiteListB(p);
            
        }
    }
        
} 



/*************************************************/
/*                                               */
/*           Main                                */
/*                                               */
/*************************************************/

void poup (Liste l)
{
        printf("Double Affichage \n") ;
        affiche_rec(l) ;
        affiche_iter(l) ;

        printf("Longueur en double %d %d \n\n", 
                           longueur_rec(l), 
                           longueur_iter(l) 
               ) ;
}

int main(int argc, char** argv)
{
    //teacher
    Liste l ;

        initVide (&l) ;

          poup(l) ;

             empile(4, &l) ;

          poup(l) ;

             empile(5, &l) ;
             empile(6, &l) ;
             empile(7, &l) ;
             empile(8, &l) ;
             empile(9, &l) ;

          poup(l) ;
        

        VireDernier_rec  (&l) ;
        VireDernier_iter (&l) ;
        depile(& l) ;

          poup(l) ;

    VideListe(&l);
    //my test

    //Q1
    printf("\nQ1\n");
    printf("ZeroEnPositionUnOuDeuxOuTrois\n"); 
    Liste l1;
        initVide (&l1);
        empile(5, &l1);
        empile(6, &l1);
        empile(7, &l1);
        empile(8, &l1);
        empile(0, &l1);
        printf("liste:\n");
    affiche_iter(l1);
    printf("%d\n",ZeroEnPositionUnOuDeuxOuTrois(l1));
    if(ZeroEnPositionUnOuDeuxOuTrois(l1)) printf("true\n");
    else printf("false\n");
//Q2
    printf("\nQ2\n");
    printf("Pluscourte\n"); 
    Liste l2;
      initVide (&l2);
        empile(5, &l2);
        empile(6, &l2);
        
    printf("1er:liste\n");
    affiche_iter(l2);
    printf("2nd:liste\n");
    affiche_iter(l1);  
    printf("%d\n",Pluscourte(l2,l1));
    if(Pluscourte(l2,l1)) printf("true\n");
    else printf("false\n");

//Q3
    printf("\nQ3\n"); 
    printf("NombreDe0AvantPositionK\n"); 
    Liste l3;
        initVide (&l3);
        empile(0, &l3);
        empile(1, &l3);
        empile(0, &l3);
        empile(0, &l3);
        empile(0, &l3);
        empile(9, &l3);
        empile(6, &l3);
        empile(5, &l3);
        empile(0, &l3);
        empile(2, &l3);
    Liste l4;
        initVide (&l4);
        empile(3, &l4);
        empile(0, &l4);    
        empile(0, &l4);    
        empile(5, &l4);     
    printf("1er:liste l3\n");
    affiche_iter(l3);
    printf("2nd:liste l4\n");
    affiche_iter(l4);            
    printf("le nombre 0 avant position 6\n");    
    printf("version recursive avec l3:%d\n",NombreDe0AvantPositionK(l3,6)); 
    printf("version recursive avec l4:%d\n",NombreDe0AvantPositionK(l4,6));

    printf("version iterative avec l3:%d\n",NombreDe0AvantPositionK1(l3,6)); 
    printf("version iterative avec l4:%d\n",NombreDe0AvantPositionK1(l4,6));
       
    printf("version recursive sous-fonc avec l3:%d\n",NombreDe0AvantPositionK2(l4,6));
    printf("version recursive sous-fonc avec l4:%d\n",NombreDe0AvantPositionK2(l3,6));

    printf("version recursive-sous procedure avec l3:%d\n",NombreDe0AvantPositionK3(l4,6));
    printf("version recursive-sous procedure avec l4:%d\n",NombreDe0AvantPositionK3(l3,6));
//Q4
    printf("\nQ4\n"); 
    printf("NombreDe0ApresRetroPositionK\n"); 
    Liste l5;
        initVide (&l5);
        empile(2, &l5);
        empile(0, &l5);
        empile(5, &l5);
        empile(6, &l5);
        empile(9, &l5);
        empile(0, &l5);
        empile(0, &l5);
        empile(0, &l5);
        empile(1, &l5);
        empile(0, &l5);
        printf("1er:liste\n");
        affiche_iter(l5); 
        printf("Position : 6\n");  
        printf("res= %d\n",NombreDe0ApresRetroPositionK(l5,6));
    Liste l6;
        initVide (&l6);
        empile(3, &l6);
        empile(0, &l6);
        empile(0, &l6);
        empile(5, &l6);
        printf("2nd:liste\n");
        affiche_iter(l6); 
        printf("Position : 6\n");  
        printf("res= %d\n",NombreDe0ApresRetroPositionK(l6,6));
//Q5
printf("\nQ5\n");
printf("FctBegaye\n");
    Liste l7;
        initVide (&l7);
        empile(8, &l7);
        empile(8, &l7);
        empile(-2, &l7);
        empile(6, &l7);
        empile(0, &l7);
        empile(1, &l7);
        empile(2, &l7);
        printf("liste:\n");
        affiche_iter(l7); 
        printf("res: version recursive\n");
        affiche_iter(FctBegaye(l7));
        printf("res: version recursive terminale\n");
        affiche_iter(FctBegaye1(l7));
        printf("res: version iterative\n");
        affiche_iter(FctBegaye2(l7));

//Q6
printf("\nQ6\n");
printf("ProcBegaye\n");
printf("liste:\n");
        affiche_iter(l7); 
 printf("res:\n");       
ProcBegaye(l7);

//Q7
printf("\nQ7\n");
printf("Permutations\n");
cpt=0;
affiche_iterListL(Permutations(3)); 
printf("\ncpt:=%d\n",cpt);

//Q8
printf("\nQ8\n");
printf("ListesBis\n");
ListesBis l8;

initVideListB(&l8);
    l8=ajouteListB(42,l8);
    l8=ajouteListB(93,l8);
    l8=ajouteListB(17,l8);
    l8=ajouteListB(23,l8);
    printf("liste :\n");
affiche_iterListB(l8);
int p=premierListB(suiteListB(suiteListB(l8)));
int *p1=&p;
retireP(p1,&l8); 
printf("liste modifie :\n");
affiche_iterListB(l8);

    return 0;
}




