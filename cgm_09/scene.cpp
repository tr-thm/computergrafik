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

#include "scene.h"
#include "filereader.h"

Scene::Scene(std::string filename)
{
    FileReader reader = FileReader(filename);
    while (reader.hasLine())
    {
        std::string type = reader.getString();
        if (type == "e")
        {
            entities.push_back(new Entity(reader.getString()));
        }
        else if (type == "m")
        {
            entities[entities.size() - 1]->setModel(reader.getString());
        }
        else if (type == "p")
        {
            entities[entities.size() - 1]->setPosition(reader.getVector3());
        }
        else if (type == "r")
        {
            entities[entities.size() - 1]->setRotation(deg2rad(reader.getVector3()));
        }
        else if (type == "s")
        {
            entities[entities.size() - 1]->setScale(reader.getFloat());
        }
        else if (type == "f")
        {
            entities[entities.size() - 1]->addFlag(reader.getString());
        }
    }
    for (int i = 0; i < entities.size(); i++)
    {
        entities[i]->load();
    }
}

Scene::~Scene()
{
    for (int i = 0; i < entities.size(); i++)
    {
        delete entities[i];
    }
    entities.clear();
}

void Scene::update(double time)
{
    for (int i = 0; i < entities.size(); i++)
    {
        entities[i]->update(time);
    }
}
