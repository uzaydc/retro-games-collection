#include <SFML/Graphics.hpp>
#include <time.h>
#include "Connector.hpp"
using namespace sf;

int kareOlcusu = 56;
Vector2f kayma(28,28);
Sprite figurler[32];
std::string mevcutPozisyon = "";
int satrancTahtasi[8][8] = {
    -1,-2,-3,-4,-5,-3,-2,-1, -6,-6,-6,-6,-6,-6,-6,-6,
     0, 0, 0, 0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0, 0, 0,
     0, 0, 0, 0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0, 0, 0,
     6, 6, 6, 6, 6, 6, 6, 6,  1, 2, 3, 4, 5, 3, 2, 1
[cite_start]}; [cite: 1317-1325]

std::string notasyonaCevir(Vector2f p) {
    std::string s = "";
    s += char(p.x/kareOlcusu + 97);
    s += char(7 - p.y/kareOlcusu + 49);
    return s;
[cite_start]} [cite: 1326-1332]

Vector2f koordinataCevir(char a, char b) {
    int x = int(a) - 97;
    int y = 7 - int(b) + 49;
    return Vector2f(x * kareOlcusu, y * kareOlcusu);
[cite_start]} [cite: 1333-1338]

void hareketEt(std::string hamle) {
    Vector2f eskiP = koordinataCevir(hamle[0], hamle[1]);
    Vector2f yeniP = koordinataCevir(hamle[2], hamle[3]);
    for(int i=0; i<32; i++) if (figurler[i].getPosition() == yeniP) figurler[i].setPosition(-100,-100);
    for(int i=0; i<32; i++) if (figurler[i].getPosition() == eskiP) figurler[i].setPosition(yeniP);
    if (hamle == "e1g1") if (mevcutPozisyon.find("e1") == -1) hareketEt("h1f1");
    if (hamle == "e8g8") if (mevcutPozisyon.find("e8") == -1) hareketEt("h8f8");
    if (hamle == "e1c1") if (mevcutPozisyon.find("e1") == -1) hareketEt("a1d1");
    if (hamle == "e8c8") if (mevcutPozisyon.find("e8") == -1) hareketEt("a8d8");
[cite_start]} [cite: 1339-1352]

void pozisyonYukle() {
    int sayac = 0;
    for(int i=0; i<8; i++)
        for(int j=0; j<8; j++) {
            int n = satrancTahtasi[i][j]; if (!n) continue;
            int x = abs(n) - 1; int y = n > 0 ? 1 : 0;
            figurler[sayac].setTextureRect(IntRect(kareOlcusu * x, kareOlcusu * y, kareOlcusu, kareOlcusu));
            figurler[sayac].setPosition(kareOlcusu * j, kareOlcusu * i); sayac++;
        }
    for(int i=0; i<mevcutPozisyon.length(); i+=5) hareketEt(mevcutPozisyon.substr(i,4));
[cite_start]} [cite: 1353-1369]

int main() {
    RenderWindow pencere(VideoMode(504, 504), "The Chess! (press SPACE)");
    ConnectToEngine("stockfish.exe");
    Texture tSekiller, tTahta;
    tSekiller.loadFromFile("images/figures.png"); tTahta.loadFromFile("images/board.png");
    for(int i=0; i<32; i++) figurler[i].setTexture(tSekiller);
    Sprite sTahta(tTahta); pozisyonYukle();
    bool hamleModu = false; float dX = 0, dY = 0; Vector2f eskiPos, yeniPos; std::string hamleStr; int seciliNo = 0;

    while (pencere.isOpen()) {
        Vector2i fareP = Mouse::getPosition(pencere) - Vector2i(kayma);
        Event olay;
        while (pencere.pollEvent(olay)) {
            if (olay.type == Event::Closed) pencere.close();
            if (olay.type == Event::KeyPressed && olay.key.code == Keyboard::BackSpace) {
                if (mevcutPozisyon.length() > 6) mevcutPozisyon.erase(mevcutPozisyon.length()-6, 5); pozisyonYukle();
            }
            if (olay.type == Event::MouseButtonPressed && olay.key.code == Mouse::Left)
                for(int i=0; i<32; i++)
                    if (figurler[i].getGlobalBounds().contains(fareP.x, fareP.y)) {
                        hamleModu = true; seciliNo = i;
                        dX = fareP.x - figurler[i].getPosition().x; dY = fareP.y - figurler[i].getPosition().y;
                        eskiPos = figurler[i].getPosition();
                    }
            if (olay.type == Event::MouseButtonReleased && olay.key.code == Mouse::Left) {
                hamleModu = false;
                Vector2f p = figurler[seciliNo].getPosition() + Vector2f(kareOlcusu/2, kareOlcusu/2);
                yeniPos = Vector2f(kareOlcusu * int(p.x/kareOlcusu), kareOlcusu * int(p.y/kareOlcusu));
                hamleStr = notasyonaCevir(eskiPos) + notasyonaCevir(yeniPos);
                hareketEt(hamleStr); if (eskiPos != yeniPos) mevcutPozisyon += hamleStr + " ";
                figurler[seciliNo].setPosition(yeniPos);
            }
        [cite_start]} [cite: 1385-1419]

        if (Keyboard::isKeyPressed(Keyboard::Space)) {
            hamleStr = getNextMove(mevcutPozisyon);
            eskiPos = koordinataCevir(hamleStr[0], hamleStr[1]);
            yeniPos = koordinataCevir(hamleStr[2], hamleStr[3]);
            for(int i=0; i<32; i++) if (figurler[i].getPosition() == eskiPos) seciliNo = i;
            for(int k=0; k<50; k++) {
                Vector2f p = yeniPos - eskiPos; figurler[seciliNo].move(p.x/50, p.y/50);
                pencere.draw(sTahta);
                for(int i=0; i<32; i++) figurler[i].move(kay);
                for(int i=0; i<32; i++) pencere.draw(figurler[i]); pencere.draw(figurler[seciliNo]);
                for(int i=0; i<32; i++) figurler[i].move(-kay); pencere.display();
            }
            hareketEt(hamleStr); mevcutPozisyon += hamleStr + " "; figurler[seciliNo].setPosition(yeniPos);
        [cite_start]} [cite: 1421-1440]
        if (hamleModu) figurler[seciliNo].setPosition(fareP.x - dX, fareP.y - dY);
        pencere.clear(); pencere.draw(sTahta);
        for(int i=0; i<32; i++) figurler[i].move(kay);
        for(int i=0; i<32; i++) pencere.draw(figurler[i]); pencere.draw(figurler[seciliNo]);
        for(int i=0; i<32; i++) figurler[i].move(-kay); pencere.display();
    }
    CloseConnection(); return 0;
}