/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiboitel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/10 15:25:29 by tiboitel          #+#    #+#             */
/*   Updated: 2017/02/16 18:10:05 by tiboitel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_TOOLS_H
# define FT_TOOLS_H

# include "malloc.h"
# ifdef DEBUG
#  define D(x) x
# else
#  define D(x)
# endif

t_maps_enquiry		maps_enquiry(void *pointer);
void				*ft_memcpy(void *dst, const void *src, size_t n);
void				ft_putpointer(void *pointer);
void				ft_putnbr(size_t size);
void				ft_putstr(const char *s);
void				ft_putendl(const char *s);
#endif
