/*********************************
* Class: MAGSHIMIM Final Project *
* Frame struct definition	 	 *
**********************************/


#ifndef FRAME_H
#define FRAME_H

#include <stdio.h>

#define MAX_PATH_SIZE (256)
#define MAX_NAME_SIZE (50)

struct Frame
{
	char name[MAX_NAME_SIZE];
	unsigned int	duration;
	char path[MAX_PATH_SIZE];  // may change to FILE*
};

typedef struct Frame frame_t;



#endif //FRAME_H
