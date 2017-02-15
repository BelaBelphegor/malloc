/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiboitel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/23 14:40:47 by tiboitel          #+#    #+#             */
/*   Updated: 2017/02/15 22:36:10 by tiboitel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int			main(void)
{
	{
		int		i;
		char	*tmp 	= NULL;

		i = 0;
		while (i < 1024)
		{	
			tmp = malloc(sizeof(char) * 1024);
			free(tmp);
			tmp = NULL;
			i++;
		}
		tmp = realloc(NULL, sizeof(char) * 4096);
		if (!tmp)
			dprintf(1, "tmp: (null)\n");
		else
			dprintf(1, "tmp: !(null)\n");
		i = 0;
		while (i < 4096)
		{
			tmp[i] = 'a';
			i++;
		}
	}
}
