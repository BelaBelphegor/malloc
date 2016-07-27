/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiboitel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/23 14:40:47 by tiboitel          #+#    #+#             */
/*   Updated: 2016/07/27 15:18:11 by tiboitel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

int			main(void)
{
	{
		char	*ptr;
		char	*tmp;
		int		i;

		tmp = malloc(100 * sizeof(char));
		i = 0;
		printf("--- SIMPLE TEST ---\n");
		ptr = (char *)malloc(sizeof(char) * 1024);
		printf("First allocation.\n");
		ptr[1023] = '\0';
		printf("Set pointer + 1024 bytes to '\\0'\n");
		while (i < 1024)
		{
			ptr[i] = (char)(48 + (23 % (i + 1)));
			i++;
		}
		printf("Content of 1024 allocated string: %s\n", ptr);
		printf("Free allocated memory.\n");
		free(ptr);
		ptr = NULL;
/*		printf("Value of ptr after free: %s\n", ptr);
		i = 0;
		while (i < 1024)
		{
			ptr = (char *)malloc(sizeof(char) * 1024);
			ptr[0] = 42;
			free(ptr);	
			i++;
		}
		free(tmp);
		while (1)
			; */
	}

}
