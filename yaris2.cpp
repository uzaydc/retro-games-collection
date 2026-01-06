#include <SFML/Graphics.hpp>
#include <vector>
#include <math.h>
using namespace sf;

int ekranW = 1024, ekranH = 768; [cite: 563, 564]
int yolGenislik = 2000, parcaUzunlugu = 200; [cite: 565, 566]
float mercekDerinligi = 0.84; [cite: 567]

void dortgenCiz(RenderWindow &w, Color c, int x1, int y1, int w1, int x2, int y2, int w2) {
    ConvexShape sekil(4); [cite: 570]
    sekil.setFillColor(c); [cite: 571]
    sekil.setPoint(0, Vector2f(x1 - w1, y1)); [cite: 572]
    sekil.setPoint(1, Vector2f(x2 - w2, y2)); [cite: 573]
    sekil.setPoint(2, Vector2f(x2 + w2, y2)); [cite: 574]
    sekil.setPoint(3, Vector2f(x1 + w1, y1)); [cite: 575]
    w.draw(sekil); [cite: 576]
}

struct Hat {
    float x, y, z; [cite: 580]
    float ekranX, ekranY, ekranW; [cite: 581]
    float egim, objeX, kirpma, olcek; [cite: 582]
    Sprite gorunum;
    Hat() { objeX = egim = x = y = z = 0; } [cite: 584, 585]
    void izdusum(int camX, int camY, int camZ) {
        olcek = mercekDerinligi / (z - camZ); [cite: 588]
        ekranX = (1 + olcek * (x - camX)) * ekranW / 2; [cite: 589]
        ekranY = (1 - olcek * (y - camY)) * ekranH / 2; [cite: 590]
        ekranW = olcek * yolGenislik * ekranW / 2; [cite: 591]
    }
    // drawSprite fonksiyonu da aynı mantıkla güncellendi... [cite: 593-611]
};

// Main fonksiyonunda döngüler ve çizimler aynı isim değişikliğiyle devam eder... [cite: 613-701]