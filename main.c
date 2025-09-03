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

int	handle_input(int keysym, t_mlx_data *data)
{
    //Check the #defines
    //find / -name keysym.h 2>/dev/null
    //find / -name keysymdef.h 2>/dev/null
    if (keysym == XK_Escape)
    {
        printf("The %d key (ESC) has been pressed\n\n", keysym);
        mlx_destroy_window(data->mlx_ptr, data->win_ptr);
        mlx_destroy_display(data->mlx_ptr);
        free(data->mlx_ptr);
        exit(1);
    }
    printf("The %d key has been pressed\n\n", keysym);
    return (0);
}

int	main(void)
{
    t_mlx_data	data;

    data.mlx_ptr = mlx_init();
    if (data.mlx_ptr == NULL)
        return (1);
    data.win_ptr = mlx_new_window(data.mlx_ptr, 
                                WIDTH, 
                                HEIGHT,
                                "My first window!");
    if (data.win_ptr == NULL)
    {
        mlx_destroy_display(data.mlx_ptr);
        free(data.mlx_ptr);
        return (1);
    }

    /*
     * HOOKS
     *  "Hooking into events" (react to events)
     * When i press a key, handle_input() is triggered
     * 💡 Every event is linked to its own prototype handler 💡
    */
    mlx_key_hook(data.win_ptr, 
                handle_input, 
                &data);

    // Leave the control to the EVENT LOOP
    mlx_loop(data.mlx_ptr);
}


// int	main()
// {
// 	void	*mlx_connection;
// 	// void	*mlx_window;
// 	void    *window1;
//     void    *window2;


// 	mlx_connection = mlx_init();
// 	if (!mlx_connection)
// 		return (1);
// 	// mlx_window = mlx_new_window(mlx_connection,
// 	// 							HEIGHT,
// 	// 							WIDTH,
// 	// 							"My window");

// 	window1 = mlx_new_window(mlx_connection, WIDTH, HEIGHT, "Window 1");
//     if (!window1)
//     {
//         mlx_destroy_display(mlx_connection);
//         free(mlx_connection);
//         return (1);
//     }

//     window2 = mlx_new_window(mlx_connection, WIDTH, HEIGHT, "Window 2");
//     if (!window2)
//     {
//         mlx_destroy_window(mlx_connection, window1);
//         mlx_destroy_display(mlx_connection);
//         free(mlx_connection);
//         return (1);
//     }

// 	// if (!mlx_window)
//     // {
//     //     mlx_destroy_display(mlx_connection); // Cleanup MLX connection
//     //     free(mlx_connection);
//     //     return (1);
//     // }
// 	mlx_loop(mlx_connection);

// 	return (0);
// }
