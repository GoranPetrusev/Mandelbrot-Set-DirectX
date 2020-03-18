/****************************************************************************************** 
 *	Chili DirectX Framework Version 16.07.20											  *	
 *	Game.h																				  *
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
#pragma once

#include "Keyboard.h"
#include "Mouse.h"
#include "Graphics.h"
#include <vector>

class Game
{
public:
	Game( class MainWindow& wnd );
	Game( const Game& ) = delete;
	Game& operator=( const Game& ) = delete;
	void Go();
private:
	void ComposeFrame();
	void UpdateModel();
	/********************************/
    int mapColor(int iterations);
    int invert(int x);
	/*  User Functions              */
	/********************************/
private:
	MainWindow& wnd;
	Graphics gfx;
	/********************************/
    int max_iterations = 1000;
    int result = 0;
    float color_const = 255.0f * (float(max_iterations) * 0.0083f); //0.0083f
    float delta_pan = 0.1f;
    float zoom = 1.5f;
    float mult_for_panning = delta_pan * zoom;
    float x_off = -0.7f;
    float y_off = -0.0f;
    static constexpr float width = Graphics::ScreenWidth;
    static constexpr float height = Graphics::ScreenHeight;
    float h_boundry = width / 2;
    float v_boundry = height / 2;
    float h_mapping = zoom / h_boundry;
    float v_mapping = zoom / v_boundry;
	/*  User Variables              */
	/********************************/
};