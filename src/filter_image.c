#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <assert.h>
#include "image.h"
#define TWOPI 6.2831853

void l1_normalize(image im)
{
    // TODO
    int i = 0;
float sum = 0;
while (i < im.c * im.h * im.w) {
  sum += im.data[i];
  i++;
}

if (sum != 0) {
  i = 0;
  while (i < im.c * im.h * im.w) {
    im.data[i] /= sum;
    i++;
  }
}

}

image make_box_filter(int w)
{
    // TODO
    image kernel;
    kernel = make_image(w,w,1);
    for(int x=0;x<kernel.w;x++){
        for(int y=0;y<kernel.h;y++){
            set_pixel(kernel,x,y,0,1.0/(w*w));
        }
    }
}



image convolve_image(image im, image filter, int preserve) {
    assert(filter.c == 1 || filter.c == im.c);
    
    int h_offset = filter.h / 2;
    int w_offset = filter.w / 2;
    
    image im_out = make_image(im.w, im.h, preserve ? im.c : 1);
    
    for (int i = 0; i < im.c; ++i) {
        for (int j = h_offset; j < im.h - h_offset; ++j) {
            for (int k = w_offset; k < im.w - w_offset; ++k) {
                float v = preserve ? 0 : get_pixel(im_out, k, j, 0);
                
                for (int m = -h_offset; m <= h_offset; ++m) {
                    for (int n = -w_offset; n <= w_offset; ++n) {
                        float im_pixel = get_pixel(im, k + n, j + m, i);
                        float filter_pixel = get_pixel(filter, n + w_offset, m + h_offset, filter.c == 1 ? 0 : i);
                        
                        v += im_pixel * filter_pixel;
                    }
                }
                
                set_pixel(im_out, k, j, preserve ? i : 0, v);
            }
        }
    }
    
    return im_out;
}



image make_highpass_filter()
{  image filter = make_image(3, 3, 1);
    float kernel[9] = {0, -1, 0,-1, 4, -1,0, -1, 0};
    memcpy(filter.data, kernel, sizeof(kernel));
    return filter;
}

image make_sharpen_filter()
{
    image sharpen_filter = make_image(3, 3, 1);
    float kernel[9] = {0, -1, 0,-1, 5, -1,0, -1, 0};
    memcpy(sharpen_filter.data, kernel, sizeof(kernel));
    return sharpen_filter;

}

image make_emboss_filter()
{
    image emboss_filter = make_image(3, 3, 1);
    float kernel[9] = {-2, -1, 0,-1, 1, 1,0, 1, 2};
    memcpy(emboss_filter.data, kernel, sizeof(kernel));
    return emboss_filter;
}

// Question 2.2.1: Which of these filters should we use preserve when we run our convolution and which ones should we not? Why?
// Answer: Box filter need to be presereved because we need to smooth the image in that case.sharpen_filter and emboss_filter should also be preserved because the output is even in this case.For highpass filter preserve can be set to 0

// Question 2.2.2: Do we have to do any post-processing for the above filters? Which ones and why?
// Answer: we need to do post-processing in the case of highpass,sharpen,emboss filter to avoid pixel being overflowed(not lie between 0 and 1).

image make_gaussian_filter(float sigma)
{
    // TODO
    return make_image(1,1,1);
}

image add_image(image a, image b)
{
    image final = make_image(a.w,a.h,a.c);
    float x,y,c;
    for(y=0;y<a.h;y++){
        for(x=0;x<a.w;x++){
            for(c=0;c<a.c;c++){
                set_pixel(final,x,y,c,get_pixel(a,x,y,c)+ get_pixel(b,x,y,z));
            }
        }
    }
return final;
}

image sub_image(image a, image b)
{
    image final = make_image(a.w,a.h,a.c);
    float x,y,c;
    for(y=0;y<a.h;y++){
        for(x=0;x<a.w;x++){
            for(c=0;c<a.c;c++){
                set_pixel(final,x,y,c,get_pixel(a,x,y,c)- get_pixel(b,x,y,z));
            }
        }
    }
return final;
}

image make_gx_filter()
{
    image gx_filter = make_image(3, 3, 1);
    float kernel[9] = {-1, 0, 1,-2, 0, 2,-1, 0, 1};
    memcpy(gx_filter.data, kernel, sizeof(kernel));
    return gx_filter;
}


image make_gy_filter()
{
    image gy_filter = make_image(3, 3, 1);
    float kernel[9] = {-1, -2, -1,0, 0, 0,1, 2, 1};
    memcpy(gy_filter.data, kernel, sizeof(kernel));
    return gy_filter;
}

void feature_normalize(image im)
{
    // TODO
}

image *sobel_image(image im)
{
    // TODO
    return calloc(2, sizeof(image));
}

image colorize_sobel(image im)
{
    // TODO
    return make_image(1,1,1);
}
