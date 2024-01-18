#include <stdio.h>
#include <stdint.h>
#include <graphics.h>
#include "setseed.h"
#include "linkedlist.h"

#define UP 0
#define DOWN 1
#define RIGHT 2
#define LEFT 3

#define SCALE 100
#define SPEED 0

void draw_grid_sqr(int color,int x,int y,int xres,int yres,int scale){
	setfillstyle(SOLID_FILL,color);
	bar((x-1)*(xres/scale)+1,(y-1)*(yres/scale)+1,(x-1)*(xres/scale)+(xres/scale)-2,(y-1)*(yres/scale)+(yres/scale)-2);
}

void move_snake(ll* snake_pos_list,int* direction,int* current_direction){
	payload_struct tmp_payload;
	switch (*direction) {
		case UP:
				tmp_payload = (payload_struct){snake_pos_list->TAIL->payload.x,snake_pos_list->TAIL->payload.y-1};
				*current_direction = UP;
			break;
		case DOWN:
				tmp_payload = (payload_struct){snake_pos_list->TAIL->payload.x,snake_pos_list->TAIL->payload.y+1};
				*current_direction = DOWN;
			break;
		case RIGHT:
				tmp_payload = (payload_struct){snake_pos_list->TAIL->payload.x+1,snake_pos_list->TAIL->payload.y};
				*current_direction = RIGHT;
			break;
		case LEFT:
				tmp_payload = (payload_struct){snake_pos_list->TAIL->payload.x-1,snake_pos_list->TAIL->payload.y};
				*current_direction = LEFT;
			break;
		default:
			printf("Invalid direction\n");
			break;
		}
	append(snake_pos_list, tmp_payload);
}

int check_snake(ll* snake_pos_list,int scale){
	payload_struct snakehead_cords = snake_pos_list->TAIL->payload;
	node* node_p = snake_pos_list->HEAD;
	payload_struct tmp_payload;
	if(snakehead_cords.x < 1 || snakehead_cords.x > scale || snakehead_cords.y < 1 || snakehead_cords.y > scale){
		printf("Hit Wall\n");
		return 1;
	}
	while(node_p->next != snake_pos_list->TAIL){
		tmp_payload = node_p->payload;
		if(tmp_payload.x == snakehead_cords.x && tmp_payload.y == snakehead_cords.y){
			printf("Hit Yourself\n");
			return 1;
		}
		node_p = node_p->next;
	}
	return 0;
}

void draw(ll* snake_pos_list,payload_struct apple,int xres,int yres,int scale){
	payload_struct tmp_payload;
	node* node_p = snake_pos_list->HEAD;
	while(node_p != NULL){
		tmp_payload = node_p->payload;
		draw_grid_sqr(WHITE,tmp_payload.x,tmp_payload.y,xres,yres,scale);
		node_p = node_p->next;
	}
	draw_grid_sqr(RED,apple.x,apple.y,xres,yres,scale);
}

int valid_direction(int current_direction, int direction){
	switch (current_direction) {
		case UP:
			if(direction == DOWN){
				return 0;
			}else{
				return 1;
			}
		case DOWN:
			if(direction == UP){
				return 0;
			}else{
				return 1;
			}
		case LEFT:
			if(direction == RIGHT){
				return 0;
			}else{
				return 1;
			}
		case RIGHT:
			if(direction == LEFT){
				return 0;
			}else{
				return 1;
			}
		default:
			
			break;
	}
}

void keyupdate(int* direction){
	char input;
	if(xkbhit()){
		input = getch();
		switch (input) {
			case 'a':
				*direction = LEFT;break;
			case 'd':
				*direction = RIGHT;break;
			case 's':
				*direction = DOWN;break;
			case 'w':
				*direction = UP;break;
			default:
				break;
		}
	}
}

int is_in_snake(ll* snake_pos_list,payload_struct cords){
	node* node_p = snake_pos_list->HEAD;
	payload_struct tmp_payload;
	while(node_p != NULL){
		tmp_payload = node_p->payload;
		if(cords.x == tmp_payload.x && cords.y == tmp_payload.y) 
			return 1;
		node_p = node_p->next;
	}
	return 0;
}

void set_apple(ll* snake_pos_list, payload_struct* apple,int scale){
	payload_struct test_apple;
	do{
	test_apple = (payload_struct){rand()%scale+1,rand()%scale+1};
	}while(is_in_snake(snake_pos_list,test_apple));
	apple->x = test_apple.x;
	apple->y = test_apple.y;
}
	

int check_apple(ll* snake_pos_list,payload_struct* apple,int scale){
	payload_struct tmp_payload;
	node* node_p = snake_pos_list->HEAD;
	while(node_p != NULL){
		tmp_payload = node_p->payload;
		if(tmp_payload.x == apple->x && tmp_payload.y == apple->y){
			set_apple(snake_pos_list,apple,scale);
			return 1;
		}
		node_p = node_p->next;
	}
	return 0;
}

int main (int argc, char *argv[]){
  int scale = SCALE;
  int speed = SPEED;
  if(argc == 3){
    scale = atoi(argv[1]);
    speed = atoi(argv[2]);
  }

	ll* snake_pos_list = new_list();
	setseed();
	append(snake_pos_list,(payload_struct){2,5});
	append(snake_pos_list,(payload_struct){3,5});

	int xres = 600,yres = 600;
	initwindow(xres,yres);
	int i = 1;
	int direction = RIGHT;
	int current_direction;
	payload_struct apple;
	set_apple(snake_pos_list,&apple,scale);
	char points_str[50];
	uint32_t points = 0;
	while(1){
		setactivepage(i%2);cleardevice();
		if(i%20== 0){
			if(valid_direction(current_direction,direction)){
				move_snake(snake_pos_list,&direction,&current_direction);
			}else{
				move_snake(snake_pos_list,&current_direction,&current_direction);
			}
			if(!check_apple(snake_pos_list,&apple,scale)){
				remove_first(snake_pos_list);
			}else {
				points++;
				if(points == 100){
					printf("You Win!\n");
					return 0;
				}
			}
			if(check_snake(snake_pos_list,scale)) return 1;
		}
		keyupdate(&direction);
		draw(snake_pos_list,apple,xres,yres,scale);
		sprintf(points_str,"%i",points);
		outtextxy(1,1,points_str);

		setvisualpage(i%2);i++;delay(speed);
	}
}
