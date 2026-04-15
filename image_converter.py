import os
import subprocess
import sys
import struct

try:
    from PIL import Image
except ImportError:
    subprocess.check_call([sys.executable, "-m", "pip", "install", "Pillow"])
    from PIL import Image

try:
    Import("env")
except:
    pass

def generate_images_header(source, target, env):
    assets_dir = "assets"
    header_file = "include/Images.h"
        
    if not os.path.exists(assets_dir):
        os.makedirs(assets_dir)

    with open(header_file, "w") as f:
        f.write("#ifndef GENERATED_IMAGES_H\n#define GENERATED_IMAGES_H\n\n#include <Arduino.h>\n\n")
        
        for filename in os.listdir(assets_dir):
            if filename.lower().endswith((".jpg", ".jpeg", ".png", ".bmp")):
                filepath = os.path.join(assets_dir, filename)
                base_name = os.path.splitext(filename)[0].replace("-", "_").replace(".", "_")
                
                img = Image.open(filepath).convert("RGB")
                width, height = img.size
                
                f.write(f"// Image: {filename} ({width}x{height})\n")
                f.write(f"const uint16_t {base_name}Width = {width};\n")
                f.write(f"const uint16_t {base_name}Height = {height};\n")
                
                # Массив будет uint16_t, так как RGB565 — это 2 байта на пиксель
                f.write(f"const uint16_t {base_name}[] __attribute__((aligned(4))) PROGMEM = {{\n  ")
                
                pixels = img.load()
                count = 0
                for y in range(height):
                    for x in range(width):
                        r, g, b = pixels[x, y]
                        rgb565 = ((r & 0xF8) << 8) | ((g & 0xFC) << 3) | (b >> 3)
                        f.write(f"0x{rgb565:04X}, ")
                        count += 1
                        if count % 12 == 0:
                            f.write("\n  ")
                
                f.write("\n};\n\n")
        
        f.write("#endif\n")

try:
    env.AddPreAction("buildprog", generate_images_header)
    env.AddPreAction("upload", generate_images_header)
except:
    generate_images_header(None, None, None)