#include "test_helpers.h"
#include <stdlib.h>

#define TEST_SKIP_MAIN
#include "../main.c"

static void test_hex_to_rgb_valid(void) {
    int r = -1, g = -1, b = -1;
    ASSERT_TRUE(hex_to_rgb("FF8040", &r, &g, &b));
    ASSERT_EQ_INT(r, 255);
    ASSERT_EQ_INT(g, 128);
    ASSERT_EQ_INT(b, 64);
}

static void test_hex_to_rgb_lowercase(void) {
    int r, g, b;
    ASSERT_TRUE(hex_to_rgb("abcdef", &r, &g, &b));
    ASSERT_EQ_INT(r, 0xAB);
    ASSERT_EQ_INT(g, 0xCD);
    ASSERT_EQ_INT(b, 0xEF);
}

static void test_hex_to_rgb_rejects_short(void) {
    int r = -1, g = -1, b = -1;
    ASSERT_TRUE(!hex_to_rgb("FFF", &r, &g, &b));
    ASSERT_EQ_INT(r, -1);
}

static void test_hex_to_rgb_rejects_long(void) {
    int r = -1, g = -1, b = -1;
    ASSERT_TRUE(!hex_to_rgb("FFFFFFF", &r, &g, &b));
    ASSERT_EQ_INT(r, -1);
}

static void test_hex_to_rgb_rejects_null(void) {
    int r, g, b;
    ASSERT_TRUE(!hex_to_rgb(NULL, &r, &g, &b));
}

static void test_hex_to_rgb_rejects_invalid_chars(void) {
    int r = -1, g = -1, b = -1;
    /* 6 chars but not hex — passes the strlen check, must be caught by sscanf.
     * Note: sscanf %x skips whitespace, so "12 456" parses to 18,69,6. */
    ASSERT_TRUE(!hex_to_rgb("ZZZZZZ", &r, &g, &b));
    ASSERT_TRUE(!hex_to_rgb("ghijkl", &r, &g, &b));
    ASSERT_EQ_INT(r, -1);
}

static void test_get_lum_hex_black_is_zero(void) {
    ASSERT_NEAR(get_lum_hex("000000"), 0.0, 1e-9);
}

static void test_get_lum_hex_white_is_one(void) {
    ASSERT_NEAR(get_lum_hex("FFFFFF"), 1.0, 1e-9);
}

static void test_get_contrast_ratio_black_white(void) {
    ASSERT_NEAR(get_contrast_ratio("000000", "FFFFFF"), 21.0, 0.01);
}

static void test_get_contrast_ratio_same_color(void) {
    ASSERT_NEAR(get_contrast_ratio("808080", "808080"), 1.0, 0.01);
}

static void test_get_contrast_ratio_symmetric(void) {
    double a = get_contrast_ratio("FF0000", "00FF00");
    double b = get_contrast_ratio("00FF00", "FF0000");
    ASSERT_NEAR(a, b, 1e-9);
    ASSERT_TRUE(a >= 1.0);
}

static void test_get_pantone_pure_black(void) {
    ASSERT_STR_EQ(get_pantone(0, 0, 0), "Black");
}

static void test_get_pantone_pure_white(void) {
    ASSERT_STR_EQ(get_pantone(255, 255, 255), "White");
}

static void test_get_pantone_red(void) {
    ASSERT_STR_EQ(get_pantone(255, 0, 0), "Red");
}

static void test_get_pantone_green(void) {
    ASSERT_STR_EQ(get_pantone(0, 128, 0), "Green");
}

static void test_get_pantone_blue(void) {
    ASSERT_STR_EQ(get_pantone(0, 0, 255), "Blue");
}

static void test_get_pantone_near_black_uses_luminance_fallback(void) {
    /* (40,40,40) has no table match within 78 Manhattan distance.
     * Perceptual luminance after sRGB→linear decode is ~0.023, well below
     * the 0.15 threshold for "Black". The buggy formula (raw sRGB) gives
     * ~0.157 — just above 0.15 — and falls through to "Red-family". */
    ASSERT_STR_EQ(get_pantone(40, 40, 40), "Black");
}

/* CSS named-color spec assertions (https://developer.mozilla.org/en-US/docs/Web/CSS/named-color).
 * Each test pins the exact RGB for one entry so future table edits can't
 * silently drift the value. */

static void test_get_pantone_cadetblue(void)     { ASSERT_STR_EQ(get_pantone(95, 158, 160), "CadetBlue"); }
static void test_get_pantone_chocolate(void)     { ASSERT_STR_EQ(get_pantone(210, 105, 30), "Chocolate"); }
static void test_get_pantone_deepskyblue(void)   { ASSERT_STR_EQ(get_pantone(0, 191, 255), "DeepSkyBlue"); }
static void test_get_pantone_forestgreen(void)   { ASSERT_STR_EQ(get_pantone(34, 139, 34), "ForestGreen"); }
static void test_get_pantone_greenyellow(void)   { ASSERT_STR_EQ(get_pantone(173, 255, 47), "GreenYellow"); }
static void test_get_pantone_lightsalmon(void)   { ASSERT_STR_EQ(get_pantone(255, 160, 122), "LightSalmon"); }
static void test_get_pantone_mistyrose(void)     { ASSERT_STR_EQ(get_pantone(255, 228, 225), "MistyRose"); }
static void test_get_pantone_paleturquoise(void) { ASSERT_STR_EQ(get_pantone(175, 238, 238), "PaleTurquoise"); }
static void test_get_pantone_rebeccapurple(void) { ASSERT_STR_EQ(get_pantone(102, 51, 153), "RebeccaPurple"); }
static void test_get_pantone_seagreen(void)      { ASSERT_STR_EQ(get_pantone(46, 139, 87), "SeaGreen"); }
static void test_get_pantone_seashell(void)      { ASSERT_STR_EQ(get_pantone(255, 245, 238), "Seashell"); }
static void test_get_pantone_springgreen(void)   { ASSERT_STR_EQ(get_pantone(0, 255, 127), "SpringGreen"); }
static void test_get_pantone_whitesmoke(void)    { ASSERT_STR_EQ(get_pantone(245, 245, 245), "WhiteSmoke"); }

/* Color-family fallback paths. Each input has min Manhattan > 78 against
 * the 139-entry table AND luminance in (0.15, 0.85), so neither table match
 * nor the "Black"/"White" luminance fallback fires. Brute-forced from the
 * full RGB space; see /tmp/find_gaps.c for the search. */

static void test_get_pantone_saturated_red(void)  { ASSERT_STR_EQ(get_pantone(135, 116, 67), "Red"); }
static void test_get_pantone_saturated_green(void){ ASSERT_STR_EQ(get_pantone(0, 152, 66), "Green"); }
static void test_get_pantone_saturated_blue(void) { ASSERT_STR_EQ(get_pantone(0, 93, 255), "Blue"); }
static void test_get_pantone_red_family(void)     { ASSERT_STR_EQ(get_pantone(150, 150, 90), "Red-family"); }
static void test_get_pantone_green_family(void)   { ASSERT_STR_EQ(get_pantone(95, 164, 82), "Green-family"); }
static void test_get_pantone_blue_family(void)    { ASSERT_STR_EQ(get_pantone(119, 173, 200), "Blue-family"); }

static void test_generate_hex_format(void) {
    char hex[7];
    generate_hex(hex);
    ASSERT_EQ_INT((int)strlen(hex), 6);
    for (int i = 0; i < 6; i++) {
        char c = hex[i];
        ASSERT_TRUE((c >= '0' && c <= '9') || (c >= 'A' && c <= 'F'));
    }
}

int main(void) {
    RUN_TEST(test_hex_to_rgb_valid);
    RUN_TEST(test_hex_to_rgb_lowercase);
    RUN_TEST(test_hex_to_rgb_rejects_short);
    RUN_TEST(test_hex_to_rgb_rejects_long);
    RUN_TEST(test_hex_to_rgb_rejects_null);
    RUN_TEST(test_hex_to_rgb_rejects_invalid_chars);
    RUN_TEST(test_get_lum_hex_black_is_zero);
    RUN_TEST(test_get_lum_hex_white_is_one);
    RUN_TEST(test_get_contrast_ratio_black_white);
    RUN_TEST(test_get_contrast_ratio_same_color);
    RUN_TEST(test_get_contrast_ratio_symmetric);
    RUN_TEST(test_get_pantone_pure_black);
    RUN_TEST(test_get_pantone_pure_white);
    RUN_TEST(test_get_pantone_red);
    RUN_TEST(test_get_pantone_green);
    RUN_TEST(test_get_pantone_blue);
    RUN_TEST(test_get_pantone_near_black_uses_luminance_fallback);
    RUN_TEST(test_get_pantone_cadetblue);
    RUN_TEST(test_get_pantone_chocolate);
    RUN_TEST(test_get_pantone_deepskyblue);
    RUN_TEST(test_get_pantone_forestgreen);
    RUN_TEST(test_get_pantone_greenyellow);
    RUN_TEST(test_get_pantone_lightsalmon);
    RUN_TEST(test_get_pantone_mistyrose);
    RUN_TEST(test_get_pantone_paleturquoise);
    RUN_TEST(test_get_pantone_rebeccapurple);
    RUN_TEST(test_get_pantone_seagreen);
    RUN_TEST(test_get_pantone_seashell);
    RUN_TEST(test_get_pantone_springgreen);
    RUN_TEST(test_get_pantone_whitesmoke);
    RUN_TEST(test_get_pantone_saturated_red);
    RUN_TEST(test_get_pantone_saturated_green);
    RUN_TEST(test_get_pantone_saturated_blue);
    RUN_TEST(test_get_pantone_red_family);
    RUN_TEST(test_get_pantone_green_family);
    RUN_TEST(test_get_pantone_blue_family);
    RUN_TEST(test_generate_hex_format);
    TEST_SUMMARY();
}