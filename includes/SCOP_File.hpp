/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SCOP_File.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stetrel <stetrel@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 19:33:09 by stetrel           #+#    #+#             */
/*   Updated: 2025/05/05 00:55:50 by swenn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

/*
 * @source:
 * 1) https://en.wikipedia.org/wiki/Wavefront_.obj_file
 * 2) https://www.scratchapixel.com/lessons/3d-basic-rendering/obj-file-format/obj-file-format.html
 * 3) https://paulbourke.net/dataformats/obj/obj_spec.pdf
*/

/*
 * @explanation .obj format:
 * in .obj format, # is for comment,
 * v for coordonates of the vertex (follow by 3 floats)
 * vn for the normals
 * vt for the textures
 * f for the faces
*/

# define UNUSED __attribute__((unused))
# define NORETURN __attribute__((noreturn))
# define DESTRUCTOR __attribute__((destructor))

# include <ctype.h>
# include <fstream>
#include <cstring>
#include <stdlib.h>
#include <stdexcept>
#include <iostream>

#define START_SIZE 16

class SCOP_File {
	public:

		SCOP_File();
		SCOP_File(const char *filepath);
		~SCOP_File();	
		void *getData(void);
		size_t getSize(void);

	private:
		void	*data;
		size_t	size;
};

typedef struct	s_vertex
{
	float	*x;
	float	*y;
	float	*z;
	float	*w; //Optional
}	t_vertex;

typedef struct	s_textures{
	float	u;
	float	v;
}	t_text;

class SCOP_Object{
	public:
		SCOP_Object();
		~SCOP_Object();
		std::string	name;
		t_vertex	v;
		t_vertex	vn;
		t_text		*vt;
};

bool	parseLine(std::string line);
