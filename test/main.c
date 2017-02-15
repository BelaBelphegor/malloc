/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiboitel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/23 14:40:47 by tiboitel          #+#    #+#             */
/*   Updated: 2017/02/15 21:12:52 by tiboitel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int			main(void)
{
	{
		int		i;
		void	*tmp 	= NULL;

		i = 0;
		while (i < 1024)
		{	
			tmp = malloc(sizeof(char) * 1024);
			free(tmp);
			i++;
		}
		show_alloc_mem();
	}
}
