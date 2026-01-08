#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#include <stdio.h>

// Convert a RGB image to Black and White ( 24bits -> 8bits )
void convert_black_white(const unsigned char* source_image, int width, int height, unsigned char* destination_image){
    int index = -1;
    for(int row = 0; row < height; ++row){
        for(int col = 0; col < width; ++col){
            destination_image[row * width + col] = 0.2126f * source_image[++index] + 0.7152f * source_image[++index] + 0.0722f * source_image[++index];
        }
    }
}

// Inverse Black And White Image Colors
void inverse_black(const unsigned char* source_image, int width, int height, unsigned char* destination_image){
    for(int row = 0; row < height; ++row){
        for(int col = 0; col < width; ++col){
            destination_image[row * width + col] = 255 - source_image[row * width + col];
        }
    }
}

// Apply Sobel Filter and return single int value
int sobel_calculations(const int** filter, const unsigned char* image, int row, int width, int col){
    return filter[0][0] * image[(row - 1) * width + col - 1] + filter[0][1] * image[(row - 1) * width + col + 0] + filter[0][2] * image[(row - 1) * width + col + 1]
         + filter[1][0] * image[(row + 0) * width + col - 1] + filter[1][1] * image[(row + 0) * width + col + 0] + filter[1][2] * image[(row + 0) * width + col + 1]
         + filter[2][0] * image[(row + 1) * width + col - 1] + filter[2][1] * image[(row + 1) * width + col + 0] + filter[2][2] * image[(row + 1) * width + col + 1];
}

void apply_sobel_0(const unsigned char* source_image, unsigned char* destination_image, int width, int height){
    int sobel_filter[3][3] = {{-1, -2, -1},
                              { 0,  0,  0},
                              { 1,  2,  1}};

    for(int row = 1; row < height - 1; ++row){
        for(int col = 1; col < width - 1; ++col){
            // destination_image[row * width + col] = sobel_calculations(sobel_filter, source_image, row, width, col);
            destination_image[row * width + col] = sobel_filter[0][0] * source_image[(row - 1) * width + col - 1] + sobel_filter[0][1] * source_image[(row - 1) * width + col + 0] + sobel_filter[0][2] * source_image[(row - 1) * width + col + 1] +
                                                   sobel_filter[1][0] * source_image[(row + 0) * width + col - 1] + sobel_filter[1][1] * source_image[(row + 0) * width + col + 0] + sobel_filter[1][2] * source_image[(row + 0) * width + col + 1] +
                                                   sobel_filter[2][0] * source_image[(row + 1) * width + col - 1] + sobel_filter[2][1] * source_image[(row + 1) * width + col + 0] + sobel_filter[2][2] * source_image[(row + 1) * width + col + 1] ;
        }
    }
}

void apply_sobel_1(const unsigned char* source_image, unsigned char* destination_image, int width, int height){
    int sobel_filter[3][3] = {{-2, -1,  0},
                              {-1,  0,  1},
                              { 0,  1,  2}};

    for(int row = 1; row < height - 1; ++row){
        for(int col = 1; col < width - 1; ++col){
            destination_image[row * width + col] = sobel_filter[0][0] * source_image[(row - 1) * width + col - 1] + sobel_filter[0][1] * source_image[(row - 1) * width + col + 0] + sobel_filter[0][2] * source_image[(row - 1) * width + col + 1] +
                                                   sobel_filter[1][0] * source_image[(row + 0) * width + col - 1] + sobel_filter[1][1] * source_image[(row + 0) * width + col + 0] + sobel_filter[1][2] * source_image[(row + 0) * width + col + 1] +
                                                   sobel_filter[2][0] * source_image[(row + 1) * width + col - 1] + sobel_filter[2][1] * source_image[(row + 1) * width + col + 0] + sobel_filter[2][2] * source_image[(row + 1) * width + col + 1] ;
        }
    }
}

void apply_sobel_2(const unsigned char* source_image, unsigned char* destination_image, int width, int height){
    int sobel_filter[3][3] = {{-1,  0,  1},
                              {-2,  0,  2},
                              {-1,  0,  1}};

    for(int row = 1; row < height - 1; ++row){
        for(int col = 1; col < width - 1; ++col){
            destination_image[row * width + col] = sobel_filter[0][0] * source_image[(row - 1) * width + col - 1] + sobel_filter[0][1] * source_image[(row - 1) * width + col + 0] + sobel_filter[0][2] * source_image[(row - 1) * width + col + 1] +
                                                   sobel_filter[1][0] * source_image[(row + 0) * width + col - 1] + sobel_filter[1][1] * source_image[(row + 0) * width + col + 0] + sobel_filter[1][2] * source_image[(row + 0) * width + col + 1] +
                                                   sobel_filter[2][0] * source_image[(row + 1) * width + col - 1] + sobel_filter[2][1] * source_image[(row + 1) * width + col + 0] + sobel_filter[2][2] * source_image[(row + 1) * width + col + 1] ;
        }
    }
}

void apply_sobel_3(const unsigned char* source_image, unsigned char* destination_image, int width, int height){
    int sobel_filter[3][3] = {{ 0,  1,  2},
                              {-1,  0,  1},
                              {-2, -1,  0}};

    for(int row = 1; row < height - 1; ++row){
        for(int col = 1; col < width - 1; ++col){
            destination_image[row * width + col] = sobel_filter[0][0] * source_image[(row - 1) * width + col - 1] + sobel_filter[0][1] * source_image[(row - 1) * width + col + 0] + sobel_filter[0][2] * source_image[(row - 1) * width + col + 1] +
                                                   sobel_filter[1][0] * source_image[(row + 0) * width + col - 1] + sobel_filter[1][1] * source_image[(row + 0) * width + col + 0] + sobel_filter[1][2] * source_image[(row + 0) * width + col + 1] +
                                                   sobel_filter[2][0] * source_image[(row + 1) * width + col - 1] + sobel_filter[2][1] * source_image[(row + 1) * width + col + 0] + sobel_filter[2][2] * source_image[(row + 1) * width + col + 1] ;
        }
    }
}

void apply_sobel_4(const unsigned char* source_image, unsigned char* destination_image, int width, int height){
    int sobel_filter[3][3] = {{ 1,  2,  1},
                              { 0,  0,  0},
                              {-1, -2, -1}};

    for(int row = 1; row < height - 1; ++row){
        for(int col = 1; col < width - 1; ++col){
            destination_image[row * width + col] = sobel_filter[0][0] * source_image[(row - 1) * width + col - 1] + sobel_filter[0][1] * source_image[(row - 1) * width + col + 0] + sobel_filter[0][2] * source_image[(row - 1) * width + col + 1] +
                                                   sobel_filter[1][0] * source_image[(row + 0) * width + col - 1] + sobel_filter[1][1] * source_image[(row + 0) * width + col + 0] + sobel_filter[1][2] * source_image[(row + 0) * width + col + 1] +
                                                   sobel_filter[2][0] * source_image[(row + 1) * width + col - 1] + sobel_filter[2][1] * source_image[(row + 1) * width + col + 0] + sobel_filter[2][2] * source_image[(row + 1) * width + col + 1] ;
        }
    }
}

void apply_sobel_5(const unsigned char* source_image, unsigned char* destination_image, int width, int height){
    int sobel_filter[3][3] = {{ 2,  1,  0},
                              { 1,  0, -1},
                              { 0, -1, -2}};

    for(int row = 1; row < height - 1; ++row){
        for(int col = 1; col < width - 1; ++col){
            destination_image[row * width + col] = sobel_filter[0][0] * source_image[(row - 1) * width + col - 1] + sobel_filter[0][1] * source_image[(row - 1) * width + col + 0] + sobel_filter[0][2] * source_image[(row - 1) * width + col + 1] +
                                                   sobel_filter[1][0] * source_image[(row + 0) * width + col - 1] + sobel_filter[1][1] * source_image[(row + 0) * width + col + 0] + sobel_filter[1][2] * source_image[(row + 0) * width + col + 1] +
                                                   sobel_filter[2][0] * source_image[(row + 1) * width + col - 1] + sobel_filter[2][1] * source_image[(row + 1) * width + col + 0] + sobel_filter[2][2] * source_image[(row + 1) * width + col + 1] ;
        }
    }
}

void apply_sobel_6(const unsigned char* source_image, unsigned char* destination_image, int width, int height){
    int sobel_filter[3][3] = {{ 1,  0, -1},
                              { 2,  0, -2},
                              { 1,  0, -1}};

    for(int row = 1; row < height - 1; ++row){
        for(int col = 1; col < width - 1; ++col){
            destination_image[row * width + col] = sobel_filter[0][0] * source_image[(row - 1) * width + col - 1] + sobel_filter[0][1] * source_image[(row - 1) * width + col + 0] + sobel_filter[0][2] * source_image[(row - 1) * width + col + 1] +
                                                   sobel_filter[1][0] * source_image[(row + 0) * width + col - 1] + sobel_filter[1][1] * source_image[(row + 0) * width + col + 0] + sobel_filter[1][2] * source_image[(row + 0) * width + col + 1] +
                                                   sobel_filter[2][0] * source_image[(row + 1) * width + col - 1] + sobel_filter[2][1] * source_image[(row + 1) * width + col + 0] + sobel_filter[2][2] * source_image[(row + 1) * width + col + 1] ;
        }
    }
}

void apply_sobel_7(const unsigned char* source_image, unsigned char* destination_image, int width, int height){
    int sobel_filter[3][3] = {{ 0, -1, -2},
                              { 1,  0, -1},
                              { 2,  1,  0}};

    for(int row = 1; row < height - 1; ++row){
        for(int col = 1; col < width - 1; ++col){
            destination_image[row * width + col] = sobel_filter[0][0] * source_image[(row - 1) * width + col - 1] + sobel_filter[0][1] * source_image[(row - 1) * width + col + 0] + sobel_filter[0][2] * source_image[(row - 1) * width + col + 1] +
                                                   sobel_filter[1][0] * source_image[(row + 0) * width + col - 1] + sobel_filter[1][1] * source_image[(row + 0) * width + col + 0] + sobel_filter[1][2] * source_image[(row + 0) * width + col + 1] +
                                                   sobel_filter[2][0] * source_image[(row + 1) * width + col - 1] + sobel_filter[2][1] * source_image[(row + 1) * width + col + 0] + sobel_filter[2][2] * source_image[(row + 1) * width + col + 1] ;
        }
    }
}

void apply_advance_sobel_0(const unsigned char* source_image, int width, int height, unsigned char* destination_image){
    int Gx[3][3] = {{-1,-2,-1},
                    { 0, 0, 0},
                    { 1, 2, 1}};

    int Gy[3][3] = {{ 1,  0, -1},
                    { 2,  0, -2},
                    { 1,  0, -1}};

    for(int row = 1; row < height - 1; ++row){
        for(int col = 1; col < width - 1; ++col){
            int gx = Gx[0][0] * source_image[(row - 1) * width + col - 1] + Gx[0][1] * source_image[(row - 1) * width + col + 0] + Gx[0][2] * source_image[(row - 1) * width + col + 1] +
                     Gx[1][0] * source_image[(row + 0) * width + col - 1] + Gx[1][1] * source_image[(row + 0) * width + col + 0] + Gx[1][2] * source_image[(row + 0) * width + col + 1] +
                     Gx[2][0] * source_image[(row + 1) * width + col - 1] + Gx[2][1] * source_image[(row + 1) * width + col + 0] + Gx[2][2] * source_image[(row + 1) * width + col + 1] ;
            
            int gy = Gy[0][0] * source_image[(row - 1) * width + col - 1] + Gy[0][1] * source_image[(row - 1) * width + col + 0] + Gy[0][2] * source_image[(row - 1) * width + col + 1] +
                     Gy[1][0] * source_image[(row + 0) * width + col - 1] + Gy[1][1] * source_image[(row + 0) * width + col + 0] + Gy[1][2] * source_image[(row + 0) * width + col + 1] +
                     Gy[2][0] * source_image[(row + 1) * width + col - 1] + Gy[2][1] * source_image[(row + 1) * width + col + 0] + Gy[2][2] * source_image[(row + 1) * width + col + 1] ;

            destination_image[row * width + col] = sqrt(gx * gx + gy * gy);
        }
    }
}

void apply_advance_sobel_1(const unsigned char* source_image, int width, int height, unsigned char* destination_image){
    int Gx[3][3] = {{-2,-1, 0},
                    {-1, 0, 1},
                    { 0, 1, 2}};

    int Gy[3][3] = {{ 0, -1, -2},
                    { 1,  0, -1},
                    { 2,  1,  0}};

    for(int row = 1; row < height - 1; ++row){
        for(int col = 1; col < width - 1; ++col){
            int gx = Gx[0][0] * source_image[(row - 1) * width + col - 1] + Gx[0][1] * source_image[(row - 1) * width + col + 0] + Gx[0][2] * source_image[(row - 1) * width + col + 1] +
                     Gx[1][0] * source_image[(row + 0) * width + col - 1] + Gx[1][1] * source_image[(row + 0) * width + col + 0] + Gx[1][2] * source_image[(row + 0) * width + col + 1] +
                     Gx[2][0] * source_image[(row + 1) * width + col - 1] + Gx[2][1] * source_image[(row + 1) * width + col + 0] + Gx[2][2] * source_image[(row + 1) * width + col + 1] ;
            
            int gy = Gy[0][0] * source_image[(row - 1) * width + col - 1] + Gy[0][1] * source_image[(row - 1) * width + col + 0] + Gy[0][2] * source_image[(row - 1) * width + col + 1] +
                     Gy[1][0] * source_image[(row + 0) * width + col - 1] + Gy[1][1] * source_image[(row + 0) * width + col + 0] + Gy[1][2] * source_image[(row + 0) * width + col + 1] +
                     Gy[2][0] * source_image[(row + 1) * width + col - 1] + Gy[2][1] * source_image[(row + 1) * width + col + 0] + Gy[2][2] * source_image[(row + 1) * width + col + 1] ;

            destination_image[row * width + col] = sqrt(gx * gx + gy * gy);
        }
    }
}

void apply_advance_sobel_2(const unsigned char* source_image, int width, int height, unsigned char* destination_image){
    int Gx[3][3] = {{-1, 0, 1},
                    {-2, 0, 2},
                    {-1, 0, 1}};

    int Gy[3][3] = {{-1, -2, -1},
                    { 0,  0,  0},
                    { 1,  2,  1}};

    for(int row = 1; row < height - 1; ++row){
        for(int col = 1; col < width - 1; ++col){
            int gx = Gx[0][0] * source_image[(row - 1) * width + col - 1] + Gx[0][1] * source_image[(row - 1) * width + col + 0] + Gx[0][2] * source_image[(row - 1) * width + col + 1] +
                     Gx[1][0] * source_image[(row + 0) * width + col - 1] + Gx[1][1] * source_image[(row + 0) * width + col + 0] + Gx[1][2] * source_image[(row + 0) * width + col + 1] +
                     Gx[2][0] * source_image[(row + 1) * width + col - 1] + Gx[2][1] * source_image[(row + 1) * width + col + 0] + Gx[2][2] * source_image[(row + 1) * width + col + 1] ;
            
            int gy = Gy[0][0] * source_image[(row - 1) * width + col - 1] + Gy[0][1] * source_image[(row - 1) * width + col + 0] + Gy[0][2] * source_image[(row - 1) * width + col + 1] +
                     Gy[1][0] * source_image[(row + 0) * width + col - 1] + Gy[1][1] * source_image[(row + 0) * width + col + 0] + Gy[1][2] * source_image[(row + 0) * width + col + 1] +
                     Gy[2][0] * source_image[(row + 1) * width + col - 1] + Gy[2][1] * source_image[(row + 1) * width + col + 0] + Gy[2][2] * source_image[(row + 1) * width + col + 1] ;

            destination_image[row * width + col] = sqrt(gx * gx + gy * gy);
        }
    }
}

void apply_advance_sobel_3(const unsigned char* source_image, int width, int height, unsigned char* destination_image){
    int Gx[3][3] = {{ 0, 1, 2},
                    {-1, 0, 1},
                    {-2,-1, 0}};

    int Gy[3][3] = {{-2, -1, 0},
                    {-1,  0, 1},
                    { 0,  1, 2}};

    for(int row = 1; row < height - 1; ++row){
        for(int col = 1; col < width - 1; ++col){
            int gx = Gx[0][0] * source_image[(row - 1) * width + col - 1] + Gx[0][1] * source_image[(row - 1) * width + col + 0] + Gx[0][2] * source_image[(row - 1) * width + col + 1] +
                     Gx[1][0] * source_image[(row + 0) * width + col - 1] + Gx[1][1] * source_image[(row + 0) * width + col + 0] + Gx[1][2] * source_image[(row + 0) * width + col + 1] +
                     Gx[2][0] * source_image[(row + 1) * width + col - 1] + Gx[2][1] * source_image[(row + 1) * width + col + 0] + Gx[2][2] * source_image[(row + 1) * width + col + 1] ;
            
            int gy = Gy[0][0] * source_image[(row - 1) * width + col - 1] + Gy[0][1] * source_image[(row - 1) * width + col + 0] + Gy[0][2] * source_image[(row - 1) * width + col + 1] +
                     Gy[1][0] * source_image[(row + 0) * width + col - 1] + Gy[1][1] * source_image[(row + 0) * width + col + 0] + Gy[1][2] * source_image[(row + 0) * width + col + 1] +
                     Gy[2][0] * source_image[(row + 1) * width + col - 1] + Gy[2][1] * source_image[(row + 1) * width + col + 0] + Gy[2][2] * source_image[(row + 1) * width + col + 1] ;

            destination_image[row * width + col] = sqrt(gx * gx + gy * gy);
        }
    }
}

void apply_advance_sobel_4(const unsigned char* source_image, int width, int height, unsigned char* destination_image){
    int Gx[3][3] = {{ 1, 2, 1},
                    { 0, 0, 0},
                    {-1,-2,-1}};

    int Gy[3][3] = {{-1,  0, 1},
                    {-2,  0, 2},
                    {-1,  0, 1}};

    for(int row = 1; row < height - 1; ++row){
        for(int col = 1; col < width - 1; ++col){
            int gx = Gx[0][0] * source_image[(row - 1) * width + col - 1] + Gx[0][1] * source_image[(row - 1) * width + col + 0] + Gx[0][2] * source_image[(row - 1) * width + col + 1] +
                     Gx[1][0] * source_image[(row + 0) * width + col - 1] + Gx[1][1] * source_image[(row + 0) * width + col + 0] + Gx[1][2] * source_image[(row + 0) * width + col + 1] +
                     Gx[2][0] * source_image[(row + 1) * width + col - 1] + Gx[2][1] * source_image[(row + 1) * width + col + 0] + Gx[2][2] * source_image[(row + 1) * width + col + 1] ;
            
            int gy = Gy[0][0] * source_image[(row - 1) * width + col - 1] + Gy[0][1] * source_image[(row - 1) * width + col + 0] + Gy[0][2] * source_image[(row - 1) * width + col + 1] +
                     Gy[1][0] * source_image[(row + 0) * width + col - 1] + Gy[1][1] * source_image[(row + 0) * width + col + 0] + Gy[1][2] * source_image[(row + 0) * width + col + 1] +
                     Gy[2][0] * source_image[(row + 1) * width + col - 1] + Gy[2][1] * source_image[(row + 1) * width + col + 0] + Gy[2][2] * source_image[(row + 1) * width + col + 1] ;

            destination_image[row * width + col] = sqrt(gx * gx + gy * gy);
        }
    }
}

void apply_advance_sobel_5(const unsigned char* source_image, int width, int height, unsigned char* destination_image){
    int Gx[3][3] = {{ 2, 1, 0},
                    { 1, 0,-1},
                    { 0,-1,-2}};

    int Gy[3][3] = {{ 0,  1, 2},
                    {-1,  0, 1},
                    {-2, -1, 0}};

    for(int row = 1; row < height - 1; ++row){
        for(int col = 1; col < width - 1; ++col){
            int gx = Gx[0][0] * source_image[(row - 1) * width + col - 1] + Gx[0][1] * source_image[(row - 1) * width + col + 0] + Gx[0][2] * source_image[(row - 1) * width + col + 1] +
                     Gx[1][0] * source_image[(row + 0) * width + col - 1] + Gx[1][1] * source_image[(row + 0) * width + col + 0] + Gx[1][2] * source_image[(row + 0) * width + col + 1] +
                     Gx[2][0] * source_image[(row + 1) * width + col - 1] + Gx[2][1] * source_image[(row + 1) * width + col + 0] + Gx[2][2] * source_image[(row + 1) * width + col + 1] ;
            
            int gy = Gy[0][0] * source_image[(row - 1) * width + col - 1] + Gy[0][1] * source_image[(row - 1) * width + col + 0] + Gy[0][2] * source_image[(row - 1) * width + col + 1] +
                     Gy[1][0] * source_image[(row + 0) * width + col - 1] + Gy[1][1] * source_image[(row + 0) * width + col + 0] + Gy[1][2] * source_image[(row + 0) * width + col + 1] +
                     Gy[2][0] * source_image[(row + 1) * width + col - 1] + Gy[2][1] * source_image[(row + 1) * width + col + 0] + Gy[2][2] * source_image[(row + 1) * width + col + 1] ;

            destination_image[row * width + col] = sqrt(gx * gx + gy * gy);
        }
    }
}

void apply_advance_sobel_6(const unsigned char* source_image, int width, int height, unsigned char* destination_image){
    int Gx[3][3] = {{ 1, 0,-1},
                    { 2, 0,-2},
                    { 1, 0,-1}};

    int Gy[3][3] = {{ 1,  2, 1},
                    { 0,  0, 0},
                    {-1, -2,-1}};

    for(int row = 1; row < height - 1; ++row){
        for(int col = 1; col < width - 1; ++col){
            int gx = Gx[0][0] * source_image[(row - 1) * width + col - 1] + Gx[0][1] * source_image[(row - 1) * width + col + 0] + Gx[0][2] * source_image[(row - 1) * width + col + 1] +
                     Gx[1][0] * source_image[(row + 0) * width + col - 1] + Gx[1][1] * source_image[(row + 0) * width + col + 0] + Gx[1][2] * source_image[(row + 0) * width + col + 1] +
                     Gx[2][0] * source_image[(row + 1) * width + col - 1] + Gx[2][1] * source_image[(row + 1) * width + col + 0] + Gx[2][2] * source_image[(row + 1) * width + col + 1] ;
            
            int gy = Gy[0][0] * source_image[(row - 1) * width + col - 1] + Gy[0][1] * source_image[(row - 1) * width + col + 0] + Gy[0][2] * source_image[(row - 1) * width + col + 1] +
                     Gy[1][0] * source_image[(row + 0) * width + col - 1] + Gy[1][1] * source_image[(row + 0) * width + col + 0] + Gy[1][2] * source_image[(row + 0) * width + col + 1] +
                     Gy[2][0] * source_image[(row + 1) * width + col - 1] + Gy[2][1] * source_image[(row + 1) * width + col + 0] + Gy[2][2] * source_image[(row + 1) * width + col + 1] ;

            destination_image[row * width + col] = sqrt(gx * gx + gy * gy);
        }
    }
}

void apply_advance_sobel_7(const unsigned char* source_image, int width, int height, unsigned char* destination_image){
    int Gx[3][3] = {{ 0,-1,-2},
                    { 1, 0,-1},
                    { 2, 1, 0}};

    int Gy[3][3] = {{ 2,  1, 0},
                    { 1,  0,-1},
                    { 0, -1,-2}};

    for(int row = 1; row < height - 1; ++row){
        for(int col = 1; col < width - 1; ++col){
            int gx = Gx[0][0] * source_image[(row - 1) * width + col - 1] + Gx[0][1] * source_image[(row - 1) * width + col + 0] + Gx[0][2] * source_image[(row - 1) * width + col + 1] +
                     Gx[1][0] * source_image[(row + 0) * width + col - 1] + Gx[1][1] * source_image[(row + 0) * width + col + 0] + Gx[1][2] * source_image[(row + 0) * width + col + 1] +
                     Gx[2][0] * source_image[(row + 1) * width + col - 1] + Gx[2][1] * source_image[(row + 1) * width + col + 0] + Gx[2][2] * source_image[(row + 1) * width + col + 1] ;
            
            int gy = Gy[0][0] * source_image[(row - 1) * width + col - 1] + Gy[0][1] * source_image[(row - 1) * width + col + 0] + Gy[0][2] * source_image[(row - 1) * width + col + 1] +
                     Gy[1][0] * source_image[(row + 0) * width + col - 1] + Gy[1][1] * source_image[(row + 0) * width + col + 0] + Gy[1][2] * source_image[(row + 0) * width + col + 1] +
                     Gy[2][0] * source_image[(row + 1) * width + col - 1] + Gy[2][1] * source_image[(row + 1) * width + col + 0] + Gy[2][2] * source_image[(row + 1) * width + col + 1] ;

            destination_image[row * width + col] = sqrt(gx * gx + gy * gy);
        }
    }
}

int main(int argc, char** argv){
    if(argc != 2){
        fprintf(stderr, "Only One Argument Allowed : code.exe image.png\n");
        return 1;
    }

    int sWidth, sHeight, sChannels;

    unsigned char* source_image = stbi_load(argv[1], &sWidth, &sHeight, &sChannels, 0);
    if(source_image == NULL){
        fprintf(stderr, "Error Loading Image : %s\n", argv[1]);
        return 1;
    }
    if(sChannels != 3){
        fprintf(stderr, "Channel Mismatch, Only Allowed : 3\n");
        stbi_image_free(source_image);
        return 1;
    }
    printf("Loaded image with width %d, height %d, channels %d\n", sWidth, sHeight, sChannels);

    unsigned char* black_image = malloc((size_t)sWidth * sHeight * 1);
    unsigned char* black_sobel_0_image = malloc((size_t)sWidth * sHeight * 1);
    unsigned char* black_sobel_1_image = malloc((size_t)sWidth * sHeight * 1);
    unsigned char* black_sobel_2_image = malloc((size_t)sWidth * sHeight * 1);
    unsigned char* black_sobel_3_image = malloc((size_t)sWidth * sHeight * 1);
    unsigned char* black_sobel_4_image = malloc((size_t)sWidth * sHeight * 1);
    unsigned char* black_sobel_5_image = malloc((size_t)sWidth * sHeight * 1);
    unsigned char* black_sobel_6_image = malloc((size_t)sWidth * sHeight * 1);
    unsigned char* black_sobel_7_image = malloc((size_t)sWidth * sHeight * 1);

    unsigned char* white_image = malloc((size_t)sWidth * sHeight * 1);
    unsigned char* white_sobel_0_image = malloc((size_t)sWidth * sHeight * 1);
    unsigned char* white_sobel_1_image = malloc((size_t)sWidth * sHeight * 1);
    unsigned char* white_sobel_2_image = malloc((size_t)sWidth * sHeight * 1);
    unsigned char* white_sobel_3_image = malloc((size_t)sWidth * sHeight * 1);
    unsigned char* white_sobel_4_image = malloc((size_t)sWidth * sHeight * 1);
    unsigned char* white_sobel_5_image = malloc((size_t)sWidth * sHeight * 1);
    unsigned char* white_sobel_6_image = malloc((size_t)sWidth * sHeight * 1);
    unsigned char* white_sobel_7_image = malloc((size_t)sWidth * sHeight * 1);

    unsigned char* advance_black_sobel_0_image = malloc((size_t)sWidth * sHeight * 1);
    unsigned char* advance_black_sobel_1_image = malloc((size_t)sWidth * sHeight * 1);
    unsigned char* advance_black_sobel_2_image = malloc((size_t)sWidth * sHeight * 1);
    unsigned char* advance_black_sobel_3_image = malloc((size_t)sWidth * sHeight * 1);
    unsigned char* advance_black_sobel_4_image = malloc((size_t)sWidth * sHeight * 1);
    unsigned char* advance_black_sobel_5_image = malloc((size_t)sWidth * sHeight * 1);
    unsigned char* advance_black_sobel_6_image = malloc((size_t)sWidth * sHeight * 1);
    unsigned char* advance_black_sobel_7_image = malloc((size_t)sWidth * sHeight * 1);

    unsigned char* advance_white_sobel_0_image = malloc((size_t)sWidth * sHeight * 1);
    unsigned char* advance_white_sobel_1_image = malloc((size_t)sWidth * sHeight * 1);
    unsigned char* advance_white_sobel_2_image = malloc((size_t)sWidth * sHeight * 1);
    unsigned char* advance_white_sobel_3_image = malloc((size_t)sWidth * sHeight * 1);
    unsigned char* advance_white_sobel_4_image = malloc((size_t)sWidth * sHeight * 1);
    unsigned char* advance_white_sobel_5_image = malloc((size_t)sWidth * sHeight * 1);
    unsigned char* advance_white_sobel_6_image = malloc((size_t)sWidth * sHeight * 1);
    unsigned char* advance_white_sobel_7_image = malloc((size_t)sWidth * sHeight * 1);

    if(black_image == NULL || black_sobel_0_image == NULL || black_sobel_1_image == NULL || black_sobel_2_image == NULL || black_sobel_3_image == NULL || black_sobel_4_image == NULL || black_sobel_5_image == NULL || black_sobel_6_image == NULL || black_sobel_7_image == NULL || white_image == NULL || white_sobel_0_image == NULL || white_sobel_1_image == NULL || white_sobel_2_image == NULL || white_sobel_3_image == NULL || white_sobel_4_image == NULL || white_sobel_5_image == NULL || white_sobel_6_image == NULL || white_sobel_7_image == NULL || advance_black_sobel_0_image == NULL || advance_black_sobel_1_image == NULL || advance_black_sobel_2_image == NULL || advance_black_sobel_3_image == NULL || advance_black_sobel_4_image == NULL || advance_black_sobel_5_image == NULL || advance_black_sobel_6_image == NULL || advance_black_sobel_7_image == NULL || advance_white_sobel_0_image == NULL || advance_white_sobel_1_image == NULL || advance_white_sobel_2_image == NULL || advance_white_sobel_3_image == NULL || advance_white_sobel_4_image == NULL || advance_white_sobel_5_image == NULL || advance_white_sobel_6_image == NULL || advance_white_sobel_7_image == NULL){
        fprintf(stderr, "Error Memory Allocation\n");
        stbi_image_free(free);
        return 1;
    }

    convert_black_white(source_image, sWidth, sHeight, black_image);
    stbi_write_png("0 black.png", sWidth, sHeight, 1, black_image, sWidth * 1);
    apply_sobel_0(black_image, black_sobel_0_image, sWidth, sHeight);
    stbi_write_png("1 black_sobel0.png", sWidth, sHeight, 1, black_sobel_0_image, sWidth * 1);
    apply_sobel_1(black_image, black_sobel_1_image, sWidth, sHeight);
    stbi_write_png("2 black_sobel1.png", sWidth, sHeight, 1, black_sobel_1_image, sWidth * 1);
    apply_sobel_2(black_image, black_sobel_2_image, sWidth, sHeight);
    stbi_write_png("3 black_sobel2.png", sWidth, sHeight, 1, black_sobel_2_image, sWidth * 1);
    apply_sobel_3(black_image, black_sobel_3_image, sWidth, sHeight);
    stbi_write_png("4 black_sobel3.png", sWidth, sHeight, 1, black_sobel_3_image, sWidth * 1);
    apply_sobel_4(black_image, black_sobel_4_image, sWidth, sHeight);
    stbi_write_png("5 black_sobel4.png", sWidth, sHeight, 1, black_sobel_4_image, sWidth * 1);
    apply_sobel_5(black_image, black_sobel_5_image, sWidth, sHeight);
    stbi_write_png("6 black_sobel5.png", sWidth, sHeight, 1, black_sobel_5_image, sWidth * 1);
    apply_sobel_6(black_image, black_sobel_6_image, sWidth, sHeight);
    stbi_write_png("7 black_sobel6.png", sWidth, sHeight, 1, black_sobel_6_image, sWidth * 1);
    apply_sobel_7(black_image, black_sobel_7_image, sWidth, sHeight);
    stbi_write_png("8 black_sobel7.png", sWidth, sHeight, 1, black_sobel_7_image, sWidth * 1);

    inverse_black(black_image, sWidth, sHeight, white_image);
    stbi_write_png("9 white.png", sWidth, sHeight, 1, white_image, sWidth * 1);
    apply_sobel_0(white_image, white_sobel_0_image, sWidth, sHeight);
    stbi_write_png("10 white_sobel0.png", sWidth, sHeight, 1, white_sobel_0_image, sWidth * 1);
    apply_sobel_1(white_image, white_sobel_1_image, sWidth, sHeight);
    stbi_write_png("11 white_sobel1.png", sWidth, sHeight, 1, white_sobel_1_image, sWidth * 1);
    apply_sobel_2(white_image, white_sobel_2_image, sWidth, sHeight);
    stbi_write_png("12 white_sobel2.png", sWidth, sHeight, 1, white_sobel_2_image, sWidth * 1);
    apply_sobel_3(white_image, white_sobel_3_image, sWidth, sHeight);
    stbi_write_png("13 white_sobel3.png", sWidth, sHeight, 1, white_sobel_3_image, sWidth * 1);
    apply_sobel_4(white_image, white_sobel_4_image, sWidth, sHeight);
    stbi_write_png("14 white_sobel4.png", sWidth, sHeight, 1, white_sobel_4_image, sWidth * 1);
    apply_sobel_5(white_image, white_sobel_5_image, sWidth, sHeight);
    stbi_write_png("15 white_sobel5.png", sWidth, sHeight, 1, white_sobel_5_image, sWidth * 1);
    apply_sobel_6(white_image, white_sobel_6_image, sWidth, sHeight);
    stbi_write_png("16 white_sobel6.png", sWidth, sHeight, 1, white_sobel_6_image, sWidth * 1);
    apply_sobel_7(white_image, white_sobel_7_image, sWidth, sHeight);
    stbi_write_png("17 white_sobel7.png", sWidth, sHeight, 1, white_sobel_7_image, sWidth * 1);

    apply_advance_sobel_0(black_image, sWidth, sHeight, advance_black_sobel_0_image);
    stbi_write_png("18 advance_black_sobel0.png", sWidth, sHeight, 1, advance_black_sobel_0_image, sWidth * 1);
    apply_advance_sobel_1(black_image, sWidth, sHeight, advance_black_sobel_1_image);
    stbi_write_png("19 advance_black_sobel1.png", sWidth, sHeight, 1, advance_black_sobel_1_image, sWidth * 1);
    apply_advance_sobel_2(black_image, sWidth, sHeight, advance_black_sobel_2_image);
    stbi_write_png("20 advance_black_sobel2.png", sWidth, sHeight, 1, advance_black_sobel_2_image, sWidth * 1);
    apply_advance_sobel_3(black_image, sWidth, sHeight, advance_black_sobel_3_image);
    stbi_write_png("21 advance_black_sobel3.png", sWidth, sHeight, 1, advance_black_sobel_3_image, sWidth * 1);
    apply_advance_sobel_4(black_image, sWidth, sHeight, advance_black_sobel_4_image);
    stbi_write_png("22 advance_black_sobel4.png", sWidth, sHeight, 1, advance_black_sobel_4_image, sWidth * 1);
    apply_advance_sobel_5(black_image, sWidth, sHeight, advance_black_sobel_5_image);
    stbi_write_png("23 advance_black_sobel5.png", sWidth, sHeight, 1, advance_black_sobel_5_image, sWidth * 1);
    apply_advance_sobel_6(black_image, sWidth, sHeight, advance_black_sobel_6_image);
    stbi_write_png("24 advance_black_sobel6.png", sWidth, sHeight, 1, advance_black_sobel_6_image, sWidth * 1);
    apply_advance_sobel_7(black_image, sWidth, sHeight, advance_black_sobel_7_image);
    stbi_write_png("25 advance_black_sobel7.png", sWidth, sHeight, 1, advance_black_sobel_7_image, sWidth * 1);

    apply_advance_sobel_0(white_image, sWidth, sHeight, advance_white_sobel_0_image);
    stbi_write_png("26 advance_white_sobel0.png", sWidth, sHeight, 1, advance_white_sobel_0_image, sWidth * 1);
    apply_advance_sobel_1(white_image, sWidth, sHeight, advance_white_sobel_1_image);
    stbi_write_png("27 advance_white_sobel1.png", sWidth, sHeight, 1, advance_white_sobel_1_image, sWidth * 1);
    apply_advance_sobel_2(white_image, sWidth, sHeight, advance_white_sobel_2_image);
    stbi_write_png("28 advance_white_sobel2.png", sWidth, sHeight, 1, advance_white_sobel_2_image, sWidth * 1);
    apply_advance_sobel_3(white_image, sWidth, sHeight, advance_white_sobel_3_image);
    stbi_write_png("29 advance_white_sobel3.png", sWidth, sHeight, 1, advance_white_sobel_3_image, sWidth * 1);
    apply_advance_sobel_4(white_image, sWidth, sHeight, advance_white_sobel_4_image);
    stbi_write_png("30 advance_white_sobel4.png", sWidth, sHeight, 1, advance_white_sobel_4_image, sWidth * 1);
    apply_advance_sobel_5(white_image, sWidth, sHeight, advance_white_sobel_5_image);
    stbi_write_png("31 advance_white_sobel5.png", sWidth, sHeight, 1, advance_white_sobel_5_image, sWidth * 1);
    apply_advance_sobel_6(white_image, sWidth, sHeight, advance_white_sobel_6_image);
    stbi_write_png("32 advance_white_sobel6.png", sWidth, sHeight, 1, advance_white_sobel_6_image, sWidth * 1);
    apply_advance_sobel_7(white_image, sWidth, sHeight, advance_white_sobel_7_image);
    stbi_write_png("33 advance_white_sobel7.png", sWidth, sHeight, 1, advance_white_sobel_7_image, sWidth * 1);



    stbi_image_free(source_image);
    free(black_image);
    free(black_sobel_0_image);
    free(black_sobel_1_image);
    free(black_sobel_2_image);
    free(black_sobel_3_image);
    free(black_sobel_4_image);
    free(black_sobel_5_image);
    free(black_sobel_6_image);
    free(black_sobel_7_image);

    free(white_image);
    free(white_sobel_0_image);
    free(white_sobel_1_image);
    free(white_sobel_2_image);
    free(white_sobel_3_image);
    free(white_sobel_4_image);
    free(white_sobel_5_image);
    free(white_sobel_6_image);
    free(white_sobel_7_image);

    free(advance_black_sobel_0_image);
    free(advance_black_sobel_1_image);
    free(advance_black_sobel_2_image);
    free(advance_black_sobel_3_image);
    free(advance_black_sobel_4_image);
    free(advance_black_sobel_5_image);
    free(advance_black_sobel_6_image);
    free(advance_black_sobel_7_image);

    free(advance_white_sobel_0_image);
    free(advance_white_sobel_1_image);
    free(advance_white_sobel_2_image);
    free(advance_white_sobel_3_image);
    free(advance_white_sobel_4_image);
    free(advance_white_sobel_5_image);
    free(advance_white_sobel_6_image);
    free(advance_white_sobel_7_image);
    
    return 0;
}