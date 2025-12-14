# Quick Reference: Floor/Ceiling Colors & Texture System

## 🎨 Floor and Ceiling Colors - Quick Summary

### What Was Fixed:
Previously, the code used **hardcoded** colors `0x0263238` for both floor and ceiling, ignoring the values in your `.cub` file.

### How It Works Now:

#### 1. **Parsing** (Already existed - in `src/parse/check_element.c`):
```c
// When reading "F 0,255,0" from map.cub:
data->texture->floor[0] = 0;     // Red
data->texture->floor[1] = 255;   // Green  
data->texture->floor[2] = 0;     // Blue

// When reading "C 225,30,0" from map.cub:
data->texture->ceiling[0] = 225; // Red
data->texture->ceiling[1] = 30;  // Green
data->texture->ceiling[2] = 0;   // Blue
```

#### 2. **Conversion** (New function):
```c
// Convert RGB array to hex color
static int rgb_to_color(unsigned char *rgb)
{
    return ((rgb[0] << 16) | (rgb[1] << 8) | rgb[2]);
}
// Example: [225, 30, 0] → 0xE11E00
```

#### 3. **Usage** (Updated in `draw_wall_slice()`):
```c
ceiling_color = rgb_to_color(data->texture->ceiling);  // Use parsed ceiling
floor_color = rgb_to_color(data->texture->floor);      // Use parsed floor

// Draw ceiling (top of screen to wall start)
draw_vertical_line(data, x, 0, draw_start, ceiling_color);

// Draw floor (wall end to bottom of screen)  
draw_vertical_line(data, x, draw_end, HEIGHT, floor_color);
```

---

## 🖼️ Texture System - Quick Summary

### Architecture:

```
.cub file paths → load_textures() → Memory (t_img structs) → Rendering
    ↓                    ↓                    ↓                    ↓
"./north.xpm"    Load 4 .xpm files    Pixel data in RAM    Sample & draw
```

### Key Components:

#### 1. **Data Structure** (`t_img`):
```c
typedef struct s_img {
    void  *img;         // MLX image pointer
    char  *addr;        // Raw pixel data
    int   width;        // Texture width (e.g., 64px)
    int   height;       // Texture height (e.g., 64px)
    int   bpp;          // Bits per pixel (32)
    int   size_line;    // Bytes per row
    int   endian;       // Byte order
} t_img;
```

#### 2. **Loading** (in `load_textures.c`):
```c
void load_textures(t_data *data) {
    // Load all 4 wall textures
    load_single_texture(data, &data->texture->north_img, data->texture->north);
    load_single_texture(data, &data->texture->south_img, data->texture->south);
    load_single_texture(data, &data->texture->west_img, data->texture->west);
    load_single_texture(data, &data->texture->east_img, data->texture->east);
}
```

#### 3. **Texture Selection** (which wall texture to use):
```c
static t_img *get_wall_texture(t_data *data, t_ray *ray) {
    if (ray->side == 0 && ray->step_x > 0)  // Hit vertical wall from left
        return (&data->texture->east_img);
    else if (ray->side == 0 && ray->step_x < 0)  // Hit vertical wall from right
        return (&data->texture->west_img);
    else if (ray->side == 1 && ray->step_y > 0)  // Hit horizontal wall from top
        return (&data->texture->south_img);
    else                                     // Hit horizontal wall from bottom
        return (&data->texture->north_img);
}
```

#### 4. **Texture Coordinates**:

**Horizontal (X) coordinate:**
```c
wall_x = fractional_hit_position;  // 0.0 to 1.0 (where on wall ray hit)
tex_x = (int)(wall_x * texture->width);  // Convert to pixel column
```

**Vertical (Y) coordinate:**
```c
step = texture->height / wall_height_on_screen;  // Scaling factor
tex_y = (int)(current_y_pos * step) % texture->height;  // Which texture row
```

#### 5. **Rendering**:
```c
// For each vertical screen line (x):
for (y = wall_start; y < wall_end; y++) {
    tex_y = calculate_texture_y(y);
    color = get_texture_pixel(texture, tex_x, tex_y);  // Sample texture
    put_pixel(screen, x, y, color);                    // Draw to screen
}
```

---

## 📝 Files Changed Summary

| File | What Changed | Why |
|------|-------------|-----|
| `inc/main.h` | Added `t_img` struct, added texture images to `t_texture`, added `wall_x` to `t_ray` | Store texture data and hit position |
| `src/raycast/load_textures.c` | Complete rewrite | Actually load textures instead of empty function |
| `src/raycast/raycast_ray.c` | Added `wall_x` calculation | Needed for horizontal texture coordinate |
| `src/raycast/raycast_drawing.c` | Added `rgb_to_color()`, `get_wall_texture()`, rewrote `draw_wall_slice()` | Use textures and parsed colors instead of hardcoded values |
| `src/main.c` | Added `load_textures(data)` call | Initialize textures before rendering |
| `Makefile` | Added `load_textures.c` | Compile the new file |

---

## 🧪 Testing Checklist

Run your program and verify:

- [ ] **Textures appear** (not solid colors)
- [ ] **Different textures** on N/S/E/W walls (if using different .xpm files)
- [ ] **Textures not mirrored** incorrectly
- [ ] **Floor color** matches `F` value in .cub file
- [ ] **Ceiling color** matches `C` value in .cub file
- [ ] **Textures scale smoothly** when moving
- [ ] **No crashes** when loading textures
- [ ] **Error message** if texture file missing

---

## 🐛 Common Issues

### Black Walls
**Cause:** Texture files not found  
**Fix:** Check paths in .cub file, ensure .xpm files exist

### Segmentation Fault on Startup
**Cause:** `load_textures()` called before `mlx_init()`  
**Fix:** Ensure order in main():
```c
data->mlx = mlx_init();     // FIRST
load_textures(data);        // SECOND
data->win = mlx_new_window(...);  // THIRD
```

### Still Seeing Solid Colors (not textures)
**Cause:** Old `draw_wall_slice()` code still active  
**Fix:** Ensure `draw_wall_slice()` calls `get_texture_pixel()` and not `draw_vertical_line()` for walls

### Wrong Floor/Ceiling Colors
**Cause:** Using old hardcoded values  
**Fix:** Verify these lines in `draw_wall_slice()`:
```c
ceiling_color = rgb_to_color(data->texture->ceiling);
floor_color = rgb_to_color(data->texture->floor);
```

---

## 🎯 Key Concepts

### Why `wall_x`?
- Tells us **where** on the wall the ray hit (0.0 = left edge, 1.0 = right edge)
- Multiply by texture width to get pixel column: `tex_x = wall_x * 64`

### Why texture flipping?
- Without it, opposite walls would show mirrored textures
- Fixes visual consistency when walking around walls

### Why `step`?
- Textures need to stretch/shrink based on distance
- Close walls: large on screen, slow step through texture
- Far walls: small on screen, fast step through texture

### Why separate textures per direction?
- Visual variety (different brick patterns on N vs S walls)
- Helps with orientation (player knows which direction they're facing)
- cub3D subject requirement

---

## 📚 Further Reading

For **complete detailed explanations** with math breakdowns, algorithm analysis, and every design decision documented:

👉 **See [TEXTURE_IMPLEMENTATION.md](TEXTURE_IMPLEMENTATION.md)**

That document is 400+ lines of comprehensive technical documentation explaining every single aspect of the implementation.
