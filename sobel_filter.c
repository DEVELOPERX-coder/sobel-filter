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
int sobel_calculations(const int (*filter)[3], const unsigned char* image, int row, int width, int col, int trim, int square){
    int val = filter[0][0] * image[(row - 1) * width + col - 1] + filter[0][1] * image[(row - 1) * width + col + 0] + filter[0][2] * image[(row - 1) * width + col + 1]
            + filter[1][0] * image[(row + 0) * width + col - 1] + filter[1][1] * image[(row + 0) * width + col + 0] + filter[1][2] * image[(row + 0) * width + col + 1]
            + filter[2][0] * image[(row + 1) * width + col - 1] + filter[2][1] * image[(row + 1) * width + col + 0] + filter[2][2] * image[(row + 1) * width + col + 1];

    if(trim){
        if(val > 255) val = 255;
        if(val < 0) val = 0;
    }
    if(square){
        val = sqrt(val * val);
    }

    return val;
}

// Apply 3x3 Filter to 8Bit Image
void apply_filter(const unsigned char* source_image, unsigned char* destination_image, int height, int width, const int (*filter)[3], int trim, int square){
    for(int row = 1; row < height - 1; ++row){
        for(int col = 1; col < width - 1; ++col){
            destination_image[row * width + col] = sobel_calculations(filter, source_image, row, width, col, trim, square);
        }
    }
}

// Apply Sobel 0 Direction X or Y Dir ( X = 0, Y = 1)
void apply_sobel_0(const unsigned char* source_image, unsigned char* destination_image, int width, int height, int dir, int trim, int square){
    int sobel_filter_x[3][3] = {{-1, -2, -1},
                                { 0,  0,  0},
                                { 1,  2,  1}};
    
    int sobel_filter_y[3][3] = {{ 1,  0, -1},
                                { 2,  0, -2},
                                { 1,  0, -1}};

    if(dir == 0) apply_filter(source_image, destination_image, height, width, sobel_filter_x, trim, square);
    else         apply_filter(source_image, destination_image, height, width, sobel_filter_y, trim, square);
}

// Apply Sobel 1 Direction X Dir
void apply_sobel_1(const unsigned char* source_image, unsigned char* destination_image, int width, int height){
    int sobel_filter[3][3] = {{-2, -1,  0},
                              {-1,  0,  1},
                              { 0,  1,  2}};

    apply_filter(source_image, destination_image, height, width, sobel_filter, 1, 1);
}

// Apply Sobel 2 Direction X Dir
void apply_sobel_2(const unsigned char* source_image, unsigned char* destination_image, int width, int height){
    int sobel_filter[3][3] = {{-1,  0,  1},
                              {-2,  0,  2},
                              {-1,  0,  1}};

    apply_filter(source_image, destination_image, height, width, sobel_filter, 1, 1);
}

// Apply Sobel 3 Direction X Dir
void apply_sobel_3(const unsigned char* source_image, unsigned char* destination_image, int width, int height){
    int sobel_filter[3][3] = {{ 0,  1,  2},
                              {-1,  0,  1},
                              {-2, -1,  0}};

    apply_filter(source_image, destination_image, height, width, sobel_filter, 1, 1);
}

// Apply Sobel 4 Direction X Dir
void apply_sobel_4(const unsigned char* source_image, unsigned char* destination_image, int width, int height){
    int sobel_filter[3][3] = {{ 1,  2,  1},
                              { 0,  0,  0},
                              {-1, -2, -1}};

    apply_filter(source_image, destination_image, height, width, sobel_filter, 1, 1);
}

// Apply Sobel 5 Direction X Dir
void apply_sobel_5(const unsigned char* source_image, unsigned char* destination_image, int width, int height){
    int sobel_filter[3][3] = {{ 2,  1,  0},
                              { 1,  0, -1},
                              { 0, -1, -2}};

    apply_filter(source_image, destination_image, height, width, sobel_filter, 1, 1);
}

// Apply Sobel 6 Direction X Dir
void apply_sobel_6(const unsigned char* source_image, unsigned char* destination_image, int width, int height){
    int sobel_filter[3][3] = {{ 1,  0, -1},
                              { 2,  0, -2},
                              { 1,  0, -1}};

    apply_filter(source_image, destination_image, height, width, sobel_filter, 1, 1);
}

// Apply Sobel 7 Direction X Dir
void apply_sobel_7(const unsigned char* source_image, unsigned char* destination_image, int width, int height){
    int sobel_filter[3][3] = {{ 0, -1, -2},
                              { 1,  0, -1},
                              { 2,  1,  0}};

    apply_filter(source_image, destination_image, height, width, sobel_filter, 1, 1);
}

// Apply Sobel 0 Direction X&Y Dir
void apply_advance_sobel_0(const unsigned char* source_image, int width, int height, unsigned char* destination_image){
    int Gx[3][3] = {{-1,-2,-1},
                    { 0, 0, 0},
                    { 1, 2, 1}};

    int Gy[3][3] = {{ 1,  0, -1},
                    { 2,  0, -2},
                    { 1,  0, -1}};

    for(int row = 1; row < height - 1; ++row){
        for(int col = 1; col < width - 1; ++col){
            int gx = sobel_calculations(Gx, source_image, row, width, col, 1, 1);
            int gy = sobel_calculations(Gy, source_image, row, width, col, 1, 1);

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
            int gx = sobel_calculations(Gx, source_image, row, width, col, 1, 1);
            int gy = sobel_calculations(Gy, source_image, row, width, col, 1, 1);

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
            int gx = sobel_calculations(Gx, source_image, row, width, col, 1, 1);
            int gy = sobel_calculations(Gy, source_image, row, width, col, 1, 1);

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
            int gx = sobel_calculations(Gx, source_image, row, width, col, 1, 1);
            int gy = sobel_calculations(Gy, source_image, row, width, col, 1, 1);

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
            int gx = sobel_calculations(Gx, source_image, row, width, col, 1, 1);
            int gy = sobel_calculations(Gy, source_image, row, width, col, 1, 1);

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
            int gx = sobel_calculations(Gx, source_image, row, width, col, 1, 1);
            int gy = sobel_calculations(Gy, source_image, row, width, col, 1, 1);

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
            int gx = sobel_calculations(Gx, source_image, row, width, col, 1, 1);
            int gy = sobel_calculations(Gy, source_image, row, width, col, 1, 1);

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
            int gx = sobel_calculations(Gx, source_image, row, width, col, 1, 1);
            int gy = sobel_calculations(Gy, source_image, row, width, col, 1, 1);

            destination_image[row * width + col] = sqrt(gx * gx + gy * gy);
        }
    }
}

int main(int argc, char** argv){
    if(argc != 2){
        fprintf(stderr, "Only One Argument Allowed : code.exe image.png\n");
        return 1;
    }

    int source_width, source_height, source_channels;
    unsigned char* source_image = stbi_load(argv[1], &source_width, &source_height, &source_channels, 0);
    if(source_image == NULL){
        fprintf(stderr, "Error Loading Image : %s\n", argv[1]);
        return 1;
    }
    if(source_channels != 3){
        fprintf(stderr, "Channel Mismatch, Only Allowed : 3\n");
        stbi_image_free(source_image);
        return 1;
    }
    printf("Loaded image with width %d, height %d, channels %d\n", source_width, source_height, source_channels);

    unsigned char* bit8_image_space = malloc((size_t)source_width * source_height * 1);
    unsigned char* bit24_image_space = malloc((size_t)source_width * source_height * 3);

    if(bit8_image_space == NULL || bit24_image_space == NULL){
        fprintf(stderr, "Memory Allocation Failed\n");
        stbi_image_free(source_image);
        return 1;
    }

    unsigned char* black_image = malloc((size_t)source_width * source_height * 1);
    unsigned char* black_sobel_0_image = malloc((size_t)source_width * source_height * 1);
    unsigned char* black_sobel_1_image = malloc((size_t)source_width * source_height * 1);
    unsigned char* black_sobel_2_image = malloc((size_t)source_width * source_height * 1);
    unsigned char* black_sobel_3_image = malloc((size_t)source_width * source_height * 1);
    unsigned char* black_sobel_4_image = malloc((size_t)source_width * source_height * 1);
    unsigned char* black_sobel_5_image = malloc((size_t)source_width * source_height * 1);
    unsigned char* black_sobel_6_image = malloc((size_t)source_width * source_height * 1);
    unsigned char* black_sobel_7_image = malloc((size_t)source_width * source_height * 1);

    unsigned char* white_image = malloc((size_t)source_width * source_height * 1);
    unsigned char* white_sobel_0_image = malloc((size_t)source_width * source_height * 1);
    unsigned char* white_sobel_1_image = malloc((size_t)source_width * source_height * 1);
    unsigned char* white_sobel_2_image = malloc((size_t)source_width * source_height * 1);
    unsigned char* white_sobel_3_image = malloc((size_t)source_width * source_height * 1);
    unsigned char* white_sobel_4_image = malloc((size_t)source_width * source_height * 1);
    unsigned char* white_sobel_5_image = malloc((size_t)source_width * source_height * 1);
    unsigned char* white_sobel_6_image = malloc((size_t)source_width * source_height * 1);
    unsigned char* white_sobel_7_image = malloc((size_t)source_width * source_height * 1);

    unsigned char* advance_black_sobel_0_image = malloc((size_t)source_width * source_height * 1);
    unsigned char* advance_black_sobel_1_image = malloc((size_t)source_width * source_height * 1);
    unsigned char* advance_black_sobel_2_image = malloc((size_t)source_width * source_height * 1);
    unsigned char* advance_black_sobel_3_image = malloc((size_t)source_width * source_height * 1);
    unsigned char* advance_black_sobel_4_image = malloc((size_t)source_width * source_height * 1);
    unsigned char* advance_black_sobel_5_image = malloc((size_t)source_width * source_height * 1);
    unsigned char* advance_black_sobel_6_image = malloc((size_t)source_width * source_height * 1);
    unsigned char* advance_black_sobel_7_image = malloc((size_t)source_width * source_height * 1);

    unsigned char* advance_white_sobel_0_image = malloc((size_t)source_width * source_height * 1);
    unsigned char* advance_white_sobel_1_image = malloc((size_t)source_width * source_height * 1);
    unsigned char* advance_white_sobel_2_image = malloc((size_t)source_width * source_height * 1);
    unsigned char* advance_white_sobel_3_image = malloc((size_t)source_width * source_height * 1);
    unsigned char* advance_white_sobel_4_image = malloc((size_t)source_width * source_height * 1);
    unsigned char* advance_white_sobel_5_image = malloc((size_t)source_width * source_height * 1);
    unsigned char* advance_white_sobel_6_image = malloc((size_t)source_width * source_height * 1);
    unsigned char* advance_white_sobel_7_image = malloc((size_t)source_width * source_height * 1);

    if(black_image == NULL || black_sobel_0_image == NULL || black_sobel_1_image == NULL || black_sobel_2_image == NULL || black_sobel_3_image == NULL || black_sobel_4_image == NULL || black_sobel_5_image == NULL || black_sobel_6_image == NULL || black_sobel_7_image == NULL || white_image == NULL || white_sobel_0_image == NULL || white_sobel_1_image == NULL || white_sobel_2_image == NULL || white_sobel_3_image == NULL || white_sobel_4_image == NULL || white_sobel_5_image == NULL || white_sobel_6_image == NULL || white_sobel_7_image == NULL || advance_black_sobel_0_image == NULL || advance_black_sobel_1_image == NULL || advance_black_sobel_2_image == NULL || advance_black_sobel_3_image == NULL || advance_black_sobel_4_image == NULL || advance_black_sobel_5_image == NULL || advance_black_sobel_6_image == NULL || advance_black_sobel_7_image == NULL || advance_white_sobel_0_image == NULL || advance_white_sobel_1_image == NULL || advance_white_sobel_2_image == NULL || advance_white_sobel_3_image == NULL || advance_white_sobel_4_image == NULL || advance_white_sobel_5_image == NULL || advance_white_sobel_6_image == NULL || advance_white_sobel_7_image == NULL){
        fprintf(stderr, "Error Memory Allocation\n");
        stbi_image_free(free);
        return 1;
    }

    convert_black_white(source_image, source_width, source_height, black_image);
    stbi_write_png("0 black.jpeg", source_width, source_height, 1, black_image, source_width * 1);
    apply_sobel_0(black_image, black_sobel_0_image, source_width, source_height, 0, 1, 1);
    stbi_write_png("1 black_sobel0.jpeg", source_width, source_height, 1, black_sobel_0_image, source_width * 1);
    apply_sobel_1(black_image, black_sobel_1_image, source_width, source_height);
    stbi_write_png("2 black_sobel1.jpeg", source_width, source_height, 1, black_sobel_1_image, source_width * 1);
    apply_sobel_2(black_image, black_sobel_2_image, source_width, source_height);
    stbi_write_png("3 black_sobel2.jpeg", source_width, source_height, 1, black_sobel_2_image, source_width * 1);
    apply_sobel_3(black_image, black_sobel_3_image, source_width, source_height);
    stbi_write_png("4 black_sobel3.jpeg", source_width, source_height, 1, black_sobel_3_image, source_width * 1);
    apply_sobel_4(black_image, black_sobel_4_image, source_width, source_height);
    stbi_write_png("5 black_sobel4.jpeg", source_width, source_height, 1, black_sobel_4_image, source_width * 1);
    apply_sobel_5(black_image, black_sobel_5_image, source_width, source_height);
    stbi_write_png("6 black_sobel5.jpeg", source_width, source_height, 1, black_sobel_5_image, source_width * 1);
    apply_sobel_6(black_image, black_sobel_6_image, source_width, source_height);
    stbi_write_png("7 black_sobel6.jpeg", source_width, source_height, 1, black_sobel_6_image, source_width * 1);
    apply_sobel_7(black_image, black_sobel_7_image, source_width, source_height);
    stbi_write_png("8 black_sobel7.jpeg", source_width, source_height, 1, black_sobel_7_image, source_width * 1);

    inverse_black(black_image, source_width, source_height, white_image);
    stbi_write_png("9 white.jpeg", source_width, source_height, 1, white_image, source_width * 1);
    apply_sobel_0(white_image, white_sobel_0_image, source_width, source_height, 0, 1, 1);
    stbi_write_png("10 white_sobel0.jpeg", source_width, source_height, 1, white_sobel_0_image, source_width * 1);
    apply_sobel_1(white_image, white_sobel_1_image, source_width, source_height);
    stbi_write_png("11 white_sobel1.jpeg", source_width, source_height, 1, white_sobel_1_image, source_width * 1);
    apply_sobel_2(white_image, white_sobel_2_image, source_width, source_height);
    stbi_write_png("12 white_sobel2.jpeg", source_width, source_height, 1, white_sobel_2_image, source_width * 1);
    apply_sobel_3(white_image, white_sobel_3_image, source_width, source_height);
    stbi_write_png("13 white_sobel3.jpeg", source_width, source_height, 1, white_sobel_3_image, source_width * 1);
    apply_sobel_4(white_image, white_sobel_4_image, source_width, source_height);
    stbi_write_png("14 white_sobel4.jpeg", source_width, source_height, 1, white_sobel_4_image, source_width * 1);
    apply_sobel_5(white_image, white_sobel_5_image, source_width, source_height);
    stbi_write_png("15 white_sobel5.jpeg", source_width, source_height, 1, white_sobel_5_image, source_width * 1);
    apply_sobel_6(white_image, white_sobel_6_image, source_width, source_height);
    stbi_write_png("16 white_sobel6.jpeg", source_width, source_height, 1, white_sobel_6_image, source_width * 1);
    apply_sobel_7(white_image, white_sobel_7_image, source_width, source_height);
    stbi_write_png("17 white_sobel7.jpeg", source_width, source_height, 1, white_sobel_7_image, source_width * 1);

    apply_advance_sobel_0(black_image, source_width, source_height, advance_black_sobel_0_image);
    stbi_write_png("18 advance_black_sobel0.jpeg", source_width, source_height, 1, advance_black_sobel_0_image, source_width * 1);
    apply_advance_sobel_1(black_image, source_width, source_height, advance_black_sobel_1_image);
    stbi_write_png("19 advance_black_sobel1.jpeg", source_width, source_height, 1, advance_black_sobel_1_image, source_width * 1);
    apply_advance_sobel_2(black_image, source_width, source_height, advance_black_sobel_2_image);
    stbi_write_png("20 advance_black_sobel2.jpeg", source_width, source_height, 1, advance_black_sobel_2_image, source_width * 1);
    apply_advance_sobel_3(black_image, source_width, source_height, advance_black_sobel_3_image);
    stbi_write_png("21 advance_black_sobel3.jpeg", source_width, source_height, 1, advance_black_sobel_3_image, source_width * 1);
    apply_advance_sobel_4(black_image, source_width, source_height, advance_black_sobel_4_image);
    stbi_write_png("22 advance_black_sobel4.jpeg", source_width, source_height, 1, advance_black_sobel_4_image, source_width * 1);
    apply_advance_sobel_5(black_image, source_width, source_height, advance_black_sobel_5_image);
    stbi_write_png("23 advance_black_sobel5.jpeg", source_width, source_height, 1, advance_black_sobel_5_image, source_width * 1);
    apply_advance_sobel_6(black_image, source_width, source_height, advance_black_sobel_6_image);
    stbi_write_png("24 advance_black_sobel6.jpeg", source_width, source_height, 1, advance_black_sobel_6_image, source_width * 1);
    apply_advance_sobel_7(black_image, source_width, source_height, advance_black_sobel_7_image);
    stbi_write_png("25 advance_black_sobel7.jpeg", source_width, source_height, 1, advance_black_sobel_7_image, source_width * 1);

    apply_advance_sobel_0(white_image, source_width, source_height, advance_white_sobel_0_image);
    stbi_write_png("26 advance_white_sobel0.jpeg", source_width, source_height, 1, advance_white_sobel_0_image, source_width * 1);
    apply_advance_sobel_1(white_image, source_width, source_height, advance_white_sobel_1_image);
    stbi_write_png("27 advance_white_sobel1.jpeg", source_width, source_height, 1, advance_white_sobel_1_image, source_width * 1);
    apply_advance_sobel_2(white_image, source_width, source_height, advance_white_sobel_2_image);
    stbi_write_png("28 advance_white_sobel2.jpeg", source_width, source_height, 1, advance_white_sobel_2_image, source_width * 1);
    apply_advance_sobel_3(white_image, source_width, source_height, advance_white_sobel_3_image);
    stbi_write_png("29 advance_white_sobel3.jpeg", source_width, source_height, 1, advance_white_sobel_3_image, source_width * 1);
    apply_advance_sobel_4(white_image, source_width, source_height, advance_white_sobel_4_image);
    stbi_write_png("30 advance_white_sobel4.jpeg", source_width, source_height, 1, advance_white_sobel_4_image, source_width * 1);
    apply_advance_sobel_5(white_image, source_width, source_height, advance_white_sobel_5_image);
    stbi_write_png("31 advance_white_sobel5.jpeg", source_width, source_height, 1, advance_white_sobel_5_image, source_width * 1);
    apply_advance_sobel_6(white_image, source_width, source_height, advance_white_sobel_6_image);
    stbi_write_png("32 advance_white_sobel6.jpeg", source_width, source_height, 1, advance_white_sobel_6_image, source_width * 1);
    apply_advance_sobel_7(white_image, source_width, source_height, advance_white_sobel_7_image);
    stbi_write_png("33 advance_white_sobel7.jpeg", source_width, source_height, 1, advance_white_sobel_7_image, source_width * 1);



    stbi_image_free(source_image);
    free(bit8_image_space);
    free(bit24_image_space);
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