#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <math.h>
#include "image.h"

float get_pixel(image im, int x, int y, int c)
{
    // TODO Fill this in
    if(x<0) {x = 0;}
    if(x>=im.w) { x = im.w-1;}
    if(y<0) { y = 0;}
    if(y>=im.h) { y = im.h-1;}
    if(c<0 || c>=im.c) {return 0;}  
     else {return im.data[x + y*im.w+c*im.w*im.h];}}

void set_pixel(image im, int x, int y, int c, float v)
{ 
    // TODO Fill this in
    if( 0<=x<im.w && 0<=y<im.h && 0<=c<im.c){
      im.data[x + y*im.w+c*im.w*im.h] = v;   }
}

image copy_image(image im)
{
    image copy = make_image(im.w, im.h, im.c);
    // TODO Fill this in
    int i;
    for(i=0;i<im.w*im.h*im.c;i++){
        copy.data[i] = im.data[i];
    }
    return copy;
}

image rgb_to_grayscale(image im)
{
    assert(im.c == 3);
    image gray = make_image(im.w, im.h, 1);
    // TODO Fill this in
    int i,j,k;
    for(i=0;i<im.w*im.h;i++){
        im.data[i] = im.data[i]*0.299;
    }
    for(j=im.w*im.h;j<2*im.w*im.h;j++){
        im.data[j] = im.data[j]*0.587;
    }
    for(k=2*im.h*im.w;k<3*im.w*im.h;k++){
        im.data[k] = im.data[k]*0.114;
    }
    for(i=0,j=im.w*im.h,k=2*im.w*im.h;i<im.w*im.h,j<2*im.w*im.h,k<3*im.w*im.h;i++,j++,k++){
        gray.data[i] = im.data[i]+im.data[j]+im.data[k];
    }
    return gray;
}

void shift_image(image im, int c, float v)
{  int i;
    // TODO Fill this in
    for(i=c*im.h*im.w;i<(c+1)*im.h*im.w;i++){
        im.data[i] = im.data[i]+v;
    }

}




void clamp_image(image im)
{  int i,k;
    // TODO Fill this in
    for(i=0;i<3*im.h*im.w;i++){
        if( im.data[i]<0){
            im.data[i] = 0;
        }
    }
    for(k=0;k<3*im.h*im.w;k++){
        if(im.data[k]>1){
            im.data[k] = 1;
        }
    }
}


// These might be handy
float three_way_max(float a, float b, float c)
{
    return (a > b) ? ( (a > c) ? a : c) : ( (b > c) ? b : c) ;
}

float three_way_min(float a, float b, float c)
{
    return (a < b) ? ( (a < c) ? a : c) : ( (b < c) ? b : c) ;
}

void rgb_to_hsv(image im)
{      int i,j,k;
       float V,m,C,S,R,G,B,H1,H;
    // TODO Fill this in
    for(i=0,j=im.h*im.w,k=2*im.h*im.w;i<im.h*im.w,j<2*im.h*im.w,k<3*im.h*im.w;i++,j++,k++){
         R = im.data[i];
         G = im.data[j];
         B = im.data[k];
        V = three_way_max(R,G,B);
        m = three_way_min(R,G,B);
        C = V-m;
        if(V == 0) { S = 0;}
        else S = C/V;
        if(C==0) H1 = 0;
        else if(V==R) { H1 = (G-B)/C;}
        else if(V==G) { H1 = ((B-R)/C)+2;}
        else if(V==B) {H1 = ((R-G)/C)+4;}
        if(H1<0) {H = (H1/6)+1;}
        else {H = H1/6;}
        im.data[i]=H;
        im.data[j]=S;
        im.data[k] = V;
    }
}

void hsv_to_rgb(image im)
{
    // TODO Fill this in
      
     int i,j,k;
       float H,H1,H2,K,S,V,X,Y,Z,R,G,B;
    // TODO Fill this in
    for(i=0,j=im.h*im.w,k=2*im.h*im.w;i<im.h*im.w,j<2*im.h*im.w,k<3*im.h*im.w;i++,j++,k++){
         H = im.data[i];
         S = im.data[j];
         V = im.data[k];
    
    H1 = H*6;
K = floor(H1);
H2 = H1-K;
X = V*(1-S);
Y = V*(1-S*H2);
Z = V*(1-S*(1-H2));
if(K==0){R = V;G = Z;B = X;}
if(K==1){R = Y;G = V;B = X;}
if(K==2){R = X;G = V;B = Z;}
if(K==3){R = X;G = Y;B = V;}
if(K==4){R = Z;G = X;B = V;}
if(K==5){R = V;G = X;B = Y;}
 im.data[i]=R;
    im.data[i+im.h*im.w]=G;
    im.data[i+2*im.h*im.w]=B;
  im.data[i] = R;
         im.data[j] = G;
        im.data[k] = B;
    }}



void scale_image(image im, int c, float v)
{  int i;

    for(i=c*im.h*im.w;i<(c+1)*im.h*im.w;i++){
        im.data[i] = im.data[i]*v;
    }

}
