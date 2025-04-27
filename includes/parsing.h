/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stetrel <stetrel@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 19:33:09 by stetrel           #+#    #+#             */
/*   Updated: 2025/04/27 20:15:51 by stetrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

/*
 * @source:
 * 1) https://en.wikipedia.org/wiki/Wavefront_.obj_file
*/

/*
 *@brief
 * struct to store all of the vertex
 * I separate all the x,y,z and w to vectorised more easilly
*/

# define UNUSED __attribute__((unused))
# define NORETURN __attribute__((noreturn))
# define DESTRUCTOR __attribute__((destructor))

# include <sys/mman.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/stat.h>

typedef struct	s_vertex
{
	int	*x;
	int	*y;
	int	*z;
	int	*w; //Optional
}	t_vertex;


t_vertex	*SCOP_parseFile(const char *file);
