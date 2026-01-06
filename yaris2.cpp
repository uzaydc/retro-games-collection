#include <SFML/Graphics.hpp>
#include <vector>
#include <math.h>

using namespace sf;

[cite_start]int genislik = 1024; [cite: 563]
[cite_start]int yukseklik = 768; [cite: 564]
[cite_start]int yolEni = 2000; [cite: 565]
[cite_start]int parcaBoyu = 200; [cite: 566]
[cite_start]float mercekDerinligi = 0.84; [cite: 567]

void dortgenCiz(RenderWindow &pencere, Color renk, int x1, int y1, int w1, int x2, int y2, int w2) {
    [cite_start]ConvexShape sekil(4); [cite: 570]
    [cite_start]sekil.setFillColor(renk); [cite: 571]
    [cite_start]sekil.setPoint(0, Vector2f(x1 - w1, y1)); [cite: 572]
    [cite_start]sekil.setPoint(1, Vector2f(x2 - w2, y2)); [cite: 573]
    [cite_start]sekil.setPoint(2, Vector2f(x2 + w2, y2)); [cite: 574]
    [cite_start]sekil.setPoint(3, Vector2f(x1 + w1, y1)); [cite: 575]
    [cite_start]pencere.draw(sekil); [cite: 576]
}

struct YolHatti {
    [cite_start]float x_3d, y_3d, z_3d; [cite: 580]
    [cite_start]float ekranX, ekranY, ekranEn; [cite: 581]
    [cite_start]float viraj, nesneX, kirpmaSiniri, olcek; [cite: 582]
    [cite_start]Sprite nesneSprite; [cite: 583]
    YolHatti() { nesneX = viraj = x_3d = y_3d = z_3d = 0; [cite_start]} [cite: 585]
    
    void izdusum(int camX, int camY, int camZ) {
        [cite_start]olcek = mercekDerinligi / (z_3d - camZ); [cite: 588]
        [cite_start]ekranX = (1 + olcek * (x_3d - camX)) * genislik / 2; [cite: 589]
        [cite_start]ekranY = (1 - olcek * (y_3d - camY)) * yukseklik / 2; [cite: 590]
        [cite_start]ekranEn = olcek * yolEni * genislik / 2; [cite: 591]
    }

    void nesneyiCiz(RenderWindow &app) {
        [cite_start]Sprite s = nesneSprite; [cite: 595]
        [cite_start]int w = s.getTextureRect().width; [cite: 596]
        [cite_start]int h = s.getTextureRect().height; [cite: 597]
        [cite_start]float hedefX = ekranX + olcek * nesneX * genislik / 2; [cite: 598]
        [cite_start]float hedefY = ekranY + 4; [cite: 599]
        [cite_start]float hedefW = w * ekranEn / 266; [cite: 600]
        [cite_start]float hedefH = h * ekranEn / 266; [cite: 601]
        [cite_start]hedefX += hedefW * nesneX; [cite: 602]
        [cite_start]hedefY += hedefH * (-1); [cite: 603]
        [cite_start]float kesmeYuksekligi = hedefY + hedefH - kirpmaSiniri; [cite: 604]
        [cite_start]if (kesmeYuksekligi < 0) kesmeYuksekligi = 0; [cite: 605]
        [cite_start]if (kesmeYuksekligi >= hedefH) return; [cite: 606]
        [cite_start]s.setTextureRect(IntRect(0, 0, w, h - h * kesmeYuksekligi / hedefH)); [cite: 607]
        [cite_start]s.setScale(hedefW / w, hedefH / h); [cite: 608]
        [cite_start]s.setPosition(hedefX, hedefY); [cite: 609]
        [cite_start]app.draw(s); [cite: 610]
    }
};

int main() {
    [cite_start]RenderWindow uygulama(VideoMode(genislik, yukseklik), "Outrun Racing!"); [cite: 615]
    [cite_start]uygulama.setFramerateLimit(60); [cite: 616]
    [cite_start]Texture dokular[50]; [cite: 617]
    [cite_start]Sprite nesneler[50]; [cite: 618]
    for (int i = 1; i <= 7; i++) {
        [cite_start]dokular[i].loadFromFile("images/" + std::to_string(i) + ".png"); [cite: 621]
        [cite_start]dokular[i].setSmooth(true); [cite: 622]
        [cite_start]nesneler[i].setTexture(dokular[i]); [cite: 623]
    }
    [cite_start]Texture arkaPlanDoku; [cite: 625]
    [cite_start]arkaPlanDoku.loadFromFile("images/bg.png"); [cite: 626]
    [cite_start]arkaPlanDoku.setRepeated(true); [cite: 627]
    [cite_start]Sprite arkaPlan(arkaPlanDoku); [cite: 628]
    [cite_start]arkaPlan.setTextureRect(IntRect(0, 0, 5000, 411)); [cite: 629]
    [cite_start]arkaPlan.setPosition(-2000, 0); [cite: 630]

    [cite_start]std::vector<YolHatti> yollar; [cite: 631]
    for (int i = 0; i < 1600; i++) {
        [cite_start]YolHatti hat; [cite: 634]
        [cite_start]hat.z_3d = i * parcaBoyu; [cite: 635]
        [cite_start]if (i > 300 && i < 700) hat.viraj = 0.5; [cite: 636]
        [cite_start]if (i > 1100) hat.viraj = -0.7; [cite: 637]
        if (i < 300 && i % 20 == 0) { hat.nesneX = -2.5; hat.nesneSprite = nesneler[5]; [cite_start]} [cite: 638]
        if (i % 17 == 0) { hat.nesneX = 2.0; hat.nesneSprite = nesneler[6]; [cite_start]} [cite: 639]
        if (i > 300 && i % 20 == 0) { hat.nesneX = -0.7; hat.nesneSprite = nesneler[4]; [cite_start]} [cite: 640]
        if (i > 800 && i % 20 == 0) { hat.nesneX = -1.2; hat.nesneSprite = nesneler[1]; [cite_start]} [cite: 641]
        if (i == 400) { hat.nesneX = -1.2; hat.nesneSprite = nesneler[7]; [cite_start]} [cite: 642]
        [cite_start]if (i > 750) hat.y_3d = sin(i / 30.0) * 1500; [cite: 643]
        [cite_start]yollar.push_back(hat); [cite: 644]
    }

    [cite_start]int N = yollar.size(); [cite: 646]
    [cite_start]float oyuncuX = 0; [cite: 647]
    [cite_start]int oyuncuKonumu = 0; [cite: 648]
    [cite_start]int kameraYuksekligi = 1500; [cite: 649]

    while (uygulama.isOpen()) {
        Event e;
        while (uygulama.pollEvent(e)) {
            [cite_start]if (e.type == Event::Closed) uygulama.close(); [cite: 655]
        }
        [cite_start]int hiz = 0; [cite: 658]
        [cite_start]if (Keyboard::isKeyPressed(Keyboard::Right)) oyuncuX += 0.1; [cite: 659]
        [cite_start]if (Keyboard::isKeyPressed(Keyboard::Left)) oyuncuX -= 0.1; [cite: 660]
        [cite_start]if (Keyboard::isKeyPressed(Keyboard::Up)) hiz = 200; [cite: 661]
        [cite_start]if (Keyboard::isKeyPressed(Keyboard::Down)) hiz = -200; [cite: 662]
        [cite_start]if (Keyboard::isKeyPressed(Keyboard::Tab)) hiz *= 3; [cite: 663]
        [cite_start]if (Keyboard::isKeyPressed(Keyboard::W)) kameraYuksekligi += 100; [cite: 664]
        [cite_start]if (Keyboard::isKeyPressed(Keyboard::S)) kameraYuksekligi -= 100; [cite: 665]

        [cite_start]oyuncuKonumu += hiz; [cite: 666]
        [cite_start]while (oyuncuKonumu >= N * parcaBoyu) oyuncuKonumu -= N * parcaBoyu; [cite: 667]
        [cite_start]while (oyuncuKonumu < 0) oyuncuKonumu += N * parcaBoyu; [cite: 668]

        [cite_start]uygulama.clear(Color(105, 205, 4)); [cite: 669]
        [cite_start]uygulama.draw(arkaPlan); [cite: 670]

        [cite_start]int baslangicNoktasi = oyuncuKonumu / parcaBoyu; [cite: 671]
        [cite_start]int camH = yollar[baslangicNoktasi].y_3d + kameraYuksekligi; [cite: 672]
        [cite_start]if (hiz > 0) arkaPlan.move(-yollar[baslangicNoktasi].viraj * 2, 0); [cite: 673]
        [cite_start]if (hiz < 0) arkaPlan.move(yollar[baslangicNoktasi].viraj * 2, 0); [cite: 674]

        [cite_start]int sonY = yukseklik; [cite: 675]
        float x = 0, dx = 0;

        for (int n = baslangicNoktasi; n < baslangicNoktasi + 300; n++) {
            [cite_start]YolHatti &l = yollar[n % N]; [cite: 680]
            [cite_start]l.izdusum(oyuncuX * yolEni - x, camH, baslangicNoktasi * parcaBoyu - (n >= N ? N * parcaBoyu : 0)); [cite: 681]
            [cite_start]x += dx; [cite: 682]
            [cite_start]dx += l.viraj; [cite: 683]
            [cite_start]l.kirpma = sonY; [cite: 684]
            [cite_start]if (l.ekranY >= sonY) continue; [cite: 685]
            [cite_start]sonY = l.ekranY; [cite: 686]

            Color cimRenk = (n / 3) % 2 ? [cite_start]Color(16, 200, 16) : Color(0, 154, 0); [cite: 687]
            Color bordurRenk = (n / 3) % 2 ? [cite_start]Color(255, 255, 255) : Color(0, 0, 0); [cite: 688]
            Color asfaltRenk = (n / 3) % 2 ? [cite_start]Color(107, 107, 107) : Color(105, 105, 105); [cite: 689]
            [cite_start]YolHatti p = yollar[(n - 1) % N]; [cite: 690]
            [cite_start]dortgenCiz(uygulama, cimRenk, 0, p.ekranY, genislik, 0, l.ekranY, genislik); [cite: 691]
            [cite_start]dortgenCiz(uygulama, bordurRenk, p.ekranX, p.ekranY, p.ekranEn * 1.2, l.ekranX, l.ekranY, l.ekranEn * 1.2); [cite: 692]
            [cite_start]dortgenCiz(uygulama, asfaltRenk, p.ekranX, p.ekranY, p.ekranEn, l.ekranX, l.ekranY, l.ekranEn); [cite: 693]
        }
        for (int n = baslangicNoktasi + 300; n > baslangicNoktasi; n--)
            [cite_start]yollar[n % N].nesneyiCiz(uygulama); [cite: 696-697]
        [cite_start]uygulama.display(); [cite: 698]
    }
    return 0;
}
