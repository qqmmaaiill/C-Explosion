#include "Screen.h"
#include <vcruntime_string.h>

namespace cave
{
	Screen::Screen() :
		m_window(NULL), m_renderer(NULL), m_texture(NULL), m_buffer1(NULL), m_buffer2(NULL)
	{

	}
	bool Screen::init()
	{
		if (SDL_Init(SDL_INIT_VIDEO) < 0)
		{
			return false;
		}
		m_window = SDL_CreateWindow("Star Explosion", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);

		if (m_window == NULL)
		{
			SDL_Quit();
			return false;
		}

		m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_PRESENTVSYNC);
		m_texture = SDL_CreateTexture(m_renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STATIC, width, height);

		if (m_renderer == NULL)
		{
			SDL_DestroyWindow(m_window);
			SDL_Quit();
			return false;
		}

		if (m_texture == NULL)
		{

			SDL_DestroyRenderer(m_renderer);
			SDL_DestroyWindow(m_window);
			SDL_Quit();
			return false;
		}

		m_buffer1 = new Uint32[width * height]; //mem for all the pixels (Uint32 is from SDL,basically an int
		m_buffer2 = new Uint32[width * height];


		memset(m_buffer1, 0, width * height * sizeof(Uint32));   //make the background white(255) or black(0)   0xFF = 16 -bit system
		memset(m_buffer2, 0, width * height * sizeof(Uint32));

		return true;
	}
	bool Screen::processEvents()
	{
		SDL_Event event;
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT) // if we encounter a quit statement(like x button)
			{
				return false;
			}
		}
		return true;
	}
	void Screen::setPixel(int x, int y, Uint8 red, Uint8 green, Uint8 blue)
	{

		if (x < 0 || x >= width || y < 0 || y >= height) //if not in range
		{
			return;
		}

		Uint32 color = 0;

		color += red;
		color <<= 8; //shifting 8 bits(1 byte)
		color += green;
		color <<= 8;
		color += blue;
		color <<= 8;
		color += 0xFF;

	    m_buffer1[(y * width) + x] = color;  //move to the exact pixel and change it - x corresponds to column,and y - to row which is equal to y*pixels in a row)
		//m_buffer[x + (y*width)] = color;
	}
	void Screen::boxBlur()
	{
		Uint32* temp = m_buffer1;
		m_buffer1 = m_buffer2;
		m_buffer2 = temp;

		for (int y = 0; y < height; y++)
		{
			for (int x = 0; x < width; x++)
			{

				int redT = 0;
				int greenT = 0;
				int blueT = 0;


				for (int row = -1; row <= 1; row++)
				{
					for (int col = -1; col <= 1; col++)
					{

						int currentX = x + col;
						int currentY = y + row;

						if (currentX >= 0 && currentX < width && currentY >= 0 && currentY < height)
						{
							//RGBA - 24 16 8 0
							Uint32 color = m_buffer2[currentY * width + currentX];

							Uint8 red = color >> 24;
							Uint8 green = color >> 16;
							Uint8 blue = color >> 8;

							redT += red;
							greenT += green;
							blueT += blue;

						}
					}
				}

				Uint8 red = redT / 9;
				Uint8 green = greenT / 9;
				Uint8 blue = blueT / 9;

				setPixel(x, y, red, green, blue);
			}
		}
		


	}
	/*void Screen::clear()
	{
		memset(m_buffer1, 0, width * height * sizeof(Uint32)); 
		memset(m_buffer2, 0, width * height * sizeof(Uint32));// clear screen with black
	}*/
	void Screen::update()
	{
		SDL_UpdateTexture(m_texture, NULL, m_buffer1, width * sizeof(Uint32)); //for testing purposes;
		SDL_RenderClear(m_renderer);  //clear with the drawing color
		SDL_RenderCopy(m_renderer, m_texture, NULL, NULL);  //copy texture to render
		SDL_RenderPresent(m_renderer);  //show on screen
	}
	void Screen::close()
	{

	delete[] m_buffer1;
	delete[] m_buffer2;
	SDL_DestroyRenderer(m_renderer);
	SDL_DestroyTexture(m_texture);
	SDL_DestroyWindow(m_window);
	SDL_Quit();
	}


}
