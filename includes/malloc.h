/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiboitel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/10 14:59:27 by tiboitel          #+#    #+#             */
/*   Updated: 2017/02/16 18:13:31 by tiboitel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MALLOC_H
# define FT_MALLOC_H

# include <sys/time.h>
# include <unistd.h>
# include <errno.h>
# include <sys/mman.h>
# include <pthread.h>
# include <stddef.h>

# define TINY 128
# define SMALL 1024

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
	pthread_mutex_t	mutex_realloc;
	pthread_mutex_t	mutex_show;
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

size_t				get_memory_pool_size(t_block *block);
t_block				*get_memory_pool_block(t_header *header, t_block *block,
		size_t size, void *pointer);
void				delete_memory_pool_block(t_block *block, size_t count);
void				*malloc(size_t size);
void				*calloc(size_t count, size_t size);
void				*realloc(void *ptr, size_t size);
void				free(void *ptr);
void				show_alloc_mem(void);
void				set_malloc_error(void);
void				release_header(t_header **head, t_header *current);
int					header_check_integrity(t_header *header, size_t size);
void				ft_write_total(size_t size);

extern t_maps		g_maps;

#endif
