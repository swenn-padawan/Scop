/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_obj.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stetrel <stetrel@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 19:27:50 by stetrel           #+#    #+#             */
/*   Updated: 2025/04/28 00:14:22 by swenn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

#define NB_IDENTIFIERS 7

static	char **getIdentifiersList(void)
{
	static	char	*list[] = {"#", "v", "vf", "vt", "vn", "vp", "f", "\0"};
	return (list);
}

UNUSED
static bool	isValidIdentifier(char *id)
{
	char	**id_list = getIdentifiersList();

	while (*id_list && ft_strcmp(id, *id_list))
		id_list++;
	return (*id_list != NULL);
}

static void	*getDataAddress(size_t size, int file_fd)
{
	void		*file_ptr;

	file_ptr = mmap(NULL, size, PROT_READ, MAP_PRIVATE, file_fd, 0);
	if (file_ptr == (void *)-1) return (NULL); //same
	return (file_ptr);
}

static size_t	line_len(char *file)
{
	size_t	len;

	len = 0;
	for (; file[len] && file[len] != '\n'; len++) ;
	return (len);
}


UNUSED static char	*parseLine(char *file, UNUSED char **remain)
{
	UNUSED	char	*line = NULL;
	UNUSED size_t	len = 0;

	len = line_len(file);
	
	/*
		* Ici il faudrait parser la string en temps reel avec le moins d'alloc possible
		* Avancer le pointeur (remain)
		* Parser et remplir les champs de mes structs
		*
	*/



	line = strndup(file, len); //TODO error management
	return (line);
}

t_vertex	*SCOP_parseFile(const char *file)
{
	UNUSED t_vertex	*vertex = {0};
	void			*file_ptr;
	int				file_fd;
	struct stat		st;

	file_fd = open(file, O_RDONLY);
	if (file_fd == -1) return (NULL); //TODO (error management)
	
	if (stat(file, &st) == -1) return (NULL); //same
	file_ptr = getDataAddress(st.st_size, file_fd);
	if (!file_ptr) return (NULL); //TODO (error management)
	parseLine(file_ptr, (char **)&file_ptr);

	munmap(file_ptr, st.st_size);
	close(file_fd);
	return (vertex);
}

int main(UNUSED int argc, char **argv){
	SCOP_parseFile(argv[1]);
}


