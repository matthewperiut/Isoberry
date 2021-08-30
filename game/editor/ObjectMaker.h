#include "../objects/Object.h"

class ObjectMaker
{
private:
    olc::PixelGameEngine* engine;
    DrawOrderSystem* DOS;

    olc::Sprite* sprite{ nullptr };
    olc::Decal* decal{ nullptr };
    Collider collider;
    Object object;

    float countedTime = 10;
    enum modes{ clear, move, resize };
    int mode = modes::move;
    std::string textMode = "Clear";

    bool active = false;

public:

    void SetGameEngine(olc::PixelGameEngine& engine);
    void SetDrawOrderSystem(DrawOrderSystem& DOS);
    void UpdateObjectSize();

    void ObjectMakerStudio(float fElapsedTime);
    void SelectMode(float fElapsedTime);
    ~ObjectMaker();
};