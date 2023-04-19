#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#define ISNOT !=
#define NOT !
#define AND &&
#define OR ||
#define then


/*************************************************/
/*                                               */
/*           Exo 1.1                             */
/*                                               */
/*************************************************/
float e(int n){
    float a=1.0;
    float sum=0;   
    for(int i=0;i<=n;i++){
        if(i!=0)
            a = a * i;
        sum=sum+1.0/a;
        printf("sum=%lf\n",sum);
    }
    printf("sum final=%lf\n",sum);
    return sum;
}
/*************************************************/
/*                                               */
/*           Exo 1.2                             */
/*                                               */
/*************************************************/

double e1(int n){
    int a=1;
    double sum=0;   
    for(int i=0;i<=n;i++){
        if(i!=0)
            a = a * i;
        sum=sum+1.0/a;
    }
    printf("sum=%f\n",sum);
    return sum;
}

void question2D(){
    //Pour comparer la différence entre un float et un double，ici on utilise e(30) pour obtenir la valeur de e
    double res = e1(30) - 1;
    printf("n=%d, res=%f\n", 0, res);
    for (int n = 1; n <= 50; n++)
    {
        res = n * res - 1;
        printf("n=%d, res=%f\n", n, res);
    }
}
void question2F(){
    float res = e(30) - 1;
    printf("n=%d, res=%f\n", 0, res);
    for (int n = 1; n <= 50; n++)
    {
        res = n * res - 1;
        printf("n=%d, res=%f\n", n, res);
    }
}

/*************************************************/
/*                                               */
/*           Exo 1.3                             */
/*                                               */
/*************************************************/
// double power1(float x,int n){
//     if(n==0)
//         return 1;
//     else
//         return power1(x,n-1)*x;
// }
long double power1(long double x,int n){
    
    if(n==0)
        return 1.0;
    else if (n > 0)
        return power1(x,n-1)*x;
    else return power1(x,n+1)/x;
}
// double power2(float x,int n){
//     double r=1;
//     for(int i=1;i<=n;i++){
//         r=r*x;
//     }
//     return r;
// }       

long double power2(long double x,int n){
    long double r=1;
    if(n>=0){
        for(int i=1;i<=n;i++){
            r=r*x;
    }
    }else{
        for(int i=n;i<0;i++){
            r=r*x;
            }
        r=1/r;
    }
    return r;
}
void pow3(long double x, int n,long double *r){
    if(n==0){

    }else{
        *r=*r*x;
        pow3(x,n-1,r);
    }
}
long double power3(long double x,int n){
    long double r=1.0;
    pow3(x,n,&r);
    return r;
}

long double pow4(long double x,int n,double r){
    if(n==0)
        return r;
    else
        return pow4(x,n-1,r*x);
}
long double power4(long double x,int n){
    return pow4(x,n,1);
}


long double power5(long double x,int n){
    if(n==0)
        return 1.0;
    else{
        if(n%2==0)
            return power5(x,n/2) * power5(x,n/2);
        else
            return power5(x,n/2)* power5(x,n/2)*x;
        
    }
}

long double power6(long double x,int n){
    if(n==0)
        return 1.0;
    else{
        long double y=power6(x,n/2);
        if(n%2==0)
            return y*y;
        else
            return y*y*x;
    }
}
long double power7(long double x,int n){
    if(n==0)
        return 1.0;
    else
        if(n%2==0)
            return power7(x*x,n/2);
        else
            return power7(x*x,n/2)*x;
}
long double pow8(long double x,int n,double r){
    if(n==0)
        return r;
    else{
        if(n%2==0)
            return pow8(x*x,n/2,r);
        else
            return pow8(x*x,n/2,r*x);       
    }
}
long double power8(long double x,int n){
    return pow8(x,n,1);
}
void pow9(long double x,int n,long double *r){
    if(n==0){

    }else{
        if(n%2==1)
            *r= *r *x;

        pow9(x*x,n/2,r);
    }

}
long double power9(long double x,int n){
    long double r=1;
    pow9(x,n,&r);
    return r;
}
long double power10(long double x,long n){
    long double r=1;
    while(n!=0){
        if(n%2==1){
            r=r*x;
        }
        n=n/2;
        x=x*x;   
    }
    return r;
}

/*************************************************/
/*                                               */
/*           Exo 1.4                             */
/*                                               */
/*************************************************/
//recursif pur
int A1(int m,int n){
  if (m==0)
     return n+1;
 else if(n==0)
     return A1(m-1,1);
    else return A1(m-1,A1(m,n-1)) ;
}
//recurso-itrative avec un pour sur n

int A2(int m,int n){
  if(m==0)
  return n+1;
  else{
    int r=1;
    for(int i =1;i<=n+1;i++)
    r = A2(m-1,r);
    return r;
  }
}

//recurso-itrative avec un pour sur m
// int A3(int m,int n){
//    if(m==0) return n+1;
//    else if(n==0)
//   return A3(m,1);
//   else{
//     int r=n;
//     for(int i =1;i<=m;i++)
//     r = (A3(m-1,A3(m,n-1)));
//     return r;
//   }
// }


/*************************************************/
/*                                               */
/*           Exo 1.5                             */
/*                                               */
/*************************************************/
//recursive
float X1(int n){
    if(n==0) return 1.0;
    else  return X1(n-1)+2/X1(n-1);       
}

// recursive terminale - sous-fonction
float sf(int n,float res){
    if(n==0) return 1.0;
    else 
    res = sf(n-1,res);
         res = res+2/res; 
       return res;
}

float X2(int n){
    if(n==0) return 1.0;
    else  
    return sf(n,0.0);
}


  //recursive terminale - sous-procedure
void sp(int n,float * res){ 
    if(n==1) *res = 1;
    else   
    sp(n-1,res);
    *res = *res+2 / *res;      
    // printf("res = %lf\n",*res);       
}

float X3(int n){
    float res = 0.0;
    if(n==0) return 1.0;
    else   
    sp(n,&res);
          return res;
}

//iterative
float X4(int n){
    float res = 1.0;
    for(int i=0;i<n;i++){
        res = res+2/res;
    }
  return res;
}
//test pour recursive
float X1_1(int n){
    if(n==0) return 1.0;
    else  return X1_1(n-1)+2/X1_1(n-1);       
}
float X1_2(int n){
    if(n==0) return 11.303429;
    else  return X1_2(n-1)+2/X1_2(n-1);       
}
float X1_3(int n){
    if(n==0) return 15.761864;
    else  return X1_3(n-1)+2/X1_3(n-1);       
}
float X1_4(int n){
    if(n==90) return 19.205021;
    else  return X1_4(n-1)+2/X1_4(n-1);       
}





int main(){
    //test du rapidite
    // int test = 1000000000;
    // long double restt = (1.0+(1.0/test));
    // printf("P10:%Lf\n",power7(restt,test));
    // printf("P10:%Lf\n",power10(restt,test));
    // printf("P10:%Lf\n",power6(restt,test));
    printf("Nos reponses pour les questions est dans les commentaires de la fonction main()\n");   
    //Q1.1
    printf("Q1.1\n");
    /*quand n=8 on a sum=2.718254,n=9 sum=2.718279,
    quand n>= 10 on a sum=2.718282 en raison des limites de la précision de type
    donc quand n=10 on peut s'arrete.
    */
    e(10);
    
    
    
    //Q1.2
    printf("Q1.2\n");
    question2F();
    question2D(); 
   /* 
   Premierement, on remarque qu'avec double, on a le resultat "exacte" jusqu'a n=50, 
   alors que pour le type float, a partir de n=39, les resultats sont devenu INF, car le nombre en question depasse
   la precision du type float.
   Enusite, on peut voir que dans ce cas, double croît plus lentement que float,
   par exemple quand n=11: double est res=0.214147, float est res=6.312073.
   Parce que le double est plus précis.
   Comme la précision du double est supérieure à celle du flottant, 
   l'erreur dans le résultat du type float devient plus importante lorsque n augmente, et le résultat du type double est plus précis.
   
   */
   
   
   
   //Q1.3
  printf("Q1.3\n");
                                                                     
    // (1 + 1/N)^N semble tendre vers e (2.718.....)
    //pour la question de l’optimisation:
    //Pour la compilateur,par rapport à la récursion simple des versions 6-9, la récursion terminal des versions 3-5 est plus mauvaise.
    //la version iterative 2 a besoin de plus de temps pour obtenir des résultats par rapport a la iterative de version 10,version 10 est rapide
    printf("test valeur negatif power1(5,-3) P1:%Lf\n",power1(5,-3));
    printf("test valeur negatif power2(5,-3) P2:%Lf\n",power2(5,-3));
    printf("(1 + 1/N)^N semble tendre vers e (2.718.....)\n");
    double x;
    for(double n=10;n<=pow(10,4);n=n*10){
        x=(1.0+(1.0/n));
        printf("N = %f \n", n);
        printf("P1:%Lf\n",power1(x,n));
        printf("P2:%Lf\n",power2(x,n));
        printf("P3:%Lf\n",power3(x,n));
        printf("P4:%Lf\n",power4(x,n));
        printf("P5:%Lf\n",power5(x,n));
        printf("P6:%Lf\n",power6(x,n));
        printf("P7:%Lf\n",power7(x,n));
        printf("P8:%Lf\n",power8(x,n));
        printf("P9:%Lf\n",power9(x,n));
        printf("P10:%Lf\n",power10(x,n));
    }  
    //conclusion pour plus grand nombre:
    for(double n=pow(10, 9);n<=pow(10,9);n=n*10){
        
        double x=(1.0+(1.0/n));
        printf("N = %f \n", n);
         //printf("P1:%Lf\n",power1(x,n)); // segmentation fault at N = 10^6
        //printf("P2:%Lf\n",power2(x,n));  //pour cette version iterative,le compilateur peut continuer a calculer,mais pour les N de grosses puissances de 10,il prends beaucoup de temps pour return le resultat
         //printf("P3:%Lf\n",power3(x,n)); // segmentation fault at N = 10^6
         //printf("P4:%Lf\n",power4(x,n)); // segmentation fault at N = 10^6
         printf("P1:segmentation fault\n");
         printf("P2:il prends du temps pour calculer,pour eviter de bloquer,on met le code dans commentaire\n");
         printf("P3:segmentation fault\n");
         printf("P4:segmentation fault\n");
        printf("patientez un peu...\n");
         printf("P5:%Lf\n",power5(x,n));  // no error but took more time to finish
         printf("P6:%Lf\n",power6(x,n));  // no error 
         printf("P7:%Lf\n",power7(x,n));  // no error 
         printf("P8:%Lf\n",power8(x,n));  // no error 
         printf("P9:%Lf\n",power9(x,n));   // no error 
         printf("P10:%Lf\n",power10(x,n)); //no error,pour cette version iterative par n/2,la fonction return le resultat rapidement
    } 


   //Q1.4 
   printf("Q1.4\n");
    for(int i=1;i<=6;i++){
    printf("i ->%d \n",i);
    if(i==6) {printf("il prend du temps pour calcuer,le resultats final pour la version recursive pur est'segment fault'(out of memory)\n");
    printf("le resultat pour la version recurso-iterative est'il continuer a calcuer sans return le resutat,Cela peut lui prendre beaucoup de temps pour arriver au résultat final',pour éviter de perdre du temps,on met le code  dans commentaire\n");
    // printf("Ackerman:%d\n",A1(i,0));
    // printf("Ackerman:%d\n",A2(i,0));
    }
    else{
    printf("patientez un peu...\n");
    printf("Ackerman:%d\n",A1(i,0));
    printf("Ackerman:%d\n",A2(i,0));
    }
    }
    // i ->1 
    // Ackerman:2
    // Ackerman:2
    // i ->2 
    // Ackerman:3
    // Ackerman:3
    // i ->3 
    // Ackerman:5
    // Ackerman:5
    // i ->4 
    // Ackerman:13
    // Ackerman:13
    // i ->5 
    // Ackerman:65533
    // Ackerman:65533
    // i ->6 
    // segmentation fault(out of memory)
    // Il continue à calculer, mais le résultat peut prendre beaucoup de temps, quelques heures ou quelques jours.

    // les differentes versions ont pas de meme comportement,pour la version recursive pur,c'est facile de out of memory,mais pour la version recurso-iterative,
    //pour i superieur a 5,il prend beaucoup de temps pour calculer,mais au moins, il a plus de possibilités pour arriver au résultat final, contrairement à la récursion pure.
  
  //Q1.5
printf("Q1.5\n");
int i = 100;
   printf("iterative:%lf\n",X4(i)); 
   printf("recursive terminale avec sou-fonction:%lf\n",X2(i));
   printf("recursive terminale avec sou-procedure:%lf\n",X3(i));
// printf("recursive pur :%lf\n",X1(i));  
   printf("patientez un peu...\n");
   printf("test: recursive1 :%lf\n",X1_1(30));
   printf("test: recursive2 :%lf\n",X1_2(30));
   printf("test: recursive3 :%lf\n",X1_3(30));
   printf("test: recursive-resultat final :%lf\n",X1_4(100));
//pour la methode recursive sans sous-fonctionalit,on le met dans commentaire ici parce que il prend beaucoup de temps pour calculer,peut-etre quelques heures,peut-etre quelques jours
// On va demontrer que on peut obtenir le resultat final par methode recursive sans sous-fonctionalite par pas à pas
// 1er pas
// on calculer X1(30) d'abord,on peut obtenir le résultat après une période de temps relativement courte,cest 11.303429
// on modifie le code de X1 pour réinitialiser le point de départ à le valeur de X30
// float X1(int n){  
//     if(n==0) return 11.303429;
//     else  return X1(n-1)+2/X1(n-1);         
// }
// Nous répétons les étapes ci-dessus deux fois:
// le resultat de X1(30) qui base de (nouvelle point de depart -> X30) est 15.761864
// le resultat de X1(30) qui base de (nouvelle point de depart -> X60) est 19.205021
// Au final
// on a obtenu le valeur de X90 d'apres les etapes precedentes -> 19.205021
// on modifie le code de X1
// float X1(int n){  
//     if(n==90) return 19.205021;
//     else  return X1(n-1)+2/X1(n-1);         
// }
// on fait X1(100) et on obtient le resultat final ->20.222178,cest la meme valeur que les 3 autres methodes
}