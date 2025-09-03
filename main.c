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
#define	SIDE_LEN		800
#define MALLOC_ERROR	1

// int f(int keysym)
// {
//     printf("Pressed %d\n", keysym);
//     //sleep to appreciate loop_hook stopping
//     sleep(1);
//     return 1;
// }

// int     change_color(t_data *data)
// {
//     // Fill the window with the current color
// //  mlx_clear_window(data->mlx, data->win);
//     mlx_string_put(data->mlx, data->win, 150, 150, data->color, "Color Changing Window!");

//     // Cycle through some basic colors: RED, GREEN, BLUE
//     if (data->color == 0xFF0000)        // If it's red
//         data->color = 0x00FF00;        // Change to green
//     else if (data->color == 0x00FF00)   // If it's green
//         data->color = 0x0000FF;        // Change to blue
//     else
//         data->color = 0xFF0000;        // Otherwise, go back to red

//     return (0);
// }

// void	my_pixel_put(t_img *img, int x, int y, int color)
// {
// 	int	offset;

// 	//🚨 Line len is in bytes. WIDTH 800 len_line ~3200 (can differ for alignment)
// 	offset = (img->line_len * y) + (x * (img->bits_per_pixel / 8));	

// 	*((unsigned int *)(offset + img->img_pixels_ptr)) = color;
// }

// void	color_screen(t_data *data, int color)
// {
// 	for (int y = 0; y < WIDTH; ++y)	
// 	{
// 		for (int x = 0; x < HEIGHT; ++x)
// 		{
// 			/*
// 			 * This function is much faster than the library one🏻
// 			 * 	~Buffer in the image and push only when ready-> No flickering effect
// 			*/
// 			my_pixel_put(&data->img,
// 						x, 
// 						y, 
// 						color);
// 		}
// 	}
// }

// int	f(int keysym, t_data *data)
// {

// 	if (keysym == XK_r)
// 	{
// 		color_screen(data, 0xff0000);
// 	}
// 	else if (keysym == XK_g)
// 	{
// 		color_screen(data, 0xff00);
// 	}
// 	else if (keysym == XK_b)
// 	{
// 		color_screen(data, 0xff);
// 	}	
// 	else if (keysym == XK_Escape)
// 		exit(1);

// 	// push the READY image to window
// 	// the last parameters are the offset image-window
// 	mlx_put_image_to_window(data->mlx,
// 							data->win, 
// 							data->img.img_ptr, 
// 							0, 0);

// 	return 0;
// }


// int     button_press(int button, int x, int y)
// {
//     if (button == 1)
//         printf("Left mouse button pressed at (%d, %d)!\n", x, y);
//     else if (button == 3)
//         printf("Right mouse button pressed at (%d, %d)!\n", x, y);

//     return (0);
// }

// int	handle_input(int keysym, t_data *data)
// {
//     //Check the #defines
//     //find / -name keysym.h 2>/dev/null
//     //find / -name keysymdef.h 2>/dev/null
//     if (keysym == XK_Escape)
//     {
//         printf("The %d key (ESC) has been pressed\n\n", keysym);
//         mlx_destroy_window(data->mlx, data->win);
//         mlx_destroy_display(data->mlx);
//         free(data->mlx);
//         exit(1);
//     }
//     printf("The %d key has been pressed\n\n", keysym);
//     return (0);
// }

// int	main(void)
// {
//     t_data	data;

//     data.mlx = mlx_init();
//     if (data.mlx == NULL)
//         return (1);
//     data.win = mlx_new_window(data.mlx, WIDTH, HEIGHT,"My first window!");
//     if (data.win == NULL)
//     {
//         mlx_destroy_display(data.mlx);
//         free(data.mlx);
//         return (1);
//     }
// 	// data.color = 0xFF0000;
// 	data.img.img_ptr = mlx_new_image(data.mlx, WIDTH, HEIGHT);
// 	data.img.img_pixels_ptr = mlx_get_data_addr(data.img.img_ptr,
// 												&data.img.bits_per_pixel,
// 												&data.img.line_len,
// 												&data.img.endian);
												
// 	printf("Line_len %d <-> WIDTH %d\n"
// 			"bpp %d\n"
// 			"endian %d\n", data.img.line_len, WIDTH, data.img.bits_per_pixel, data.img.endian);

	

// 	mlx_key_hook(data.win,
//                 f, 
//                 &data);

//     // mlx_key_hook(data.win, 
//     //             handle_input, 
//     //             &data);
	
// 	// mlx_loop_hook(data.mlx,
// 	// 			change_color,
// 	// 			&data);

// 	// mlx_hook(data.win, 
//     //         ButtonPress, 
//     //         ButtonPressMask,
//     //         &button_press, 
//     //         &data);

//     // Leave the control to the EVENT LOOP
//     mlx_loop(data.mlx);
// 	return (0);
// }
// typedef struct s_img
// {
// 	void	*img_ptr;
// 	char	*img_pixels_ptr;
// 	int		bits_per_pixel;
// 	int		endian;
// 	int		line_len;
// }				t_img;

// /*
//  * This struct contains all the mlx stuff 
//  * and the image where i will buffer my pixels
// */
// typedef struct	s_var
// {
// 	void	*mlx;
// 	void	*win;
// 	t_img	img;
// }				t_var;


// /*
//  * Plot in a 2D image the pixel
// */
// void	my_pixel_put(t_img *img, int x, int y, int color)
// {
// 	int	offset;

// 	//🚨 Line len is in bytes. WIDTH 800 len_line ~3200 (can differ for alignment)
// 	offset = (img->line_len * y) + (x * (img->bits_per_pixel / 8));	

// 	*((unsigned int *)(offset + img->img_pixels_ptr)) = color;
// }

// /*
//  * 🔥 my_pixel_put
// */
// void	color_screen(t_var *data, int color)
// {
// 	for (int y = 0; y < SIDE_LEN; ++y)	
// 	{
// 		for (int x = 0; x < SIDE_LEN; ++x)
// 		{
// 			/*
// 			 * This function is much faster than the library one🏻
// 			 * 	~Buffer in the image and push only when ready-> No flickering effect
// 			*/
// 			my_pixel_put(&data->img,
// 						x, 
// 						y, 
// 						color);
// 		}
// 	}
// }

// /*
//  * This time i plug color in hexadecimal directly
//  * easy vanilla
// */
// int	f(int keysym, t_var *data)
// {

// 	if (keysym == XK_r)
// 	{
// 		color_screen(data, 0xff0000);
// 	}
// 	else if (keysym == XK_g)
// 	{
// 		color_screen(data, 0xff00);
// 	}
// 	else if (keysym == XK_b)
// 	{
// 		color_screen(data, 0xff);
// 	}	
// 	else if (keysym == XK_Escape)
// 		exit(1);

// 	// push the READY image to window
// 	// the last parameters are the offset image-window
// 	mlx_put_image_to_window(data->mlx,
// 							data->win, 
// 							data->img.img_ptr, 
// 							0, 0);

// 	return 0;
// }


// /*
//  * All the checks for errors like 
//  * 		
//  * 	~if (vars.mlx == NULL) exit(1);
//  *
//  * are not written to not clog te code!
//  * But u know this stuff is a necessary evil 😂
// */
// int	main()
// {
// 	t_var	vars;

// 	vars.mlx = mlx_init();
// 	vars.win = mlx_new_window(vars.mlx,
// 								SIDE_LEN, 
// 								SIDE_LEN, 
// 								"My window");
	

// 	// Code to create an image and get the related DATA
// 	vars.img.img_ptr = mlx_new_image(vars.mlx,
// 									SIDE_LEN, 
// 									SIDE_LEN);
// 	vars.img.img_pixels_ptr = mlx_get_data_addr(vars.img.img_ptr, 
// 												&vars.img.bits_per_pixel, 
// 												&vars.img.line_len, 
// 												&vars.img.endian);


// 	printf("Line_len %d <-> SIDE_LEN %d\n"
// 			"bpp %d\n"
// 			"endian %d\n", vars.img.line_len, SIDE_LEN, vars.img.bits_per_pixel, vars.img.endian);

// 	mlx_key_hook(vars.win, 
// 				f,
// 				&vars);
// 	mlx_loop(vars.mlx);
// }


int	main(int argc, char *argv[])
{
	if (2 == argc && !ft_strncmp(argv[1], "mandlebrot", 10)
		|| 4 == argc && !ft_strncmp(argv[1], "julia", 5))
	{


	}	
	else
	{
		ft_putstr_fd("Error" ,STDERR_FILENO);
		exit(EXIT_FAILURE);
	}

}