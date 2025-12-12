#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <stdlib.h>
#include "../../../Documents/mlx/mlx.h"

#define WIDTH 1280
#define HEIGHT 720

typedef struct s_player {
    int player_x_pos;
    int player_y_pos;
    bool up;
    bool down;
    bool left;
    bool right;
} t_player;

typedef struct s_game {
    void *mlx;
    void *win;
    void *img;
    char *ptr;
    int bpp;
    int size_line;
    int endian;
    t_player player;
} t_game;

void init_player(t_player *player) {
    player->player_x_pos = WIDTH / 2;
    player->player_y_pos = HEIGHT / 2;
    player->up = player->down = player->left = player->right = false;
}

void put_pix(int x, int y, int col, t_game *access) {
    if (x < 0 || y < 0 || x >= WIDTH || y >= HEIGHT)
        return;
    int tmp = y * access->size_line + x * access->bpp / 8;
    access->ptr[tmp] = (col) & 0xFF;
    access->ptr[tmp + 1] = (col >> 8) & 0xFF;
    access->ptr[tmp + 2] = (col >> 16) & 0xFF;
}

void draw_sq(int x, int y, int size, int color, t_game *access) {
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            put_pix(x + i, y + j, color, access);
}

int key_press(int key, t_game *game) {
    if (key == 65307) // ESC
        exit(0);
    else if (key == 119) // W
        game->player.up = true;
    else if (key == 115) // S
        game->player.down = true;
    else if (key == 97) // A
        game->player.left = true;
    else if (key == 100) // D
        game->player.right = true;
    return 0;
}

int key_release(int key, t_game *game) {
    if (key == 119)
        game->player.up = false;
    else if (key == 115)
        game->player.down = false;
    else if (key == 97)
        game->player.left = false;
    else if (key == 100)
        game->player.right = false;
    return 0;
}

void move_player(t_player *player) {
    int speed = 3;
    if (player->up) player->player_y_pos -= speed;
    if (player->down) player->player_y_pos += speed;
    if (player->left) player->player_x_pos -= speed;
    if (player->right) player->player_x_pos += speed;
}

int render(t_game *game) {
    game->img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
    game->ptr = mlx_get_data_addr(game->img, &game->bpp, &game->size_line, &game->endian);

    move_player(&game->player);
    draw_sq(game->player.player_x_pos, game->player.player_y_pos, 20, 0x00FF00, game);

    mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
    mlx_destroy_image(game->mlx, game->img);
    return 0;
}

void init_game(t_game *game) {
    game->mlx = mlx_init();
    game->win = mlx_new_window(game->mlx, WIDTH, HEIGHT, "CUBE3DOFFICIAL");

    init_player(&game->player);

    mlx_hook(game->win, 2, 1L << 0, key_press, game);
    mlx_hook(game->win, 3, 1L << 1, key_release, game);
    mlx_loop_hook(game->mlx, render, game);
}

int main() {
    t_game game;
    init_game(&game);
    mlx_loop(game.mlx);
    return 0;
}
