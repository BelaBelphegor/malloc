/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiboitel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/10 15:26:28 by tiboitel          #+#    #+#             */
/*   Updated: 2016/03/10 17:07:32 by tiboitel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <malloc.h>

t_maps			g_maps = {NULL, NULL, NULL, 0, 0, 0};

static void		init_global(void)
{
	struct rlimit		rlp;

	g_maps.size_tiny = TINY;
	g_maps.size_small = SMALL;
	if (!getrlimit(RLIMIT_DATA, &rlp))
		g_maps.max_size = rlp.rlim_cur;
}

void			*malloc(size_t size)
{
	void		*ptr;

	if (!g_maps.tiny && !g_maps.small && g_maps.small)
		init_global();
	/*
	 * Implementation explanation:
	 * - Si la taille totale (size + sizeof(t_header)) est superier a la taille maximale || ou que la taille depasse la taille max retourner null
	 *  - On regarde si le malloc est un tiny, un small ou un large
	 *  - Si le ptr existe decaler de la taille d'un block
	 */
	if (size + sizeof(t_header) >= g_maps.max_size)
		return (NULL);
	size += sizeof(t_block);
	if (ptr)
		ptr = (void *)ptr + sizeof(t_block);
	size = (size <= 0) ? 1 : size;
	return (ptr);
}
