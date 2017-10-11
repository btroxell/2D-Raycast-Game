// game.cpp
// Alex Rutan
// 4/1/15
#include <iostream>
#include <SDL2/SDL.h>
#include <math.h>
#include "game.h"
#include "map.h"
#include "camera.h"
#include "raycast.h"
#include "Player.h"

using namespace std;

/*
Game constructor 
defines the values used for the resolution of the screen
initializes values used by SDL for renderer, window, and textures
 */
Game::Game()
{
    resX = 360;
    resY = 240;
    window = NULL;
    surface = NULL;
    ammoTexture = NULL;
    enemyTexture = NULL;
    weaponTexture = NULL;
    renderer = NULL;
} //end constructor

Game::~Game()
{
} //end destructor


/*
Initializes SDL and creates window, renderer, and assigns values for their initialization
Has checks to make sure everythin initializes properly
Otherwise it would be very hard to pinpoint what is breaking when nothing happens
 */
bool Game::init()
{
    bool success = true;
    if(SDL_Init(SDL_INIT_VIDEO) < 0)
    {
	printf("SDL broke or something.");
	success = false;
    } //end if
    else
    {
	window = SDL_CreateWindow("The Adventures of Raymond Caste", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, resX, resY, SDL_WINDOW_SHOWN);
	if(window == NULL)
	{
	    printf("Window Can't Be Created Fool");
	    success = false;
	}
	else
	{
	    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	    if(!renderer)
	    {
		cout << "Couldn't create window :( " << endl;
		cout << SDL_GetError() << endl;
		success = false;
	    } //end if
	    else
	    {
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	    } //end else
	} //end else
    } //end else
    return success;
} //end init

/*
Uses a single surface to load several .bmp images
And call SDL's CreateTextureFromSurface method to convert the images to a more efficient format called "textures"
Just reuse one surface and assign a new source image for each texture creation
We destroy the surface in close()

Includes the same type of "success" bool checker to make it easier to pinpoint what goes wrong 
Because no error would be thrown otherwise
 */
bool Game::loadTextures()
{
    bool success = true;
    surface = SDL_LoadBMP("block.bmp");
    if(surface == NULL)
    {
	printf("Couldn't load textures sry :(");
	cout << SDL_GetError() << endl;
	success = false;
    } //end if
    else{
	ammoTexture = SDL_CreateTextureFromSurface(renderer, surface);
	if(ammoTexture == NULL)
	{
	    success = false;
	} //end if
    } //end else
    surface = SDL_LoadBMP("enemy.bmp");
    if(surface == NULL)
    {
	cout << "Couldn't load textures sry" << endl;
	success = false;
    } //end if
    else{
	enemyTexture = SDL_CreateTextureFromSurface(renderer, surface);
	if(enemyTexture == NULL)
	{
	    success = false;
	} //end if
    } //end else
    surface = SDL_LoadBMP("weapon.bmp");
    if(surface == NULL)
    {
	cout << "Couldn't load textures sry" << endl;
	success = false;
    } //end if
    else{
	weaponTexture = SDL_CreateTextureFromSurface(renderer, surface);
	if(weaponTexture == NULL)
	{
	    success = false;
	} //end if
    } //end else
    return success;
} //end loadMedia

/*
Destroy each of the textures, surface, window, and renderer
Otherwise things hang around in memory
Execute "SDL_Quit()" to properly close SDL
 */
void Game::close()
{
    SDL_DestroyRenderer(renderer);
    renderer = NULL;

    SDL_FreeSurface(surface);
    surface = NULL;
    
    SDL_DestroyTexture(ammoTexture);
    ammoTexture = NULL;

    SDL_DestroyTexture(enemyTexture);
    enemyTexture = NULL;

    SDL_DestroyTexture(weaponTexture);
    weaponTexture = NULL;

    SDL_DestroyWindow(window);
    window = NULL;

    SDL_Quit();
} //end close

/*
First, take each of the textures and assign them to their own specific rectangles to be drawn later
Create and instance of map, map is loaded when it is constructed
Pass the map information on to player and the setEnemyMap via pointer
Create an instance of camera and send it values for number of rays and player's initial position
Create an instance of SDL_Event for player input, events change bools to "true"
 */
int Game::run()
{
    bool drawAmmo;
    SDL_Rect srcAmmoRect;
    SDL_Rect dstAmmoRect;
    srcAmmoRect.x = 0;
    srcAmmoRect.y = 0;
    srcAmmoRect.w = 100;
    srcAmmoRect.h = 100;
    dstAmmoRect.x = 0;
    dstAmmoRect.y = 0;
    dstAmmoRect.w = 100;
    dstAmmoRect.h = 100;

    bool drawEnemy;
    SDL_Rect srcEnemyRect;
    SDL_Rect dstEnemyRect;
    srcEnemyRect.x = 0;
    srcEnemyRect.y = 0;
    srcEnemyRect.w = 200;
    srcEnemyRect.h = 100;
    dstEnemyRect.x = 0;
    dstEnemyRect.y = 0;
    dstEnemyRect.w = 200;
    dstEnemyRect.h = 100;

    bool drawWeapon;
    SDL_Rect srcWeaponRect;
    SDL_Rect dstWeaponRect;
    srcWeaponRect.x = 0;
    srcWeaponRect.y = 0;
    srcWeaponRect.w = 50;
    srcWeaponRect.h = 50;
    dstWeaponRect.x = 160;
    dstWeaponRect.y = 200;
    dstWeaponRect.w = 50;
    dstWeaponRect.h = 50;

    Map m;
    //m.loadMap("map");
    m.setEnemyMap(&m);

    Player p(&m);
    for(int i = 0; i < m.enemies.size(); i++)
    {
	m.enemies[i].setPlayer(&p);
	m.enemies[i].updateDest();
	//cout << m.enemies.size() << endl;
    }
    Camera c(p.getPosX(), p.getPosY(), p.getDir(), 90, resY, &m); //4th parameter is number of rays currently 90;

    SDL_Event event;
    
    int r = 0;
    int nextRay = 0;
    
    bool shoot = false;
    bool forward = false;
    bool backward = false;
    bool sleft = false;
    bool sright = false;
    bool rrotate = false;
    bool lrotate = false;

    if (!init())
    {
	printf("Coudn't initialize");
    } //end if
    else
    {
	//Check to make sure all of the textures loaded in fine
	if (!loadTextures())
	{
	    printf("The media is attempting to deceive the American people. Wait no. Different media. This kind of media just isn't there.");
	} //end if
	else
	{
	    //int frames = 0;
	    /*
	      Main game loop using a while-keepGoing loop
	      First check for keydowns, while keys are down, bools are set to true
	      Then check for keyups, when a key is let up, it sets the bool to false
	      If we just check for held down keys, it mimics when you hold down a key in a text editor by pausing before continuing like this rrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrr	      
	     */
	    bool keepGoing = true;
	    while(keepGoing)
	    {
		while(SDL_PollEvent(&event) != 0)
		{
		    if(event.type == SDL_KEYDOWN)
		    {	
			if(event.key.keysym.sym == SDLK_ESCAPE)
			{
			    keepGoing = false;
			} //end if
			if(event.key.keysym.sym == SDLK_SPACE)
			{
			    shoot = true;
			} //end if
			if(event.key.keysym.sym == SDLK_w)
			{
			    forward = true;
		       	} //end if
			if(event.key.keysym.sym == SDLK_s)
			{
			    backward = true;
			} //end if
			if(event.key.keysym.sym == SDLK_RIGHT)
			{
			    rrotate = true;
			} //end if
			if(event.key.keysym.sym == SDLK_LEFT)
			{
			    lrotate = true;
			} //end if
		    } //end if

		    if(event.type == SDL_KEYUP)
		    {	
		        if(event.key.keysym.sym == SDLK_SPACE)
			{
			    shoot = false;
			} //end if
			if(event.key.keysym.sym == SDLK_w)
			{
			    forward = false;
		       	} //end if
			if(event.key.keysym.sym == SDLK_s)
			{
			    backward = false;
			} //end if
			if(event.key.keysym.sym == SDLK_RIGHT)
			{
			    rrotate = false;
			} //end if
			if(event.key.keysym.sym == SDLK_LEFT)
			{
			    lrotate = false;
			} //end if
		    } //end if
		} //end while
		
		/*
		  Update the surface on which everything is drawn every loop
		  Set the draw color to the color of the ceiling and then clear the screen, which turns the whole screen that color
		 */
		SDL_UpdateWindowSurface(window);
		SDL_SetRenderDrawColor(renderer, 80, 80, 80, 255);
		SDL_RenderClear(renderer);
		
		/*
		  Calls the functions in player that are associated with inputs
		 */
		if(forward)
		{
		    //    forward = false;
		    p.move (1);
		} //end if
		if(backward)
		{
		    //    backward = false;
		    p.move (0);
		} //end if
		if(sleft)
		{
		    // sleft = false;
		    p.move (1);
		} //end if
		if(sright)
		{
		    // sright = false;
		    p.move (0);
		} //end if
		if(rrotate)
		{
		    p.rotate(5);
		} //end if
		if(lrotate)
		{
		    p.rotate(-5);
		} //end if
		/*
		  Calls the updateDest method for each of the enemies in our enemy array
		  This is where they each grab the location of the player and set that as their point of destination
		 */
		for(int i = 0; i < m.enemies.size(); i++)
		{
		    m.enemies[i].updateDest();
		}
		
		/*
		  Update camera by sending it the player's current position and direction
		  Camera position and direction is thereby directly tied to the player
		 */
		c.update(p.getPosX(), p.getPosY(), p.getDir());
		
		/*
		  Tell camera to cast its rays 200 times, which corresponds with the limit of step in camera
		 */
		for(r = 0; r < 200; r++)
		{
		   c.castRay();
		   c.step++;
		} //end for

		/*
		  This is where we tell the renderer to draw our lines based on camera's ray distance values
		  We set the camera to draw different colors for each list to give it a shading effect
		  Walls on X axis are drawn light blue
		  Walls on Y exis are drawn dark blue
		 */
	        for(r = 0; r < resX; r++)
		{
		    //Draw the floor
		    SDL_SetRenderDrawColor(renderer, 140, 140, 140, 255);
		    SDL_RenderDrawLine(renderer, r, resY/2, r, resY);
		  //cout << "r " << r << endl;
		    if(r % 4 == 0) //increment the ray we're drawing every four loops to fit our x resolution
		    {
			nextRay++;
		    } //end if
		    
		    //draw our x rays
		    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
		    SDL_RenderDrawLine(renderer, r, c.xRaysY1[nextRay - 1], r, c.xRaysY2[nextRay - 1]);

		    // SDL_RenderDrawLine(renderer, c.getLoc('x'), c.getLoc('y'), c.getLoc('z')+c.getLoc('x'), c.getLoc('w')+c.getLoc('y'));
		    //SDL_RenderDrawLine(renderer, c.getLoc('x'), c.getLoc('y'), c.currentX[nextRay], c.currentY[nextRay]);
		   
		    //draw our y rays
		    SDL_SetRenderDrawColor(renderer, 0, 0, 110, 255);
		    SDL_RenderDrawLine(renderer, r, c.yRaysY1[nextRay - 1], r, c.yRaysY2[nextRay - 1]);
		    
                    //SDL_SetRenderDrawColor(renderer, 0, 250, 0, 255);
		    //SDL_RenderDrawLine(renderer, r, c.PickupY1[nextRay - 1], r, c.PickupY2[nextRay - 1]);
		    
		    //Determine whether or not we can see the pickup and then draw the sprite based on the rays hitting it
		    //It sets the drawAmmo bool to true so we know to actually blit the texture onto the renderer
		    //If we can't see a pickup then we don't bother drawing it
		    if(c.PickupY1[nextRay - 1] != 0)
		    {
			dstAmmoRect.h = c.PickupY1[nextRay - 1] / 2;
			dstAmmoRect.w = c.PickupY1[nextRay - 1] / 2;
			dstAmmoRect.x = r - dstAmmoRect.w * 2;
			dstAmmoRect.y = sqrt(c.PickupY2[nextRay - 1]) + 160;
		        drawAmmo = true;
		    } //end if
		    
		    //Determine whether or not we can see an enemy and then draw the sprite based on the rays hitting it 
		    //It sets the drawEnemy bool to true so we know to actually blit the texture onto the renderer
		    //If we can't see an enemy then we don't bother drawing it
		    if(c.EnemyY1[nextRay - 1] != 0)
		    {
			dstEnemyRect.h = c.EnemyY1[nextRay - 1] / 2 + 40; 
			dstEnemyRect.w = c.EnemyY1[nextRay - 1] / 2;
		        dstEnemyRect.x = r - dstEnemyRect.w * 2 - 30;
			dstEnemyRect.y = c.EnemyY2[nextRay - 1] - 40;
		        drawEnemy = true;
		    } //end if
		    
		    //For now, we should always draw our weapon viewmodel on screen
		    drawWeapon = true;

		} //end for
		
		//reset our nextRay variable each loop since we use it to iterate
		nextRay = 0;

		/*
		  Blits the texture/rectangle to the position indicated up above in our rays
		  For each type of sprite
		 */
		if(drawAmmo)
		{
		    SDL_RenderCopy(renderer, ammoTexture, &srcAmmoRect, &dstAmmoRect);
		    drawAmmo = false;
		} //end if
	
		if(drawEnemy)
		{
		  //cout << "draw enemy" << endl;
		    SDL_RenderCopy(renderer, enemyTexture, &srcEnemyRect, &dstEnemyRect);
		    drawEnemy = false;
		} //end if
		
		if(drawWeapon)
		{
		    SDL_RenderCopy(renderer, weaponTexture, &srcWeaponRect, &dstWeaponRect);
		    drawWeapon = false;
		} //end if

		//This updates the screen with what has been drawn on the renderer
		SDL_RenderPresent(renderer);
		
		//We have a blanket delay since the game is not intensive on any semi-modern system
		//One day we'll intelligently set the framerate
	       	SDL_Delay(40);

		// updates
		//Call player and enemy update method
                //This is where they move, take/give damage, etc
		p.update();
		//if the shoot boolean returns true (if the space bar has been pressed), then call player's shoot method
		if(shoot)
		{
		    p.shoot();
		} //end if
		for(int i = 0; i < m.enemies.size(); i++)
		{
		      m.enemies[i].move();
		}
		// end updates

	    } //end while 
	} //end else
    } //end else    
    return(0);
} //end run
