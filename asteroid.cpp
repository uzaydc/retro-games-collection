#include <SFML/Graphics.hpp>
#include <time.h>
#include <list>
using namespace sf;

const int EN = 1200, BOY = 800;
float RAD = 0.017453f;

class Canlandirma {
public:
    float KARE, hiz; Sprite gorunum; std::vector<IntRect> kareler;
    Canlandirma(){}
    Canlandirma (Texture &t, int x, int y, int w, int h, int adet, float s) {
        KARE = 0; hiz = s;
        for (int i=0; i<adet; i++) kareler.push_back(IntRect(x + i*w, y, w, h));
        gorunum.setTexture(t); gorunum.setOrigin(w/2, h/2); gorunum.setTextureRect(kareler[0]);
    }
    void guncelle() {
        KARE += hiz; int n = kareler.size();
        if (KARE >= n) KARE -= n;
        if (n > 0) gorunum.setTextureRect(kareler[int(KARE)]);
    }
    bool bittiMi() { return KARE + hiz >= kareler.size(); }
[cite_start]}; [cite: 1595-1623]

class Nesne {
public:
    float x, y, dx, dy, R, aci; bool canli; std::string tur; Canlandirma anim;
    Nesne() { canli = 1; }
    void ayarlar(Canlandirma &a, int X, int Y, float Angle=0, int radius=1) {
        anim = a; x = X; y = Y; aci = Angle; R = radius;
    }
    virtual void guncelle(){};
    void ciz(RenderWindow &app) {
        anim.gorunum.setPosition(x, y); anim.gorunum.setRotation(aci + 90); app.draw(anim.gorunum);
    }
    virtual ~Nesne(){};
[cite_start]}; [cite: 1624-1655]

class Gezegen: public Nesne {
public:
    Gezegen() { dx = rand()%8-4; dy = rand()%8-4; tur = "asteroid"; }
    void guncelle() {
        x += dx; y += dy;
        if (x > EN) x = 0; if (x < 0) x = EN;
        if (y > BOY) y = 0; if (y < 0) y = BOY;
    }
[cite_start]}; [cite: 1656-1672]

class Mermi: public Nesne {
public:
    Mermi() { tur = "bullet"; }
    void guncelle() {
        dx = cos(aci*RAD)*6; dy = sin(aci*RAD)*6; x += dx; y += dy;
        if (x > EN || x < 0 || y > BOY || y < 0) canli = 0;
    }
[cite_start]}; [cite: 1673-1689]

class Gemi: public Nesne {
public:
    bool gaz;
    Gemi() { tur = "player"; }
    void guncelle() {
        if (gaz) { dx += cos(aci*RAD)*0.2; dy += sin(aci*RAD)*0.2; }
        else { dx *= 0.99; dy *= 0.99; }
        float s = sqrt(dx*dx + dy*dy); if (s > 15) { dx *= 15/s; dy *= 15/s; }
        x += dx; y += dy;
        if (x > EN) x = 0; if (x < 0) x = EN;
        if (y > BOY) y = 0; if (y < 0) y = BOY;
    }
[cite_start]}; [cite: 1690-1716]

bool carpismaVarMi(Nesne *a, Nesne *b) {
    return (b->x - a->x)*(b->x - a->x) + (b->y - a->y)*(b->y - a->y) < (a->R + b->R)*(a->R + b->R);
[cite_start]} [cite: 1717-1722]

int main() {
    srand(time(0)); RenderWindow uygulama(VideoMode(EN, BOY), "Asteroids!"); uygulama.setFramerateLimit(60);
    Texture t1, t2, t3, t4, t5, t6, t7;
    t1.loadFromFile("images/spaceship.png"); t2.loadFromFile("images/background.jpg"); t3.loadFromFile("images/explosions/type_C.png");
    t4.loadFromFile("images/rock.png"); t5.loadFromFile("images/fire_blue.png"); t6.loadFromFile("images/rock_small.png"); t7.loadFromFile("images/explosions/type_B.png");
    Sprite sArka(t2);
    Canlandirma cPatlama(t3, 0,0,256,256, 48, 0.5), cTas(t4, 0,0,64,64, 16, 0.2), cKucukTas(t6, 0,0,64,64, 16, 0.2), cMermi(t5, 0,0,32,64, 16, 0.8), cGemi(t1, 40,0,40,40, 1, 0), cGemiGaz(t1, 40,40,40,40, 1, 0), cGemiPatlama(t7, 0,0,192,192, 64, 0.5);
    std::list<Nesne*> listem;
    for(int i=0; i<15; i++) { Gezegen *g = new Gezegen(); g->ayarlar(cTas, rand()%EN, rand()%BOY, rand()%360, 25); listem.push_back(g); }
    [cite_start]Gemi *p = new Gemi(); p->ayarlar(cGemi, 200, 200, 0, 20); listem.push_back(p); [cite: 1746-1755]

    while (uygulama.isOpen()) {
        Event olay;
        while (uygulama.pollEvent(olay)) {
            if (olay.type == Event::Closed) uygulama.close();
            if (olay.type == Event::KeyPressed && olay.key.code == Keyboard::Space) {
                Mermi *m = new Mermi(); m->ayarlar(cMermi, p->x, p->y, p->aci, 10); listem.push_back(m);
            }
        [cite_start]} [cite: 1760-1770]
        if (Keyboard::isKeyPressed(Keyboard::Right)) p->aci += 3;
        if (Keyboard::isKeyPressed(Keyboard::Left)) p->aci -= 3;
        p->gaz = Keyboard::isKeyPressed(Keyboard::Up);

        for(auto a: listem) for(auto b: listem) {
            if (a->tur == "asteroid" && b->tur == "bullet")
                if (carpismaVarMi(a, b)) {
                    a->canli = b->canli = false; Nesne *e = new Nesne(); e->ayarlar(cPatlama, a->x, a->y); e->tur = "explosion"; listem.push_back(e);
                    for(int i=0; i<2; i++) { if (a->R == 15) continue; Nesne *k = new Gezegen(); k->ayarlar(cKucukTas, a->x, a->y, rand()%360, 15); listem.push_back(k); }
                }
            if (a->tur == "player" && b->tur == "asteroid")
                if (carpismaVarMi(a, b)) {
                    b->canli = false; Nesne *e = new Nesne(); e->ayarlar(cGemiPatlama, a->x, a->y); e->tur = "explosion"; listem.push_back(e);
                    p->ayarlar(cGemi, EN/2, BOY/2, 0, 20); p->dx = 0; p->dy = 0;
                }
        [cite_start]} [cite: 1776-1807]
        p->anim = p->gaz ? cGemiGaz : cGemi;
        if (rand()%150 == 0) { Gezegen *g = new Gezegen(); g->ayarlar(cTas, 0, rand()%BOY, rand()%360, 25); listem.push_back(g); }
        for(auto i=listem.begin(); i!=listem.end(); ) {
            Nesne *e = *i; e->guncelle(); e->anim.guncelle();
            if (e->canli == false || (e->tur == "explosion" && e->anim.bittiMi())) { i = listem.erase(i); delete e; }
            else i++;
        }
        uygulama.draw(sArka); for(auto i: listem) i->ciz(uygulama); uygulama.display();
    }
    return 0;
}