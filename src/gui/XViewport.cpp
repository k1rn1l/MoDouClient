#include "XViewport.h"
#include "main.h"
#include <sstream>
#include <guichan/sdl.hpp>
#include <SDL.h>

namespace modou
{
    XViewport::XViewport() : gcn::Container(),
        mMap(NULL),
        mPixelViewX(0),
        mPixelViewY(0)
    {
        addMouseListener(this);
        //mMap = new XMap(320, 240, mapTileSize, mapTileSize);
    }

    XViewport::~XViewport()
    {
        if (mMap)
            delete(mMap);
    }

    void XViewport::setMap(TmxMap *map)
    {
        mMap = map;
    }

    void XViewport::draw(gcn::Graphics *graphics)
    {
        if (!mMap) {
            graphics->setColor(gcn::Color(64, 64, 64));
            graphics->fillRectangle(gcn::Rectangle(0, 0, getWidth(), getHeight()));
            return;
        }
        
        if (globals::localPlayer) {
            XVector pos = globals::localPlayer->getPosition();
            mPixelViewX = static_cast<int>(pos.x) - screenWidth/2;
            mPixelViewY = static_cast<int>(pos.y) - screenHeight/2;
        }
        
        const int viewMaxX = mMap->GetWidth() * mMap->GetTileWidth() - getWidth();
        const int viewMaxY = mMap->GetHeight() * mMap->GetTileHeight() - getHeight();

        if (mPixelViewX < 0)
            mPixelViewX = 0;
        if (mPixelViewY < 0)
            mPixelViewY = 0;
        if (mPixelViewX > viewMaxX)
            mPixelViewX = viewMaxX;
        if (mPixelViewY > viewMaxY)
            mPixelViewY = viewMaxY;

        mMap->draw(graphics, mPixelViewX, mPixelViewY, getWidth(), getHeight());
        gcn::SDLGraphics *g = static_cast<gcn::SDLGraphics *>(graphics);
        std::stringstream ss;
        ss << "X:" << mPixelViewX << ", Y:" << mPixelViewY;
        g->drawText(ss.str(), 0, 0);
    }

    void XViewport::mousePressed(gcn::MouseEvent &event)
    {
        if (event.getSource() != this || event.isConsumed())
            return;
        if (!mMap)
            return;
        if (event.getButton() == gcn::MouseEvent::LEFT)
        {
            leftMouseAction();
        }
    }

    bool XViewport::leftMouseAction()
    {
        followMouse();
        return true;
    }

    void XViewport::followMouse()
    {
        if (globals::localPlayer) {
            int px, py;
            SDL_GetMouseState(&px, &py);
            XVector pos = globals::localPlayer->getPosition();
            if (px > getWidth()/2) {
                pos.x += mapTileSize;
                if (pos.x > globals::map->GetWidth() * mapTileSize)
                    pos.x = globals::map->GetWidth() * mapTileSize;
            } else {
                pos.x -= mapTileSize;
                if (pos.x < 0)
                    pos.x = 0;
            }
            globals::localPlayer->setPosition(pos);
            //globals::localPlayer->navigateTo(pos.x, pos.y);
        } else {
            std::cout << "local Player is no init " << std::endl;
        }
    }
}
