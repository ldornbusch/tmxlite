/*********************************************************************
(c) Matt Marchant & contributors 2016 - 2019
http://trederia.blogspot.com

tmxlite - Zlib license.

This software is provided 'as-is', without any express or
implied warranty. In no event will the authors be held
liable for any damages arising from the use of this software.

Permission is granted to anyone to use this software for any purpose,
including commercial applications, and to alter it and redistribute
it freely, subject to the following restrictions:

1. The origin of this software must not be misrepresented;
you must not claim that you wrote the original software.
If you use this software in a product, an acknowledgment
in the product documentation would be appreciated but
is not required.

2. Altered source versions must be plainly marked as such,
and must not be misrepresented as being the original software.

3. This notice may not be removed or altered from any
source distribution.
*********************************************************************/

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>

#include <tmxlite/Map.hpp>

#include "SFMLOrthogonalLayer.hpp"

int main()
{
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "SFML window");
    window.setVerticalSyncEnabled(true);

    tmx::Map map;
    //map.load("assets/demo.tmx");
    //map.load("assets/demo2.tmx");
    map.load("../../wild_fairies/data/maps/Louy_1.tmx");
    //map.load("../../wild_fairies/data/maps/test_level.tmx");

    MapLayer layerZero(map, 0);
    MapLayer layerOne(map, 1);
    MapLayer layerTwo(map, 2);
    MapLayer layerThree(map, 3);
    MapLayer layerFour(map, 4);
    MapLayer layerFive(map, 5);

    tmx::TileLayer::Tile t = layerOne.getTile(24,13);
    layerFour.setTile(37,5,t,true);

    for(int x=0; x<5; x++)
    {
        layerZero.setColor(34,20+x,sf::Color(140,140,140,255));
        layerZero.setColor(25,20+x,sf::Color(140,140,140,255));
        layerZero.setColor(43,20+x,sf::Color(140,140,140,255));
    }

    layerThree.setColor(3,4,sf::Color::White,true);
    layerThree.setColor(3,5,sf::Color::White,true);
    layerThree.setColor(3,22,sf::Color::White,true);
    layerThree.setColor(3,23,sf::Color::White,true);
    layerThree.setColor(8,22,sf::Color::White,true);
    layerThree.setColor(8,23,sf::Color::White,true);

    for(int y=0; y<5; y++)
    {
        for(int x=0; x<5; x++)
        {
            layerZero.setColor(57+6*x,14+y,sf::Color(140,140,140,255), true);
            layerZero.setColor(58+6*x,14+y,sf::Color(140,140,140,255), true);
            layerZero.setColor(59+6*x,14+y,sf::Color(140,140,140,255), true);
        }
    }

    float yOff=1.f, xOff=1.f;
    int frames = 0;
    sf::Clock globalClock;
    while (window.isOpen())
    {

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyPressed)
            {
                int breakpoint=1;
        }
        }

        auto v=window.getView();
        v.move(xOff, yOff);
        if ((v.getCenter().x-v.getSize().x/2)<0 || (v.getCenter().x+v.getSize().x/2) > map.getTileCount().x*map.getTileSize().x){xOff = -xOff;}
        if ((v.getCenter().y-v.getSize().y/2)<0 || (v.getCenter().y+v.getSize().y/2)>map.getTileCount().y*map.getTileSize().y) {yOff = -yOff;}
        window.setView(v);

        int delta=(255-180)/2;
        double intensity = sin(static_cast<double>(frames)/11) * delta+delta;
        auto c = sf::Color(intensity+180, intensity+180, intensity+180);
        layerZero.setColor(4,9,c,false);
        layerZero.setColor(4,10,c,false);
        layerZero.setColor(5,9,c,false);
        layerZero.setColor(5,10,c,false);

        layerFour.setColor(9,12,c,false);
        layerFour.setColor(10,12,c,false);
        layerFour.setColor(11,12,c,false);
        layerFour.setColor(9,13,c,false);
        layerFour.setColor(10,13,c,false);
        layerFour.setColor(11,13,c,true);


        c = sf::Color(intensity*0.75+180, intensity*0.75+180, intensity*0.75+180);
        layerZero.setColor(3,9,c,false);
        layerZero.setColor(3,10,c,false);
        layerZero.setColor(6,9,c,false);
        layerZero.setColor(6,10,c,true);

        sf::Time duration = globalClock.restart();
        layerZero.update(duration);

        layerOne.update(duration);
        layerTwo.update(duration);
        layerThree.update(duration);
        layerFour.update(duration);

        double r = sin(static_cast<double>(frames)/41)*0.5+0.5;
        double g = cos(static_cast<double>(frames)/13)*0.5+0.5;
        double b = sin(static_cast<double>(frames)/61)*0.5+0.5;
        for(unsigned int y=0; y<map.getTileCount().y;y++)
        {
            double min=64;
            delta=(255-min)/2;
            for(unsigned int x=0; x<map.getTileCount().x;x++)
            {
            intensity = sin(static_cast<double>(frames)/15+static_cast<double>(y*x)/2000) * delta+delta;
            c = sf::Color(intensity+min*r, intensity+min*g, intensity+min*b);
                layerZero.setColor(x,y,c, false);
            }
        }
        layerZero.generateTiles();

        window.clear(sf::Color::Black);
        window.draw(layerZero);
        window.draw(layerOne);
        window.draw(layerTwo);
        window.draw(layerThree);
        window.draw(layerFour);
        window.draw(layerFive);
        window.display();
        frames++;
    }

    return frames;
}
