#include "geometry.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

int verify(point p, point a, point b) {
  int minx;
  int maxx;
  int maxy;
  int miny;
  if (a.x > b.x) {
    maxx = a.x;
    minx = b.x;
  } else {
    maxx = b.x;
    minx = a.x;
  }
  if (a.y > b.y) {
    maxy = a.y;
    miny = b.y;
  } else {
    maxy = b.y;
    miny = a.y;
  }
  //  printf("come\n");
  //   //  printf("%d\n",a.x);
  //   printf("%d\n",a.y);
  //   //   printf("%d\n",b.x);
  //     printf("%d\n",b.y);
  //   //   printf("%d\n",p.x);
  //     printf("%d\n",p.y);

  double tx = ((double)(a.y - b.y) / (double)(a.x - b.x));

  double k = (a.y - (tx * a.x));

  double dif = abs(((10 * tx * p.x) + 10 * k) - 10 * p.y);

  ///// rotacao
  if ((p.y == miny) && (p.x < minx || p.x < maxx) && (abs(p.x - ((double)(p.y - k) / (double)tx)) > 0.000001)) {
    // printf("entrou no shake 0\n ");
    // printf("%d",(p.x - ((double)(p.y-k)/(double)tx)) < 0.000001) ;
    return 0;
  }

  if ((p.y == maxy) && (p.x < minx || p.x < maxx) && (abs(p.x - ((double)(p.y - k) / (double)tx)) > 0.000001)) {

    //  printf("entrou no shake 1\n ");
    if (p.x < ((double)(p.y - k) / (double)tx)) {

      return 1;
    }
  }
  if (a.x != b.x) {

    //// 2
    if ((dif < 0.000001) && ((a.y <= p.y && p.y <= b.y) || (b.y <= p.y && p.y <= a.y)) && (p.x <= minx || p.x <= maxx)) {
      if (a.y == b.y) {
        if (p.x < minx && p.x < maxx) {
          return 0;
        }
      }
      // printf("%d\n",a.y - b.y);
      // printf("%d\n",a.x - b.x);
      // printf("%lf\n",tx);
      // printf("%lf\n",k);
      // printf("%lf \n",dif);

      return 2;
    }

    ///ve se ta tocando -- 1

    if (((a.y <= p.y && p.y <= b.y) || (b.y <= p.y && p.y <= a.y)) && (p.x <= minx || p.x <= maxx)) {
      if (p.x < ((double)(p.y - k) / (double)tx)) {

        return 1;
      }
    }
  }

  else {

    if ((p.y == miny) && (p.x < minx || p.x < maxx)) {
      // printf("entrou no shake 0\n ");
      // printf("%d",(p.x - ((double)(p.y-k)/(double)tx)) < 0.000001) ;
      return 0;
    }

    if ((p.y == maxy) && (p.x < minx || p.x < maxx)) {

      //  printf("entrou no shake 1\n ");
      if (p.x < ((double)(p.y - k) / (double)tx)) {

        return 1;
      }
    }

    if (p.x == a.x && ((a.y <= p.y && p.y <= b.y) || (b.y <= p.y && p.y <= a.y))) {

      return 2;
    }
    if (((a.y <= p.y && p.y <= b.y) || (b.y <= p.y && p.y <= a.y)) && (p.x <= minx || p.x <= maxx)) {
      return 1;
    }
  }

  return 0;
}

int inside(point p, point poly[], int n) {
  int i;
  int sum = 0;
  int v;
  printf("come\n");
  for (i = 0; i < n; i++) {
    // printf("for\n");
    if (i + 1 == n) {
      //se o i ja está no ultimo ponto, o ponto seguinte eh o primeiro.
      v = verify(p, poly[i], poly[0]);
    } else {
      //se não o ponto seguinte eh i+1.
      v = verify(p, poly[i], poly[i + 1]);
    }

    printf("%d \n", v);
    if (v == 2) {
      printf("entrei 2\n");
      return 1;
    }

    if (v == 1) {
      sum += v;
    }
  }
  printf("sum %d\n", sum);

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