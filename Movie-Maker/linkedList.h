/*********************************
* Class: MAGSHIMIM Final Project *
* Link struct definition	 	 *
**********************************/

#ifndef LINKEDLISTH
#define LINKEDLISTH


#include "Frame.h"

struct Link
{
	frame_t	*frame;
	struct Link	*next;
};

typedef struct Link	link_t;
#endif
