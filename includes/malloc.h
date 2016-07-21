/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiboitel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/10 14:59:27 by tiboitel          #+#    #+#             */
/*   Updated: 2016/07/21 07:13:21 by tiboitel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MALLOC_H
# define FT_MALLOC_H

#include <sys/time.h>
#include <unistd.h>
#include <errno.h>
#include <sys/mman.h>
#include <pthread.h>
#include <stddef.h>

#define TINY 512
#define SMALL 1536

typedef struct		s_header
{
	struct s_header	*prev;
	size_t			size;
	size_t			used;
}					t_header;

typedef struct		s_maps
{
	t_header		*tiny;
	t_header		*small;
	t_header		*large;
	pthread_mutex_t	mutex;
}					t_maps;

typedef struct		s_block
{
	void			*pointer;
	unsigned int	size:31;
	unsigned int	freed:1;
}					t_block;

void				*malloc(size_t size);
void				*calloc(size_t count, size_t size);
void				*realloc(void *ptr, size_t size);
void				*lalloc(size_t size, void **map);
void				show_alloc_mem(void);

void				set_malloc_error(void);

extern t_maps		g_maps;

#endif
