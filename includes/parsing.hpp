/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stetrel <stetrel@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 19:33:09 by stetrel           #+#    #+#             */
/*   Updated: 2025/05/04 11:02:00 by swenn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

/*
 * @source:
 * 1) https://en.wikipedia.org/wiki/Wavefront_.obj_file
 * 2) https://www.scratchapixel.com/lessons/3d-basic-rendering/obj-file-format/obj-file-format.html
 * 3) https://paulbourke.net/dataformats/obj/obj_spec.pdf
*/

# define UNUSED __attribute__((unused))
# define NORETURN __attribute__((noreturn))
# define DESTRUCTOR __attribute__((destructor))

# include <sys/mman.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <ctype.h>
# include <stdbool.h>
#include <stdexcept>
#include <iostream>

/*
 *@brief
 * struct to store all of the vertex
 * I separate all the x,y,z and w to vectorised more easilly
*/

class SCOP_MapFile {
	public:

		SCOP_MapFile() = default;

		SCOP_MapFile(const char *filepath){
			int	fd = open(filepath, O_RDONLY);
			if (fd == -1) throw std::runtime_error("failed to open file");

			struct stat st;
			fstat(fd, &st);
			size = st.st_size;
			data = mmap(nullptr, size, PROT_READ, MAP_PRIVATE, fd, 0);
			close(fd);

			if (data == MAP_FAILED)
				throw std::runtime_error("mmap failed");
		}

		~SCOP_MapFile(){
			if (data) munmap(data, size); 
		}
		
		void *getData(void){
			return (data);
		}

		size_t getSize(void){
			return (size);
		}

	private:
		void	*data = nullptr;
		size_t	size = 0;

};

/*
typedef struct	s_vertex
{
	int	*x;
	int	*y;
	int	*z;
	int	*w; //Optional
}	t_vertex;
*/

