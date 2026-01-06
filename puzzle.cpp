#include <SFML/Graphics.hpp>
#include <iostream>
using namespace sf;

int main() {
    RenderWindow pencere(VideoMode(256, 256), "15-Puzzle!"); [cite: 381]
    pencere.setFramerateLimit(60); [cite: 382]
    Texture doku;
    doku.loadFromFile("images/15.png"); [cite: 384]

    int hucreGenisligi = 64; [cite: 385]
    int bulmacaTablosu[6][6] = {0}; [cite: 386]
    Sprite parcaSprite[20]; [cite: 387]
    int parcaSayisi = 0; [cite: 388]

    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++) {
            parcaSayisi++; [cite: 392]
            parcaSprite[parcaSayisi].setTexture(doku); [cite: 393]
            parcaSprite[parcaSayisi].setTextureRect(IntRect(i * hucreGenisligi, j * hucreGenisligi, hucreGenisligi, hucreGenisligi)); [cite: 394]
            bulmacaTablosu[i + 1][j + 1] = parcaSayisi; [cite: 395]
        } [cite: 396]

    while (pencere.isOpen()) {
        Event olay;
        while (pencere.pollEvent(olay)) {
            if (olay.type == Event::Closed) pencere.close(); [cite: 402, 403]
            if (olay.type == Event::MouseButtonPressed)
                if (olay.key.code == Mouse::Left) {
                    Vector2i fareBasili = Mouse::getPosition(pencere); [cite: 407]
                    int satir = fareBasili.x / hucreGenisligi + 1; [cite: 408]
                    int sutun = fareBasili.y / hucreGenisligi + 1; [cite: 409]
                    int yonX = 0, yonY = 0; [cite: 410, 411]
                    if (bulmacaTablosu[satir + 1][sutun] == 16) { yonX = 1; yonY = 0; }; [cite: 412]
                    if (bulmacaTablosu[satir][sutun + 1] == 16) { yonX = 0; yonY = 1; }; [cite: 413]
                    if (bulmacaTablosu[satir][sutun - 1] == 16) { yonX = 0; yonY = -1; }; [cite: 414]
                    if (bulmacaTablosu[satir - 1][sutun] == 16) { yonX = -1; yonY = 0; }; [cite: 415]
                    int seciliNo = bulmacaTablosu[satir][sutun]; [cite: 416]
                    bulmacaTablosu[satir][sutun] = 16; [cite: 417]
                    bulmacaTablosu[satir + yonX][sutun + yonY] = seciliNo; [cite: 418]

                    parcaSprite[16].move(-yonX * hucreGenisligi, -yonY * hucreGenisligi); [cite: 420]
                    float hiz = 3; [cite: 421]
                    for (int i = 0; i < hucreGenisligi; i += hiz) {
                        parcaSprite[seciliNo].move(hiz * yonX, hiz * yonY); [cite: 423]
                        pencere.draw(parcaSprite[16]); [cite: 424]
                        pencere.draw(parcaSprite[seciliNo]); [cite: 425]
                        pencere.display(); [cite: 426]
                    }
                }
        }

        pencere.clear(Color::White); [cite: 429]
        for (int i = 0; i < 4; i++)
            for (int j = 0; j < 4; j++) {
                int no = bulmacaTablosu[i + 1][j + 1]; [cite: 433]
                parcaSprite[no].setPosition(i * hucreGenisligi, j * hucreGenisligi); [cite: 434]
                pencere.draw(parcaSprite[no]); [cite: 435]
            } [cite: 436]
        pencere.display(); [cite: 437]
    }
    return 0; [cite: 439]
}