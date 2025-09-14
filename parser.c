/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clouden <clouden@student.42madrid.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 17:25:55 by clouden           #+#    #+#             */
/*   Updated: 2025/09/13 17:25:57 by clouden          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

bool	is_all_whitespace(const char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (false);
	while (s[i])
	{
		if (!(s[i] == ' '))
			return (false);
		i++;
	}
	if (i == 1)
		return (true);
	return (true);
}

static int	valid_number(char *str)
{
	int	i;
	int	dec;

	i = 0;
	dec = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (i == 0 && (str[i] == '+' || str[i] == '-'))
			i++;
		if (i != 0 && str[i] == '.' && dec == 0)
		{
			i++;
			dec = 1;
		}
		if (ft_isdigit(str[i]) != 1)
			return (0);
		i++;
	}
	return (1);
}

static char	**arg_separation(int argc, char *argv[])
{
	int		i;
	char	**strarr;
	char	**split;
	char	**joined;

	i = 2;
	strarr = NULL;
	while (i < argc)
	{
		if (is_all_whitespace(argv[i]))
			return (NULL);
		split = ft_split(argv[i], ' ');
		if (!split)
			return (ft_strarr_free(&strarr), NULL);
		joined = ft_strarr_join(strarr, split);
		ft_strarr_free(&split);
		if (!joined)
			return (ft_strarr_free(&strarr), NULL);
		ft_strarr_free(&strarr);
		strarr = joined;
		i++;
	}
	return (strarr);
}

static double	*digit_manager(t_parser *p)
{
	int			i;
	double		val;

	i = 0;
	p->len = ft_strarr_len(p->strarr);
	p->intarr = ft_calloc(p->len + 1, sizeof(int));
	if (!p->intarr)
		return (NULL);
	while (i < p->len)
	{
		if (!valid_number(p->strarr[i]))
		{
			ft_floatarr_free(&p->intarr);
			return (NULL);
		}
		val = ft_atof(p->strarr[i]);
		if (val > (__int128_t)INT_MAX || val < (__int128_t)INT_MIN)
		{
			ft_floatarr_free(&p->intarr);
			return (NULL);
		}
		p->intarr[i] = val;
		i++;
	}
	return (p->intarr);
}

t_parser	*parse_controller(int argc, char *argv[])
{
	t_parser	*p_data;

	p_data = ft_calloc(1, sizeof(t_parser));
	if (!p_data)
		return (NULL);
	p_data->strarr = arg_separation(argc, argv);
	if (!p_data->strarr)
	{
		free(p_data);
		return (NULL);
	}
	p_data->intarr = digit_manager(p_data);
	if (!p_data->intarr)
	{
		ft_strarr_free(&p_data->strarr);
		free(p_data->intarr);
		p_data->intarr = NULL;
		free(p_data);
		return (NULL);
	}
	return (p_data);
}

