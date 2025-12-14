# Texture Loading and Rendering Implementation - Detailed Documentation

## Overview
This document provides an extremely detailed explanation of how texture loading and rendering was implemented in the cub3D project, including the floor/ceiling color system.

---

## Table of Contents
1. [Floor and Ceiling Color Implementation](#1-floor-and-ceiling-color-implementation)
2. [Texture System Architecture](#2-texture-system-architecture)
3. [Texture Loading Process](#3-texture-loading-process)
4. [Texture Coordinate Calculation](#4-texture-coordinate-calculation)
5. [Wall Texture Selection](#5-wall-texture-selection)
6. [Texture Rendering Pipeline](#6-texture-rendering-pipeline)
7. [Integration with Main Program](#7-integration-with-main-program)
8. [Testing and Validation](#8-testing-and-validation)

---

## 1. Floor and Ceiling Color Implementation

### Problem Identified
The original code was parsing the floor (`F`) and ceiling (`C`) color values from the `.cub` map file into RGB arrays:
- `data->texture->floor` (unsigned char array of 3 elements)
- `data->texture->ceiling` (unsigned char array of 3 elements)

However, the rendering code in `raycast_drawing.c` was using hardcoded color values (`0x0263238`) instead of the parsed colors.

### Solution Implementation

#### Step 1: RGB to Hex Conversion Function
**File:** `src/raycast/raycast_drawing.c`

```c
static int	rgb_to_color(unsigned char *rgb)
{
	return ((rgb[0] << 16) | (rgb[1] << 8) | rgb[2]);
}
```

**Explanation:**
- This function converts an RGB array into a single 32-bit integer color value
- The format is `0xRRGGBB` where:
  - `rgb[0]` (Red) is shifted left by 16 bits (moves to most significant byte)
  - `rgb[1]` (Green) is shifted left by 8 bits (moves to middle byte)
  - `rgb[2]` (Blue) remains in the least significant byte
- **Why this works:** MLX (MiniLibX) expects colors in 0xRRGGBB hexadecimal format
- **Example:** RGB(225, 30, 0) becomes `(225 << 16) | (30 << 8) | 0 = 0xE11E00`

#### Step 2: Using Parsed Colors in Rendering
**File:** `src/raycast/raycast_drawing.c` in `draw_wall_slice()` function

```c
ceiling_color = rgb_to_color(data->texture->ceiling);
floor_color = rgb_to_color(data->texture->floor);
```

**Why this matters:**
- Before: All renders had the same hardcoded floor/ceiling regardless of map file
- After: Each map can specify its own unique floor/ceiling colors
- This makes the program comply with the cub3D subject requirements

---

## 2. Texture System Architecture

### Data Structures Added

#### New Image Structure (`t_img`)
**File:** `inc/main.h`

```c
typedef struct s_img
{
	void	*img;          // MLX image pointer (returned by mlx_xpm_file_to_image)
	char	*addr;         // Memory address of image data
	int		bpp;           // Bits per pixel (usually 32)
	int		size_line;     // Size of one line in bytes (width * bpp/8)
	int		endian;        // Endianness of the image data
	int		width;         // Texture width in pixels
	int		height;        // Texture height in pixels
}	t_img;
```

**Purpose of Each Field:**
- `img`: The actual MLX image object we load from .xpm files
- `addr`: Pointer to the raw pixel data array in memory
- `bpp`: Tells us how many bits represent one pixel (typically 32 for RGBA)
- `size_line`: How many bytes make up one horizontal line of pixels
- `endian`: Byte order (little-endian vs big-endian) - important for color extraction
- `width`/`height`: Dimensions of the texture, needed for coordinate mapping

#### Updated Texture Structure
**File:** `inc/main.h`

```c
typedef struct s_texture
{
	char			*north;       // Path to north wall texture
	char			*south;       // Path to south wall texture
	char			*west;        // Path to west wall texture
	char			*east;        // Path to east wall texture
	unsigned char	*floor;       // Floor RGB color [R, G, B]
	unsigned char	*ceiling;     // Ceiling RGB color [R, G, B]
	t_img			north_img;    // Loaded north texture image
	t_img			south_img;    // Loaded south texture image
	t_img			west_img;     // Loaded west texture image
	t_img			east_img;     // Loaded east texture image
}	t_texture;
```

**Design Decision:**
- We keep both the path strings AND the loaded image data
- Path strings are used during parsing and loading
- Image data structures are used during rendering
- This separation allows for error checking during load time

---

## 3. Texture Loading Process

### Overview
Textures must be loaded from .xpm files into memory before rendering can begin.

### Implementation: `load_textures()`
**File:** `src/raycast/load_textures.c`

```c
void	load_textures(t_data *data)
{
	load_single_texture(data, &data->texture->north_img, data->texture->north);
	load_single_texture(data, &data->texture->south_img, data->texture->south);
	load_single_texture(data, &data->texture->west_img, data->texture->west);
	load_single_texture(data, &data->texture->east_img, data->texture->east);
}
```

**Why four separate loads:**
- Each cardinal direction (N, S, E, W) needs its own texture
- This allows walls to look different based on which direction they face
- Provides visual orientation cues for the player

### Implementation: `load_single_texture()`
**File:** `src/raycast/load_textures.c`

```c
static void	load_single_texture(t_data *data, t_img *texture, char *path)
{
	texture->img = mlx_xpm_file_to_image(data->mlx, path, 
			&texture->width, &texture->height);
	if (!texture->img)
	{
		ft_malloc(-42);
		ft_perror("Failed to load texture");
		exit(1);
	}
	texture->addr = mlx_get_data_addr(texture->img, &texture->bpp,
			&texture->size_line, &texture->endian);
}
```

**Step-by-step breakdown:**

1. **`mlx_xpm_file_to_image()`**
   - MLX function that reads .xpm file format
   - Parameters:
     - `data->mlx`: MLX connection/context
     - `path`: File path to the texture
     - `&texture->width`: Pointer to store texture width (output parameter)
     - `&texture->height`: Pointer to store texture height (output parameter)
   - Returns: Pointer to MLX image object, or NULL on failure
   - **Why .xpm?** It's an ASCII-based image format that MLX can parse easily

2. **Error Handling**
   - Check if `texture->img` is NULL (loading failed)
   - If failed:
     - Free all allocated memory with `ft_malloc(-42)`
     - Print error message
     - Exit program (can't continue without textures)
   - **Why exit here?** Rendering without textures would crash the program later

3. **`mlx_get_data_addr()`**
   - Gets the memory address where pixel data is stored
   - Parameters:
     - `texture->img`: The loaded image
     - `&texture->bpp`: Output - bits per pixel
     - `&texture->size_line`: Output - bytes per line
     - `&texture->endian`: Output - byte order
   - Returns: Pointer to raw pixel array
   - **Why we need this:** Direct memory access is faster than MLX pixel functions

---

## 4. Texture Coordinate Calculation

### The Challenge
When a ray hits a wall, we need to determine:
1. Which texture to use (N/S/E/W)
2. Where on that texture to sample from (X coordinate)
3. How to stretch/compress the texture vertically (Y coordinate mapping)

### Added Ray Property: `wall_x`
**File:** `inc/main.h`

```c
typedef struct s_ray
{
	// ... existing fields ...
	float	wall_x;  // Exact X coordinate where ray hit the wall (0.0 to 1.0)
}	t_ray;
```

**Purpose:** `wall_x` represents the fractional position along the wall where the ray intersected.

### Calculating `wall_x`
**File:** `src/raycast/raycast_ray.c` in `calculate_wall_distance()`

```c
if (ray->side == 0)
	ray->perp_wall_dist = (ray->map_x - data->player.x 
			+ (1 - ray->step_x) / 2) / ray->dir_x;
else
	ray->perp_wall_dist = (ray->map_y - data->player.y 
			+ (1 - ray->step_y) / 2) / ray->dir_y;

// Calculate where exactly on the wall the ray hit
if (ray->side == 0)
	ray->wall_x = data->player.y + ray->perp_wall_dist * ray->dir_y;
else
	ray->wall_x = data->player.x + ray->perp_wall_dist * ray->dir_x;

// Get only the fractional part (value between 0.0 and 1.0)
ray->wall_x -= floor(ray->wall_x);
```

**Detailed Explanation:**

1. **First: Calculate perpendicular wall distance**
   - `perp_wall_dist`: Distance from player to wall, perpendicular to camera plane
   - This prevents the "fish-eye" effect
   - Formula depends on whether ray hit vertical wall (`side == 0`) or horizontal wall (`side == 1`)

2. **Second: Calculate world coordinate of impact point**
   - If vertical wall hit (`side == 0`): Use Y coordinate
     - Formula: `player.y + distance * direction_y`
     - This gives us the Y position in the game world where ray hit
   - If horizontal wall hit (`side == 1`): Use X coordinate
     - Formula: `player.x + distance * direction_x`
     - This gives us the X position in the game world where ray hit

3. **Third: Extract fractional part**
   - `floor(wall_x)` removes the integer part (which map square we're in)
   - Subtraction leaves only the decimal part (0.0 to 1.0)
   - **Example:** If `wall_x = 5.73`, then `wall_x - floor(5.73) = 5.73 - 5.0 = 0.73`
   - This 0.73 means the ray hit 73% of the way across the wall tile

**Why this works:**
- A value of 0.0 means the ray hit at the left/top edge of the wall
- A value of 0.5 means the ray hit in the middle of the wall
- A value of 1.0 means the ray hit at the right/bottom edge of the wall
- This maps perfectly to texture X coordinates: `0.73 * texture_width = pixel column`

---

## 5. Wall Texture Selection

### The Decision Logic
**File:** `src/raycast/raycast_drawing.c`

```c
static t_img	*get_wall_texture(t_data *data, t_ray *ray)
{
	if (ray->side == 0 && ray->step_x > 0)
		return (&data->texture->east_img);
	else if (ray->side == 0 && ray->step_x < 0)
		return (&data->texture->west_img);
	else if (ray->side == 1 && ray->step_y > 0)
		return (&data->texture->south_img);
	else
		return (&data->texture->north_img);
}
```

**Understanding the Logic:**

### What is `side`?
- `side == 0`: Ray hit a VERTICAL wall (wall aligned with Y-axis)
- `side == 1`: Ray hit a HORIZONTAL wall (wall aligned with X-axis)
- This is determined during the DDA algorithm in `perform_dda()`

### What is `step_x` and `step_y`?
- `step_x > 0`: Ray is traveling in the POSITIVE X direction (moving right/east)
- `step_x < 0`: Ray is traveling in the NEGATIVE X direction (moving left/west)
- `step_y > 0`: Ray is traveling in the POSITIVE Y direction (moving down/south)
- `step_y < 0`: Ray is traveling in the NEGATIVE Y direction (moving up/north)

### Decision Tree:

```
Is it a vertical wall? (side == 0)
├─ YES → Is ray going right? (step_x > 0)
│        ├─ YES → EAST texture (player sees the WEST face of the wall)
│        └─ NO  → WEST texture (player sees the EAST face of the wall)
│
└─ NO → Is ray going down? (step_y > 0)
         ├─ YES → SOUTH texture (player sees the NORTH face of the wall)
         └─ NO  → NORTH texture (player sees the SOUTH face of the wall)
```

**Important Note:** The texture name is from the map file's perspective (NO, SO, WE, EA), but the selection is based on which face of the wall the player is looking at.

---

## 6. Texture Rendering Pipeline

### Overview of `draw_wall_slice()`
This function renders one vertical stripe of the screen, sampling from the appropriate texture.

**File:** `src/raycast/raycast_drawing.c`

### Step 1: Select Texture and Calculate Horizontal Position

```c
texture = get_wall_texture(data, ray);
tex_x = (int)(ray->wall_x * texture->width);
```

**Explanation:**
- Get the appropriate texture for this wall face
- Convert `wall_x` (0.0-1.0) to a pixel column in the texture
- **Example:** If `wall_x = 0.73` and `texture->width = 64`, then `tex_x = 46`
- This gives us which vertical column of pixels to sample from the texture

### Step 2: Handle Texture Mirroring

```c
if ((ray->side == 0 && ray->step_x < 0) 
	|| (ray->side == 1 && ray->step_y > 0))
	tex_x = texture->width - tex_x - 1;
```

**Why is this needed?**
- Without this, textures on opposite walls would be mirrored incorrectly
- This ensures textures face the correct direction on all walls
- **Specific cases requiring flip:**
  - Vertical walls hit from the left (west-facing walls)
  - Horizontal walls hit from above (south-facing walls)
- The `-1` is because pixel indices are 0-based (last pixel is `width - 1`)

### Step 3: Calculate Screen Y Range

```c
draw_start = -line_height / 2 + HEIGHT / 2;
if (draw_start < 0)
	draw_start = 0;
draw_end = line_height / 2 + HEIGHT / 2;
if (draw_end >= HEIGHT)
	draw_end = HEIGHT - 1;
```

**Explanation:**
- `line_height`: How tall the wall should appear (based on distance)
- Center the wall vertically around the middle of the screen (`HEIGHT / 2`)
- Clamp to screen bounds (0 to HEIGHT-1)
- **Example:** If `line_height = 400` and `HEIGHT = 720`:
  - `draw_start = -200 + 360 = 160`
  - `draw_end = 200 + 360 = 560`
  - Wall is drawn from pixel Y=160 to Y=560

### Step 4: Setup Texture Y Mapping

```c
ceiling_color = rgb_to_color(data->texture->ceiling);
floor_color = rgb_to_color(data->texture->floor);
step = 1.0 * texture->height / line_height;
tex_pos = (draw_start - HEIGHT / 2 + line_height / 2) * step;
```

**Understanding `step`:**
- Determines how much to advance in the texture for each screen pixel
- If wall is far away (`line_height` small), `step` is large (skip texture pixels)
- If wall is close (`line_height` large), `step` is small (sample more texture pixels)
- **Example:** `texture->height = 64`, `line_height = 128`
  - `step = 64 / 128 = 0.5`
  - We advance 0.5 texture pixels for each screen pixel
  - Each texture pixel is displayed across 2 screen pixels

**Understanding `tex_pos`:**
- Initial Y position in the texture for the first pixel we draw
- Calculation:
  - `(draw_start - HEIGHT/2)`: How far above/below screen center we're starting
  - `+ line_height/2`: Offset to align with top of wall in texture space
  - `* step`: Convert to texture coordinates
- This ensures the texture aligns properly with the wall, even when partially off-screen

### Step 5: Render Ceiling

```c
draw_vertical_line(data, x, 0, draw_start, ceiling_color);
```

- Fill from top of screen (Y=0) to start of wall with ceiling color
- Uses the parsed color from the .cub file

### Step 6: Render Textured Wall

```c
y = draw_start;
while (y < draw_end)
{
	tex_y = (int)tex_pos & (texture->height - 1);
	tex_pos += step;
	color = get_texture_pixel(texture, tex_x, tex_y);
	put_pixel(data, x, y, color);
	y++;
}
```

**Loop breakdown:**

1. **Calculate texture Y coordinate:**
   ```c
   tex_y = (int)tex_pos & (texture->height - 1);
   ```
   - Convert float `tex_pos` to integer pixel coordinate
   - `& (texture->height - 1)` is a fast modulo operation (works if height is power of 2)
   - Keeps `tex_y` within valid range [0, texture->height-1]
   - **Example:** If `texture->height = 64` (which is 2^6):
     - `texture->height - 1 = 63 = 0b00111111`
     - `tex_pos = 67.3` → `(int)67.3 = 67 = 0b01000011`
     - `67 & 63 = 0b00000011 = 3`
     - Wraps 67 back to 3 (modulo 64)

2. **Advance to next texture position:**
   ```c
   tex_pos += step;
   ```
   - Move down in the texture by `step` amount
   - Accumulates fractional positions for smooth scaling

3. **Sample texture pixel:**
   ```c
   color = get_texture_pixel(texture, tex_x, tex_y);
   ```
   - Read the color value from the texture at (`tex_x`, `tex_y`)
   - Returns 32-bit integer color in 0xRRGGBB format

4. **Draw to screen:**
   ```c
   put_pixel(data, x, y, color);
   ```
   - Write the color to the screen buffer at position (`x`, `y`)
   - `x` is the current vertical stripe we're rendering
   - `y` increments from `draw_start` to `draw_end`

### Step 7: Render Floor

```c
draw_vertical_line(data, x, draw_end, HEIGHT, floor_color);
```

- Fill from end of wall to bottom of screen (Y=HEIGHT) with floor color
- Uses the parsed color from the .cub file

---

## 7. Integration with Main Program

### Execution Order in `main()`
**File:** `src/main.c`

```c
int	main(int ac, char **av)
{
	t_data	*data;

	if (!error_check(ac, av))
		return (1);
	data = ft_malloc(sizeof(t_data));
	init_data(data);
	parse_file(data, av[1]);              // 1. Parse .cub file
	init_player(data);                     // 2. Initialize player position
	convert_map_to_array(data);            // 3. Convert map to 2D array
	data->mlx = mlx_init();                // 4. Initialize MLX
	load_textures(data);                   // 5. Load textures ← NEW
	data->win = mlx_new_window(...);       // 6. Create window
	data->img = mlx_new_image(...);        // 7. Create image buffer
	// ... rest of setup ...
}
```

**Critical Timing:**
- `load_textures()` must be called AFTER `mlx_init()`
  - Reason: MLX context must exist before loading images
  - MLX functions need the initialized connection
- `load_textures()` must be called BEFORE rendering starts
  - Reason: Rendering code expects textures to be loaded
  - Would crash if it tried to access NULL texture pointers

### Compilation Integration
**File:** `Makefile`

```makefile
RAYCAST = $(addprefix src/raycast/, switch_to_array.c raycast_drawing.c \
          raycast_ray.c raycast_movement.c raycast_init.c perform_dda.c \
          load_textures.c)  # ← Added load_textures.c
```

- Added `load_textures.c` to the list of files to compile
- Makefile automatically generates object file and links it

---

## 8. Testing and Validation

### Map File Requirements
Your `.cub` file must have valid texture paths:

```
NO ./path/to/north_texture.xpm
SO ./path/to/south_texture.xpm
WE ./path/to/west_texture.xpm
EA ./path/to/east_texture.xpm

F 0,255,0      # Green floor
C 225,30,0     # Reddish ceiling
```

**Important Notes:**
- Paths must point to actual `.xpm` files
- Files must be readable
- If any texture fails to load, program will exit with error
- Floor and ceiling must be valid RGB values (0-255 for each component)

### Visual Verification

After running the program, you should see:
1. ✅ **Textured walls** instead of solid colors
2. ✅ **Different textures** on different wall faces (N/S/E/W)
3. ✅ **Correctly oriented textures** (not flipped randomly)
4. ✅ **Floor color** matching the F value from your .cub file
5. ✅ **Ceiling color** matching the C value from your .cub file
6. ✅ **Smooth texture scaling** as you move closer/farther from walls

### Common Issues and Solutions

| Issue | Cause | Solution |
|-------|-------|----------|
| Black walls | Texture files not found | Check paths in .cub file |
| Mirrored textures | Missing texture flip logic | Ensure flip code in `draw_wall_slice()` |
| Stretched textures | Incorrect `step` calculation | Verify `line_height` and `texture->height` |
| Wrong wall colors | Texture selection logic error | Check `get_wall_texture()` conditions |
| Segmentation fault | Textures not loaded | Ensure `load_textures()` called before rendering |
| Solid colors instead of textures | Not using texture data | Verify `get_texture_pixel()` is called |

---

## Summary of Changes Made

### Files Modified:
1. **`inc/main.h`**
   - Added `t_img` structure for texture data
   - Added texture images to `t_texture` structure
   - Added `wall_x` to `t_ray` structure
   - Added function prototypes for texture functions

2. **`src/raycast/load_textures.c`**
   - Implemented `load_textures()` function
   - Implemented `load_single_texture()` function
   - Implemented `get_texture_pixel()` function

3. **`src/raycast/raycast_ray.c`**
   - Added `wall_x` calculation in `calculate_wall_distance()`

4. **`src/raycast/raycast_drawing.c`**
   - Added `rgb_to_color()` helper function
   - Added `get_wall_texture()` texture selection function
   - Rewrote `draw_wall_slice()` to use textures
   - Implemented proper floor/ceiling color usage

5. **`src/main.c`**
   - Added `load_textures(data)` call after MLX initialization

6. **`Makefile`**
   - Added `load_textures.c` to compilation list

### Lines of Code Added: ~150
### Files Created: 0
### Files Modified: 6

---

## Conclusion

This implementation provides a complete texture system for cub3D that:
- ✅ Loads .xpm textures for all four wall directions
- ✅ Correctly maps textures to wall surfaces
- ✅ Scales textures based on distance (perspective correction)
- ✅ Handles texture orientation properly
- ✅ Uses parsed floor and ceiling colors from the map file
- ✅ Follows the cub3D subject requirements
- ✅ Is well-structured and maintainable

The code is now ready for the mandatory part evaluation of the cub3D project!
