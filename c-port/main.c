#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

int hex_to_rgb(const char* hex, int* r, int* g, int* b) {
    return sscanf(hex, "%02x%02x%02x", r, g, b);
}

void generate_hex(char* hex) {
    static int seeded = 0;
    if (!seeded) {
        seeded = 1;
        srand(time(NULL));
    }
    int r = rand() % 255 + 1, g = rand() % 255 + 1, b = rand() % 255 + 1;
    sprintf(hex, "%02X%02X%02X", r, g, b);
}

char* get_pantone(int r, int g, int b) {
    if (r > 180 && g > 180 && b > 180) return "White";
    if (r < 60 && g < 60 && b < 60) return "Black";
    if (r > g && r > b) return "Magenta";
    if (g > r && g > b) return "Lime";
    if (b > r && b > g) return "Cyan";
    if (r + g + b < 150) return "Dark";
    if (r + g + b > 450) return "Light";
    return "Gray";
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
    
    printf("Color One: %s - %s\n", hex1, hex1);
    printf("Color Two: %s - %s\n", hex2, hex2);
    printf("Description: %s and %s\n", hex1, hex2);
    printf("Full text: %s - %s\n%s - %s\n(Contrast ratio: %.1f:1 | %.0f)\n",
           hex1, hex1, hex2, hex2, get_contrast_ratio(hex1, hex2), get_contrast_ratio(hex1, hex2) * 5);
    
    return 0;
}
