#include <SDL.h>
#include <Windows.h>

long double map(long double value, long double in_min, long double in_max, long double out_min, long double out_max)
{
	return (value - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}
int main(int argc, char* argv[])
{
	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_Window* window;
	SDL_Renderer* renderer;
	int width = 800;
	int height = 800;
	long double min = -2.78;
	long double max = 1;
	int maxIteration = 200;
	long double factor = 1;
	SDL_CreateWindowAndRenderer(1920,1080,0,&window,&renderer);
	SDL_RenderSetLogicalSize(renderer, width, height);
	for (int i = 0; i < 39; i++)
	{
		max -= 0.1 * factor;
		min += 0.15 * factor;
		factor *= 0.94;
		SDL_RenderPresent(renderer);
		for (int x = 0; x < width; x++)
		{
			for (int y = 0; y < height; y++)
			{
				long double a = map(x, 0, width, min, max);
				long double b = map(y, 0, height, min, max);
				long double ai = a;
				long double bi = b;
				int i = 0;
				for (i ; i < maxIteration; i++)
				{
					long double a1 = a * a - b * b;
					long double b1 = 2 * a * b;
					a = a1 + ai;
					b = b1 + bi;
					if ((a + b) > 2)
					{
						break;
					}
				}
				int bright = map(n, 0, maxIteration, 0, 255);
				if (i == maxIteration||bright<21 )
				{
					bright = 0;
				}
				int red = map(bright * bright, 0, 4242, 0, 255);
				int green = bright;
				int blue = map(sqrt(bright), 0, 42, 0, 255);
				SDL_SetRenderDrawColor(renderer, red, green, blue, 255);
				SDL_RenderDrawPoint(renderer, x, y);
			}
		}
	}
	return 0;
}
