//
// Created by matthewperiut on 5/7/21.
//

#define OLC_IMAGE_STB
#define OLC_PGE_APPLICATION
#include "Game.h"
#include "../utility/AssetPath.h"
#include "tool/input/Options.h"
#include "objects/Object.h"

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

    maker.SetGameEngine(*this);
    maker.SetDrawOrderSystem(l.DOS);

    Clear(olc::Pixel(52, 92, 72));
    l = Level(*this);
    l.LoadFromFile(GetAssetPath() + "levels/basis.txt");

    Shadow::CreateImages();
    test.Construct();
    return true;
}

bool Game::OnUserUpdate(float fElapsedTime)
{
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
    DrawDecal(olc::vf2d(0,0), debugOverlayDecal);
    return true;
}

bool Game::OnUserDestroy()
{
    delete debugOverlay;
    delete debugOverlayDecal;
    return true;
}