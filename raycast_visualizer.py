import pygame
import math

# Map settings
MAP = [
    "111111",
    "100001",
    "101101",
    "100001",
    "111111"
]
TILE_SIZE = 64
MAP_WIDTH = len(MAP[0])
MAP_HEIGHT = len(MAP)

# Player settings
player_x = 2.5 * TILE_SIZE
player_y = 2.5 * TILE_SIZE
player_angle = math.pi / 4  # 45 degrees

# Ray casting settings
FOV = math.pi / 3  # 60 degrees
NUM_RAYS = 60
MAX_DEPTH = 300

# Colors
WHITE = (255, 255, 255)
GRAY = (100, 100, 100)
RED = (255, 0, 0)
BLUE = (0, 0, 255)
GREEN = (0, 255, 0)
BLACK = (0, 0, 0)

def draw_map(screen):
    for y, row in enumerate(MAP):
        for x, cell in enumerate(row):
            color = GRAY if cell == '1' else WHITE
            pygame.draw.rect(
                screen, color,
                (x * TILE_SIZE, y * TILE_SIZE, TILE_SIZE, TILE_SIZE)
            )
            pygame.draw.rect(
                screen, BLACK,
                (x * TILE_SIZE, y * TILE_SIZE, TILE_SIZE, TILE_SIZE), 1
            )

def cast_rays(screen, px, py, pa):
    start_angle = pa - FOV / 2
    for ray in range(NUM_RAYS):
        ray_angle = start_angle + ray * FOV / NUM_RAYS
        for depth in range(MAX_DEPTH):
            target_x = px + math.cos(ray_angle) * depth
            target_y = py + math.sin(ray_angle) * depth
            map_x = int(target_x / TILE_SIZE)
            map_y = int(target_y / TILE_SIZE)
            if 0 <= map_x < MAP_WIDTH and 0 <= map_y < MAP_HEIGHT:
                if MAP[map_y][map_x] == '1':
                    pygame.draw.line(
                        screen, RED,
                        (px, py), (target_x, target_y), 1
                    )
                    break

def draw_player(screen, px, py, pa):
    pygame.draw.circle(screen, BLUE, (int(px), int(py)), 8)
    # Draw direction line
    dx = math.cos(pa) * 30
    dy = math.sin(pa) * 30
    pygame.draw.line(screen, GREEN, (px, py), (px + dx, py + dy), 3)

def main():
    pygame.init()
    screen = pygame.display.set_mode(
        (MAP_WIDTH * TILE_SIZE, MAP_HEIGHT * TILE_SIZE)
    )
    clock = pygame.time.Clock()
    running = True
    angle = player_angle
    x, y = player_x, player_y

    while running:
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                running = False

        keys = pygame.key.get_pressed()
        if keys[pygame.K_LEFT]:
            angle -= 0.03
        if keys[pygame.K_RIGHT]:
            angle += 0.03
        if keys[pygame.K_UP]:
            x += math.cos(angle) * 2
            y += math.sin(angle) * 2
        if keys[pygame.K_DOWN]:
            x -= math.cos(angle) * 2
            y -= math.sin(angle) * 2

        screen.fill(BLACK)
        draw_map(screen)
        cast_rays(screen, x, y, angle)
        draw_player(screen, x, y, angle)
        pygame.display.flip()
        clock.tick(60)

    pygame.quit()

if __name__ == "__main__":
    main()
