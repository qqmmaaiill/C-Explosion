#include "SDL.h"
#include "Screen.h"
#include <iostream>
#include <cmath>
#include <stdlib.h>
#include "Swarm.h"
using namespace std;
using namespace cave;

int main(int argc, char* argv[])
{
	//SDL_Init(SDL_INIT_VIDEO);

	/*SDL_Window* window = SDL_CreateWindow
	("An SDL2 window", // window's title
		10, 25, // coordinates on the screen, in pixels, of the window's upper left corner
		640, 480, // window's length and height in pixels  
		SDL_WINDOW_OPENGL);

	SDL_Delay(3000); // window lasts 3 seconds
	SDL_DestroyWindow(window);
	SDL_Quit();*/
	
	Screen screen;

	if (screen.init() == false)
	{
		cout << "Error" << endl;
	}

	Swarm swarm;
	
	while (true) //to display a window with infinite loop;
	{

		int elapsed = SDL_GetTicks();
		//get the miliseconds since start of the program(number)
		//for blur
		//screen.clear();


		swarm.update(elapsed); //to move particles

		unsigned char green = (unsigned char)((1 + sin(elapsed * 0.0001)) * 128);
		unsigned char red = (unsigned char)((1 + sin(elapsed * 0.0002)) * 128);
		unsigned char blue = (unsigned char)((1 + sin(elapsed * 0.0013)) * 128);
		const Particle* const pParticles = swarm.getParticles();

		for (int i = 0; i < Swarm::NPARTICLES; i++)
		{
			Particle particle = pParticles[i];

			//int x = (particle.m_x + 1) * Screen::width /2;
			//int y = (particle.m_y + 1) * Screen::height /2;

			int x = (particle.m_x + 1) * Screen::width / 2;
			int y = particle.m_y * Screen::width / 2 + Screen::height / 2;

			screen.setPixel(x, y, red, green, blue);

		}

		//to blur the screen
		screen.boxBlur();
		// todo particles
		

		/*for (int y = 0; y < screen.height; y++)
		{
			for (int x = 0; x < screen.width; x++)
			{
				screen.setPixel(x, y, red, green, blue);
			}
		}*/

		//screen.setPixel(400, 300, 128, 0, 255);
		//draw the screen 
		screen.update();

		if (screen.processEvents() == false)
		{
			break;
		}

	}

	screen.close();
	
	return 0;
}