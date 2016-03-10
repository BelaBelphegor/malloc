/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiboitel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/10 14:59:27 by tiboitel          #+#    #+#             */
/*   Updated: 2016/03/10 15:35:28 by tiboitel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MALLOC_H
# define FT_MALLOC_H

#include <sys/mann.h>
#include <sys/time.h>
#include <sys/ressources.h>
#include <unistd.h>
#include <errno.h>

#define TINY 512
#define SMALL 1536

typedef enum		e_area_memory
{
	A_TINY, A_SMALL, A_LARGE
}					t_area_mem;

typedef struct		s_maps
{
	void			*tiny;
	void			*small;
	void			*large;
	unsigned int	size_int;
	unsigned int	size_small;
	size_t			max_size;
}					t_maps;

typedef struct		s_header
{
	struct s_header	*next;
	struct s_header	*prev;
	struct s_block	*first;
	void			*end;
	t_area_mem		format;
	size_t			size;
}					t_header;


typedef struct		s_block
{
	unsigned int	prev;
	size_t			next;
	unsigned char	flag;
}					t_block;

void				*malloc(size_t size);
void				*calloc(size_t count, size_t size);
void				*realloc(void *ptr, size_t size);
void				*lalloc(size_t size, void **map);
void				show_alloc_mem(void);

void				set_malloc_error(void);

extern t_maps		g_maps;

#endif
