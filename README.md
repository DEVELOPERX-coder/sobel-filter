**The simplest way to read and write images in C is by using libraries like `stb_image` and `stb_image_write`, or by working directly with simple formats like PPM/PGM which are text-based and easy to parse.**

---

## 📖 Approaches to Reading and Writing Images in C

### 1. Using the `stb_image` and `stb_image_write` Libraries

These are lightweight, single-header libraries widely used in C/C++ projects.

- **Setup:**

  - Download from [stb GitHub](https://github.com/nothings/stb).
  - Include headers in your project:
    ```c
    #define STB_IMAGE_IMPLEMENTATION
    #include "stb_image.h"
    #define STB_IMAGE_WRITE_IMPLEMENTATION
    #include "stb_image_write.h"
    ```

- **Reading an Image:**

  ```c
  int width, height, channels;
  unsigned char *img = stbi_load("input.jpg", &width, &height, &channels, 0);
  if(img == NULL) {
      printf("Error loading image\n");
      return 1;
  }
  printf("Loaded image with width %d, height %d, channels %d\n", width, height, channels);
  ```

- **Writing an Image:**
  ```c
  stbi_write_png("output.png", width, height, channels, img, width * channels);
  stbi_image_free(img);
  ```

👉 Supports formats like **JPEG, PNG, BMP, TGA** for reading, and **PNG, BMP, TGA, JPG** for writing.

---

### 2. Working with PPM/PGM Formats (Portable Pixmap/Graymap)

These formats are plain text or binary, making them easy to handle without external libraries.

- **PPM Example (RGB Image):**
  - File starts with a header:
    ```
    P3
    width height
    max_color_value
    r g b r g b ...
    ```
  - **Reading:**
    ```c
    FILE *fp = fopen("image.ppm", "r");
    int width, height, maxval;
    fscanf(fp, "P3 %d %d %d", &width, &height, &maxval);
    int r, g, b;
    for(int i=0; i<width*height; i++) {
        fscanf(fp, "%d %d %d", &r, &g, &b);
        // process pixel
    }
    fclose(fp);
    ```
  - **Writing:**
    ```c
    FILE *fp = fopen("output.ppm", "w");
    fprintf(fp, "P3\n%d %d\n255\n", width, height);
    for(int i=0; i<width*height; i++) {
        fprintf(fp, "%d %d %d ", r, g, b);
    }
    fclose(fp);
    ```

👉 Best for learning image basics since the format is human-readable.

---

gcc .\sobel_filter.c -o sobel_filter
.\sobel_filter.exe source.jpg  
Loaded image with width 1920, height 1280, channels 3
