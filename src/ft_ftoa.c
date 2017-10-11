/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ftoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmichaud <gmichaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/03 09:26:00 by gmichaud          #+#    #+#             */
/*   Updated: 2017/10/10 18:35:36 by gmichaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static int	num_len(long long n)
{
	int len;

	len = 0;
	if (n == 0)
		return (1);
	while (n != 0)
	{
		n /= 10;
		len++;
	}
	return (len);
}

static char	*get_decimal(double f, long long n, double prec)
{
	long long	d;
	int			len;
	size_t		i;
	char		*s1;
	char		*s2;

	d = llabs((long long)((fabs(f) - (double)n) * pow(10, prec)));
	if (!(s1 = ft_strnew(sizeof(*s1) * prec)))
		return (NULL);
	len = num_len(d);
	i = 0;
	while (i < prec - len)
		s1[i++] = '0';
	s2 = ft_lltoa(d);
	ft_strcat(s1, s2);
	free(s2);
	return (s1);
}

static char	*join_parts(double f, double prec, char *part1, char *part2)
{
	int		sign;
	char	*dest;

	sign = (f < 0) ? 1 : 0;
	if (!(dest =
		ft_strnew(sizeof(char) * (num_len((long long)f) + prec + sign + 1))))
		return (NULL);
	if (sign == 1)
		dest[0] = '-';
	ft_strcat(dest, part1);
	ft_strcat(dest, ".");
	ft_strcat(dest, part2);
	ft_strdel(&part1);
	ft_strdel(&part2);
	return (dest);
}

char		*ft_ftoa(double f, double prec)
{
	long long	n;
	char		*part1;
	char		*part2;

	n = llabs((long long)f);
	if (!(part1 = ft_lltoa(n)))
		return (NULL);
	if (!(part2 = get_decimal(f, n, prec)))
		return (NULL);
	return (join_parts(f, prec, part1, part2));
}
