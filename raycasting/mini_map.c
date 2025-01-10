#include "raycasting.h"

/* Draws a square on the passed image starting from the passed x and y starting position and according to the passed size and colour */
void	draw_cell(mlx_image_t *image, int start_x, int start_y, int cell_size, uint32_t color)
{
    int y;
    int x;

    if (start_x >= WIDTH || start_y >= HEIGHT)
        return;
    y = 0;
    while (y < cell_size && (start_y + y) < HEIGHT)
    {
        x = 0;
        while (x < cell_size && (start_x + x) < WIDTH)
        {
            mlx_put_pixel(image, start_x + x, start_y + y, color);
            x++;
        }
        y++;
    }
}
// checks if starting positions are on the screen
// starts from top (y = 0) left (x = 0) going to the right edge of the cell
// always checks if still in bounds by adding starting position to the position within the cell
// draws a pixel at the starting position + the position within the cell thus getting the actual pixel on the screen

// void    draw_direction(t_cub *cub)
// {
//     float drawn_dir = 0;
//     float scale = 20;

//     if (cub->start_dir == 'N')
//     {
//         while (drawn_dir < scale)
//         {
//             int pixel_x = 16 + (cub->dir_player.x /* * drawn_dir */);
//             int pixel_y = 16 - (cub->dir_player.y * drawn_dir);
//             if (pixel_x >= 0 && pixel_x < 32 && pixel_y >= 0 && pixel_y < 32)
//             {
//                 printf(RED"drawing\n"WHITE);
//                 mlx_put_pixel(cub->player_image, pixel_x, pixel_y, 0xFF0AA0FF);
//             }
//             drawn_dir += 0.01;
//         }
//     }
// }

void    draw_direction(t_cub *cub)
{
    int pixel_x; // The starting x-pixel position of the direction vector
    int pixel_y; // The starting y-pixel position of the direction vector
    float step_y = 0;

    pixel_x = cub->pos_player.x * 64 + 32; // adjust to center
    pixel_y = cub->pos_player.y * 64 + 32; 
    if (!(cub->dir_image = mlx_new_image(cub->mlx, WIDTH / 2, HEIGHT)))
        printf("Error mlx_image\n");
    // check for start_dir = NSEW
    if (cub->start_dir == 'N')
    {
        while (step_y < 0.1)
        {
            pixel_y -= step_y;
            printf("pixel_y = %d\n", pixel_y);
            if (pixel_x >= 0 && pixel_x < (WIDTH / 2) && pixel_y >= 0 && pixel_y < HEIGHT)
            {
                // printf(RED"drawing\n"WHITE);
                mlx_put_pixel(cub->dir_image, pixel_x, pixel_y, 0xFF0AA0FF);
            }
            step_y += 0.001;
        }
    }
    if (cub->start_dir == 'S')
    {
        while (step_y < 1.1)
        {
            pixel_y += step_y;
            // printf("pixel_y = %d\n", pixel_y);
            // printf("step_y = %f\n", step_y);
            if (pixel_x >= 0 && pixel_x < (WIDTH / 2) && pixel_y >= 0 && pixel_y < HEIGHT)
            {
                // printf(RED"drawing\n"WHITE);
                mlx_put_pixel(cub->dir_image, pixel_x, pixel_y, 0xFF0AA0FF);
            }
            step_y += 0.001;
        }
    }
    mlx_image_to_window(cub->mlx, cub->dir_image, 0, 0);
    
}

void    draw_player(t_cub *cub)
{
    int player_pixel_x = cub->pos_player.x * 64 + 16;  // The starting pixel position of the player
    int player_pixel_y = cub->pos_player.y * 64 + 16; 

    printf(GREEN"playerpixel_x: %d\n"WHITE, player_pixel_x);
    printf(GREEN"playerpixel_y: %d\n"WHITE, player_pixel_y);
    draw_cell(cub->player_image, 0, 0, 32, 0xFFFF00FF); 
    // y=0 and x=0 refer to the top left corner of the player image !! not the map
    draw_direction(cub);
    if (mlx_image_to_window(cub->mlx, cub->player_image, player_pixel_x, player_pixel_y) == -1)
        printf("Error mlx_image to window\n");
    // this passes the entire image on to the game window at the coordinates of the player's starting position
    cub->player_image->instances[0].x = player_pixel_x;
    cub->player_image->instances[0].y = player_pixel_y;
    // cub->dir_image->instances[0].x = player_pixel_x;
    // cub->dir_image->instances[0].y = player_pixel_y;
}

void	create_map(t_cub *cub)
{
    int x;
    int y;
    int cell_size = 64;
    int start_x, start_y; // The actual pixel location on the window (map location * cell_size)

    cub->mlx = mlx_init(WIDTH, HEIGHT, "Minimap", true);
    if (cub->mlx == NULL)
    {
        printf("Failed to initialize mlx\n");
        exit(EXIT_FAILURE);
    }
    // intialises new Window
    cub->image = mlx_new_image(cub->mlx, WIDTH, HEIGHT);
    if (cub->image == NULL)
    {
        printf("Failed to create image\n");
        exit(EXIT_FAILURE);
    }
    // creates a new image on which the minimap will be portrayed
    if (!(cub->player_image = mlx_new_image(cub->mlx, 32, 32))) //
        printf("Error mlx_image\n");
    // creates a new image on which the player will be portrayed
    // it is 32x32 in size trying to draw beyond that will cause a segfault
    y = 0;
    while (cub->map[y] != NULL)
    {
        x = 0;
        while (cub->map[y][x] != '\0')
        {
            start_x = x * cell_size;
            start_y = y * cell_size;
            // determines where to start drawing
            if (cub->map[y][x] == '1')
                draw_cell(cub->image, start_x, start_y, cell_size - 1, 0x000000FF);
            else if (cub->map[y][x] == '0')
                draw_cell(cub->image, start_x, start_y, cell_size - 1, 0xFFFFFFFF);
            else if (is_player(cub->map[y][x], cub))
                draw_cell(cub->image, start_x, start_y, cell_size - 1, 0xFFFFFFFF); 
            else
                draw_cell(cub->image, start_x, start_y, cell_size, 0x00000000);
            x++;
        }
        y++;
    }
    // finds starting position and angle of player
    create_vectors(cub);
    // interates over map and draws cells according to 1 and 0
    mlx_image_to_window(cub->mlx, cub->image, 0, 0);
    // displays image on window at x = 0 and y = 0
    draw_player(cub);
}

void ft_hook(void* param)
{
	t_cub *cub = param;

	if (mlx_is_key_down(cub->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(cub->mlx);
	if (mlx_is_key_down(cub->mlx, MLX_KEY_UP) && (cub->player_image->instances[0].y >= 1) && cub->map[(cub->player_image->instances[0].y - 5) / 64][cub->player_image->instances[0].x / 64] != '1')
    {
		cub->player_image->instances[0].y -= 5;
        cub->dir_image->instances[0].y -= 5;
    }
	if (mlx_is_key_down(cub->mlx, MLX_KEY_DOWN) && (cub->player_image->instances[0].y <= HEIGHT - 31) && cub->map[(cub->player_image->instances[0].y + 36) / 64][cub->player_image->instances[0].x / 64] != '1')
    {
		cub->player_image->instances[0].y += 5;
        cub->dir_image->instances[0].y += 5;
    }
	if (mlx_is_key_down(cub->mlx, MLX_KEY_LEFT) && (cub->player_image->instances[0].x >= 1) && cub->map[cub->player_image->instances[0].y / 64][(cub->player_image->instances[0].x - 5) / 64] != '1')
    {
		cub->player_image->instances[0].x -= 5;
        cub->dir_image->instances[0].x -= 5;
    }
	if (mlx_is_key_down(cub->mlx, MLX_KEY_RIGHT) && (cub->player_image->instances[0].x <= (WIDTH / 2) - 31) && cub->map[(cub->player_image->instances[0].y) / 64][(cub->player_image->instances[0].x + 36) / 64] != '1')
    {
		cub->player_image->instances[0].x += 5;
        cub->dir_image->instances[0].x += 5;
    }
    // printf("x = %d\n", cub->player_image->instances[0].x);
    // printf("y = %d\n", cub->player_image->instances[0].y);
}

// values for the boarder have to be changed later, although the program should also always track the current cell and check if the cell is a 1

int main()
{
    t_cub   cub;

    char	*map[] = {
        "1111111111",
        "1000000001",
        "1000000001",
        "1000000001",
        "1000000101",
        "1000000001",
        "100000S001",
        "1000000001",
        "1000000101",
        "1111111111",
        NULL
    };

    cub.map = map;
    // stores psyeudo map for testing
    create_map(&cub);
    // draws map and player
    // raycaster(&cub);
    mlx_loop_hook(cub.mlx, ft_hook, &cub);
    // handles key presses
    mlx_loop(cub.mlx);
    // handles window

    return 0;
}
