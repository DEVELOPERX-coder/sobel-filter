# Sobel Filter - Advanced Edge Detection

A comprehensive C-based image processing tool that implements multiple Sobel edge detection algorithms with directional variants and advanced gradient visualization. This project provides both simple and advanced edge detection capabilities for various image processing applications.

[![GitHub stars](https://img.shields.io/github/stars/DEVELOPERX-coder/sobel-filter?style=social)](https://github.com/DEVELOPERX-coder/sobel-filter)
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](LICENSE)
[![Patreon](https://img.shields.io/badge/Support%20on-Patreon-FF424D?logo=patreon&logoColor=white)](https://www.patreon.com/1911945/join)

## Table of Contents

- [Features](#features)
- [Installation](#installation)
- [Usage](#usage)
- [Sobel Operators](#sobel-operators)
- [Examples](#examples)
- [Project Structure](#project-structure)
- [Technical Details](#technical-details)
- [Contributing](#contributing)
- [Support](#support)
- [License](#license)

## Features

### Core Capabilities

- **Multiple Sobel Variants**: 8 different Sobel operator configurations (Sobel 0-7)
- **Directional Analysis**: Separate X and Y directional edge detection
- **Advanced Mode**: Combined Gx and Gy calculations for enhanced edge detection
- **Image Format Support**: RGB image loading with PNG and JPEG output options
- **Grayscale Conversion**: Automatic RGB to 8-bit grayscale conversion using standard luminosity formula
- **Edge Gradient Visualization**: HSV-based colorized gradient representation with magnitude and angle encoding
- **Image Inversion**: Black and white image color inversion capability
- **Trimming & Normalization**: Optional value clamping to [0, 255] range
- **Interactive CLI**: User-friendly command-line interface with real-time processing

### Advanced Features

- **8 Directional Sobel Operators**: Detect edges at different orientations (0°, 45°, 90°, 135°, 180°, 225°, 270°, 315°)
- **Gradient Magnitude & Angle**: Calculate both magnitude and angle of edge gradients
- **HSV to RGB Conversion**: Professional color mapping for edge visualization
- **Timestamp-based Output**: Automatic filename generation with processing timestamps
- **Memory Efficient**: Optimized memory allocation and processing pipeline

## Installation

### Prerequisites

- GCC (or any C compiler supporting C99 standard)
- `stb_image.h` and `stb_image_write.h` (single-header libraries included)
- Standard C libraries: `stdio.h`, `stdlib.h`, `math.h`, `time.h`
- Linux/Unix/Windows environment

### Build Instructions

```bash
# Clone the repository
git clone https://github.com/DEVELOPERX-coder/sobel-filter.git
cd sobel-filter

# Compile the program
gcc -o sobel_filter sobel_filter.c -lm

# Run the program
./sobel_filter
```

**Note**: The `-lm` flag links the math library required for mathematical functions (`sqrt`, `pow`, `atan2`, etc.).

## Usage

### Running the Program

```bash
./sobel_filter
```

The program presents an interactive menu:

```
Write Number to Choose :
0. Exit
1. Change Image
2. Apply Black and White
3. Apply Inverse to Black and White
4. Apply Simple Sobel
5. Apply Advance Sobel
6. Change Image Output Format
7. Apply Edge Gradient
```

### Step-by-Step Workflow

#### 1. Load an Image

```
Choose: 1
Enter filename: input.png
```

- Only 3-channel RGB images are supported
- Supported formats: PNG, JPG, BMP, TGA, etc. (via stb_image)

#### 2. Apply Black and White Conversion

```
Choose: 2
```

Converts RGB (24-bit) to grayscale (8-bit) using the standard luminosity formula:

```
Gray = 0.2126 × R + 0.7152 × G + 0.0722 × B
```

#### 3. Apply Simple Sobel Filter

```
Choose: 4
Enter: Sobel_Num Sobel_Dir Sobel_Trim Sobel_Square
Example: 0 0 0 0
```

**Parameters**:

- `Sobel_Num`: Operator variant (0-7)
- `Sobel_Dir`: Direction (0 = X-direction, 1 = Y-direction)
- `Sobel_Trim`: Value clipping (0 = disabled, 1 = enabled)
- `Sobel_Square`: Square normalization (0 = disabled, 1 = enabled)

#### 4. Apply Advanced Sobel Filter

```
Choose: 5
Enter: Sobel_Num Sobel_Trim
Example: 0 0
```

Combines X and Y gradients using magnitude calculation:

```
Magnitude = √(Gx² + Gy²)
```

#### 5. Edge Gradient Visualization

```
Choose: 7
```

Creates a colorized gradient representation:

- **Hue**: Edge direction angle (0-360°)
- **Saturation**: Fixed at 0.8 for vibrant colors
- **Value**: Normalized magnitude with gamma correction (0.5)

#### 6. Change Output Format

```
Choose: 6
Select: 0 (PNG) or 1 (JPEG)
```

## Sobel Operators

### Operator Variants

The program implements 8 different Sobel operator configurations, each optimized for detecting edges at specific orientations:

| Variant | Primary Direction   | Use Case                           |
| ------- | ------------------- | ---------------------------------- |
| Sobel 0 | Horizontal/Vertical | General edge detection             |
| Sobel 1 | Diagonal (45°)      | Corner and diagonal edge detection |
| Sobel 2 | Vertical emphasis   | Horizontal edge emphasis           |
| Sobel 3 | Diagonal (135°)     | Anti-diagonal edge detection       |
| Sobel 4 | Inverted horizontal | Alternative horizontal detection   |
| Sobel 5 | Inverted diagonal   | Alternative diagonal detection     |
| Sobel 6 | Enhanced vertical   | Vertical emphasis variant          |
| Sobel 7 | Enhanced diagonal   | Alternative corner detection       |

### Example Operator: Sobel 0

```
Gx (X-direction):        Gy (Y-direction):
-1  -2  -1             1   0  -1
 0   0   0             2   0  -2
 1   2   1             1   0  -1
```

## Examples

### Generated Output Samples

Generated example images are stored in the `/examples` directory:

```
examples/
├── input_images/
│   ├── sample_landscape.png
│   ├── sample_portrait.jpg
│   └── sample_shapes.png
├── output_grayscale/
│   ├── 2024-01-15_10-30-45_Black&White.png
│   └── ...
├── output_sobel_simple/
│   ├── 2024-01-15_10-31-20_sobel.png
│   └── ...
├── output_sobel_advanced/
│   ├── 2024-01-15_10-32-15_sobel.png
│   └── ...
└── output_edge_gradient/
    ├── 2024-01-15_10-33-00_sobel_edge_gradient.png
    └── ...
```

**To use example images**:

1. Place your test images in `/examples/input_images/`
2. Run the program and reference them by filename when prompted
3. View the processed outputs in the respective output subdirectories

### Sample Results

When you run edge detection on a landscape photo:

- **Simple Sobel**: Clear edge outlines with high contrast
- **Advanced Sobel**: Smoother, more comprehensive edge representation
- **Edge Gradient**: Rainbow-colored visualization showing edge direction and strength

## Project Structure

```
sobel-filter/
├── sobel_filter.c              # Main source code
├── stb_image.h                 # Image loading library
├── stb_image_write.h           # Image writing library
├── README.md                   # Project documentation
├── LICENSE                     # MIT License
└── examples/                   # Example images and outputs
    ├── input_images/
    ├── output_grayscale/
    ├── output_sobel_simple/
    ├── output_sobel_advanced/
    └── output_edge_gradient/
```

## Technical Details

### Grayscale Conversion Formula

```
Gray = 0.2126 × R + 0.7152 × G + 0.0722 × B
```

This ITU-R BT.709 standard formula accounts for human eye sensitivity to different color channels.

### Sobel Filter Theory

The Sobel operator is a discrete differentiation operator that computes an approximation of the gradient of the image intensity function.

**Magnitude**: `M = √(Gx² + Gy²)`

**Angle**: `θ = atan2(Gy, Gx) × 180/π`

### Edge Gradient Color Mapping

The gradient visualization uses HSV color space for intuitive edge representation:

- **Hue** encodes the edge direction (0° = red, 120° = green, 240° = blue)
- **Value** represents edge magnitude with gamma correction for better perception
- **Saturation** set to 0.8 for vibrant, distinguishable colors

### Memory Management

- Input image: `width × height × 3` bytes (RGB)
- Grayscale buffer: `width × height × 1` bytes
- Processing buffer: `width × height × 1` or `3` bytes (depending on output type)
- Automatic cleanup via `stbi_image_free()` and `free()`

## Contributing

Contributions are welcome! Please follow these guidelines:

1. **Fork the repository** on GitHub
2. **Create a feature branch**: `git checkout -b feature/your-feature`
3. **Commit your changes**: `git commit -am 'Add new feature'`
4. **Push to the branch**: `git push origin feature/your-feature`
5. **Submit a Pull Request** with a detailed description

## Support

### Getting Help

- **Issues**: Report bugs or request features via [GitHub Issues](https://github.com/DEVELOPERX-coder/sobel-filter/issues)
- **Documentation**: Refer to inline code comments for function details
- **Examples**: Check the `/examples` directory for sample outputs

### Show Your Support

If you find this project helpful:

- ⭐ **Star the repository**: [GitHub Stars](https://github.com/DEVELOPERX-coder/sobel-filter)
- 💝 **Support development**: [Become a Patron](https://www.patreon.com/1911945/join)

Your support helps fund ongoing development and maintenance!

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

The project uses the following open-source libraries:

- **stb_image.h**: Public Domain by Sean Barrett
- **stb_image_write.h**: Public Domain by Sean Barrett

## Acknowledgments

This project implements classic Sobel edge detection operators with modern optimizations. It serves as both a practical tool for image processing and an educational resource for understanding edge detection algorithms.

---

**Made with ❤️ by DEVELOPERX**

[GitHub](https://github.com/DEVELOPERX-coder/sobel-filter) | [Support on Patreon](https://www.patreon.com/1911945/join)
