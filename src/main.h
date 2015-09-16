#ifndef _MAIN_H
#define _MAIN_H
#include <guichan.hpp>
#include <tmxparser/Tmx.h>
#include "font/XFont.h"
#include "map/XMap.h"
#include "net/LoginConn.h"
#include "net/MapConn.h"
#include "being/XLocalPlayer.h"
#include "map/TmxMap.h"
#include "Game.h"
#include <stdint.h>
#include "gui/ChatWindow.h"
#include "gui/NpcDialog.h"

namespace globals
{
    extern gcn::Gui *gui;
    extern modou::TmxMap *map;
    extern modou::XLocalPlayer *localPlayer;
    extern modou::LoginConn *loginConn;
    extern modou::Game *gGame;
    extern uint64_t tick;
    extern modou::NpcDialog *gNpcDlg;
    extern modou::ChatWindow *gChatWindow;
    extern modou::MapConn *mapConn;
}

static const int mapTileSize = 32;
static const int screenWidth = 800;
static const int screenHeight = 600;



#endif
