#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

int hex_to_rgb(const char* hex, int* r, int* g, int* b) {
    return sscanf(hex, "%02x%02x%02x", r, g, b);
}

#define MAX_COLORS 100

static struct {
    const char* name;
    int r, g, b;
} html_colors[MAX_COLORS] = {
    {"White", 255, 255, 255}, {"Black", 0, 0, 0}, {"Red", 255, 0, 0}, {"Green", 0, 128, 0},
    {"Blue", 0, 0, 255}, {"Yellow", 255, 255, 0}, {"Purple", 128, 0, 128}, {"Orange", 255, 165, 0},
    {"Pink", 255, 192, 203}, {"Brown", 165, 42, 42}, {"Lime", 0, 255, 0}, {"Teal", 0, 128, 128},
    {"Magenta", 255, 0, 255}, {"Cyan", 0, 255, 255}, {"Gold", 255, 215, 0}, {"Silver", 192, 192, 192},
    {"Crimson", 220, 20, 60}, {"Cornsilk", 255, 248, 220}, {"AliceBlue", 240, 248, 255},
    {"Lavender", 230, 230, 250}, {"Wheat", 245, 222, 179}, {"BurlyWood", 222, 184, 135},
    {"Tan", 210, 180, 140}, {"Chocolate", 210, 180, 140}, {"Sienna", 160, 82, 45},
    {"Maroon", 128, 0, 0}, {"Aqua", 0, 255, 255}, {"LightGray", 211, 211, 211},
    {"DarkGray", 169, 169, 169}, {"Gray", 128, 128, 128}, {"DimGray", 105, 105, 105},
    {"LightYellow", 255, 255, 224}, {"NavajoWhite", 255, 222, 173}, {"WhiteSmoke", 240, 240, 240},
    {"Moccasin", 255, 228, 181}, {"PapayaWhip", 255, 239, 213}, {"PeachPuff", 255, 218, 185},
    {"Beige", 245, 245, 220}, {"Honeydew", 240, 255, 240}, {"OldLace", 253, 245, 230},
    {"FloralWhite", 255, 250, 240}, {"Seashell", 255, 245, 245}, {"Linen", 250, 240, 230},
    {"GhostWhite", 248, 248, 255}, {"MistyRose", 252, 241, 244}, {"LightPink", 255, 182, 193},
    {"PaleVioletRed", 219, 112, 147}, {"Coral", 255, 127, 80}, {"Tomato", 255, 99, 71},
    {"OrangeRed", 255, 69, 0}, {"DarkOrange", 255, 140, 0}, {"IndianRed", 205, 92, 92},
    {"Salmon", 250, 128, 114}, {"SandyBrown", 244, 164, 96}, {"DarkSalmon", 233, 150, 122},
    {"LightGoldenrodYellow", 250, 250, 210}, {"Khaki", 240, 230, 140},
    {"Bisque", 255, 228, 196}, {"Plum", 221, 160, 221}, {"MediumPurple", 147, 112, 219},
    {"MediumSlateBlue", 123, 104, 238}, {"DarkMagenta", 139, 0, 139}, {"BlueViolet", 138, 43, 226},
    {"YellowGreen", 154, 205, 50}, {"LawnGreen", 124, 252, 0}, {"MediumAquamarine", 102, 205, 170},
    {"MediumSpringGreen", 0, 250, 154}, {"DarkSeaGreen", 143, 188, 143},
    {"DarkOrchid", 153, 50, 204}, {"DarkGoldenrod", 184, 134, 11}, {"DarkGreen", 0, 100, 0},
    {"DarkCyan", 0, 139, 139}, {"LightCoral", 240, 128, 128}, {"LightSlateGray", 119, 136, 153},
    {"LightSkyBlue", 135, 206, 250}, {"LightSteelBlue", 176, 196, 222}, {"LightBlue", 173, 216, 230},
    {"PowderBlue", 176, 224, 230}, {"LightGreen", 144, 238, 144}, {"LightSeaGreen", 32, 178, 170},
};

void generate_hex(char* hex) {
    int r = rand() % 255 + 1, g = rand() % 255 + 1, b = rand() % 255 + 1;
    sprintf(hex, "%02X%02X%02X", r, g, b);
}

char* get_pantone(int r, int g, int b) {
    int tolerance = 26;  // 10% of 255
    
    /* Check HTML color lookup table */
    for (int i = 0; i < MAX_COLORS; i++) {
        int diff = abs(html_colors[i].r - r) + abs(html_colors[i].g - g) + abs(html_colors[i].b - b);
        if (diff <= 3 * tolerance) {
            return html_colors[i].name;
        }
    }
    
    /* Luminance-based fallback */
    double lum = 0.2126 * (r / 255.0) + 0.7152 * (g / 255.0) + 0.0722 * (b / 255.0);
    
    if (lum > 0.85) return "White";
    if (lum < 0.15) return "Black";
    
    /* Color family detection */
    double max_c = fmax(r, fmax(g, b));
    double min_c = fmin(r, fmin(g, b));
    double saturation = (max_c - min_c) / max_c;
    
    if (max_c == r && saturation > 0.5) return "Red";
    if (max_c == g && saturation > 0.5) return "Green";
    if (max_c == b && saturation > 0.5) return "Blue";
    
    /* Generic fallback */
    if (max_c == r) return "Red-family";
    if (max_c == g) return "Green-family";
    return "Blue-family";
}

char* get_ntc(char* hex) {
    int R, G, B, L;
    sscanf(hex, "%02x%02x%02x", &R, &G, &B);
    L = (int)(0.2126*R + 0.7152*G + 0.0722*B);
    if (L > 90) return "C2";
    if (L > 60) return "C1";
    if (L > 40) return "C1";
    if (L > 20) return "B7";
    return "A8";
}

char* get_roygbiv(char* hex) {
    int R, G, B;
    sscanf(hex, "%02x%02x%02x", &R, &G, &B);
    if (R > G + 30 && G > B - 20) {
        return (B > 150) ? "Indigo" : "Red";
    } else if (R < B - 30 && G < R + 20) {
        return "Blue";
    } else if (G > R + 30 && R < G - 20) {
        return (R > 80) ? "Green" : "Green";
    } else if (B > R + 30 && R > B - 20) {
        return "Violet";
    } else if (B > G + 30 && G > B - 20) {
        return "Blue";
    } else if (R > 160 && G > 160 && B > 160) {
        return "Orange";
    } else if (R < 80 && G < 80 && B < 80) {
        return "Black";
    }
    return "Grey";
}

double get_lum_hex(const char* hex) {
    int r, g, b;
    hex_to_rgb(hex, &r, &g, &b);
    double R = r / 255.0, G = g / 255.0, B = b / 255.0;
    double r_lin = R <= 0.03928 ? R / 12.92 : pow((R + 0.055) / 1.055, 2.4);
    double g_lin = G <= 0.03928 ? G / 12.92 : pow((G + 0.055) / 1.055, 2.4);
    double b_lin = B <= 0.03928 ? B / 12.92 : pow((B + 0.055) / 1.055, 2.4);
    return 0.2126 * r_lin + 0.7152 * g_lin + 0.0722 * b_lin;
}

double get_contrast_ratio(const char* c1, const char* c2) {
    double L1 = get_lum_hex(c1), L2 = get_lum_hex(c2);
    double Lmax = fmax(L1, L2), Lmin = fmin(L1, L2);
    return Lmax / Lmin;
}

int main(void) {
    srand(time(NULL));  // Seed RNG once at startup
    char hex1[10], hex2[10];
    int attempts = 0;
    const int max_attempts = 1000;
    
    do {
        generate_hex(hex1);
        generate_hex(hex2);
        attempts++;
    } while (get_contrast_ratio(hex1, hex2) < 4.5 && attempts < max_attempts);
    
    if (attempts >= max_attempts) {
        fprintf(stderr, "Warning: max attempts reached\n");
    }
    
    int r1, g1, b1, r2, g2, b2;
    hex_to_rgb(hex1, &r1, &g1, &b1);
    hex_to_rgb(hex2, &r2, &g2, &b2);
    
    char* name1 = get_pantone(r1, g1, b1);
    char* name2 = get_pantone(r2, g2, b2);
    
    printf("Color One: %s - %s\n", hex1, name1);
    printf("Color Two: %s - %s\n", hex2, name2);
    printf("Description: %s and %s\n", hex1, hex2);
    printf("Full text: %s - %s\n%s - %s\n(Contrast ratio: %.1f:1 | %.0f)\n",
           hex1, name1, hex2, name2, get_contrast_ratio(hex1, hex2), get_contrast_ratio(hex1, hex2) * 5);
    
    return 0;
}
