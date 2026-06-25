#!/usr/bin/env python3
import re

with open('c-port/main.c', 'r') as f:
    content = f.read()

# Count color entries: {"Name", r, g, b}
colors = len(re.findall(r'\{\s*"[^"]+",\s*\d+', content))

print(f"Total colors: {colors}")

# Extract color table
match = re.search(r'html_colors\[MAX_COLORS\] = \{([^}]+)\};', content, re.DOTALL)
if match:
    table = match.group(1)
    colors = len(re.findall(r'"\{', table))
    print(f"Colors in table: {colors}")