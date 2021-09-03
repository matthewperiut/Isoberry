#include "../objects/Object.h"

class ObjectMaker
{
private:
    olc::PixelGameEngine* engine{};
    DrawOrderSystem* DOS{};

    olc::Sprite* sprite{ nullptr };
    olc::Decal* decal{ nullptr };
    Object object{v3(10,10,10), v3(-11, 0, 0)};

    float countedTime = 10;
    std::string textMode = "Clear";
    enum modes{ clear, move, resize };
    int mode = modes::move;

    olc::vi2d initialMouse{ 0, 0 };
    olc::vi2d finalMouse{ 0, 0 };
    char axis = 'o';

    bool active = false;

public:

    ObjectMaker();

public: // MUST set before usage
    void SetGameEngine(olc::PixelGameEngine& engine);
    void SetDrawOrderSystem(DrawOrderSystem& DOS);

private: // internal use (and debug for now)
    void UpdateObjectSize();

public: // MUST use per frame
    void ObjectMakerStudio(float fElapsedTime);

private: // subcomponents of ObjectMakerStudio
    void SelectMode(float fElapsedTime);
    void SelectAxis();
    void Move();
    void Resize();

public:
    ~ObjectMaker();

    Object GetObject();
};