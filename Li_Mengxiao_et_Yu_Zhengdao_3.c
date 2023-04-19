#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<math.h>


#define MaxSize 1000

#define ISNOT !=
#define NOT !
#define AND &&
#define OR ||
#define then
typedef enum { false, true } bool;
/*************************************************/
/*                                               */
/*                 la structure                  */
/*                                               */
/*************************************************/
typedef struct bloc_image
    { 
        bool toutnoir ;
        struct bloc_image * fils[4] ;
    } bloc_image ;
typedef bloc_image *image ;


/*************************************************/
/*                                               */
/*                predeclarations                */
/*                                               */
/*************************************************/
image Construit_Blanc();
image Construit_Noir();
image Construit_Composee(image i0,image i1,image i2,image i3);
void affiche_normal(image i);
void affiche_profondeur(image i);
image tapes_image();
bool EstNoire(image i);
bool EstBlanche(image i);
image QuartDeTour(image i);
void Negatif(image *i);
image SimplifieProfP(int p,image i);
bool Incluse(image i1,image i2);
int HautMaxBlanc(image i);
void BlanchitProfP(image *i,int p,int x,int y);
image Chute(image i);


/*************************************************/
/*                                               */
/*            fonctions et procedures            */
/*                                               */
/*************************************************/

/*************************************************/
/* Q(3.2.1) Construit_Blanc                      */           
/* Une fonction pour construit un image blanc    */
/* IN: rien;                                     */
/* OUT: image Blanc;                             */
/*************************************************/

//l'image = blanc des que le pointeur est NULL
image Construit_Blanc(){
    image i = NULL;
    return i;
}


/*************************************************/
/* Q(3.2.1) Construit_Noir                       */           
/* Une fonction pour construit un image Noir     */
/* IN: rien;                                     */
/* OUT: image Noir;                              */
/*************************************************/


//image Noir: toutnoir -> true,fils[] sont NULL
image Construit_Noir(){
    image i = (image) malloc(sizeof(bloc_image));
    i->toutnoir = true;
    i->fils[0] = NULL;
    i->fils[1] = NULL;
    i->fils[2] = NULL;
    i->fils[3] = NULL;
    return i;
}

/*************************************************/
/* Q(3.2.1) Construit_Composee                   */           
/* Une fonction pour construit une image composee*/
/* des sous-images.                              */
/* IN: 4 sous-images;                            */
/* OUT: image composee;                          */
/*************************************************/


//image compose: toutnoir -> false, image divisé par 4 sous-images fils[1],fils[2],fils[3],fils[4]
image Construit_Composee(image i0,image i1,image i2,image i3){
    image i = (image) malloc(sizeof(bloc_image));
    i->toutnoir = false;
    i->fils[0] = i0;
    i->fils[1] = i1;
    i->fils[2] = i2;
    i->fils[3] = i3;
    return i;
}

/******************************************************/
/* Q(3.2.2) affiche_normal                            */           
/* Procedure pour Affichages une image en modes normal*/
/* IN: image;                                         */
/* OUT: rien;                                         */
/******************************************************/

//3.2.2
void affiche_normal(image i){
    if(i == NULL){                  //si il est une image blanc
        printf("B");
    }else if(i->toutnoir){           //si il est une image noir 
        printf("N");
    }else{                           //si il est une image composee
        printf("(");                 // "(" indique le début d'une image decomposee
        for(int j=0;j<4;j++){        // récusife les 4 sous-image
            affiche_normal(i->fils[j]);
        }
        printf(")");                 //fin d'une image decomposee
    }
   
}

/**********************************************************/
/* Q(3.2.2) affiche_profondeur                            */           
/* Procedure pour Affichages une image en modes profondeur*/
/* IN: image;                                             */
/* OUT: rien;                                             */
/**********************************************************/

void aux_affiche_profondeur(image i, int cpt){
    if(i == NULL){
        printf("B%d", cpt);
    }else if(i->toutnoir){
        printf("N%d",cpt);
    }else{
        printf("(");
        for(int j=0;j<4;j++){
            aux_affiche_profondeur(i->fils[j],cpt+1); //Chaque récursivité au sous_image, profondeur +1;
            
        }
        printf(")");
    }
}
void affiche_profondeur(image i){
    int cpt=0;                    //calculeur pour profondeur;
    aux_affiche_profondeur(i,cpt);
    printf("\n");
}


/**********************************************************/
/* Q(3.2.3) tapes_image                                   */           
/* Fonction pour saisir une image a partir du clavier     */
/* IN: rien;                                              */
/* OUT: image;                                            */
/**********************************************************/ 


image aux_tapes_image(char str[],int *cpt){
                                 
    while (str[*cpt] == ')'){               //fin de sous-image,la position +1, on recule la position
        *cpt = *cpt + 1;
    }
    char s = str[*cpt];                     //s est le caractere que on est en cours de traduire  
    if(s!='\0'){                            //Si la chaîne de image n'est pas entierement saisie
        
        *cpt = *cpt + 1;                   
        
        if(s=='N'){
            return Construit_Noir();
        }else if(s=='B'){
            return Construit_Blanc();
        }else if(s=='('){                      //Si le caractère est "(", Cela signifie que les caracteres qui le suivront seront un image composee
                                                //Via ligne 176 *cpt = *cpt + 1; Nous pouvons commencer à traduire le caractère suivant par récursivité
            image f0=aux_tapes_image(str,cpt);
            image f1=aux_tapes_image(str,cpt);
            image f2=aux_tapes_image(str,cpt);
            image f3=aux_tapes_image(str,cpt);
            return Construit_Composee(f0,f1,f2,f3);

        }else{
            printf("Mal image\n");
            exit(-1);
        }
    }else{
        return 0;
    }
      
} 

image tapes_image(){
    char str[512];
    printf("tapes un image:(Majuscule)\n"); 
    fgets(str,512,stdin);               //tapes un image stocker dans str.
    int cpt=0;                          //la position vers le caractère courant
    image i=aux_tapes_image(str,&cpt);
    return i;

} 
 
/**********************************************************/
/* Q(3.2.4) EstNoire et EstBlanche                        */           
/* test si l'image en argument est resp. noir/blanc       */
/* IN: image;                                             */
/* OUT: bool;                                             */
/**********************************************************/ 

bool EstNoire(image i){
    if(i==NULL){
        return false;
    }else if(i->toutnoir){
        return true;        
    }else{
        return EstNoire(i->fils[0]) AND EstNoire(i->fils[1]) AND EstNoire(i->fils[2]) AND EstNoire(i->fils[3]);
    }
}


bool EstBlanche(image i){
    if(i==NULL){
        return true;
    }else if(i->toutnoir){
        return false;        
    }else{
        return EstBlanche(i->fils[0]) AND EstBlanche(i->fils[1]) AND EstBlanche(i->fils[2]) AND EstBlanche(i->fils[3]);
    }
}

/**********************************************************/
/* Q(3.2.5) Diagonal                                      */           
/* test si l'image en argument est resp. noir/blanc       */
/* IN: image;                                             */
/* OUT: bool;                                             */
/**********************************************************/ 


void aux_Diagonal(int p, image *img){
    if(p==0){
        *img=Construit_Noir();          
    }else{                              
        image i = (image) malloc(sizeof(bloc_image));
        i->toutnoir = false;
        i->fils[1]=Construit_Blanc();
        i->fils[2]=Construit_Blanc();  //fils[1] et fils[2] sont toujours blancs
        aux_Diagonal(p-1,&i->fils[0]); //Nous récurons à travers la profondeur -1 jusqu'à ce que la profondeur soit égale à 0(fils[0] et fils[3])
        aux_Diagonal(p-1,&i->fils[3]);
        *img=i;
    }
}
image Diagonal(int p){
    image i;
    
    aux_Diagonal(p,&i);
    
    return i;
}


/**********************************************************/
/* Q(3.2.6) QuartDeTour                                   */           
/* rendre l'image en argument tournee d'un quart de tour  */
/* IN: image;                                             */
/* OUT: image;                                            */
/**********************************************************/ 


image QuartDeTour(image i){
    if(i==NULL){
        return Construit_Blanc();
    }else if(i->toutnoir){
        return Construit_Noir();
    }else{                                 //Pour realiser une rotation dans le sens des aiguilles d'une montre,
        image f0=QuartDeTour(i->fils[2]);  //le fils[0] de la nouvelle image est le fils[2] de l'ancienne image et le fils[2] est celle de  fils[3] de l'anciene....etc.
        image f1=QuartDeTour(i->fils[0]);  //Nous faisons tourner toutes les sous-images par récurrence
        image f2=QuartDeTour(i->fils[3]);  
        image f3=QuartDeTour(i->fils[1]); 
        return Construit_Composee(f0,f1,f2,f3);  
    }
}



/**********************************************************/
/* Q(3.2.7) Negatif                                       */           
/* transforme l'image argument en negatif                 */
/* IN: image;                                             */
/* OUT: image;                                            */
/**********************************************************/ 

void aux_Negatif(image i,image *img){
    if(i==NULL){
        *img=Construit_Noir();
    }else if(i->toutnoir){
        *img=Construit_Blanc();
    }else{
        image imag = (image) malloc(sizeof(bloc_image));
        imag->toutnoir = false;
        for(int j=0;j<4;j++){
            aux_Negatif(i->fils[j],&imag->fils[j]);
        }
        *img=imag;
        
    }
}
void Negatif(image *i){
    image img=NULL;
    aux_Negatif(*i,&img);
    *i=img;    
}

/**********************************************************/
/* Q(3.2.8) SimplifieProfP                                */           
/* remplace les arbres monochromes à pro P par B/N        */
/* IN: image,int;                                         */
/* OUT: image;                                            */
/**********************************************************/ 


image SimplifieProfP(int p,image i){
    if(p==0){       //Nous récurons à travers la profondeur -1 jusqu'à ce que la profondeur soit égale à 0
        if(EstBlanche(i)){  //auquel point on remplace les arbre monochromes par B ou N
            return Construit_Blanc();
        }else if(EstNoire(i)){
            return Construit_Noir();//on utilise Estnoir/blanc pour determiner si cet image composé est blanc ou noir,si oui,on le remplace
        }else{
            return i;
        }
    }else{
        if((i==NULL) OR (i->toutnoir)){ //Lorsque nous faisons une récursion vers une image monochrome (blanc/noir) qui n'a pas encore atteint la profondeur indiquée,
            return i;                 // nous la retournons directement 
        }else{
            image f0=SimplifieProfP(p-1,i->fils[0]);//mais pour les sous-images composés qui n'a pas encore atteint la profondeur indiquée,
            image f1=SimplifieProfP(p-1,i->fils[1]);//Nous récurons jusqu'à ce que nous atteignions la profondeur
            image f2=SimplifieProfP(p-1,i->fils[2]);
            image f3=SimplifieProfP(p-1,i->fils[3]);
            return Construit_Composee(f0,f1,f2,f3);
        }
    }
}



/*****************************************************************/
/* Q(3.2.9) Incluse                                              */           
/* verifier si le 1er image en argument est incluse dans le 2ieme*/
/* IN: 2 images                                                  */
/* OUT: bool;                                                    */
/*****************************************************************/ 

//l'idee：la seconde est noire partout où la premiere est noire
bool Incluse(image i1,image i2){
    if(EstNoire(i1)){
        if(EstNoire(i2)){ //Si le premier est tout noir, le second doit l'être aussi, sinon nous retournerons false.
            return true;
        }else{
            return false;
        }
    }else if(EstBlanche(i2)){
        if(NOT EstBlanche(i1)){ //Si le 2ieme est tout blanc, le premier doit l'être aussi, sinon nous retournerons false.
            return false;
        }else{
            return true;
        }
    }else if(EstBlanche(i1) OR EstNoire(i2)){ //Nous en discutons dans diverses situations
        return true;       
    }else{      
        return Incluse(i1->fils[0],i2->fils[0]) AND Incluse(i1->fils[1],i2->fils[1]) AND Incluse(i1->fils[2],i2->fils[2]) AND Incluse(i1->fils[3],i2->fils[3]);
    }
}


/**********************************************************/
/* Q(3.2.10) HautMaxBlanc                                 */           
/* rend le maximum des hauteurs des sous-images blanches  */
/* IN: image;                                             */
/* OUT: int;                                              */
/**********************************************************/ 

int max4(int a,int b,int c, int d){ //Renvoie la valeur maximale des 4 arguments
    int max=a;
    if(b>max){
        max=b;
    }
    if(c>max){
        max=c;
    }
    if(d>max){
        max=d;
    }
    return max;
}

int HautMaxBlanc(image i){
    if(EstBlanche(i)){//Lorsqu'il s'agit d'une image blanche，on discute par cas: L'image blanche la plus simple, OU l'image blanche composite
        if(i==NULL){ //si le pointeur est NULL,ca veut dire l'image blanc le plus simple,-> B,donc l'hauteur est 0.On rends 0
            return 0;
        }else{//S'il s'agit d'une image blanche composite, nous comparons les hauteurs des quatre sous-images par récurrence, en retournant la valeur maximale
            return max4(HautMaxBlanc(i->fils[0]),HautMaxBlanc(i->fils[1]),HautMaxBlanc(i->fils[2]),HautMaxBlanc(i->fils[3]))+1;
        }

    }else if(EstNoire(i)){//par enonce,on rends -1 si cest une image noire
        return -1;
    }else{
        return max4(HautMaxBlanc(i->fils[0]),HautMaxBlanc(i->fils[1]),HautMaxBlanc(i->fils[2]),HautMaxBlanc(i->fils[3]));//递归直到找到全是白色的大方块（很个或一个白色组成）
    }
}


/**********************************************************/
/* Q(3.2.11) BlanchitProfP                                */           
/* blanchit le pixel de profondeur p, de coordonnees(x,y) */
/* IN: arbre,inr:profondeur,2entiers: x,y;                */
/*                                                        */
/**********************************************************/ 

void aux_BlanchitProfP(image *i,int p,int x,int y,int n){
    //afin que trouver la position correspondant aux coordonnées，
    //dans la récursion suivante, nous continuons à aller dans différents coins de l'image en changeant x, y, n, 
    //soit le coin supérieur gauche, soit le coin inférieur droit.
    if(n==1){//Lorsque n=1, nous avons atteint la position des coordonnées dans l'image 
        *i=Construit_Blanc();//et nous remplaçons cette image par une image blanche
    }else{
        image img = *i;
        if(NOT EstBlanche(img)){//Nous divisons la situation, si l'image n'est pas complètement blanche，on fait les operations suivantes
            if(img->toutnoir){//Si l'image est noire, nous transformons cette image en une image composite afin d'atteindre la position des coordonnées dans l'image
                img=Construit_Composee(Construit_Noir(),Construit_Noir(),Construit_Noir(),Construit_Noir());
            }
            if(x<(n/2)){//on recherche l'image avec les coordonnées indiquées par dichotomie
                if(y<(n/2)){
                    aux_BlanchitProfP(&img->fils[2],p,x,y,n/2);//x<n/2,y<n/2，ca veut dire que les coordonnées sont dans le coin inférieur gauche de cette image,
                    //on entre par récurrence dans le coin inférieur gauche de l'image, qui est fils[2]
                }else{
                    aux_BlanchitProfP(&img->fils[0],p,x,y-(n/2),n/2);//x<n/2,y>n/2，ca veut dire que les coordonnées sont dans le coin superieur gauche de cette image,
                    // on entre par récurrence dans le coin superieur gauche de l'image, qui est fils[0]
                    //En soustrayant n/2, on obtient la nouvelle coordonnée y （y-（n/2））
                }
            }else{
                if(y<(n/2)){//idem Coin inférieur droit de l'image
                    aux_BlanchitProfP(&img->fils[3],p,x-(n/2),y,n/2);
                }else{//idem Coin supérieur droit de l'image
                     aux_BlanchitProfP(&img->fils[1],p,x-(n/2),y-(n/2),n/2);
                }
            }
        }
        //si l'image est blanche,on rien fait
        *i=img;
    }

}
void BlanchitProfP(image *i,int p,int x,int y){
    int n=pow(2,p);  //n = 2^p，longueur de l'image
    //La valeur initiale de n est la longueur de l'image.
    aux_BlanchitProfP(i,p,x,y,n);
  
} 

/***********************************************************************************/
/* Q(3.2.12) Chute                                                                 */           
/* La gravite agit sur les pixels qui tombent et s’empilent dans le bas de l’image */
/* IN: image                                                                       */
/* OUT： image                                                                     */
/***********************************************************************************/ 

//Nous introduisons le système de coordonnées de la question precedente

//Le but de fonction calN_inX est de découper l'image en la plus petite et la plus simple des images,
//c'est-à-dire l'image correspondant à une coordonnée dans le système de coordonnées.
//Nous calculons ensuite le nombre de ces images noires minimales dans la colonne correspondant à la coordonnée horizontale x
int calN_inX(image i,int x,int n){
    int cpt=0;//cpt ： Nombre d'images noires minimales
    int y=0;//  y：Coordonnées verticales
    while(y<n){//x est l'invariant et nous calculons le nombre d'images minimales noires de 0 à la coordonnée verticale y
        int y1=y;
        int x1=x;
        image img=i;
        int n1=n;    
        while (n1!=1)//idem de exo precedent,nous localisons l'image avec les coordonnées indiquées
        {   if(EstBlanche(img) OR EstNoire(img)){
                break;
            }
            if(x1<(n1/2)){
                if(y1<(n1/2)){
                    img=img->fils[2];
                }else{
                    img=img->fils[0];
                    y1=y1-(n1/2);
                }
            }else{
                x1=x1-(n1/2);
                if(y1<(n1/2)){
                    img=img->fils[3];
                }else{
                     img=img->fils[1];
                     y1=y1-(n1/2);
                }
            }           
            n1=n1/2;            
        }
        if(EstNoire(img)){//Si cette image est noire, cpt+1
            cpt++;
        }       
        y++;        
    }
    return cpt;    
}

int profondeur(image i){//Une fonction pour calculer la profondeur maximale d'une image entrante
    if(i==NULL OR i->toutnoir){
        return 0;
    }else{
       return max4(profondeur(i->fils[0]),profondeur(i->fils[1]),profondeur(i->fils[2]),profondeur(i->fils[3]))+1; 
    }
}

//L'idee de fonction Chute est de:
//En introduisant le système de coordonnées de l'exercice précédent, 
//nous divisons l'image en un certain nombre d'images minimales, 
//puis nous calculons le nombre d'images minimales noires dans chaque colonne.

//Ensuite, nous créons une image entièrement noire
//Parce que ci-dessus nous avons calculé le nombre d'images minimales noires pour différentes colonnes
//Dans cette image noire que nous avons créée，
//Dans chaque colonne, nous gardons les images en noir de la coordonnée verticale 0 au nombre calculé, 
//au-dessus de cette coordonnée, les images deviennent blanches.
//ensuite on rends cet image que on vient de créer et de modifier

//De cette façon, nous avons obtenu l'effet de gravité du piexl noir.
image Chute(image i){
    int p=profondeur(i);//p : Profondeur maximale de l'image entrante
    int n=pow(2,p);//n = 2^p,Puisque nous avons introduit le système de coordonnées du exo précédent, ici n est la longueur de l'image
    image img=Construit_Noir();
    for(int x=0;x<8;x++){//x est la coordonnée horizontale et y est la coordonnée verticale
        
        int nbB=calN_inX(i,x,n);//nbB ： le nombre d'images minimales noires dans la colonne de coordonnees horizontale x
        
        int y;

        //Via la fonction blanchitProfP(),on transforme en blanc les petites image de la colonne x 
        //dont les coordonnées verticales sont supérieures ou égales à nbB
        for(y=nbB;y<n;y++){
            BlanchitProfP(&img,p,x,y);
        }
        
    }
    return img;
}

/*************************************************/
/*                                               */
/*                  test main                    */
/*                                               */
/*************************************************/
int main(int argc, const char * argv[])
{
   
//q1
    printf("q1 Construit_Blanc() Construit_Noir() Construit_Composee\n");
    printf("\n"); 
    image b = Construit_Blanc();
    image n = Construit_Noir();
    image i =Construit_Composee(n,b,b,Construit_Composee(n,b,Construit_Composee(b,n,n,b),n));
    printf("\n");

    //image i1=Construit_Composee(n,Construit_Composee(b,b,n,b),b,Construit_Composee(n,Construit_Composee(n,n,b,Construit_Composee(n,b,n,n)),b,n));
//q2
    printf("q2  affiche_profondeur affiche_normal\n");
    printf("\n"); 
    printf("affiche profondeur:\n");
    affiche_profondeur(i);
    printf("affiche normal:\n");
    affiche_normal(i);  
    printf("\n");
    printf("\n"); 
    
//q3 
    printf("q3 tapes_image  \n");
    printf("\n"); 
    image i3=tapes_image(); 
    affiche_normal(i3);
    printf("\n"); 
    printf("\n");

//q4
    printf("q4 EstNoire et EstBlanche \n");
    printf("\n"); 
    image i4=Construit_Composee(b,b,b,Construit_Composee(b,b,Construit_Composee(b,b,b,b),b));
    affiche_normal(i4);
    
    if(!EstBlanche(i4)) printf("l'image nest pas blanc\n");else printf("l'image est blanc\n");
    if(!EstNoire(i4)) printf("l'image nest pas noire\n");else printf("l'image est noire\n");
    // printf("%d\n",EstBlanche(i4));
    //printf("%d\n",EstNoire(n));
    printf("\n");

//q5
    printf("q5 Diagonal \n");
    printf("\n"); 
    //image i5=Diagonal(3);
    affiche_normal(Diagonal(3));
    printf("\n"); 
    printf("\n");

//q6
    printf("q6 QuartDeTour \n");
    printf("\n"); 
    image i6=Construit_Composee(Construit_Composee(b,n,n,n),b,Construit_Composee(n,n,b,b),n);
    affiche_normal(i6);
    printf("\n");
    image i66=QuartDeTour(i6);
    printf("Apres de tourner:\n");
    affiche_normal(i66);
    printf("\n");
    printf("\n");
//q7
    printf("q7 Negatif  \n");
    printf("\n"); 
    image i7=Construit_Composee(Construit_Composee(b,n,n,n),b,Construit_Composee(n,n,b,b),n);
    affiche_normal(i7); 
    printf("\n");
    Negatif(&i7);
    printf("Le negatif:\n");
    affiche_normal(i7); 
    printf("\n");
    printf("\n");

//q8
    printf("q8 SimplifieProfP \n");
    printf("\n"); 
    image i8=Construit_Composee(n,Construit_Composee(n,b,Construit_Composee(n,n,Construit_Composee(n,n,n,n),n),b),Construit_Composee(n,b,n,Construit_Composee(n,b,n,Construit_Composee(b,b,b,b))),Construit_Composee(b,b,Construit_Composee(b,b,b,b),b));
    affiche_normal(i8); 
    printf("\n");
    image i88=SimplifieProfP(2,i8);
    printf("Apres simplifie:\n");
    affiche_normal(i88); 
    printf("\n");
    printf("\n");

//q9
    printf("q9 Incluse \n");
    printf("\n"); 
    image i9=Construit_Composee(Construit_Composee(Construit_Composee(b,b,b,b),n,b,n),b,n,Construit_Composee(Construit_Composee(b,b,n,n),b,b,Construit_Composee(n,b,b,n)));
    image i99=Construit_Composee(Construit_Composee(b,n,n,n),Construit_Composee(b,b,n,b),Construit_Composee(n,n,n,n),Construit_Composee(n,b,n,Construit_Composee(n,n,n,b)));
    affiche_normal(i9); 
    printf("\n");
    affiche_normal(i99); 
    printf("\n");
    if(!Incluse(i9,i99)) printf("le 1er image nest pas incluse dans le 2ieme\n");else printf("le 1er image est incluse dans le 2ieme\n");
    printf("\n");
    // printf("%d\n",Incluse(i9,i99));

 //q10
    printf("q10 HautMaxBlanc \n");
    printf("\n"); 
    image i10=tapes_image();
    //((BBBB)N(BNBN)(NBN(NB(BB(BBBB)(BBB(BBBB)))N)))
    affiche_normal(i10);
    printf("\n");
    printf("Le max hauteur  de sous-image blanc est : %d\n",HautMaxBlanc(i10));
    printf("\n");  

//q11
    printf("q11 BlanchitProfP \n");
    printf("\n"); 
    image i11=Construit_Composee(n,b,n,b);
    affiche_normal(i11);
    printf("\n");
    BlanchitProfP(&i11,2,1,3);    
    printf("Apres de blanchir:\n");
    affiche_normal(i11);
    printf("\n");
    image i111=Construit_Composee(Construit_Composee(n,Construit_Composee(n,b,n,n),n,n),b,n,b);
    affiche_normal(i111);
    printf("\n");
    BlanchitProfP(&i111,2,1,3);
    printf("Apres de blanchir:\n");
    affiche_normal(i111);
    printf("\n");
    printf("\n");

 //q12
    printf("q12 Chute \n");
    printf("\n"); 
    image i12=Construit_Composee(n,Construit_Composee(Construit_Composee(n,b,n,n),n,b,Construit_Composee(b,n,b,n)),Construit_Composee(n,Construit_Composee(n,b,b,n),Construit_Composee(b,n,n,n),Construit_Composee(n,b,n,b)),Construit_Composee(n,n,Construit_Composee(n,b,b,b),Construit_Composee(b,n,b,n)));
    //(N((NBNN)NB(BNBN)) (N(NBBN)(BNNN)(NBNB)) (NN(NBBB)(BNBN)))
    affiche_normal(i12);
    printf("\n");
    image i122=Chute(i12);
    affiche_normal(i122);
    printf("\n"); 

    return 0;
}