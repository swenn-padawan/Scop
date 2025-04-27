/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_obj.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stetrel <stetrel@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 19:27:50 by stetrel           #+#    #+#             */
/*   Updated: 2025/04/27 20:25:11 by stetrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include <stdio.h>

static void	*getDataAddress(const char *file)
{
	int			file_fd;
	void		*file_ptr;
	struct stat	st;

	file_fd = open(file, O_RDONLY);
	if (file_fd == -1) return (NULL); //TODO (error management)
	if (stat(file, &st) == -1) return (NULL); //same
	file_ptr = mmap(NULL, st.st_size, PROT_READ, MAP_PRIVATE, file_fd, 0);
	if (file_ptr == (void *)-1) return (NULL); //same
	return (file_ptr);
}

t_vertex	*SCOP_parseFile(const char *file)
{
	UNUSED t_vertex	*vertex = {0};
	void			*file_ptr;

	file_ptr = getDataAddress(file);
	if (!file) return (NULL); //TODO (error management)
	
	printf("data = %s\n", (char *)file_ptr);


	return (vertex);
}

int main(UNUSED int argc, char **argv){
	SCOP_parseFile(argv[1]);
}


