#ifndef GENERATE_COLOR_IMG_HPP
#define GENERATE_COLOR_IMG_HPP

#include <SFML/Graphics.hpp>
#include <iostream>

#include "PerlinNoise.hpp"
#include "Defines.hpp"

void generateTexture() {
    std::srand(std::time(nullptr));
    int random_value = std::rand();

    const siv::PerlinNoise::seed_type seedRed = std::rand();
    const siv::PerlinNoise::seed_type seedGreen = rand();
    const siv::PerlinNoise::seed_type seedBlue = rand();
    sf::Uint8* pixels = new sf::Uint8[GEN_IMG_WIDTH*GEN_IMG_HEIGHT*4];

	const siv::PerlinNoise redPerlin{ seedRed };
    const siv::PerlinNoise greenPerlin{ seedGreen };
    const siv::PerlinNoise bluePerlin{ seedBlue };

    float frequency = 1.;
    const double fx = (frequency / GEN_IMG_WIDTH);
    const double fy = (frequency / GEN_IMG_HEIGHT);

    int maxColor = 255;
    int octaves = 2;
    float persistens = 4.;
	
	for (int y = 0; y < GEN_IMG_HEIGHT; ++y)
	{
		for (int x = 0; x < GEN_IMG_WIDTH; ++x)
		{
			const double red = redPerlin.octave2D_01((x * fx), (y * fy), octaves, persistens) * maxColor;
            const double green = greenPerlin.octave2D_01((x * fx), (y * fy), octaves, persistens) * maxColor;
            const double blue = bluePerlin.octave2D_01((x * fx), (y * fy), octaves, persistens) * maxColor;

            int index = (y * GEN_IMG_WIDTH + x) *4;
            pixels[index] = red;
            pixels[index+1] = green;
            pixels[index+2] = blue;
            pixels[index+3] = 255;	
		}
	}
    //delete[] pixels;
    sf::Image colorIMG;
    colorIMG.create(GEN_IMG_WIDTH, GEN_IMG_HEIGHT, pixels);
    colorIMG.saveToFile(RESOURCE_PATH "color_textures/colorPIC_gen.png");
}

#endif