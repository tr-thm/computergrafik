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

#include <fstream>
#include <sstream>
#include <string>
#include "cgmath.h"

struct FileReader
{
    FileReader(std::string filename);
    bool hasLine();
    std::string getString();
    float getFloat();
    Vector2 getVector2();
    Vector3 getVector3();

    std::ifstream fileStream;
    std::istringstream lineStream;
};
