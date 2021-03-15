#pragma once
#include <SDL2/SDL.h>


#define SP_HEIGHT 1000
#define SP_WIDTH 1000

#define SCREEN_HEIGHT  700    
#define SCREEN_WIDTH  1000
SDL_Event e;
SDL_Renderer* renderer;
SDL_Window *window;
int quit = 0;

struct FRUSTUM {

        unsigned int FAR;
};



typedef struct PLAYER {

        struct FRUSTUM frustum;


        unsigned int x;
        unsigned int y;
	unsigned int z;

	unsigned int ROTATION;


} PLAYER;

typedef struct COMMANDER_IMAGE {
	char IMAGE[5000];
	SDL_Rect RECT;

} COMMANDER_IMAGE;
/*Rendered object*/
typedef struct OBJECT {

	unsigned int x;
	unsigned int y; 
	unsigned int z;

	unsigned int h;
	unsigned int w;
	
	unsigned int Y_ROTATION;
	unsigned int X_ROTATION;
	COMMANDER_IMAGE image;
		
	

} OBJECT;
typedef struct COMMANDER_VERTEX_2D {

	int x;	
	int y;


} COMMANDER_VERTEX_2D;
	
typedef struct COMMANDER_RECT {
	
	int TOP;
	int BOTTOM;
	int LEFT;
	int RIGHT;

	int h;
	int w;
} COMMANDER_RECT;
int CALCULATE_OBJECT_SIZE(unsigned int y, unsigned int size) {

	int i = 0;
	int SIZE = size;
	SIZE = SIZE - y;
	return SIZE;

}
COMMANDER_RECT CALCULATE_RECT_SIDES(COMMANDER_RECT RECT, int x, int y) {
	RECT.TOP = y;
	RECT.BOTTOM = y + RECT.h;

	RECT.LEFT = x;
	RECT.RIGHT = x + RECT.w;
	
	
	return RECT;
}
OBJECT DRAW_OBJ(OBJECT obj, PLAYER player) {
	/*TODO: Draw objects*/
	
        
        
        unsigned int y = obj.y - player.y;
	//printf("\ny:%d x:%d\n", player.y, player.x);
	if (y <= player.frustum.FAR) { 
		int degree = obj.h / 180;
       
       		 /*Prepare texture for rendering*/
        	
        	SDL_Texture* texture = NULL;
                                                                                           
        	SDL_Surface* temp = NULL; 
        	temp = SDL_LoadBMP(obj.image.IMAGE);

        	texture = SDL_CreateTextureFromSurface(renderer, temp);

        	SDL_FreeSurface(temp); 
        	/*Prepare rect to store sprite in*/
        	
        	obj.image.RECT.x = player.x - obj.x;
	
        	obj.image.RECT.y = player.z - obj.z; 
		/*TODO: Calculate height and width based on coordinates relative to player frustuma*/

		
		obj.image.RECT.h = CALCULATE_OBJECT_SIZE(y, obj.h);
		obj.image.RECT.w = CALCULATE_OBJECT_SIZE(y, obj.w);
		//printf("\n\n\n\n\n\nh:%d\n\n\n\n\n\n", rect.h);
        	SDL_RenderCopy(renderer, texture, NULL, &obj.image.RECT);
		
		
       		//SDL_RenderPresent(renderer);
        
      	//printf("h:%d\nw:%d\n", obj.image.RECT.h, obj.image.RECT.w);

   

        	SDL_DestroyTexture(texture);
	}
	return obj;
}
void DRAW_SKYBOX(char IMG[5000], int x, int y) {
	        SDL_Texture* texture = NULL;

                SDL_Surface* temp = NULL;
                temp = SDL_LoadBMP(IMG);

                texture = SDL_CreateTextureFromSurface(renderer, temp);

                SDL_FreeSurface(temp);
		SDL_Rect rect;


                rect.x = x;
                rect.y = y;

		rect.h = 1000;
		rect.w = SCREEN_WIDTH;
		
		SDL_RenderCopy(renderer, texture, NULL, &rect);
                //SDL_RenderPresent(renderer);
		SDL_DestroyTexture(texture);
}
void DRAW_IMAGE(char IMG[5000], int x, int y, int h, int w) {
                SDL_Texture* texture = NULL;

                SDL_Surface* temp = NULL;
                temp = SDL_LoadBMP(IMG);

                texture = SDL_CreateTextureFromSurface(renderer, temp);

                SDL_FreeSurface(temp);
                SDL_Rect rect;


                rect.x = x;
                rect.y = y;

                rect.h = h;
                rect.w = w;

                SDL_RenderCopy(renderer, texture, NULL, &rect);
                //SDL_RenderPresent(renderer);
                SDL_DestroyTexture(texture);



}
/*UNDER CONSTRUCTION*/
int CHECK_COLLISION(COMMANDER_IMAGE obj1, COMMANDER_IMAGE obj2) {
	
                COMMANDER_RECT RECT_1;
		COMMANDER_RECT RECT_2;
		RECT_1.h = obj1.RECT.h;
		RECT_1.w = obj1.RECT.w;
		
		RECT_2.h = obj2.RECT.h;
		RECT_2.w = obj2.RECT.w;
		
		RECT_1 = CALCULATE_RECT_SIDES(RECT_1, obj1.RECT.x, obj1.RECT.y);
		RECT_2 = CALCULATE_RECT_SIDES(RECT_2, obj2.RECT.x, obj2.RECT.y);
	//	printf("RECT1 H:%d, RECT1 W:%d\n", RECT_1.h, RECT_1.w);
		//printf("RECT2 H:%d, RECT2 W:%d\n", RECT_2.h, RECT_2.w);
             	if (RECT_1.BOTTOM <= RECT_2.TOP) {
			/*No collision*/
			return 0;
			
		}
		if (RECT_1.TOP >= RECT_2.BOTTOM) {
		        /*No collision*/
                        return 0;
		}
                if (RECT_1.RIGHT <= RECT_2.LEFT) {
                        /*No collision*/
                        return 0;
                }
                if (RECT_1.LEFT >= RECT_2.RIGHT) {
                        /*No collision*/
                        return 0;
                }


		/*We have a collision!*/
		return 1;
}

int RANDOM_INT(int lower, int upper) {
	return (rand() % (upper - lower + 1)) + lower;
}
