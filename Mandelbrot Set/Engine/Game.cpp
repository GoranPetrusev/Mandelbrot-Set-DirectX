/****************************************************************************************** 
 *	Chili DirectX Framework Version 16.07.20											  *	
 *	Game.cpp																			  *
 *	Copyright 2016 PlanetChili.net <http://www.planetchili.net>							  *
 *																						  *
 *	This file is part of The Chili DirectX Framework.									  *
 *																						  *
 *	The Chili DirectX Framework is free software: you can redistribute it and/or modify	  *
 *	it under the terms of the GNU General Public License as published by				  *
 *	the Free Software Foundation, either version 3 of the License, or					  *
 *	(at your option) any later version.													  *
 *																						  *
 *	The Chili DirectX Framework is distributed in the hope that it will be useful,		  *
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of						  *
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the						  *
 *	GNU General Public License for more details.										  *
 *																						  *
 *	You should have received a copy of the GNU General Public License					  *
 *	along with The Chili DirectX Framework.  If not, see <http://www.gnu.org/licenses/>.  *
 ******************************************************************************************/
#include "MainWindow.h"
#include "Game.h"
#include <math.h>
#include <vector>

Game::Game( MainWindow& wnd )
	:
	wnd( wnd ),
	gfx( wnd )
{
}

void Game::Go()
{
	gfx.BeginFrame();	
	UpdateModel();
	ComposeFrame();
	gfx.EndFrame();
}

void Game::UpdateModel()
{
    mult_for_panning = delta_pan * zoom;
    if (wnd.kbd.KeyIsPressed('W'))
    {
        zoom -= (mult_for_panning);
    }
    else if (wnd.kbd.KeyIsPressed('S'))
    {
        zoom += (mult_for_panning);
    }
    if (wnd.kbd.KeyIsPressed(VK_UP))
    {
        y_off -= (mult_for_panning);
    }
    else if (wnd.kbd.KeyIsPressed(VK_DOWN))
    {
        y_off += (mult_for_panning);
    }
    if (wnd.kbd.KeyIsPressed(VK_LEFT))
    {
        x_off -= (mult_for_panning);
    }
    else if (wnd.kbd.KeyIsPressed(VK_RIGHT))
    {
        x_off += (mult_for_panning);
    }
}

void Game::ComposeFrame()
{
    for (float im = -v_boundry; im < v_boundry; im += 1.0f)
    {
        // idk why or how but adding -100 here fixes the stretching in the x-axis
        h_mapping = zoom / h_boundry;
        v_mapping = zoom / v_boundry;

        int drawing_y = im + int(v_boundry);
        float zi = im * v_mapping + y_off;

        for (float re = -h_boundry; re < h_boundry; re += 1.0f)
        {
            int drawing_x = re + int(h_boundry);

            float zr = re * h_mapping + x_off;
            float x = 0;
            float y = 0;
            float const_zr = zr;
            float rsquare = 0;
            float isquare = 0;
            float zsquare = 0;
            int iterations = 0;

            while (rsquare + isquare <= 4 && iterations < max_iterations)
            {
                x = rsquare - isquare + const_zr;
                y = zsquare - rsquare - isquare + zi;
                rsquare = x * x;
                isquare = y * y;
                zsquare = (x + y) * (x + y);
                iterations++;

            }
            /*
            while(x*x + y*y <= 4 && iterations < max_iterations)
            {
                float tempx = x * x - y * y + const_zr;
                y = 2 * x * y + zi;
                x = tempx;
                iterations++;
            }
            */

            int c_current_pixel = mapColor(iterations);
            Color c;
            c.SetR(c_current_pixel);
            c.SetG(c_current_pixel);
            c.SetB(c_current_pixel);
            gfx.PutPixel(drawing_x, drawing_y, c);
        }
    }
}

int Game::invert(int x) {
    if (x < 255) return x;
    else if ((x / 255) % 2 == 1) return 255 - (x % 255);
    else return 0 + (x % 255);
}

int Game::mapColor(int iterations)
{
    if (iterations == max_iterations)
        return 0;

    return invert((color_const / max_iterations) * iterations);
}

