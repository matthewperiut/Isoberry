//
// Created by matthewperiut on 5/6/21.
//
#include "native.h"
#include "resolution.h"

#ifdef __linux__
#include <X11/Xlib.h>

using namespace X11;

vi2d GetNativeResolution()
{
    Display* d = XOpenDisplay(NULL);
    Screen*  s = DefaultScreenOfDisplay(d);
    int width = s->width;
    int height = s->height;
    return vi2d(width, height);
}
#elif _WIN32
#include <Windows.h>
vi2d GetNativeResolution()
{
    HWND hd = GetDesktopWindow();
	RECT rect;
	GetClientRect(hd, &rect);
	int client_width = (rect.right - rect.left);
	int client_height = (rect.bottom - rect.top);
	return vi2d(client_width, client_height);
}
#elif  __APPLE__
    #include <CoreGraphics/CGDisplayConfiguration.h>
    vi2d GetNativeResolution()
    {
        auto mainDisplayId = CGMainDisplayID();
        int width = CGDisplayPixelsWide(mainDisplayId);
        int height = CGDisplayPixelsHigh(mainDisplayId);
        return vi2d(width, height);
    }
#endif

vi2d ConvertToHeight(vi2d input, int& scaleReturned)
{
    float scale = float(input.y)/NATIVESCREENHEIGHT;
    scaleReturned = round(scale);
    int width = input.x / scale;
    int height = input.y / scale;
    return vi2d(width, height);
}
vi2d ConvertToHeight(vi2d input)
{
    int scaleReturned;
    return ConvertToHeight(input, scaleReturned);
}

vi2d GetResolution()
{
    vi2d native = GetNativeResolution();
    return ConvertToHeight(native);
}