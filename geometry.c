#include <math.h>
#include  <stdlib.h>
#include <stdio.h>
#include "geometry.h"

int verify(point p, point a, point b) {
    int minx;
    int maxx;
    int maxy;
    int miny;
    if(a.x> b.x){
      maxx = a.x;
      minx= b.x;
    }
    else{
      maxx = b.x;
      minx =a.x;
    }
     if(a.y> b.y){
      maxy = a.y;
      miny = b.y;
    }
    else{
     maxy = b.y;
     miny = a.y;
   }

    double tx =( (double)(a.y - b.y) / (double)(a.x - b.x));
    double k = (a.y - (tx *a.x));
    double dif = abs(( (10*tx * p.x) + 10*k) - 10*p.y);
    
    ///// rotacao
    if ((p.y == miny)  && (p.x < minx || p.x < maxx) && (abs(p.x - ((double)(p.y-k)/(double)tx)) > 0.000001) ){
  
      return 0;
    }

    if ((p.y == maxy)  && (p.x < minx || p.x < maxx) && (abs(p.x - ((double)(p.y-k)/(double)tx)) > 0.000001) ){
      if( p.x < ((double)(p.y-k)/(double)tx)){
  
            return 1;
          }
    }
    if (a.x != b.x ){

      ////  Para xs != , resultado == 2 (testando para ver se esta na funcao)
      if (( dif < 0.000001) && ((a.y <= p.y && p.y <= b.y) || (b.y <= p.y && p.y <= a.y))&& (p.x <= minx || p.x <= maxx)) {
        if ( a.y == b.y){
          if (p.x < minx && p.x < maxx){
              return 0;
          }

        }
        return 2;
      }
      
       ///vPara xs =! , resultado ==1 ( testanto se esta entre as bordas e  a aresta está na frente, ou seja depois xo x )

      if(((a.y <= p.y && p.y <= b.y) || (b.y <= p.y && p.y <= a.y))&&(p.x <= minx || p.x <= maxx)  ) {
          if( p.x < ((double)(p.y-k)/(double)tx)){
  
            return 1;
          }
      }
    }
    // Para xs iguais
     else{

       if ((p.y == miny)  && (p.x < minx )){
        return 0;
      }

    if ((p.y == maxy)  && (p.x < minx ) ){
      
      if( p.x < ((double)(p.y-k)/(double)tx)){
  
            return 1;
          }
    }
        if (p.x == a.x && ((a.y <= p.y && p.y <= b.y) || (b.y <= p.y && p.y <= a.y)) ){
          
          return 2;
        }
        if(((a.y <= p.y && p.y <= b.y) || (b.y <= p.y && p.y <= a.y))&&(p.x <= minx || p.x <= maxx)){
          return 1;

        }
     }
    return 0;
}

int inside(point p, point poly[], int n) {
  int i;
  int sum = 0;
  int v;
  for (i = 0; i < n; i++) {
    if (i + 1 == n) {
      //se o i ja está no ultimo ponto, o ponto seguinte eh o primeiro.
      v = verify(p, poly[i], poly[0]);
    } else {
      //se não o ponto seguinte eh i+1.
      v = verify(p, poly[i], poly[i + 1]);
    }
    if (v == 2) {
      return 1;
    }

    if (v == 1) {
      sum += v;
    }
  }

  if (sum == 1) {
    return 1;
  }
  if (sum % 2 == 0) {
    return 0;
  } else {
    return 1;
  }
  return 0;
}