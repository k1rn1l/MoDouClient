#include <SDL.h>
#include <iostream>
#include <guichan.hpp>
#include "main.h"
#include "sdlhelp.hpp"
#include "helloworld.hpp"

gcn::Gui *(globals::gui) = new gcn::Gui();

modou::NpcDialog *(globals::gNpcDlg) = new modou::NpcDialog();
modou::ChatWindow *(globals::gChatWindow) = new modou::ChatWindow();

modou::TmxMap *(globals::map) = NULL;
modou::XLocalPlayer *(globals::localPlayer) = NULL;

modou::Game *(globals::gGame) = NULL;
uint64_t globals::tick=0;

// this connection must be init after dialog.
modou::LoginConn *(globals::loginConn) = new modou::LoginConn("127.0.0.1", 2048);
modou::MapConn *(globals::mapConn) = new modou::MapConn("127.0.0.1", 2049);
modou::ChatConn *(globals::chatConn) = new modou::ChatConn("127.0.0.1", 2050);

int main(int argc, char *argv[])
{
    try
    {
        sdl::init();
        modou::init();
        sdl::run();
        modou::halt();
        sdl::halt();
    }
    // Catch all Guichan exceptions.
    catch (gcn::Exception e)
    {
        std::cerr << e.getMessage() << std::endl;
        return 1;
    }
    // Catch all Std exceptions.
    catch (std::exception e)
    {
        std::cerr << "Std exception: " << e.what() << std::endl;
        return 1;
    }
    // Catch all unknown exceptions.
    catch (...)
    {
        std::cerr << "Unknown exception" << std::endl;
        return 1;
    }
    return 0;
}
