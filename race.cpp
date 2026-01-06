#include <SFML/Graphics.hpp>
#include <math.h>
using namespace sf;

const int noktaAdedi = 8;
int durakNoktalari[noktaAdedi][2] = { {300, 610}, {1270, 430}, {1380, 2380}, {1900, 2460}, {1970, 1700}, {2550, 1680}, {2560, 3150}, {500, 3300} }; [cite: 445-452]

struct Araba {
    float x, y, hiz, aci;
    int hedef;
    Araba() { hiz = 2; aci = 0; hedef = 0; } [cite: 456]
    void hareketEt() {
        x += sin(aci) * hiz;
        y -= cos(aci) * hiz;
    } [cite: 457-461]
    void hedefeYonel() {
        float hedefX = durakNoktalari[hedef][0]; [cite: 464]
        float hedefY = durakNoktalari[hedef][1]; [cite: 465]
        float sapma = aci - atan2(hedefX - x, -hedefY + y); [cite: 466]
        if (sin(sapma) < 0) aci += 0.005 * hiz; else aci -= 0.005 * hiz; [cite: 467]
        if ((x - hedefX) * (x - hedefX) + (y - hedefY) * (y - hedefY) < 25 * 25) hedef = (hedef + 1) % noktaAdedi; [cite: 468]
    }
};

int main() {
    RenderWindow pencere(VideoMode(640, 480), "Araba Yarisi!"); [cite: 473]
    pencere.setFramerateLimit(60); [cite: 474]
    Texture tZemin, tArac;
    tZemin.loadFromFile("images/background.png"); [cite: 476]
    tArac.loadFromFile("images/car.png"); [cite: 477]
    tZemin.setSmooth(true); tArac.setSmooth(true); [cite: 478, 479]
    Sprite sZemin(tZemin), sArac(tArac); [cite: 480]
    sZemin.scale(2, 2); sArac.setOrigin(22, 22); [cite: 481, 482]

    float yariCap = 22; [cite: 483]
    const int ARAC_SAYISI = 5;
    Araba araclar[ARAC_SAYISI]; [cite: 485]
    for (int i = 0; i < ARAC_SAYISI; i++) {
        araclar[i].x = 300 + i * 50;
        araclar[i].y = 1700 + i * 80;
        araclar[i].hiz = 7 + i;
    } [cite: 488-491]

    float hiz = 0, aci = 0; [cite: 492]
    float limitHiz = 12.0, ivme = 0.2, fren = 0.3, donusHizi = 0.08; [cite: 493-495]
    int kaymaX = 0, kaymaY = 0; [cite: 496]

    while (pencere.isOpen()) {
        Event olay;
        while (pencere.pollEvent(olay)) {
            if (olay.type == Event::Closed) pencere.close(); [cite: 502, 503]
        }

        bool gaz = 0, sag = 0, frenYap = 0, sol = 0; [cite: 505]
        if (Keyboard::isKeyPressed(Keyboard::Up)) gaz = 1; [cite: 506]
        if (Keyboard::isKeyPressed(Keyboard::Right)) sag = 1; [cite: 507]
        if (Keyboard::isKeyPressed(Keyboard::Down)) frenYap = 1; [cite: 508]
        if (Keyboard::isKeyPressed(Keyboard::Left)) sol = 1; [cite: 509]

        if (gaz && hiz < limitHiz) { if (hiz < 0) hiz += fren; else hiz += ivme; } [cite: 511-513]
        if (frenYap && hiz > -limitHiz) { if (hiz > 0) hiz -= fren; else hiz -= ivme; } [cite: 514-516]
        if (!gaz && !frenYap) { if (hiz - fren > 0) hiz -= fren; else if (hiz + fren < 0) hiz += fren; else hiz = 0; } [cite: 517-520]

        if (sag && hiz != 0) aci += donusHizi * hiz / limitHiz; [cite: 521]
        if (sol && hiz != 0) aci -= donusHizi * hiz / limitHiz; [cite: 522]

        araclar[0].hiz = hiz; araclar[0].aci = aci; [cite: 523, 524]
        for (int i = 0; i < ARAC_SAYISI; i++) araclar[i].hareketEt(); [cite: 525]
        for (int i = 1; i < ARAC_SAYISI; i++) araclar[i].hedefeYonel(); [cite: 526]

        // Çarpışma kontrolleri [cite: 528-542] aynı mantıkla değişken isimleri güncellendi...
        pencere.clear(Color::White); [cite: 543]
        if (araclar[0].x > 320) kaymaX = araclar[0].x - 320; [cite: 544]
        if (araclar[0].y > 240) kaymaY = araclar[0].y - 240; [cite: 545]
        sZemin.setPosition(-kaymaX, -kaymaY); pencere.draw(sZemin); [cite: 546, 547]

        Color renkPaleti[5] = { Color::Red, Color::Green, Color::Magenta, Color::Blue, Color::White }; [cite: 548]
        for (int i = 0; i < ARAC_SAYISI; i++) {
            sArac.setPosition(araclar[i].x - kaymaX, araclar[i].y - kaymaY);
            sArac.setRotation(araclar[i].aci * 180 / 3.141593);
            sArac.setColor(renkPaleti[i]);
            pencere.draw(sArac);
        } [cite: 549-555]
        pencere.display(); [cite: 556]
    }
    return 0; [cite: 558]
}