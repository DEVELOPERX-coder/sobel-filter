#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#include <stdio.h>
#include <time.h>
#include <math.h>

#define PI 3.141592654

// Load Image
int Load_Image(unsigned char** source_image_space, int* width, int* height, int* channel, char* source_image_name){
    *source_image_space = stbi_load(source_image_name, width, height, channel, 0);
    if(*source_image_space == NULL){
        fprintf(stderr, "Error Loading Image : %s\n", source_image_name);
        return 1;
    }
    if(*channel != 3){
        fprintf(stderr, "Channel Mismatch, Only Allowed : 3\n");
        stbi_image_free(*source_image_space);
        return 1;
    }
    printf("Loaded image with width %d, height %d, channels %d\n", *width, *height, *channel);
    return 0;
}

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

// Apply Sobel 0 Direction X or Y Dir ( X = 0, Y = 1 )
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

// Apply Sobel 1 Direction X or Y Dir ( X = 0, Y = 1 )
void apply_sobel_1(const unsigned char* source_image, unsigned char* destination_image, int width, int height, int dir, int trim, int square){
    int sobel_filter_x[3][3] = {{-2, -1,  0},
                                {-1,  0,  1},
                                { 0,  1,  2}};

    int sobel_filter_y[3][3] = {{ 0, -1, -2},
                                { 1,  0, -1},
                                { 2,  1,  0}};

    if(dir == 0) apply_filter(source_image, destination_image, height, width, sobel_filter_x, trim, square);
    else         apply_filter(source_image, destination_image, height, width, sobel_filter_y, trim, square);
}

// Apply Sobel 2 Direction X or Y Dir ( X = 0, Y = 1 )
void apply_sobel_2(const unsigned char* source_image, unsigned char* destination_image, int width, int height, int dir, int trim, int square){
    int sobel_filter_x[3][3] = {{-1,  0,  1},
                                {-2,  0,  2},
                                {-1,  0,  1}};

    int sobel_filter_y[3][3] = {{-1, -2, -1},
                                { 0,  0,  0},
                                { 1,  2,  1}};

    if(dir == 0) apply_filter(source_image, destination_image, height, width, sobel_filter_x, trim, square);
    else         apply_filter(source_image, destination_image, height, width, sobel_filter_y, trim, square);
}

// Apply Sobel 3 Direction X or Y Dir ( X = 0, Y = 1 )
void apply_sobel_3(const unsigned char* source_image, unsigned char* destination_image, int width, int height, int dir, int trim, int square){
    int sobel_filter_x[3][3] = {{ 0,  1,  2},
                                {-1,  0,  1},
                                {-2, -1,  0}};

    int sobel_filter_y[3][3] = {{-2, -1, 0},
                                {-1,  0, 1},
                                { 0,  1, 2}};

    if(dir == 0) apply_filter(source_image, destination_image, height, width, sobel_filter_x, trim, square);
    else         apply_filter(source_image, destination_image, height, width, sobel_filter_y, trim, square);
}

// Apply Sobel 4 Direction X or Y Dir ( X = 0, Y = 1 )
void apply_sobel_4(const unsigned char* source_image, unsigned char* destination_image, int width, int height, int dir, int trim, int square){
    int sobel_filter_x[3][3] = {{ 1,  2,  1},
                                { 0,  0,  0},
                                {-1, -2, -1}};

    int sobel_filter_y[3][3] = {{-1,  0, 1},
                                {-2,  0, 2},
                                {-1,  0, 1}};

    if(dir == 0) apply_filter(source_image, destination_image, height, width, sobel_filter_x, trim, square);
    else         apply_filter(source_image, destination_image, height, width, sobel_filter_y, trim, square);
}

// Apply Sobel 5 Direction X or Y Dir ( X = 0, Y = 1 )
void apply_sobel_5(const unsigned char* source_image, unsigned char* destination_image, int width, int height, int dir, int trim, int square){
    int sobel_filter_x[3][3] = {{ 2,  1,  0},
                                { 1,  0, -1},
                                { 0, -1, -2}};
                    
    int sobel_filter_y[3][3] = {{ 0,  1, 2},
                                {-1,  0, 1},
                                {-2, -1, 0}};

    if(dir == 0) apply_filter(source_image, destination_image, height, width, sobel_filter_x, trim, square);
    else         apply_filter(source_image, destination_image, height, width, sobel_filter_y, trim, square);
}

// Apply Sobel 6 Direction X or Y Dir ( X = 0, Y = 1 )
void apply_sobel_6(const unsigned char* source_image, unsigned char* destination_image, int width, int height, int dir, int trim, int square){
    int sobel_filter_x[3][3] = {{ 1,  0, -1},
                                { 2,  0, -2},
                                { 1,  0, -1}};

    int sobel_filter_y[3][3] = {{ 1,  2, 1},
                                { 0,  0, 0},
                                {-1, -2,-1}};

    if(dir == 0) apply_filter(source_image, destination_image, height, width, sobel_filter_x, trim, square);
    else         apply_filter(source_image, destination_image, height, width, sobel_filter_y, trim, square);
}

// Apply Sobel 7 Direction X or Y Dir ( X = 0, Y = 1 )
void apply_sobel_7(const unsigned char* source_image, unsigned char* destination_image, int width, int height, int dir, int trim, int square){
    int sobel_filter_x[3][3] = {{ 0, -1, -2},
                                { 1,  0, -1},
                                { 2,  1,  0}};

    int sobel_filter_y[3][3] = {{ 2,  1, 0},
                                { 1,  0,-1},
                                { 0, -1,-2}};

    if(dir == 0) apply_filter(source_image, destination_image, height, width, sobel_filter_x, trim, square);
    else         apply_filter(source_image, destination_image, height, width, sobel_filter_y, trim, square);
}

// Apply Sobel 0 Direction X&Y Dir
void apply_advance_sobel_0(const unsigned char* source_image, int width, int height, unsigned char* destination_image, int trim){
    int Gx[3][3] = {{-1,-2,-1},
                    { 0, 0, 0},
                    { 1, 2, 1}};

    int Gy[3][3] = {{ 1,  0, -1},
                    { 2,  0, -2},
                    { 1,  0, -1}};

    for(int row = 1; row < height - 1; ++row){
        for(int col = 1; col < width - 1; ++col){
            int gx = sobel_calculations(Gx, source_image, row, width, col, trim, 0);
            int gy = sobel_calculations(Gy, source_image, row, width, col, trim, 0);

            destination_image[row * width + col] = sqrt(gx * gx + gy * gy);
        }
    }
}

// Apply Sobel 1 Direction X&Y Dir
void apply_advance_sobel_1(const unsigned char* source_image, int width, int height, unsigned char* destination_image, int trim){
    int Gx[3][3] = {{-2,-1, 0},
                    {-1, 0, 1},
                    { 0, 1, 2}};

    int Gy[3][3] = {{ 0, -1, -2},
                    { 1,  0, -1},
                    { 2,  1,  0}};

    for(int row = 1; row < height - 1; ++row){
        for(int col = 1; col < width - 1; ++col){
            int gx = sobel_calculations(Gx, source_image, row, width, col, trim, 0);
            int gy = sobel_calculations(Gy, source_image, row, width, col, trim, 0);

            destination_image[row * width + col] = sqrt(gx * gx + gy * gy);
        }
    }
}

// Apply Sobel 2 Direction X&Y Dir
void apply_advance_sobel_2(const unsigned char* source_image, int width, int height, unsigned char* destination_image, int trim){
    int Gx[3][3] = {{-1, 0, 1},
                    {-2, 0, 2},
                    {-1, 0, 1}};

    int Gy[3][3] = {{-1, -2, -1},
                    { 0,  0,  0},
                    { 1,  2,  1}};

    for(int row = 1; row < height - 1; ++row){
        for(int col = 1; col < width - 1; ++col){
            int gx = sobel_calculations(Gx, source_image, row, width, col, trim, 0);
            int gy = sobel_calculations(Gy, source_image, row, width, col, trim, 0);

            destination_image[row * width + col] = sqrt(gx * gx + gy * gy);
        }
    }
}

// Apply Sobel 3 Direction X&Y Dir
void apply_advance_sobel_3(const unsigned char* source_image, int width, int height, unsigned char* destination_image, int trim){
    int Gx[3][3] = {{ 0, 1, 2},
                    {-1, 0, 1},
                    {-2,-1, 0}};

    int Gy[3][3] = {{-2, -1, 0},
                    {-1,  0, 1},
                    { 0,  1, 2}};

    for(int row = 1; row < height - 1; ++row){
        for(int col = 1; col < width - 1; ++col){
            int gx = sobel_calculations(Gx, source_image, row, width, col, trim, 0);
            int gy = sobel_calculations(Gy, source_image, row, width, col, trim, 0);

            destination_image[row * width + col] = sqrt(gx * gx + gy * gy);
        }
    }
}

// Apply Sobel 4 Direction X&Y Dir
void apply_advance_sobel_4(const unsigned char* source_image, int width, int height, unsigned char* destination_image, int trim){
    int Gx[3][3] = {{ 1, 2, 1},
                    { 0, 0, 0},
                    {-1,-2,-1}};

    int Gy[3][3] = {{-1,  0, 1},
                    {-2,  0, 2},
                    {-1,  0, 1}};

    for(int row = 1; row < height - 1; ++row){
        for(int col = 1; col < width - 1; ++col){
            int gx = sobel_calculations(Gx, source_image, row, width, col, trim, 0);
            int gy = sobel_calculations(Gy, source_image, row, width, col, trim, 0);

            destination_image[row * width + col] = sqrt(gx * gx + gy * gy);
        }
    }
}

// Apply Sobel 5 Direction X&Y Dir
void apply_advance_sobel_5(const unsigned char* source_image, int width, int height, unsigned char* destination_image, int trim){
    int Gx[3][3] = {{ 2, 1, 0},
                    { 1, 0,-1},
                    { 0,-1,-2}};

    int Gy[3][3] = {{ 0,  1, 2},
                    {-1,  0, 1},
                    {-2, -1, 0}};

    for(int row = 1; row < height - 1; ++row){
        for(int col = 1; col < width - 1; ++col){
            int gx = sobel_calculations(Gx, source_image, row, width, col, trim, 0);
            int gy = sobel_calculations(Gy, source_image, row, width, col, trim, 0);

            destination_image[row * width + col] = sqrt(gx * gx + gy * gy);
        }
    }
}

// Apply Sobel 6 Direction X&Y Dir
void apply_advance_sobel_6(const unsigned char* source_image, int width, int height, unsigned char* destination_image, int trim){
    int Gx[3][3] = {{ 1, 0,-1},
                    { 2, 0,-2},
                    { 1, 0,-1}};

    int Gy[3][3] = {{ 1,  2, 1},
                    { 0,  0, 0},
                    {-1, -2,-1}};

    for(int row = 1; row < height - 1; ++row){
        for(int col = 1; col < width - 1; ++col){
            int gx = sobel_calculations(Gx, source_image, row, width, col, trim, 0);
            int gy = sobel_calculations(Gy, source_image, row, width, col, trim, 0);

            destination_image[row * width + col] = sqrt(gx * gx + gy * gy);
        }
    }
}

// Apply Sobel 7 Direction X&Y Dir
void apply_advance_sobel_7(const unsigned char* source_image, int width, int height, unsigned char* destination_image, int trim){
    int Gx[3][3] = {{ 0,-1,-2},
                    { 1, 0,-1},
                    { 2, 1, 0}};

    int Gy[3][3] = {{ 2,  1, 0},
                    { 1,  0,-1},
                    { 0, -1,-2}};

    for(int row = 1; row < height - 1; ++row){
        for(int col = 1; col < width - 1; ++col){
            int gx = sobel_calculations(Gx, source_image, row, width, col, trim, 0);
            int gy = sobel_calculations(Gy, source_image, row, width, col, trim, 0);

            destination_image[row * width + col] = sqrt(gx * gx + gy * gy);
        }
    }
}

// Function to convert HSV to RGB 
void hsv_to_rgb(float h, float s, float v, int *r, int *g, int *b){
    float c = v * s; // Chroma
    float x = c * (1 - fabs(fmod(h / 60.0, 2) - 1));
    float m = v - c;
    float r1, g1, b1;
    
    if (h >= 0 && h < 60) { r1 = c; g1 = x; b1 = 0; }
    else if (h >= 60 && h < 120) { r1 = x; g1 = c; b1 = 0; }
    else if (h >= 120 && h < 180) { r1 = 0; g1 = c; b1 = x; }
    else if (h >= 180 && h < 240) { r1 = 0; g1 = x; b1 = c; }
    else if (h >= 240 && h < 300) { r1 = x; g1 = 0; b1 = c; }
    else { r1 = c; g1 = 0; b1 = x; }
    
    *r = (int)((r1 + m) * 255);
    *g = (int)((g1 + m) * 255);
    *b = (int)((b1 + m) * 255);
}

// Show Sobel Edge Gradient
void apply_Edge_Gradient(const unsigned char* bit8_source_image, int width, int height, unsigned char* bit24_destination_image){
    int Gx[3][3] = {{-1, 0, 1},
                    {-2, 0, 2},
                    {-1, 0, 1}};

    int Gy[3][3] = {{-1, -2, -1},
                    { 0,  0,  0},
                    { 1,  2,  1}};

    for(int row = 1; row < height - 1; ++row){
        for(int col = 1; col < width - 1; ++col){
            int gx = sobel_calculations(Gx, bit8_source_image, row, width, col, 1, 1);
            int gy = sobel_calculations(Gy, bit8_source_image, row, width, col, 1, 1);

            double magnitude = sqrt(gx * gx + gy * gy);
            double angle = atan2(gy, gx);

            angle = angle * 180 / PI;
            if(angle < 0) angle += 360;

            double mag_norm = pow(magnitude / 255.0f, 0.5);

            double gamma = 0.8f;

            int r,g,b;
            hsv_to_rgb(angle, gamma, mag_norm, &r, &g, &b);

            bit24_destination_image[(row * width + col) * 3 + 0] = r;
            bit24_destination_image[(row * width + col) * 3 + 1] = g;
            bit24_destination_image[(row * width + col) * 3 + 2] = b;
        }
    }
}

int main(){

    int source_width, source_height, source_channels;
    unsigned char* source_image;

    unsigned char* bit8_black_image_space = NULL;
    unsigned char* bit8_image_space = NULL;
    unsigned char* bit24_image_space = NULL;

    int running = 1;
    int format = 0;
    while(running){
        printf("Write Number to Choose :\n");
        printf("0. Exit\n");
        printf("1. Change Image\n");
        printf("2. Apply Black and White\n");
        printf("3. Apply Inverse to Black and White\n");
        printf("4. Apply Simple Sobel\n");
        printf("5. Apply Advance Sobel\n");
        printf("6. Change Image Ourput Format\n");
        printf("7. Apply Edge Gradient\n");

        int choice;
        scanf("%d", &choice);

        // Exiting
        if(choice == 0) running = 0;

        // Choosing Image
        else if(choice == 1){
            printf("Image can only be of 3 Channel, Like : RGB\n");
            printf("Write name of image Like : source.png\n");
            char image_name[256];
            scanf("%256s", image_name);

            if(Load_Image(&source_image, &source_width, &source_height, &source_channels, image_name)){
                fprintf(stderr, "Error Loading Image : %s\n Try Again...\n", image_name);
            }

            bit8_black_image_space = malloc((size_t)source_width * source_height * 1);
            bit8_image_space = malloc((size_t)source_width * source_height * 1);
            bit24_image_space = malloc((size_t)source_width * source_height * 3);

            if(bit8_image_space == NULL || bit24_image_space == NULL || bit8_black_image_space == NULL){
                fprintf(stderr, "Memory Allocation Failed\n");
                return 1;
            }
        }

        // Getting Black and White Image
        else if(choice == 2){
            if(source_image == NULL){
                fprintf(stderr, "Image Not Selected, First Select Image\n");
                continue;
            }

            convert_black_white(source_image, source_width, source_height, bit8_black_image_space);

            time_t rawTime;
            time(&rawTime);
            char buffer[80];
            struct tm *timeinfo;

            timeinfo = localtime(&rawTime);
            strftime(buffer, sizeof(buffer), "%Y-%m-%d_%H-%M-%S", timeinfo);


            if(format == 0){
                strcat(buffer, "_Black&White.png");
                stbi_write_png(buffer, source_width, source_height, 1, bit8_black_image_space, source_width * 1);
            }
            else if(format == 1){
                strcat(buffer, "_Black&White.jpg");
                stbi_write_jpg(buffer, source_width, source_height, 1, bit8_black_image_space, source_width * 1);
            }

            printf("Image Processed : %s\n", buffer);
        }

        // Inversing Black and White Image
        else if(choice == 3){
            if(source_image == NULL){
                fprintf(stderr, "Image Not Selected, First Select Image\n");
                continue;
            }

            convert_black_white(source_image, source_width, source_height, bit8_black_image_space);
            inverse_black(bit8_black_image_space, source_width, source_height, bit8_image_space);

            time_t rawTime;
            time(&rawTime);
            char buffer[80];
            struct tm *timeinfo;

            timeinfo = localtime(&rawTime);
            strftime(buffer, sizeof(buffer), "%Y-%m-%d_%H-%M-%S", timeinfo);

            if(format == 0){
                strcat(buffer, "_Inverse_Black&White.png");
                stbi_write_png(buffer, source_width, source_height, 1, bit8_image_space, source_width * 1);
            }
            else if(format == 1){
                strcat(buffer, "_Inverse_Black&White.jpg");
                stbi_write_jpg(buffer, source_width, source_height, 1, bit8_image_space, source_width * 1);
            }

            printf("Image Processed : %s\n", buffer);
        }

        // Apply Sobel
        else if(choice == 4){
            if(source_image == NULL){
                fprintf(stderr, "Image Not Selected, First Select Image\n");
                continue;
            }

            int choice_num, choice_dir, choice_trim, choice_square;

            printf("Write Your Choice : Sobel_Num Sobel_Dir Sobel_Trim Sobel_Square\n");
            printf("Example : 0 0 0 0 : 0 Direction , X Direction, Trim FALSE, Square False\n");
            scanf("%d %d %d %d", &choice_num, &choice_dir, &choice_trim, &choice_square);

            if(choice_num < 0 || choice_num > 7) choice_num = 0;
            if(choice_dir < 0 || choice_dir > 1) choice_dir = 0;
            if(choice_trim < 0 || choice_trim > 1) choice_trim = 0;
            if(choice_square < 0 || choice_square > 1) choice_square = 0;

            convert_black_white(source_image, source_width, source_height, bit8_black_image_space);

            if(choice_num == 0) apply_sobel_0(bit8_black_image_space, bit8_image_space, source_width, source_height, choice_dir, choice_trim, choice_square);
            else if(choice_num == 1) apply_sobel_1(bit8_black_image_space, bit8_image_space, source_width, source_height, choice_dir, choice_trim, choice_square);
            else if(choice_num == 2) apply_sobel_2(bit8_black_image_space, bit8_image_space, source_width, source_height, choice_dir, choice_trim, choice_square);
            else if(choice_num == 3) apply_sobel_3(bit8_black_image_space, bit8_image_space, source_width, source_height, choice_dir, choice_trim, choice_square);
            else if(choice_num == 4) apply_sobel_4(bit8_black_image_space, bit8_image_space, source_width, source_height, choice_dir, choice_trim, choice_square);
            else if(choice_num == 5) apply_sobel_5(bit8_black_image_space, bit8_image_space, source_width, source_height, choice_dir, choice_trim, choice_square);
            else if(choice_num == 6) apply_sobel_6(bit8_black_image_space, bit8_image_space, source_width, source_height, choice_dir, choice_trim, choice_square);
            else if(choice_num == 7) apply_sobel_7(bit8_black_image_space, bit8_image_space, source_width, source_height, choice_dir, choice_trim, choice_square);

            time_t rawTime;
            time(&rawTime);
            char buffer[80];
            struct tm *timeinfo;

            timeinfo = localtime(&rawTime);
            strftime(buffer, sizeof(buffer), "%Y-%m-%d_%H-%M-%S", timeinfo);

            if(format == 0){
                strcat(buffer, "_sobel.png");
                stbi_write_png(buffer, source_width, source_height, 1, bit8_image_space, source_width * 1);
            }
            else if(format == 1){
                strcat(buffer, "_sobel.jpg");
                stbi_write_jpg(buffer, source_width, source_height, 1, bit8_image_space, source_width * 1);
            }

            printf("Image Processed : %s\n", buffer);
        }

        // Apply Advance Sobel
        else if(choice == 5){
            if(source_image == NULL){
                fprintf(stderr, "Image Not Selected, First Select Image\n");
                continue;
            }

            int choice_num, choice_trim;

            printf("Write Your Choice : Sobel_Num Sobel_Trim\n");
            printf("Example : 0 0 : 0 Trim FALSE\n");
            scanf("%d %d %d %d", &choice_num, &choice_trim);

            if(choice_num < 0 || choice_num > 7) choice_num = 0;
            if(choice_trim < 0 || choice_trim > 1) choice_trim = 0;
            
            convert_black_white(source_image, source_width, source_height, bit8_black_image_space);

            if(choice_num == 0) apply_advance_sobel_0(bit8_black_image_space, source_width, source_height, bit8_image_space, choice_trim);
            else if(choice_num == 1) apply_advance_sobel_1(bit8_black_image_space, source_width, source_height, bit8_image_space, choice_trim);
            else if(choice_num == 2) apply_advance_sobel_2(bit8_black_image_space, source_width, source_height, bit8_image_space, choice_trim);
            else if(choice_num == 3) apply_advance_sobel_3(bit8_black_image_space, source_width, source_height, bit8_image_space, choice_trim);
            else if(choice_num == 4) apply_advance_sobel_4(bit8_black_image_space, source_width, source_height, bit8_image_space, choice_trim);
            else if(choice_num == 5) apply_advance_sobel_5(bit8_black_image_space, source_width, source_height, bit8_image_space, choice_trim);
            else if(choice_num == 6) apply_advance_sobel_6(bit8_black_image_space, source_width, source_height, bit8_image_space, choice_trim);
            else if(choice_num == 7) apply_advance_sobel_7(bit8_black_image_space, source_width, source_height, bit8_image_space, choice_trim);

            time_t rawTime;
            time(&rawTime);
            char buffer[80];
            struct tm *timeinfo;

            timeinfo = localtime(&rawTime);
            strftime(buffer, sizeof(buffer), "%Y-%m-%d_%H-%M-%S", timeinfo);

            if(format == 0){
                strcat(buffer, "_sobel.png");
                stbi_write_png(buffer, source_width, source_height, 1, bit8_image_space, source_width * 1);
            }
            else if(format == 1){
                strcat(buffer, "_sobel.jpg");
                stbi_write_jpg(buffer, source_width, source_height, 1, bit8_image_space, source_width * 1);
            }

            printf("Image Processed : %s\n", buffer);
        }

        // Format Selection
        else if(choice == 6){
            printf("Choose Format Type :\n");
            printf("0. PNG\n");
            printf("1. JPEG\n");

            int format_chocie;
            scanf("%d", &format_chocie);

            if(format_chocie == 0){
                printf("Format Choose : .png\n");
                format = 0;
            }

            else if(format_chocie == 1){
                printf("Format Choose : .jpg\n");
                format = 1;
            }

            else{
                fprintf(stderr, "Not Supported Format : %d , DEFAULT : .png\n", format_chocie);
                format = 1;
            }
        }

        // Apply Edge Gradient
        else if(choice == 7){
            if(source_image == NULL){
                fprintf(stderr, "Image Not Selected, First Select Image\n");
                continue;
            }

            convert_black_white(source_image, source_width, source_height, bit8_black_image_space);
            apply_Edge_Gradient(bit8_black_image_space, source_width, source_height, bit24_image_space);

            time_t rawTime;
            time(&rawTime);
            char buffer[80];
            struct tm *timeinfo;

            timeinfo = localtime(&rawTime);
            strftime(buffer, sizeof(buffer), "%Y-%m-%d_%H-%M-%S", timeinfo);

            if(format == 0){
                strcat(buffer, "_sobel_edge_gradient.png");
                stbi_write_png(buffer, source_width, source_height, 3, bit24_image_space, source_width * 3);
            }
            else if(format == 1){
                strcat(buffer, "_sobel_edge_gradient.jpg");
                stbi_write_jpg(buffer, source_width, source_height, 3, bit24_image_space, source_width * 3);
            }

            printf("Image Processed : %s\n", buffer);
        }
    }

    printf("Closing Program ....\n");

    stbi_image_free(source_image);
    free(bit8_image_space);
    free(bit24_image_space);
    free(bit8_black_image_space);
    
    return 0;
}