#include <SFML/Graphics.hpp>
#include <time.h>
#include <vector>
using namespace sf;

const int SINIR = 6;
int boruGenislik = 54;
Vector2f kaymaMiktari(65,55);
Vector2i YUKARI(0,-1), ASAGI(0,1), SAG(1,0), SOL(-1,0);
Vector2i YONLER[4] = {YUKARI, SAG, ASAGI, SOL};

struct BoruHucresi {
    std::vector<Vector2i> baglantilar;
    int yonIndex;
    float aci;
    bool aktif;
    BoruHucresi() { aci = 0; }
    void dondur() {
        for(int i=0; i<baglantilar.size(); i++)
            if (baglantilar[i] == YUKARI) baglantilar[i] = SAG;
            else if (baglantilar[i] == SAG) baglantilar[i] = ASAGI;
            else if (baglantilar[i] == ASAGI) baglantilar[i] = SOL;
            else if (baglantilar[i] == SOL) baglantilar[i] = YUKARI;
    }
    bool bagliMi(Vector2i yon) {
        for(auto b: baglantilar) if (b == yon) return true;
        return false;
    }
[cite_start]} boruIzgarasi[SINIR][SINIR]; [cite: 975-996]

BoruHucresi& hucreSec(Vector2i v) { return boruIzgarasi[v.x][v.y]; }
bool disaridaMi(Vector2i v) { return !IntRect(0,0,SINIR,SINIR).contains(v); }

void haritaUret() {
    std::vector<Vector2i> duraklar;
    duraklar.push_back(Vector2i(rand()%SINIR, rand()%SINIR));
    while(!duraklar.empty()) {
        int n = rand()%duraklar.size();
        Vector2i v = duraklar[n];
        Vector2i d = YONLER[rand()%4];
        if (hucreSec(v).baglantilar.size() == 3) { duraklar.erase(duraklar.begin() + n); continue; }
        if (hucreSec(v).baglantilar.size() == 2) if (rand()%50) continue;
        bool bitti = 1;
        for(auto D: YONLER) if (!disaridaMi(v+D) && hucreSec(v+D).baglantilar.empty()) bitti = 0;
        if (bitti) { duraklar.erase(duraklar.begin() + n); continue; }
        if (disaridaMi(v+d)) continue;
        if (!hucreSec(v+d).baglantilar.empty()) continue;
        hucreSec(v).baglantilar.push_back(d);
        hucreSec(v+d).baglantilar.push_back(-d);
        duraklar.push_back(v+d);
    }
[cite_start]} [cite: 999-1020]

void enerjiDagit(Vector2i v) {
    if (hucreSec(v).aktif) return;
    hucreSec(v).aktif = true;
    for(auto d: YONLER)
        if (!disaridaMi(v+d))
            if (hucreSec(v).bagliMi(d) && hucreSec(v+d).bagliMi(-d))
                enerjiDagit(v+d);
[cite_start]} [cite: 1021-1029]

int main() {
    srand(time(0));
    RenderWindow uygulama(VideoMode(390, 390), "The Pipe Puzzle!");
    Texture tZemin, tPc, tServer, tBorular;
    tZemin.loadFromFile("images/background.png");
    tPc.loadFromFile("images/comp.png");
    tServer.loadFromFile("images/server.png");
    tBorular.loadFromFile("images/pipes.png");
    tBorular.setSmooth(true);
    Sprite sZemin(tZemin), sPc(tPc), sServer(tServer), sBoru(tBorular);
    sBoru.setOrigin(27,27); sPc.setOrigin(18,18); sServer.setOrigin(20,20);

    haritaUret();
    for(int i=0; i<SINIR; i++)
        for(int j=0; j<SINIR; j++) {
            BoruHucresi &h = boruIzgarasi[j][i];
            for(int n=4; n>0; n--) {
                std::string yol = "";
                for(auto d: YONLER) yol += h.bagliMi(d) ? '1' : '0';
                if (yol == "0011" || yol == "0111" || yol == "0101" || yol == "0010") h.yonIndex = n;
                h.dondur();
            }
            for(int n=0; n<rand()%4; n++) { boruIzgarasi[j][i].yonIndex++; boruIzgarasi[j][i].dondur(); }
        [cite_start]} [cite: 1044-1058]

    Vector2i anaBilgisayarPos;
    while(hucreSec(anaBilgisayarPos).baglantilar.size() == 1) anaBilgisayarPos = Vector2i(rand()%SINIR, rand()%SINIR);
    sServer.setPosition(Vector2f(anaBilgisayarPos * boruGenislik));
    sServer.move(kaymaMiktari);

    while (uygulama.isOpen()) {
        Event olay;
        while (uygulama.pollEvent(olay)) {
            if (olay.type == Event::Closed) uygulama.close();
            if (olay.type == Event::MouseButtonPressed)
                if (olay.key.code == Mouse::Left) {
                    Vector2i pos = Mouse::getPosition(uygulama) + Vector2i(boruGenislik/2, boruGenislik/2) - Vector2i(kaymaMiktari);
                    pos /= boruGenislik;
                    if (disaridaMi(pos)) continue;
                    hucreSec(pos).yonIndex++;
                    hucreSec(pos).dondur();
                    for(int i=0; i<SINIR; i++) for(int j=0; j<SINIR; j++) boruIzgarasi[j][i].aktif = 0;
                    enerjiDagit(anaBilgisayarPos);
                }
        [cite_start]} [cite: 1065-1083]

        uygulama.clear(); uygulama.draw(sZemin);
        for(int i=0; i<SINIR; i++)
            for(int j=0; j<SINIR; j++) {
                BoruHucresi &h = boruIzgarasi[j][i];
                int tip = h.baglantilar.size();
                if (tip == 2 && h.baglantilar[0] == -h.baglantilar[1]) tip = 0;
                h.aci += 5;
                if (h.aci > h.yonIndex * 90) h.aci = h.yonIndex * 90;
                sBoru.setTextureRect(IntRect(boruGenislik * tip, 0, boruGenislik, boruGenislik));
                sBoru.setRotation(h.aci);
                sBoru.setPosition(j * boruGenislik, i * boruGenislik); sBoru.move(kaymaMiktari);
                uygulama.draw(sBoru);
                if (tip == 1) {
                    if (h.aktif) sPc.setTextureRect(IntRect(53, 0, 36, 36));
                    else sPc.setTextureRect(IntRect(0, 0, 36, 36));
                    sPc.setPosition(j * boruGenislik, i * boruGenislik); sPc.move(kaymaMiktari);
                    uygulama.draw(sPc);
                }
            }
        uygulama.draw(sServer); uygulama.display();
    }
    return 0;
}