#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>


SDL_Texture *init_image_texture(char* file_name, SDL_Renderer *renderer);

static const int width = 1280;
static const int height = 720;

struct initialize_texture_from_file {
    //SDL_Renderer *renderer;
    SDL_Texture *image_texture;
    SDL_Rect texture_destination;
    int image_width;
    int image_height;
};


int main()
{
    struct initialize_texture_from_file lena_jpg;
    struct initialize_texture_from_file rabbit_hole_jpg;


    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window *window = SDL_CreateWindow("Hello, SDL2", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_OPENGL);

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);

    //

    lena_jpg.image_texture = init_image_texture("lena.jpg", renderer);

    SDL_QueryTexture(lena_jpg.image_texture, NULL, NULL, &lena_jpg.image_width, &lena_jpg.image_height);

    lena_jpg.texture_destination.x = 100;
    lena_jpg.texture_destination.y = 50;
    lena_jpg.texture_destination.w = lena_jpg.image_width;
    lena_jpg.texture_destination.h = lena_jpg.image_height;


    //

    rabbit_hole_jpg.image_texture = init_image_texture("rabbit_hole.jpg", renderer);

    SDL_QueryTexture(rabbit_hole_jpg.image_texture, NULL, NULL, &rabbit_hole_jpg.image_width, &rabbit_hole_jpg.image_height);

    rabbit_hole_jpg.texture_destination.x = 530;
    rabbit_hole_jpg.texture_destination.y = 70;
    rabbit_hole_jpg.texture_destination.w = rabbit_hole_jpg.image_width;
    rabbit_hole_jpg.texture_destination.h = rabbit_hole_jpg.image_height;



        bool running = true;
        SDL_Event event;
        while(running)
        {
            // Process events
            while(SDL_PollEvent(&event))
            {
                if(event.type == SDL_QUIT)
                {
                    running = false;
                }
            }

            // Clear screen
            SDL_RenderClear(renderer);

            // Draw
            SDL_RenderCopy(renderer, lena_jpg.image_texture, NULL, &lena_jpg.texture_destination);
            SDL_RenderCopy(renderer, rabbit_hole_jpg.image_texture, NULL, &rabbit_hole_jpg.texture_destination);

            // Show what was drawn
            SDL_RenderPresent(renderer);
        }

        // Release resources
        SDL_DestroyTexture(lena_jpg.image_texture);
        SDL_DestroyTexture(rabbit_hole_jpg.image_texture);
        IMG_Quit();
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();

        return 0;


}
SDL_Texture *init_image_texture(char* file_name, SDL_Renderer *renderer) {
    SDL_Surface *image = IMG_Load(file_name);
    SDL_Texture *image_texture = SDL_CreateTextureFromSurface(renderer, image);
    SDL_FreeSurface(image);
    return image_texture;
}
