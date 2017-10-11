/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_e_ftoa.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmichaud <gmichaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/06 09:38:23 by gmichaud          #+#    #+#             */
/*   Updated: 2017/10/09 09:49:50 by gmichaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static int	get_pow(double *f)
{
	int		power;
	int		sign;

	power = 0;
	sign = (*f < 0) ? -1 : 1;
	if (*f == 0)
		return (power);
	*f = fabs(*f);
	while (*f > 10 || *f < 1)
	{
		*f = (*f < 1) ? *f * 10 : *f / 10;
		power++;
	}
	*f *= sign;
	return (power);
}

static char	*add_pow(char *dest, int power, int len)
{
	char	*part2;

	if (!(part2 = ft_itoa(power)))
		return (NULL);
	if (power > 10)
		ft_strcat(dest, part2);
	else
	{
		dest[len + 2] = '0';
		ft_strcat(dest, part2);
	}
	free(part2);
	return (dest);
}

char		*ft_e_ftoa(double f, int prec)
{
	int		sign;
	int		len;
	int		power;
	char	*part1;
	char	*dest;

	sign = (f > -1 && f < 1 && f != 0) ? 1 : 0;
	power = get_pow(&f);
	if (!(part1 = ft_ftoa(f, prec)))
		return (NULL);
	len = ft_strlen(part1);
	if (!(dest = ft_strnew(sizeof(*dest) * (len + 4))))
	{
		free(part1);
		return (NULL);
	}
	ft_strcat(dest, part1);
	free(part1);
	dest[len] = 'e';
	dest[len + 1] = sign ? '-' : '+';
	return (add_pow(dest, power, len));
}
