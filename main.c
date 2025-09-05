/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clouden <clouden@student.42madird.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 20:30:25 by clouden           #+#    #+#             */
/*   Updated: 2025/09/01 20:30:28 by clouden          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int     change_color(t_data *data)
{
    // Fill the window with the current color
//  mlx_clear_window(data->mlx, data->win);
    mlx_string_put(data->mlx, data->win, 150, 150, data->color, "Color Changing Window!");

    // Cycle through some basic colors: RED, GREEN, BLUE
    if (data->color == 0xFF0000)        // If it's red
        data->color = 0x00FF00;        // Change to green
    else if (data->color == 0x00FF00)   // If it's green
        data->color = 0x0000FF;        // Change to blue
    else
        data->color = 0xFF0000;        // Otherwise, go back to red

    return (0);
}

int     button_press(int button, int x, int y)
{
    if (button == 1)
        printf("Left mouse button pressed at (%d, %d)!\n", x, y);
    else if (button == 3)
        printf("Right mouse button pressed at (%d, %d)!\n", x, y);
	else if (button == 4)
        printf("Zoom in scroll at (%d, %d)!\n", x, y);
	else if (button == 5)
        printf("Zoom out scroll at (%d, %d)!\n", x, y);

    return (0);
}

int	handle_input(int keysym, t_data *data)
{
    //Check the #defines
    //find / -name keysym.h 2>/dev/null
    //find / -name keysymdef.h 2>/dev/null
    if (keysym == XK_Escape)
    {
        printf("The %d key (ESC) has been pressed\n\n", keysym);
        mlx_destroy_window(data->mlx, data->win);
        mlx_destroy_display(data->mlx);
        free(data->mlx);
        exit(1);
    }
    printf("The %d key has been pressed\n\n", keysym);
    return (0);
}

//Line len is in bytes. WIDTH 800 len_line ~3200 (can differ for alignment)
void	put_pixel(t_img *img, int x, int y, int color)
{
	int	offset;

	offset = (img->line_len * y) + (x * (img->bits_per_pixel / 8));	

	*((unsigned int *)(offset + img->img_pixels_ptr)) = color;
}

void	color_screen(t_data *data, int color)
{
	int y = 0;
	while (y < HEIGHT)	
	{
		int x = 0;
		while (x < WIDTH)
		{
			put_pixel(&data->img, x, y, color);
			++x;
		}
		++y;
	}
}

int cleanup(void *param)
{
	t_data *data = (t_data *)param;
	if (data->img.img_ptr)
		mlx_destroy_image(data->mlx, data->img.img_ptr);
	if (data->win)
		mlx_destroy_window(data->mlx, data->win);
	if (data->mlx)
		mlx_destroy_display(data->mlx);
	if (data->mlx)
		free(data->mlx); 
	exit(0);
}

int	f(int keysym, t_data *data)
{
	printf("The %d key has been pressed\n\n", keysym);
	if (keysym == XK_r)
	{
		color_screen(data, 0x011616);
	}
	else if (keysym == XK_g)
	{
		color_screen(data, 0x054b4c);
	}
	else if (keysym == XK_b)
	{
		color_screen(data, 0x0dbdbf);
	}	
	else if (keysym == XK_Escape)
	{
		printf("The %d key (ESC) has been pressed\n\n", keysym);
		cleanup((void *)data);
	}
	

	// push the READY image to window
	// the last parameters are the offset image-window
	mlx_put_image_to_window(data->mlx,
							data->win, 
							data->img.img_ptr, 
							0, 0);

	return 0;
}

int main(void)
{
	t_data data;

	data.mlx = mlx_init();
	if (!data.mlx)
		return (1);
	data.win = mlx_new_window(data.mlx, WIDTH, HEIGHT, "MyWindow");
	if (!data.win)
	{
		mlx_destroy_display(data.mlx);
		free(data.mlx);
		return (1);
	}
	data.img.img_ptr = mlx_new_image(data.mlx, WIDTH, HEIGHT);
	data.img.img_pixels_ptr = mlx_get_data_addr(data.img.img_ptr, &data.img.bits_per_pixel, &data.img.line_len, &data.img.endian);
	printf("Line_len %d <-> WIDTH%d HEIGHT%d\n"
			"bpp %d\n"
			"endian %d\n", data.img.line_len, WIDTH, HEIGHT, data.img.bits_per_pixel, data.img.endian);
	mlx_hook(data.win, 
            ButtonPress,
            ButtonPressMask,
            &button_press, 
            &data);
	mlx_hook(data.win, DestroyNotify, 0, &cleanup, &data);
	// mlx_loop_hook(data.mlx, change_color, &data);
	mlx_key_hook(data.win, f, &data);
	mlx_loop(data.mlx);
	// mlx_key_hook(data.win, handle_input, &data);
	// mlx_destroy_window(data.mlx, data.win);
	// mlx_destory_display(data.mlx);
	// free(data.mlx);
}

// int     main(void)
// {
//     t_data  data;

//     data.mlx = mlx_init();
// 	if (!data.mlx)
// 		return (1);
//     data.win = mlx_new_window(data.mlx, WIDTH, HEIGHT, "Sample Window");
//     data.color = 0xFF0000;  // Start with red color

//     // mlx_key_hook(data.win,
//     //             f, 
//     //             &data);

//     //mlx_loop_hook is one hook that is triggered when there's no event processed.
//     //Cool to have a continuous rendering on the screen
//    	mlx_loop_hook(data.mlx,
//                change_color,
//                &data);
//     mlx_loop(data.mlx);

//     return (0);
// }