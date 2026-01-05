#include <SFML/Graphics.hpp>
#include <time.h>

using namespace sf;

int GENISLIK = 30, YUKSEKLIK = 20;
int KARE_BOYUTU = 16;
int ekranW = KARE_BOYUTU * GENISLIK;
int ekranH = KARE_BOYUTU * YUKSEKLIK;

int yon, govdeUzunlugu = 4;

struct Bogum { int x, y; } yilan[100];
struct Yem { int x, y; } elma;

void hareketEt() {
    for (int i = govdeUzunlugu; i > 0; --i) {
        yilan[i].x = yilan[i-1].x; 
        yilan[i].y = yilan[i-1].y;
    }

    if (yon == 0) yilan[0].y += 1; // Aşağı
    if (yon == 1) yilan[0].x -= 1; // Sol
    if (yon == 2) yilan[0].x += 1; // Sağ
    if (yon == 3) yilan[0].y -= 1; // Yukarı

    // Yem yeme kontrolü
    if ((yilan[0].x == elma.x) && (yilan[0].y == elma.y)) {
        govdeUzunlugu++; 
        elma.x = rand() % GENISLIK; 
        elma.y = rand() % YUKSEKLIK;
    }

    // Duvarlardan geçme mantığı
    if (yilan[0].x >= GENISLIK) yilan[0].x = 0; if (yilan[0].x < 0) yilan[0].x = GENISLIK - 1;
    if (yilan[0].y >= YUKSEKLIK) yilan[0].y = 0; if (yilan[0].y < 0) yilan[0].y = YUKSEKLIK - 1;

    // Kendine çarpma kontrolü
    for (int i = 1; i < govdeUzunlugu; i++)
        if (yilan[0].x == yilan[i].x && yilan[0].y == yilan[i].y) govdeUzunlugu = i;
}

int main() {
    srand(time(0));
    RenderWindow ekran(VideoMode(ekranW, ekranH), "Yilan Avda!");

    Texture tArka, tObje;
    tArka.loadFromFile("images/white.png");
    tObje.loadFromFile("images/red.png");

    Sprite kareIzgarasi(tArka), objeGorunumu(tObje);
    Clock zamanlayici;
    float saniyeBasina = 0, gecikme = 0.1;

    elma.x = 10; elma.y = 10;

    while (ekran.isOpen()) {
        float sure = zamanlayici.getElapsedTime().asSeconds();
        zamanlayici.restart();
        saniyeBasina += sure;

        Event olay;
        while (ekran.pollEvent(olay)) {
            if (olay.type == Event::Closed) ekran.close();
        }

        if (Keyboard::isKeyPressed(Keyboard::Left)) yon = 1;
        if (Keyboard::isKeyPressed(Keyboard::Right)) yon = 2;
        if (Keyboard::isKeyPressed(Keyboard::Up)) yon = 3;
        if (Keyboard::isKeyPressed(Keyboard::Down)) yon = 0;

        if (saniyeBasina > gecikme) { saniyeBasina = 0; hareketEt(); }

        ekran.clear();
        for (int i = 0; i < GENISLIK; i++)
            for (int j = 0; j < YUKSEKLIK; j++) {
                kareIzgarasi.setPosition(i * KARE_BOYUTU, j * KARE_BOYUTU);
                ekran.draw(kareIzgarasi);
            }

        for (int i = 0; i < govdeUzunlugu; i++) {
            objeGorunumu.setPosition(yilan[i].x * KARE_BOYUTU, yilan[i].y * KARE_BOYUTU);
            ekran.draw(objeGorunumu);
        }

        objeGorunumu.setPosition(elma.x * KARE_BOYUTU, elma.y * KARE_BOYUTU);
        ekran.draw(objeGorunumu);
        ekran.display();
    }
    return 0;
}