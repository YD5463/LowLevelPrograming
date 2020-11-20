#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Frame.h"
#include "linkedList.h"
#include "view.h"

#define STR_LEN 50
#define BIG_LEN	500
#define EXIT 0

void menu();
int print_menu();
int add_frame(link_t** head);
void printList(link_t* list);
void change_dur_frame(link_t** head);
void delete_frame(link_t** head);
void change_all_dur_frames(link_t** head);
void change_frame_place(link_t** head);
void play_movie(link_t* head);
int load_project(link_t** head);
void save_project(link_t* head);
void free_link(link_t** head);

int main(void)
{
	menu();
	system("PAUSE");
	return 0;
} 
/*
This function is the menu of program, she call to function by the choice's user and tell to the user if the option does not exist.
input:none
output:none.
*/
void menu()
{
	int choice = -1;
	link_t* head = NULL;
	load_project(&head);
	while (choice != EXIT)
	{
		choice = print_menu();
		switch (choice)
		{
			case 0:
				free_link(&head);
				break;
			case 1:
				add_frame(&head);
				break;
			case 2:
				delete_frame(&head);
				break;
			case 3:
				change_frame_place(&head);
				break;
			case 4:
				change_dur_frame(&head);
				break;
			case 5:
				change_all_dur_frames(&head);
				break;
			case 6:
				printList(head);
				break;
			case 7:
				play_movie(head);
				break;
			case 8:
				save_project(head);
				break;
			default:
				printf("You should type one of the options - 0-8!\n");
				break;
		}
	}
}
/*
This function get from the user path to file there she save the frames when in every line she save frame and she put
',' char between every felid in the frame.
input:the value of the head of the linked list.
output:none.
*/
void save_project(link_t* head)
{
	char path_project[STR_LEN] = { 0 };
	printf("Please enter path to save your project\n");
	getchar();
	fgets(path_project, STR_LEN, stdin);
	path_project[strlen(path_project) - 1] = 0;
	link_t* curr = head;
	if (!fopen(path_project,"w"))
	{
		printf("the file does not exist\n");
	}
	else
	{
		FILE* file_save = fopen(path_project, "w");
		while (curr)
		{
			fprintf(file_save,"%s,%d,%s,\n",curr->frame->path,curr->frame->duration,curr->frame->name);
			curr = curr->next;
		}
		printf("the project saved!\n");
		fclose(file_save);
	}
}
/*
This function check if the list is empty and allotment dynamic memory to the node in link and to the frame in the node after that she input from the
user path and check if the file is exist if yes she copy to the frame in the node if no she app flag after that she input frome
user duration and name to the frame and check if the flag is app she tell to the user if the is down she copy the duration and the name
to the frame, if the frame not empty she add one more check who check if the name of the new frame is already exist and tell to user if yes.
input:pointer of the head of the list.
output:none.
*/
int add_frame(link_t** head)
{
	printf("\n\n		*** Creating new frame ***\n");
	char temp[STR_LEN] = { 0 };
	int flag = 0;
	int dur = 0;
	link_t* last = NULL;
	link_t* curr = *head;
	if (!(*head))
	{
		(*head) = (link_t*)malloc(sizeof(link_t));
		if (!(*head))
		{
			printf("Unsuccessful malloc");
			return 1;
		}
		(*head)->frame = (frame_t*)malloc(sizeof(frame_t));
		if (!(*head)->frame)
		{
			printf("Unsuccessful malloc");
			return 1;
		}
		printf("Please insert frame path:\n");
		getchar();
		fgets(temp, STR_LEN, stdin);
		temp[strlen(temp) - 1] = 0;
		if (fopen(temp, "r"))
		{
			strcpy((*head)->frame->path, temp);
		}
		else
		{
			flag = 1;
		}
		printf("Please insert frame duration(in miliseconds):\n");
		scanf("%d", &dur);
		printf("Please choose a name for that frame:\n");
		getchar();
		fgets(temp, STR_LEN, stdin);
		temp[strlen(temp) - 1] = 0;
		if (flag == 1)
		{
			printf("Can't find file! Frame will not be added\n");
			free((*head)->frame);
			free((*head));
			(*head) = NULL;
		}
		else
		{
			(*head)->frame->duration = dur;
			strcpy((*head)->frame->name, temp);
			(*head)->next = NULL;
		}
	}
	else
	{
		while (curr->next)
		{
			curr = curr->next;
		}
		curr->next = (link_t*)malloc(sizeof(link_t));
		if (!curr->next)
		{
			printf("Unsuccessful malloc");
			return 1;
		}
		last = curr;
		curr = curr->next;
		curr->frame = (frame_t*)malloc(sizeof(frame_t));
		if (!curr->frame)
		{
			printf("Unsuccessful malloc");
			return 1;
		}
		printf("Please insert frame path:\n");
		getchar();
		fgets(temp, STR_LEN, stdin);
		temp[strlen(temp) - 1] = 0;
		if (fopen(temp, "r"))
		{
			strcpy(curr->frame->path, temp);
		}
		else
		{
			flag = 1;
		}
		printf("Please insert frame duration(in miliseconds):\n");
		scanf("%d", &dur);
		printf("Please choose a name for that frame:\n");
		getchar();
		fgets(temp, STR_LEN, stdin);
		temp[strlen(temp) - 1] = 0;
		if (flag == 1)
		{
			printf("Can't find file! Frame will not be added\n");
			free(curr->frame);
			free(last->next);
			last->next = NULL;
		}
		else
		{
			curr->next = NULL;
			last = curr;
			curr = *head;
			while (curr->next)
			{
				while (strcmp(curr->frame->name, temp) == 0)
				{
					printf("The name is already taken, please enter an other name\n");
					fgets(temp, STR_LEN, stdin);
					temp[strlen(temp) - 1] = 0;
				}
				curr = curr->next;
			}
			curr = last;
			curr->frame->duration = dur;
			strcpy(curr->frame->name, temp);
		}
	}
}
/*
This function asked the user if she wont's to create a new project(regular) or to load existing project and do by the choice
input:pointer of the head of the list.
output:none.
*/
int load_project(link_t** head)
{
	int load = 0;
	char name_file[STR_LEN] = { 0 };
	char temp[STR_LEN][BIG_LEN] = { 0 };
	char name[MAX_NAME_SIZE] = { 0 };
	int duration = 0;
	char dur[STR_LEN] = { 0 };
	char path[MAX_PATH_SIZE] = { 0 };
	link_t* curr = *head;
	char c = ' ';
	int i = 0;
	int len = 0;
	int j = 0;
	int y = 0;
	printf("\n***** VIDEOINPUT LIBRARY - 0.1995 - TFW07 *****\n\n\n");
	printf("Welcome to Magshimim Movie Maker! what would you like to do?\n");
	printf(" [0] Create a new project\n [1] Load existing project\n");
	scanf("%d", &load);
	if (load == 1)
	{
		printf("Enter the path of the project <including name>\n");
		getchar();
		fgets(name_file, STR_LEN, stdin);
		name_file[strlen(name_file) - 1] = 0;
		if (fopen(name_file, "r"))
		{
			FILE* file_save = fopen(name_file, "r");
			while ((c=fgetc(file_save)) != EOF)
			{
				if (c == '\n')
				{
					len++;
					i++;
					j = 0;
				}
				else
				{
					temp[i][j] = c;
					j++;
				}
			}
			for (i = 0; i < len; i++)
			{				
				while (temp[i][j] != ',')
				{
					path[y++] = temp[i][j++];
				}
				y = 0;
				j++;
				while (temp[i][j] != ',')
				{
					dur[y++]= temp[i][j++];
				}
				y = 0;
				duration = atoi(dur);
				j++;
				while (temp[i][j] != ',')
				{
					name[y++]= temp[i][j++];
				}
				y = 0;
				j = 0;
				if (!(*head))
				{
					(*head) = (link_t*)malloc(sizeof(link_t));
					if (!(*head))
					{
						printf("Unsuccessful malloc");
						return 1;
					}
					(*head)->frame = (frame_t*)malloc(sizeof(frame_t));
					if (!(*head)->frame)
					{
						printf("Unsuccessful malloc");
						return 1;
					}
					strcpy((*head)->frame->path,path);
					(*head)->frame->duration = duration;
					strcpy((*head)->frame->name,name);
					(*head)->next = NULL;
					curr = *head;//upgate curr
				}
				else
				{
					while (curr->next)
					{
						curr = curr->next;
					}
					curr->next = (link_t*)malloc(sizeof(link_t));
					if (!curr->next)
					{
						printf("Unsuccessful malloc");
						return 1;
					}
					curr = curr->next;
					curr->frame = (frame_t*)malloc(sizeof(frame_t));
					if (!curr->frame)
					{
						printf("Unsuccessful malloc");
						return 1;
					}
					strcpy(curr->frame->path, path);
					curr->frame->duration = duration;
					strcpy(curr->frame->name, name);
					curr->next = NULL;
					curr = *head;//upgate curr
				}
			}
			fclose(file_save);
		}
		else
		{
			printf("Error- cant open file,creating a new project\n");
		}
	}
	printf("Editing Project! what would you like to do?\n");
}
/*
This function input from the user if she wont's to play the movie(picture after picture from the list)
from the start of list she just call to play function, if she wont's to play the movie from some index in the list the input index
and the function sheck if the index is in the list if no she tell to user if yes she get the node in the user start index and call
to play function with the node(the new head).
input:get the head of the list.
output:none.
*/
void play_movie(link_t* head)
{
	int choice = 0;
	int start_index = 0;
	link_t* curr = head;
	int len = 1;
	int i = 0;
	printf("If you wish to play the whole movie press 1\n");
	printf("If you want to play the movie from a certain point press 2\n");
	scanf("%d", &choice);
	if (choice == 1)
	{
		play(head);
	}
	else if (choice == 2)
	{
		printf("Where do you wish to start playing the movie from?\n");
		scanf("%d",&start_index);
		while (curr)//get the lenght of list
		{
			len++;
			curr = curr->next;
		}
		curr = head;
		if (start_index > len || start_index <= 0)
		{
			printf("the movie has only %d frames!",len);
		}
		else
		{
			for (i = 1; i < start_index; i++)
			{
				curr = curr->next;
			}
			play(curr);
		}
	}
}
/*
This function input from the user name of frame and check if the frame is exist, if yes she save the frame in anther varible,
and get the lenght of the list, after that she input from the user index to move the frame and check if the index is in the list
(by the lenght of list),afterwards she get the the frame in the index and switch between them.
input:pointer of the head list.
output:none.
*/
void change_frame_place(link_t** head)
{
	char name_frame[STR_LEN] = { 0 };
	link_t* curr = *head;
	link_t* frame_to_move = NULL;
	link_t* frame_in_new_index = NULL;
	link_t* temp = NULL;
	int flag = 0;
	int i = 1;
	int new_index = 0;
	int len = 0;
	printf("enter the name of the frame\n");
	getchar();
	fgets(name_frame, STR_LEN, stdin);
	name_frame[strlen(name_frame) - 1] = 0;
	while (curr)
	{
		if (strcmp(curr->frame->name, name_frame) == 0)
		{
			flag = 1;
		}
		len++;
		curr = curr->next;
	}
	if (flag != 1)
	{
		printf("this frame does not exist\n");
	}
	else
	{
		printf("Enter the new index in the movie you wish to place the frame\n");
		scanf("%d", &new_index);
		while (new_index>len || new_index<=0)
		{
			printf("The movie contains only %d frames!\n", len);
			printf("Enter the new index in the movie you wish to place the frame\n");
			scanf("%d", &new_index);
		}
		if (len != 1)
		{
			curr = *head;
			while (curr)
			{
				if (i == new_index)
				{
					frame_in_new_index = curr;
				}
				i++;
				curr = curr->next;
			}
			curr = *head;
			if (strcmp(curr->frame->name, name_frame) == 0)
			{
				frame_to_move = *head;
				*head = curr->next;
			}
			else
			{
				while (curr->next)
				{
					if (strcmp(curr->next->frame->name, name_frame) == 0)
					{
						frame_to_move = curr->next;
						curr->next = frame_to_move->next;
					}
					curr = curr->next;
				}
			}
			temp = frame_in_new_index->next;
			frame_in_new_index->next = frame_to_move;
			frame_to_move->next = temp;
		}
	}
}
/*
This function input from the user new duration(number) and change it in the all frames.
input:pointer of the head of the list.
output:none.
*/
void change_all_dur_frames(link_t** head)
{
	int new_dur = 0;
	link_t* curr = *head;
	printf("enter the duration for all frames\n");
	scanf("%d", &new_dur);
	if (*head)
	{
		while (curr)
		{
			curr->frame->duration = new_dur;
			curr = curr->next;
		}
	}
}
/*
This function input from the user name of frame after that she check if the frame is exist if yes she save the frame in anther
variable, input new duration and insert to the durtion in the frame we save, else she tell to user about that(frame not exist).
input:pointer of the head of the list.
output:none.
*/
void change_dur_frame(link_t** head)
{
	link_t* frame_change = NULL;
	link_t* curr = *head;
	char name_frame[STR_LEN] = { 0 };
	int new_dur = 0;
	int flag = 0;
	printf("enter the name of the frame\n");
	getchar();
	fgets(name_frame, STR_LEN, stdin);
	name_frame[strlen(name_frame) - 1] = 0;
	if (*head)
	{
		while (curr && flag!=1)
		{
			if (strcmp(curr->frame->name, name_frame) == 0)
			{
				frame_change = curr;
				flag = 1;
			}
			curr = curr->next;
		}
	}
	if (flag == 1)
	{
		printf("enter the new duration\n");
		scanf("%d", &new_dur);
		frame_change->frame->duration = new_dur;
	}
	else
	{
		printf("the frame does not exist\n");
	}
}
/*
This function input from the user name of frame to delete and check if the frame is the first frame or if the frame is the ather frame and
delete(free the memory of the frame) and app flag to check in the end if the function find the frame or the frame does not exist.
input:pointer of the head of the list.
output:none.
*/
void delete_frame(link_t** head)
{
	link_t* curr = *head;
	link_t* temp = NULL;
	int flag = 0;
	char name_frame[STR_LEN] = { 0 };
	printf("Enter the name of the frame you wish to erase\n");
	getchar();//clean buffer
	fgets(name_frame, STR_LEN, stdin);
	name_frame[strlen(name_frame) - 1] = 0;
	if (*head)
	{
		if (0 == strcmp((*head)->frame->name, name_frame))
		{
			flag = 1;
			*head = (*head)->next;
			free(curr);
		}
		else
		{
			while (curr->next)
			{
				if ((0 == strcmp(curr->next->frame->name, name_frame))) // waiting to be on the node BEFORE the one we want to delete
				{
					temp = curr->next; // put aside the node to delete
					curr->next = temp->next; // link the node before it, to the node after it
					free(temp); // delete the node
					flag = 1;
				}
				else
				{
					curr = curr->next;
				}
			}
		}
	}
	if (flag != 1)
	{
		printf("The frame was not found\n");
	}
}
/*
this function print the menu and input choice frome the user.
input:none.
output:the user choice.
*/
int print_menu()
{
	int choice = 0;
	printf(" [0] exit\n [1] Add new Frame\n [2] Remove a Frame\n [3] change frame index\n [4] Change frame duration\n");
	printf(" [5] Change duration of all frames\n [6] List frames\n [7] Play movie!\n [8] save project\n");
	scanf("%d", &choice);
	return choice;
}
/*
This function run on the list and print the varible in every frame and stop when the frame is null(end of list).
input:get the head of the list.
output:none.
*/
void printList(link_t* list)
{
	link_t* curr = list;
	printf("		Name			Duration		Path\n");
	while (curr)
	{
		printf("		%s			%d ms			%s\n", curr->frame->name, curr->frame->duration, curr->frame->path);
		curr = curr->next;
	}
	printf("\n\n");
}
/*
This function free the link list that we were dynamic allocatd
input:pointer of the head list.
output:none.
*/
void free_link(link_t** head)
{
	link_t* temp = NULL;
	while (*head)
	{
		temp = (*head)->next;
		free((*head)->frame);
		free(*head);
		*head = temp;
	}
	*head = NULL;
}
