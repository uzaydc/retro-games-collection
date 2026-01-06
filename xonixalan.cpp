#include <SFML/Graphics.hpp>
#include <time.h>

using namespace sf;

[cite_start]const int BOY = 25; [cite: 706]
[cite_start]const int EN = 40; [cite: 707]
[cite_start]int haritaVerisi[BOY][EN] = {0}; [cite: 708]
[cite_start]int kareOlcusu = 18; [cite: 709]

struct KotuKarakter {
    [cite_start]int x, y, hizX, hizY; [cite: 711]
    KotuKarakter() {
        [cite_start]x = y = 300; [cite: 714]
        [cite_start]hizX = 4 - rand() % 8; [cite: 715]
        [cite_start]hizY = 4 - rand() % 8; [cite: 716]
    }
    void ilerle() {
        x += hizX; if (haritaVerisi[y / kareOlcusu][x / kareOlcusu] == 1) { hizX = -hizX; x += hizX; [cite_start]} [cite: 720]
        y += hizY; if (haritaVerisi[y / kareOlcusu][x / kareOlcusu] == 1) { hizY = -hizY; y += hizY; [cite_start]} [cite: 721]
    }
};

void alaniDoldur(int y, int x) {
    [cite_start]if (haritaVerisi[y][x] == 0) haritaVerisi[y][x] = -1; [cite: 726]
    [cite_start]if (haritaVerisi[y - 1][x] == 0) alaniDoldur(y - 1, x); [cite: 727]
    [cite_start]if (haritaVerisi[y + 1][x] == 0) alaniDoldur(y + 1, x); [cite: 728]
    [cite_start]if (haritaVerisi[y][x - 1] == 0) alaniDoldur(y, x - 1); [cite: 729]
    [cite_start]if (haritaVerisi[y][x + 1] == 0) alaniDoldur(y, x + 1); [cite: 730]
}

int main() {
    [cite_start]srand(time(0)); [cite: 734]
    [cite_start]RenderWindow pencere(VideoMode(EN * kareOlcusu, BOY * kareOlcusu), "Xonix Game!"); [cite: 735]
    [cite_start]pencere.setFramerateLimit(60); [cite: 736]
    [cite_start]Texture t1, t2, t3; [cite: 737]
    [cite_start]t1.loadFromFile("images/tiles.png"); [cite: 738]
    [cite_start]t2.loadFromFile("images/gameover.png"); [cite: 739]
    [cite_start]t3.loadFromFile("images/enemy.png"); [cite: 740]
    [cite_start]Sprite sKutu(t1), sKaybettin(t2), sDusman(t3); [cite: 741]
    [cite_start]sKaybettin.setPosition(100, 100); [cite: 742]
    [cite_start]sDusman.setOrigin(20, 20); [cite: 743]
    [cite_start]int canavarSayisi = 4; [cite: 744]
    [cite_start]KotuKarakter canavarlar[10]; [cite: 745]
    [cite_start]bool aktifMi = true; [cite: 746]
    [cite_start]int oyuncuX = 0, oyuncuY = 0, yonX = 0, yonY = 0; [cite: 747]
    [cite_start]float zamanlayici = 0, gecikme = 0.07; [cite: 748]
    [cite_start]Clock saat; [cite: 749]

    for (int i = 0; i < BOY; i++)
        for (int j = 0; j < EN; j++)
            [cite_start]if (i == 0 || j == 0 || i == BOY - 1 || j == EN - 1) haritaVerisi[i][j] = 1; [cite: 752]

    while (pencere.isOpen()) {
        [cite_start]float gecenZaman = saat.getElapsedTime().asSeconds(); [cite: 755]
        [cite_start]saat.restart(); [cite: 756]
        [cite_start]zamanlayici += gecenZaman; [cite: 757]
        Event olay;
        while (pencere.pollEvent(olay)) {
            [cite_start]if (olay.type == Event::Closed) pencere.close(); [cite: 762]
            if (olay.type == Event::KeyPressed)
                if (olay.key.code == Keyboard::Escape) {
                    for (int i = 1; i < BOY - 1; i++)
                        [cite_start]for (int j = 1; j < EN - 1; j++) haritaVerisi[i][j] = 0; [cite: 768]
                    [cite_start]oyuncuX = 10; oyuncuY = 0; aktifMi = true; [cite: 769-770]
                }
        }
        if (Keyboard::isKeyPressed(Keyboard::Left)) { yonX = -1; yonY = 0; [cite_start]}; [cite: 773]
        if (Keyboard::isKeyPressed(Keyboard::Right)) { yonX = 1; yonY = 0; [cite_start]}; [cite: 774]
        if (Keyboard::isKeyPressed(Keyboard::Up)) { yonX = 0; yonY = -1; [cite_start]}; [cite: 775]
        if (Keyboard::isKeyPressed(Keyboard::Down)) { yonX = 0; yonY = 1; [cite_start]}; [cite: 776]

        [cite_start]if (!aktifMi) continue; [cite: 777]
        if (zamanlayici > gecikme) {
            [cite_start]oyuncuX += yonX; oyuncuY += yonY; [cite: 780-781]
            [cite_start]if (oyuncuX < 0) oyuncuX = 0; if (oyuncuX > EN - 1) oyuncuX = EN - 1; [cite: 782]
            [cite_start]if (oyuncuY < 0) oyuncuY = 0; if (oyuncuY > BOY - 1) oyuncuY = BOY - 1; [cite: 783]
            [cite_start]if (haritaVerisi[oyuncuY][oyuncuX] == 2) aktifMi = false; [cite: 784]
            [cite_start]if (haritaVerisi[oyuncuY][oyuncuX] == 0) haritaVerisi[oyuncuY][oyuncuX] = 2; [cite: 785]
            [cite_start]zamanlayici = 0; [cite: 786]
        }
        [cite_start]for (int i = 0; i < canavarSayisi; i++) canavarlar[i].ilerle(); [cite: 788]
        if (haritaVerisi[oyuncuY][oyuncuX] == 1) {
            [cite_start]yonX = yonY = 0; [cite: 791]
            [cite_start]for (int i = 0; i < canavarSayisi; i++) alaniDoldur(canavarlar[i].y / kareOlcusu, canavarlar[i].x / kareOlcusu); [cite: 793]
            for (int i = 0; i < BOY; i++)
                for (int j = 0; j < EN; j++)
                    [cite_start]if (haritaVerisi[i][j] == -1) haritaVerisi[i][j] = 0; [cite: 796]
                    [cite_start]else haritaVerisi[i][j] = 1; [cite: 797]
        }
        for (int i = 0; i < canavarSayisi; i++)
            [cite_start]if (haritaVerisi[canavarlar[i].y / kareOlcusu][canavarlar[i].x / kareOlcusu] == 2) aktifMi = false; [cite: 800]

        [cite_start]pencere.clear(); [cite: 802]
        for (int i = 0; i < BOY; i++)
            for (int j = 0; j < EN; j++) {
                [cite_start]if (haritaVerisi[i][j] == 0) continue; [cite: 806]
                [cite_start]if (haritaVerisi[i][j] == 1) sKutu.setTextureRect(IntRect(0, 0, kareOlcusu, kareOlcusu)); [cite: 807]
                [cite_start]if (haritaVerisi[i][j] == 2) sKutu.setTextureRect(IntRect(54, 0, kareOlcusu, kareOlcusu)); [cite: 808]
                [cite_start]sKutu.setPosition(j * kareOlcusu, i * kareOlcusu); pencere.draw(sKutu); [cite: 809-810]
            }
        [cite_start]sKutu.setTextureRect(IntRect(36, 0, kareOlcusu, kareOlcusu)); [cite: 812]
        [cite_start]sKutu.setPosition(oyuncuX * kareOlcusu, oyuncuY * kareOlcusu); [cite: 813]
        [cite_start]pencere.draw(sKutu); [cite: 814]
        [cite_start]sDusman.rotate(10); [cite: 815]
        for (int i = 0; i < canavarSayisi; i++) {
            [cite_start]sDusman.setPosition(canavarlar[i].x, canavarlar[i].y); pencere.draw(sDusman); [cite: 818-819]
        }
        [cite_start]if (!aktifMi) pencere.draw(sKaybettin); [cite: 821]
        [cite_start]pencere.display(); [cite: 822]
    }
    return 0;
}