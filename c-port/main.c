#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

int hex_to_rgb(const char* hex, int* r, int* g, int* b) {
    if (hex == NULL || strlen(hex) != 6) return 0;
    unsigned int ur, ug, ub;
    if (sscanf(hex, "%02x%02x%02x", &ur, &ug, &ub) != 3) return 0;
    *r = (int)ur;
    *g = (int)ug;
    *b = (int)ub;
    return 1;
}

#define HTML_COLORS_LEN (sizeof(html_colors) / sizeof(html_colors[0]))

static struct {
    const char* name;
    int r, g, b;
} html_colors[] = {
    {"AliceBlue", 240, 248, 255},
    {"AntiqueWhite", 250, 235, 215},
    {"Aquamarine", 127, 255, 212},
    {"Azure", 240, 255, 255},
    {"Beige", 245, 245, 220},
    {"Bisque", 255, 228, 196},
    {"Black", 0, 0, 0},
    {"BlanchedAlmond", 255, 235, 205},
    {"Blue", 0, 0, 255},
    {"BlueViolet", 138, 43, 226},
    {"Brown", 165, 42, 42},
    {"BurlyWood", 222, 184, 135},
    {"CadetBlue", 95, 158, 160},
    {"Chartreuse", 127, 255, 0},
    {"Chocolate", 210, 105, 30},
    {"Coral", 255, 127, 80},
    {"CornflowerBlue", 100, 149, 237},
    {"Cornsilk", 255, 248, 220},
    {"Crimson", 220, 20, 60},
    {"Cyan", 0, 255, 255},
    {"DarkBlue", 0, 0, 139},
    {"DarkCyan", 0, 139, 139},
    {"DarkGoldenRod", 184, 134, 11},
    {"DarkGray", 169, 169, 169},
    {"DarkGreen", 0, 100, 0},
    {"DarkKhaki", 189, 183, 107},
    {"DarkMagenta", 139, 0, 139},
    {"DarkOliveGreen", 85, 107, 47},
    {"DarkOrange", 255, 140, 0},
    {"DarkOrchid", 153, 50, 204},
    {"DarkRed", 139, 0, 0},
    {"DarkSalmon", 233, 150, 122},
    {"DarkSeaGreen", 143, 188, 143},
    {"DarkSlateBlue", 72, 61, 139},
    {"DarkSlateGray", 47, 79, 79},
    {"DarkTurquoise", 0, 206, 209},
    {"DarkViolet", 148, 0, 211},
    {"DeepPink", 255, 20, 147},
    {"DeepSkyBlue", 0, 191, 255},
    {"DimGray", 105, 105, 105},
    {"DodgerBlue", 30, 144, 255},
    {"FireBrick", 178, 34, 34},
    {"FloralWhite", 255, 250, 240},
    {"ForestGreen", 34, 139, 34},
    {"Gainsboro", 220, 220, 220},
    {"GhostWhite", 248, 248, 255},
    {"Gold", 255, 215, 0},
    {"GoldenRod", 218, 165, 32},
    {"Gray", 128, 128, 128},
    {"Green", 0, 128, 0},
    {"GreenYellow", 173, 255, 47},
    {"HoneyDew", 240, 255, 240},
    {"HotPink", 255, 105, 180},
    {"IndianRed", 205, 92, 92},
    {"Indigo", 75, 0, 130},
    {"Ivory", 255, 255, 240},
    {"Khaki", 240, 230, 140},
    {"Lavender", 230, 230, 250},
    {"LavenderBlush", 255, 240, 245},
    {"LawnGreen", 124, 252, 0},
    {"LemonChiffon", 255, 250, 205},
    {"LightBlue", 173, 216, 230},
    {"LightCoral", 240, 128, 128},
    {"LightCyan", 224, 255, 255},
    {"LightGoldenrod", 238, 213, 160},
    {"LightGoldenrodYellow", 250, 250, 210},
    {"LightGray", 211, 211, 211},
    {"LightGreen", 144, 238, 144},
    {"LightPink", 255, 182, 193},
    {"LightSalmon", 255, 160, 122},
    {"LightSeaGreen", 32, 178, 170},
    {"LightSkyBlue", 135, 206, 250},
    {"LightSlateGray", 119, 136, 153},
    {"LightSteelBlue", 176, 196, 222},
    {"LightYellow", 255, 255, 224},
    {"Lime", 0, 255, 0},
    {"LimeGreen", 50, 205, 50},
    {"Linen", 250, 240, 230},
    {"Magenta", 255, 0, 255},
    {"Maroon", 128, 0, 0},
    {"MediumAquamarine", 102, 205, 170},
    {"MediumBlue", 0, 0, 205},
    {"MediumOrchid", 186, 85, 211},
    {"MediumPurple", 147, 112, 219},
    {"MediumSeaGreen", 60, 179, 113},
    {"MediumSlateBlue", 123, 104, 238},
    {"MediumSpringGreen", 0, 250, 154},
    {"MediumTurquoise", 72, 209, 204},
    {"MediumVioletRed", 199, 21, 133},
    {"MidnightBlue", 25, 25, 112},
    {"MintCream", 245, 255, 250},
    {"MistyRose", 255, 228, 225},
    {"Moccasin", 255, 228, 181},
    {"NavajoWhite", 255, 222, 173},
    {"Navy", 0, 0, 128},
    {"OldLace", 253, 245, 230},
    {"Olive", 128, 128, 0},
    {"OliveDrab", 107, 142, 35},
    {"Orange", 255, 165, 0},
    {"OrangeRed", 255, 69, 0},
    {"Orchid", 218, 112, 214},
    {"PaleGoldenRod", 238, 232, 170},
    {"PaleGreen", 152, 251, 152},
    {"PaleTurquoise", 175, 238, 238},
    {"PaleVioletRed", 219, 112, 147},
    {"PapayaWhip", 255, 239, 213},
    {"PeachPuff", 255, 218, 185},
    {"Peru", 205, 133, 63},
    {"Pink", 255, 192, 203},
    {"Plum", 221, 160, 221},
    {"PowderBlue", 176, 224, 230},
    {"Purple", 128, 0, 128},
    {"RebeccaPurple", 102, 51, 153},
    {"Red", 255, 0, 0},
    {"RosyBrown", 188, 143, 143},
    {"RoyalBlue", 65, 105, 225},
    {"SaddleBrown", 139, 69, 19},
    {"Salmon", 250, 128, 114},
    {"SandyBrown", 244, 164, 96},
    {"SeaGreen", 46, 139, 87},
    {"Seashell", 255, 245, 238},
    {"Sienna", 160, 82, 45},
    {"Silver", 192, 192, 192},
    {"SkyBlue", 135, 206, 235},
    {"SlateBlue", 106, 90, 205},
    {"SlateGray", 112, 128, 144},
    {"Snow", 255, 250, 250},
    {"SpringGreen", 0, 255, 127},
    {"SteelBlue", 70, 130, 180},
    {"Tan", 210, 180, 140},
    {"Teal", 0, 128, 128},
    {"Thistle", 216, 191, 216},
    {"Tomato", 255, 99, 71},
    {"Turquoise", 64, 224, 208},
    {"Violet", 238, 130, 238},
    {"Wheat", 245, 222, 179},
    {"White", 255, 255, 255},
    {"WhiteSmoke", 245, 245, 245},
    {"Yellow", 255, 255, 0},
    {"YellowGreen", 154, 205, 50},
    {"Amaranth", 255, 128, 171}
};

void generate_hex(char* hex) {
    int r = rand() % 256, g = rand() % 256, b = rand() % 256;
    sprintf(hex, "%02X%02X%02X", r, g, b);
}

static double get_luminance(int r, int g, int b) {
    double R = r / 255.0, G = g / 255.0, B = b / 255.0;
    double r_lin = R <= 0.03928 ? R / 12.92 : pow((R + 0.055) / 1.055, 2.4);
    double g_lin = G <= 0.03928 ? G / 12.92 : pow((G + 0.055) / 1.055, 2.4);
    double b_lin = B <= 0.03928 ? B / 12.92 : pow((B + 0.055) / 1.055, 2.4);
    return 0.2126 * r_lin + 0.7152 * g_lin + 0.0722 * b_lin;
}

const char* get_pantone(int r, int g, int b) {
    int tolerance = 26;  // 10% of 255
    
    /* Check HTML color lookup table — keep best (smallest diff) match */
    int best_diff = 3 * tolerance + 1;
    const char* best_name = NULL;
    for (int i = 0; i < (int)HTML_COLORS_LEN; i++) {
        int diff = abs(html_colors[i].r - r) + abs(html_colors[i].g - g) + abs(html_colors[i].b - b);
        if (diff < best_diff) {
            best_diff = diff;
            best_name = html_colors[i].name;
        }
    }
    if (best_name != NULL) return best_name;
    
    /* Luminance-based fallback (WCAG: sRGB→linear first, then weighted sum) */
    double lum = get_luminance(r, g, b);

    if (lum > 0.85) return "White";
    if (lum < 0.15) return "Black";
    
    /* Color family detection */
    int max_v = r, min_v = r, imax = 0;
    if (g > max_v) { max_v = g; imax = 1; }
    if (b > max_v) { max_v = b; imax = 2; }
    if (g < min_v) { min_v = g; }
    if (b < min_v) { min_v = b; }
    double saturation = max_v == 0 ? 0.0 : (double)(max_v - min_v) / max_v;

    if (saturation > 0.5) {
        if (imax == 0) return "Red";
        if (imax == 1) return "Green";
        return "Blue";
    }

    /* Generic fallback */
    if (imax == 0) return "Red-family";
    if (imax == 1) return "Green-family";
    return "Blue-family";
}

double get_lum_hex(const char* hex) {
    int r, g, b;
    hex_to_rgb(hex, &r, &g, &b);
    return get_luminance(r, g, b);
}

double get_contrast_ratio(const char* c1, const char* c2) {
    double L1 = get_lum_hex(c1), L2 = get_lum_hex(c2);
    double Lmax = fmax(L1, L2), Lmin = fmin(L1, L2);
    return (Lmax + 0.05) / (Lmin + 0.05);
}

#ifndef TEST_SKIP_MAIN
static void print_contrast_report(const char* hex1, const char* hex2) {
    int r1, g1, b1, r2, g2, b2;
    hex_to_rgb(hex1, &r1, &g1, &b1);
    hex_to_rgb(hex2, &r2, &g2, &b2);

    const char* name1 = get_pantone(r1, g1, b1);
    const char* name2 = get_pantone(r2, g2, b2);

    printf("Description: %s (#%s) and %s (#%s)\n", name1, hex1, name2, hex2);
    printf("Full text: %s #%s\n%s #%s\n", name1, hex1, name2, hex2);
    {
        double ratio = get_contrast_ratio(hex1, hex2);
        const char* rating;
        if (ratio >= 7.0) rating = "AAA";
        else if (ratio < 4.5) rating = "N/A";
        else rating = "AA";
        printf("(Contrast ratio: %.1f:1 | %s)\n", ratio, rating);
    }
    printf("Color One: #%s\n", hex1);
    printf("Color Two: #%s\n", hex2);
}

static void print_machine_report(const char* hex1, const char* hex2) {
    int r1, g1, b1, r2, g2, b2;
    hex_to_rgb(hex1, &r1, &g1, &b1);
    hex_to_rgb(hex2, &r2, &g2, &b2);

    const char* name1 = get_pantone(r1, g1, b1);
    const char* name2 = get_pantone(r2, g2, b2);
    double ratio = get_contrast_ratio(hex1, hex2);
    const char* rating;
    if (ratio >= 7.0) rating = "AAA";
    else if (ratio < 4.5) rating = "N/A";
    else rating = "AA";
    printf("ratio=%.2f\nrating=%s\nname1=%s\nname2=%s\n", ratio, rating, name1, name2);
}

int main(int argc, char** argv) {
    if (argc == 4 && strcmp(argv[1], "--hex") == 0) {
        if (strlen(argv[2]) != 6 || strlen(argv[3]) != 6) {
            fprintf(stderr, "Each hex must be exactly 6 chars\n");
            return 1;
        }
        print_machine_report(argv[2], argv[3]);
        return 0;
    }
    if (argc != 1) {
        fprintf(stderr, "Usage: %s [--hex AABBCC DDEEFF]\n", argv[0]);
        return 1;
    }

    srand(time(NULL));
    char hex1[7], hex2[7];
    int attempts = 0;
    const int max_attempts = 1000;

    printf("Generating random color contrast...\n");
    do {
        generate_hex(hex1);
        generate_hex(hex2);
        attempts++;
    } while (get_contrast_ratio(hex1, hex2) < 4.5 && attempts < max_attempts);

    if (attempts >= max_attempts) {
        fprintf(stderr, "Warning: max attempts reached\n");
    } else {
        printf("Generated random color contrast!\n");
    }

    print_contrast_report(hex1, hex2);
    return 0;
}
#endif
