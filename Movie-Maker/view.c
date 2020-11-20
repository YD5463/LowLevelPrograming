/*********************************
* Class: MAGSHIMIM Final Project *
* Play function				 	 *
**********************************/

#include "view.h"

/**
play the movie!!
input: a linked list of frames to display
display the images each for the duration of the frame one by one and close the window
**/
void play(link_t *list)
{
	cvNamedWindow("Display window", CV_WINDOW_AUTOSIZE); //create a window
	int counter = 1;
	IplImage* image;
	while (list != 0)
	{
		image = cvLoadImage(list->frame->path, 1);
		if (!image)//The image is empty.
		{
			printf("could not open or find image number %d", counter);
		}
		else
		{
			cvShowImage("Display window", image);//display the image
			cvWaitKey(list->frame->duration);//wait
			list = list->next;
			cvReleaseImage(&image);
		}
		counter++;
	}
	cvDestroyWindow("Display window");
	return;
}