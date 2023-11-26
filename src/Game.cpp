//
// Created by matthewperiut on 5/7/21.
//

#define OLC_IMAGE_STB
#define OLC_PGE_APPLICATION
#include "Game.h"
#include "utility/AssetPath.h"
#include "tool/input/Options.h"
#include "objects/collision/Physical.h"

Game::Game() {
    sAppName = "Isoberry";
}

olc::Sprite* debugOverlay;
olc::Decal* debugOverlayDecal;
bool Game::OnUserCreate()
{
    debugOverlay = new olc::Sprite(ScreenWidth(), ScreenHeight());
    for(int i = 0; i < ScreenWidth(); i++)
    {
        for(int j = 0; j < ScreenHeight(); j++)
        {
            debugOverlay->SetPixel(i, j, olc::BLANK);
        }
    }
    debugOverlayDecal = new olc::Decal(debugOverlay);

    Clear(olc::Pixel(52, 92, 72));
    l = Level(*this);
    l.LoadFromFile(GetAssetPath() + "levels/basis.txt");

    maker.SetGameEngine(*this);
    maker.SetDrawOrderSystem(l.DOS);

    Shadow::CreateImages();
    test.Construct();

    clientBundle.localPlayer = &test;
    clientBundle.level = &l;
    client.StartThread(clientBundle);
    return true;
}

bool Game::OnUserUpdate(float fElapsedTime)
{
    Clear(olc::Pixel(52, 92, 72));
    maker.ObjectMakerStudio(fElapsedTime);
    res.handle(*this);

    // temporary
    static bool ShowFPS = false;
    if (GetKey(olc::F3).bPressed) ShowFPS = !ShowFPS;
    if (ShowFPS) DrawStringDecal(olc::vf2d(0,ScreenHeight()-8), std::to_string(GetFPS()));

    VSyncToggle(*this, fElapsedTime, olc::F4);
    FullScreenToggle(*this, fElapsedTime, olc::F5);

    if (GetKey(olc::ESCAPE).bPressed) return false;

    test.KeyboardInput(*this);
    test.Move(fElapsedTime);

    l.DOS.DrawAll();
    l.Loop(fElapsedTime);
    DrawDecal(olc::vf2d(0,0), debugOverlayDecal);
    return true;
}

bool Game::OnUserDestroy()
{
    garbage.DeleteAll();
    *clientBundle.running = false;
    client.clientThread.join();
    delete debugOverlay;
    delete debugOverlayDecal;
    return true;
}