/**
 * Computergrafik
 * Copyright (C) 2023 Tobias Reimann
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

#define GLFW_INCLUDE_GLEXT
#include <GLFW/glfw3.h>
#include <iostream>
#include "cgmath.h"
#include "settings.h"

static Settings settings;
static int viewportWidth = 0;
static int viewportHeight = 0;
static int resizeViewport = false;
static Matrix viewMatrix = matrixTranslate(0.0f, 0.0f, -2.0f);

static void setViewport()
{
    if (resizeViewport)
    {
        resizeViewport = false;

        glViewport(0,0, viewportWidth, viewportHeight);
        double zNear = 0.1;
        double zFar = 100.0;
        double fov = 0.785; //45deg

        double h = zNear * tan(fov * 0.5);
        double w = h * (double)viewportWidth / (double)viewportHeight;

        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glFrustum(-w, w, -h, h, zNear, zFar);
    }
}

bool graphicsStart(Settings props)
{
    settings = props;
    glfwSwapInterval(props.vsync ? 1 : 0);
    if (settings.msaa) glEnable(GL_MULTISAMPLE);
    if (settings.culling) glEnable(GL_CULL_FACE);

    glClearColor(0.29f,0.36f,0.4f,1.0f);

    return true;
}

void graphicsLoop()
{
    setViewport();
    
    glClear(GL_COLOR_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glMultMatrixf(viewMatrix.values);

    glBegin(GL_QUADS);
    glColor3f(0.5f, 0.73f, 0.14f);
    glVertex3f(-0.6f, 0.0f, 0.0f);
    glVertex3f(0.0f, -0.6f, 0.0f);
    glVertex3f(0.6f, 0.0f, 0.0f);
    glVertex3f(0.0f, 0.6f, 0.0f);
    glEnd();
}

void graphicsTerminate()
{

}

void graphicsSetWindowSize(int width, int height)
{
    std::cout << "Resolution: " << width << "x" << height << std::endl;
    viewportWidth = width;
    viewportHeight = height;
    resizeViewport = true;
}