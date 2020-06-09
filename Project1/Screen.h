#pragma once
#ifndef SCREEN_H_
#define SCREEN_H_

#include<SDL.h>
namespace cave
{

	class Screen
	{
		private:

			SDL_Window* m_window;
			SDL_Renderer* m_renderer;
			SDL_Texture* m_texture;
			Uint32* m_buffer1;
			Uint32* m_buffer2;

		public:

			const static int width = 800;
			const static int height = 600;

			Screen();

			bool init();
			void update();
			void setPixel(int x, int y, Uint8 red, Uint8 green, Uint8 blue);
			bool processEvents();
			void close();
			//void clear();
			void boxBlur();

	};



}


#endif // !SCREEN_H


