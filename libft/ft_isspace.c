/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isspace.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmichaud <gmichaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/23 17:42:55 by gmichaud          #+#    #+#             */
/*   Updated: 2016/11/23 17:46:55 by gmichaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		ft_isspace(int c)
{
	if ((c >= 9 && c <= 13) || c == ' ')
		return (1);
	return (0);
}
