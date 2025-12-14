# cub3D - Raycasting Game Engine

A 3D graphical representation using raycasting, inspired by Wolfenstein 3D.

## Recent Updates

### ✅ Texture System Implementation (December 14, 2025)

#### What Was Added:
1. **Complete Texture Loading System**
   - Loads .xpm texture files for all 4 wall directions (North, South, East, West)
   - Proper error handling for missing or invalid textures
   - Texture data stored in memory for fast rendering

2. **Texture Rendering Pipeline**
   - Wall textures mapped correctly to wall surfaces
   - Proper texture coordinate calculation (horizontal and vertical)
   - Texture scaling based on wall distance (perspective correction)
   - Correct texture orientation (automatic flipping for proper facing)

3. **Floor and Ceiling Colors**
   - Now properly uses RGB values parsed from .cub map file
   - Previously hardcoded colors now replaced with dynamic values
   - Format: `F R,G,B` for floor and `C R,G,B` for ceiling

## Compilation

```bash
make        # Compile the project
make clean  # Remove object files
make fclean # Remove object files and executable
make re     # Recompile everything
```

## Usage

```bash
./cub3D maps/map.cub
```

## Controls

- **W/A/S/D**: Move forward/left/backward/right
- **←/→ Arrow Keys**: Rotate camera left/right
- **ESC**: Exit the program
- **X (close button)**: Exit the program

## Map File Format

Example `.cub` file:

```
NO ./assets/north_texture.xpm
SO ./assets/south_texture.xpm
WE ./assets/west_texture.xpm
EA ./assets/east_texture.xpm

F 120,120,120    # Floor color (RGB)
C 70,70,255      # Ceiling color (RGB)

        1111111111111111111
        1000000000110000001
        1011000001110000001
        100100000000000W001
111111110110000001110000001
100000000011000001110111111
11110111111111011100000001
11110111111111011101010001
11000000110101011100000001
10000000000000001100000001
10000000000000001101010001
11000001110101011111011111
11110111 1110101 101111010001
11111111 1111111 111111111111
```

### Map Rules:
- `1` = Wall
- `0` = Empty space
- `N/S/E/W` = Player starting position and orientation
- Map must be surrounded by walls
- Only one player position allowed

## Project Structure

```
├── inc/
│   └── main.h              # Header file with all structures and prototypes
├── src/
│   ├── main.c              # Program entry point and initialization
│   ├── parse/              # Map file parsing and validation
│   │   ├── check_element.c # Parse textures and colors from .cub file
│   │   ├── map_check.c     # Validate map structure
│   │   ├── parse_file.c    # Main parsing logic
│   │   └── validate_map.c  # Map validation (walls, player, etc.)
│   ├── raycast/            # Raycasting engine
│   │   ├── load_textures.c     # ✨ NEW: Load .xpm textures into memory
│   │   ├── raycast_drawing.c   # ✨ UPDATED: Render with textures + colors
│   │   ├── raycast_ray.c       # ✨ UPDATED: Calculate texture coordinates
│   │   ├── raycast_init.c      # Initialize player direction vectors
│   │   ├── raycast_movement.c  # Handle player movement
│   │   ├── perform_dda.c       # DDA algorithm for ray-wall intersection
│   │   └── switch_to_array.c   # Convert linked list map to 2D array
│   └── utils/              # Utility functions
│       └── [various helper functions]
├── maps/
│   └── map.cub             # Example map file
└── assets/
    ├── m4sec.xpm           # Wall texture 1
    └── big_m4sec.xpm       # Wall texture 2
```

## Technical Implementation Details

### Raycasting Algorithm
1. **Ray Casting**: For each vertical stripe on screen, cast a ray from player position
2. **DDA Algorithm**: Digital Differential Analysis to find ray-wall intersections
3. **Distance Calculation**: Calculate perpendicular distance to prevent fish-eye effect
4. **Texture Mapping**: Map texture coordinates to wall surfaces
5. **Rendering**: Draw ceiling, textured wall, and floor for each screen column

### Texture System Architecture

#### Data Structures:
- **`t_img`**: Stores texture image data (MLX image pointer, pixel array, dimensions)
- **`t_texture`**: Contains all 4 wall textures + floor/ceiling colors
- **`t_ray`**: Includes `wall_x` for exact texture coordinate calculation

#### Key Functions:
- **`load_textures()`**: Loads all 4 .xpm files into memory
- **`get_texture_pixel()`**: Extracts color from texture at given coordinates
- **`get_wall_texture()`**: Selects correct texture based on wall orientation
- **`rgb_to_color()`**: Converts RGB array to hexadecimal color format

### Texture Coordinate Calculation:
```c
// Horizontal texture coordinate (which column of texture to use)
wall_x = fractional_part_of_wall_intersection  // 0.0 to 1.0
tex_x = (int)(wall_x * texture_width)           // Convert to pixel column

// Vertical texture coordinate (which row of texture to use)
step = texture_height / wall_height_on_screen   // How much to advance per pixel
tex_y = (int)current_position & (texture_height - 1)  // Wrap within texture
```

### Color System:
```c
// RGB to Hex conversion for MLX
color = (R << 16) | (G << 8) | B
// Example: RGB(225, 30, 0) → 0xE11E00
```

## Features Implemented

### Mandatory Part:
- ✅ Argument validation (.cub file required)
- ✅ Map parsing (walls, floor, ceiling, textures)
- ✅ Map validation (closed by walls, valid characters, single player)
- ✅ Player initialization with orientation
- ✅ Raycasting engine with DDA algorithm
- ✅ **Textured wall rendering** (all 4 directions)
- ✅ **Floor and ceiling colors from map file**
- ✅ Smooth WASD movement
- ✅ Smooth arrow key rotation
- ✅ Window management (ESC and X to close)
- ✅ Memory management (leak-free with custom allocator)

### Bonus Features (Not Yet Implemented):
- ⬜ Wall collisions
- ⬜ Minimap system
- ⬜ Doors that can open/close
- ⬜ Animated sprites
- ⬜ Mouse rotation

## Completion Status

**Current Progress: ~85%**

**Completed:**
- Core raycasting engine ✅
- Map parsing and validation ✅
- Texture loading and rendering ✅
- Floor/ceiling color system ✅
- Player movement and rotation ✅
- Memory management ✅

**Remaining for 100% Mandatory:**
- Verify all edge cases in map validation
- Test with various map configurations
- Ensure norm compliance

**For Bonus:**
- Wall collision detection
- Minimap rendering
- Door mechanics
- Sprite system

## Documentation

For an **extremely detailed explanation** of the texture loading and rendering implementation, including step-by-step breakdowns of every function, algorithm, and design decision, see:

📄 **[TEXTURE_IMPLEMENTATION.md](TEXTURE_IMPLEMENTATION.md)**

This document includes:
- Complete explanation of floor/ceiling color system
- Texture loading process (step-by-step)
- Texture coordinate calculation mathematics
- Wall texture selection logic
- Rendering pipeline with code examples
- Integration guide
- Troubleshooting and testing

## Authors

- yabarhda
- jait-chd

## Acknowledgments

- 42 Network for the project subject
- MiniLibX for graphics library
- Wolfenstein 3D for raycasting inspiration
