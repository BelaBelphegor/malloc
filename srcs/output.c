/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiboitel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/27 14:43:52 by tiboitel          #+#    #+#             */
/*   Updated: 2016/07/27 14:54:43 by tiboitel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <malloc.h>
#include <tools.h>

void	ft_putpointer(void *pointer)
{
	size_t	n;
	char	c;
	
	n = (size_t)pointer;
	if (n >= 16)
		ft_putpointer((void *)(n / 16));
	else
		write(1, "0x", 2);
	n %= 16;
	if (n >= 10)
		c = 'A' + n - 10;
	else
		c = '0' + n;
	write(1, &c, 1);
}

void	ft_putnbr(size_t size)
{
	size_t	n;
	char	c;

	n = (size_t)size;
	if (n >= 10)
		ft_putnbr(n / 10);
	n %= 10;
	c = '0'+ n;
	write(1, &c, 1);
}

void	ft_putstr(const char *s)
{
	int		i;

	i = 0;
	while (s[i])
		i++;
	write(1, s, i);
}
