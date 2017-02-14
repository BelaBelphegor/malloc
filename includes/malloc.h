/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiboitel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/10 14:59:27 by tiboitel          #+#    #+#             */
/*   Updated: 2017/02/14 21:48:23 by tiboitel         ###   ########.fr       */
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

#define TINY 128
#define SMALL 1024

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
	pthread_mutex_t	mutex_free;
}					t_maps;

typedef struct		s_block
{
	void			*pointer;
	unsigned int	size:31;
	unsigned int	freed:1;
}					t_block;

typedef struct		s_maps_enquiry
{
	t_header		**head;
	t_block			*block;
	t_header		*header;
	void			*pointer;
}					t_maps_enquiry;

void				*malloc(size_t size);
void				*calloc(size_t count, size_t size);
void				*realloc(void *ptr, size_t size);
void				*lalloc(size_t size, void **map);
void				show_alloc_mem(void);
void				set_malloc_error(void);
void				release_header(t_header **head, t_header *current);

extern t_maps		g_maps;

#endif
