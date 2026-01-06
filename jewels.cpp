#include <SFML/Graphics.hpp>
#include <time.h>
using namespace sf;

int kareBoyutu = 54;
Vector2i kenarBoslugu(48,24);

struct Mucevher { 
    int x, y, sutun, satir, tip, eslesme, saydamlik;
    Mucevher() { eslesme = 0; saydamlik = 255; }
[cite_start]} mucevherTablosu[10][10]; [cite: 832-835]

void yerDegistir(Mucevher m1, Mucevher m2) {
    std::swap(m1.sutun, m2.sutun);
    std::swap(m1.satir, m2.satir);
    mucevherTablosu[m1.satir][m1.sutun] = m1;
    mucevherTablosu[m2.satir][m2.sutun] = m2;
[cite_start]} [cite: 836-842]

int main() {
    srand(time(0));
    RenderWindow uygulama(VideoMode(740,480), "Match-3 Game!");
    uygulama.setFramerateLimit(60);
    Texture tArkaplan, tTakilar;
    tArkaplan.loadFromFile("images/background.png");
    tTakilar.loadFromFile("images/gems.png");
    Sprite sArkaplan(tArkaplan), sTakilar(tTakilar);

    for (int i=1; i<=8; i++)
        for (int j=1; j<=8; j++) {
            mucevherTablosu[i][j].tip = rand()%3;
            mucevherTablosu[i][j].sutun = j;
            mucevherTablosu[i][j].satir = i;
            mucevherTablosu[i][j].x = j * kareBoyutu;
            mucevherTablosu[i][j].y = i * kareBoyutu;
        [cite_start]} [cite: 852-860]

    int eskiX, eskiY, yeniX, yeniY, tiklamaSayisi = 0; 
    Vector2i fareKonumu;
    bool takasYapildi = false, hareketVarMi = false;

    while (uygulama.isOpen()) {
        Event olay;
        while (uygulama.pollEvent(olay)) {
            if (olay.type == Event::Closed) uygulama.close();
            if (olay.type == Event::MouseButtonPressed)
                if (olay.key.code == Mouse::Left) {
                    if (!takasYapildi && !hareketVarMi) tiklamaSayisi++;
                    fareKonumu = Mouse::getPosition(uygulama) - kenarBoslugu;
                }
        [cite_start]} [cite: 865-876]

        if (tiklamaSayisi == 1) { eskiX = fareKonumu.x/kareBoyutu+1; eskiY = fareKonumu.y/kareBoyutu+1; }
        if (tiklamaSayisi == 2) {
            yeniX = fareKonumu.x/kareBoyutu+1; yeniY = fareKonumu.y/kareBoyutu+1;
            if (abs(yeniX-eskiX) + abs(yeniY-eskiY) == 1) { 
                yerDegistir(mucevherTablosu[eskiY][eskiX], mucevherTablosu[yeniY][yeniX]); 
                takasYapildi = 1; tiklamaSayisi = 0; 
            } else tiklamaSayisi = 1;
        [cite_start]} [cite: 878-890]

        for(int i=1; i<=8; i++)
            for(int j=1; j<=8; j++) {
                if (mucevherTablosu[i][j].tip == mucevherTablosu[i+1][j].tip && mucevherTablosu[i][j].tip == mucevherTablosu[i-1][j].tip)
                    for(int n=-1; n<=1; n++) mucevherTablosu[i+n][j].eslesme++;
                if (mucevherTablosu[i][j].tip == mucevherTablosu[i][j+1].tip && mucevherTablosu[i][j].tip == mucevherTablosu[i][j-1].tip)
                    for(int n=-1; n<=1; n++) mucevherTablosu[i][j+n].eslesme++;
            [cite_start]} [cite: 891-901]

        hareketVarMi = false;
        for (int i=1; i<=8; i++)
            for (int j=1; j<=8; j++) {
                Mucevher &m = mucevherTablosu[i][j];
                int dx, dy;
                for(int n=0; n<4; n++) {
                    dx = m.x - m.sutun * kareBoyutu;
                    dy = m.y - m.satir * kareBoyutu;
                    if (dx) m.x -= dx/abs(dx);
                    if (dy) m.y -= dy/abs(dy);
                }
                if (dx || dy) hareketVarMi = 1;
            [cite_start]} [cite: 902-915]

        if (!hareketVarMi)
            for (int i=1; i<=8; i++)
                for (int j=1; j<=8; j++)
                    if (mucevherTablosu[i][j].eslesme) 
                        if (mucevherTablosu[i][j].saydamlik > 10) { 
                            mucevherTablosu[i][j].saydamlik -= 10; hareketVarMi = true; 
                        [cite_start]} [cite: 917-920]

        int toplamPuan = 0;
        for (int i=1; i<=8; i++)
            for (int j=1; j<=8; j++) toplamPuan += mucevherTablosu[i][j].eslesme;

        if (takasYapildi && !hareketVarMi) { 
            if (!toplamPuan) yerDegistir(mucevherTablosu[eskiY][eskiX], mucevherTablosu[yeniY][yeniX]); 
            takasYapildi = 0; 
        [cite_start]} [cite: 927-928]

        if (!hareketVarMi) {
            for(int i=8; i>0; i--)
                for(int j=1; j<=8; j++)
                    if (mucevherTablosu[i][j].eslesme)
                        for(int n=i; n>0; n--)
                            if (!mucevherTablosu[n][j].eslesme) { 
                                yerDegistir(mucevherTablosu[n][j], mucevherTablosu[i][j]); break; 
                            }
            for(int j=1; j<=8; j++)
                for(int i=8, n=0; i>0; i--)
                    if (mucevherTablosu[i][j].eslesme) {
                        mucevherTablosu[i][j].tip = rand()%7;
                        mucevherTablosu[i][j].y = -kareBoyutu * n++;
                        mucevherTablosu[i][j].eslesme = 0;
                        mucevherTablosu[i][j].saydamlik = 255;
                    }
        [cite_start]} [cite: 930-946]

        uygulama.draw(sArkaplan);
        for (int i=1; i<=8; i++)
            for (int j=1; j<=8; j++) {
                Mucevher m = mucevherTablosu[i][j];
                sTakilar.setTextureRect(IntRect(m.tip*49, 0, 49, 49));
                sTakilar.setColor(Color(255, 255, 255, m.saydamlik));
                sTakilar.setPosition(m.x, m.y);
                sTakilar.move(kenarBoslugu.x - kareBoyutu, kenarBoslugu.y - kareBoyutu);
                uygulama.draw(sTakilar);
            }
        uygulama.display();
    }
    return 0;
}