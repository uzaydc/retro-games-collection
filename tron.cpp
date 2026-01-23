#include <SFML/Graphics.hpp>
#include <time.h>
using namespace sf;

const int GEN = 600, YUK = 480;
int aracHizi = 4;
bool izHaritasi[GEN][YUK] = {0};

struct Yarisci {
    int x, y, yon;
    Color renk;
    Yarisci(Color c) {
        x = rand() % GEN; y = rand() % YUK;
        renk = c; yon = rand() % 4;
    }
    void konumGuncelle() {
        if (yon == 0) y += 1;
        if (yon == 1) x -= 1;
        if (yon == 2) x += 1;
        if (yon == 3) y -= 1;
        if (x >= GEN) x = 0; if (x < 0) x = GEN - 1;
        if (y >= YUK) y = 0; if (y < 0) y = YUK - 1;
    [cite_start]} [cite: 1244-1252]
};

int main() {
    srand(time(0));
    RenderWindow pencere(VideoMode(GEN, YUK), "The Tron Game!");
    pencere.setFramerateLimit(60);
    Texture tArka; tArka.loadFromFile("background.jpg");
    Sprite sArka(tArka);
    Yarisci y1(Color::Red), y2(Color::Green);
    Sprite sGosterge; RenderTexture rDoku;
    rDoku.create(GEN, YUK); rDoku.setSmooth(true);
    sGosterge.setTexture(rDoku.getTexture());
    rDoku.clear(); rDoku.draw(sArka);
    bool oyunDevam = 1;

    while (pencere.isOpen()) {
        Event olay;
        while (pencere.pollEvent(olay)) { if (olay.type == Event::Closed) pencere.close(); }
        if (Keyboard::isKeyPressed(Keyboard::Left) && y1.yon != 2) y1.yon = 1;
        if (Keyboard::isKeyPressed(Keyboard::Right) && y1.yon != 1) y1.yon = 2;
        if (Keyboard::isKeyPressed(Keyboard::Up) && y1.yon != 0) y1.yon = 3;
        if (Keyboard::isKeyPressed(Keyboard::Down) && y1.yon != 3) y1.yon = 0;
        if (Keyboard::isKeyPressed(Keyboard::A) && y2.yon != 2) y2.yon = 1;
        if (Keyboard::isKeyPressed(Keyboard::D) && y2.yon != 1) y2.yon = 2;
        if (Keyboard::isKeyPressed(Keyboard::W) && y2.yon != 0) y2.yon = 3;
        [cite_start]if (Keyboard::isKeyPressed(Keyboard::S) && y2.yon != 3) y2.yon = 0; [cite: 1280-1287]

        if (!oyunDevam) continue;
        for(int i=0; i<aracHizi; i++) {
            y1.konumGuncelle(); y2.konumGuncelle();
            if (izHaritasi[y1.x][y1.y] == 1) oyunDevam = 0;
            if (izHaritasi[y2.x][y2.y] == 1) oyunDevam = 0;
            izHaritasi[y1.x][y1.y] = 1; izHaritasi[y2.x][y2.y] = 1;
            CircleShape nokta(3);
            nokta.setPosition(y1.x, y1.y); nokta.setFillColor(y1.renk); rDoku.draw(nokta);
            nokta.setPosition(y2.x, y2.y); nokta.setFillColor(y2.renk); rDoku.draw(nokta);
            rDoku.display();
        [cite_start]} [cite: 1289-1300]
        pencere.clear(); pencere.draw(sGosterge); pencere.display();
    }
    return 0;
}