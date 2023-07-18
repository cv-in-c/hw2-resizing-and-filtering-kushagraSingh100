#include <math.h>
#include "image.h"

float nn_interpolate(image im, float x, float y, int c)
{
    // TODO Fill in
    return get_pixel(im, round(x),round(y),c);
}

image nn_resize(image im, int w, int h)
{
    // TODO Fill in (also fix that first line)
    image new_image;
    int x_;
    int y_;
    new_image = make_image(w,h,im.c);
    float w_scaled = (float)im.w / new_image.w;
    float h_scaled = (float)im.h / new_image.h;
    for(int i=0;i<new_image.c;i++){
        for(int j=0;j<new_image.h;j++){
            for(int k=0 ; k<new_image.w;k++){
                x_ = w_scaled*(k);
                y_ = h_scaled*(j);
                set_pixel(new_image,k,j,i,nn_interpolate(im,x_,y_,i));
            }
        }
    }

return new_image;
}

float bilinear_interpolate(image im, float x, float y, int c)
{
    // TODO
    float a1x,a1y,a2x,a2y,a3x,a3y,a4x,a4y;
    a1x = floorf(x);
    a2y = floorf(y);
    a2x = ceilf(x);
    a2y = floorf(y);
    a3x = floorf(x);
    a3y = ceilf(y);
    a4x = ceilf(x);
    a4y = ceilf(y);
    float v1,v2,v3,v4;
    v1 = get_pixel(im,a1x,a1y,c);
    v2 = get_pixel(im,a2x,a2y,c);
    v3 = get_pixel(im,a3x,a3y,c);
    v4 = get_pixel(im,a4x,a4y,c);
    float d1,d2,d3,d4;
    d1 = x-a1x;
    d2 = ceilf(x) - x;
    d3 = y - a2y;
    d4 = ceilf(y) - y;
    float q1,q2,q3;
    q1 = v1*d2 + v2*d1;
    q2 = v3*d2 + v4*d1;
    q3 = q1*d4 + q2*d3;
    return q3;
}

image bilinear_resize(image im, int w, int h)
{
    image new_image;
    int x_;
    int y_;
    new_image = make_image(w,h,im.c);
    float w_scaled = (float)im.w / new_image.w;
    float h_scaled = (float)im.h / new_image.h;
    for(int i=0;i<new_image.c;i++){
        for(int j=0;j<new_image.h;j++){
            for(int k=0 ; k<new_image.w;k++){
                x_ = (w_scaled)*(k+0.5);
                y_ = (h_scaled)*(j+0.5);
                set_pixel(new_image,k,j,i,bilinear_interpolate(im,x_,y_,i));
            }
        }
    }

return new_image;
}

