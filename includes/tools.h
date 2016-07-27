/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiboitel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/10 15:25:29 by tiboitel          #+#    #+#             */
/*   Updated: 2016/07/27 14:49:11 by tiboitel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_TOOL_H
# define FT_TOOL_H

#include "malloc.h"

t_maps_enquiry		maps_enquiry(void *pointer);
void				ft_putpointer(void *pointer);
void				ft_putnbr(size_t size);
void				ft_putstr(const char *s);
#endif
