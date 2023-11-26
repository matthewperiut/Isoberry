//
// Created by matthewperiut on 5/6/21.
//
#pragma once

#include <olcPixelGameEngine.h>

using namespace olc;

vi2d ConvertToHeight(vi2d input, int& scaleReturned);
vi2d ConvertToHeight(vi2d input);
vi2d GetNativeResolution();
vi2d GetResolution();