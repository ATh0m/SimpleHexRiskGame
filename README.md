# SimpleHexRiskGame

------

## OPIS:

Jest to prosta gra strategiczna opierająca się na zasadach gry ***"Ryzyko"*** i planszą złożoną z sześcioboków. Graczami mogą być ludzie jak i komputer.

---

## SCREENY:

![Wstępna wersja](https://raw.githubusercontent.com/AThom0x7cc/SimpleHexRiskGame/master/screens/screen.png)

![Wstępna wersja](https://raw.githubusercontent.com/AThom0x7cc/SimpleHexRiskGame/master/screens/screen2.png)

![Wstępna wersja](https://raw.githubusercontent.com/AThom0x7cc/SimpleHexRiskGame/master/screens/screen3.png)

------

## INSTALACJA:

Wymaga [cmake](cmake.org)

### OS X:

Przydatny [Homebrew](http://brew.sh)

``` shell
brew install sdl2 sdl2_gfx sdl2_ttf
mkdir build
cd build
cmake ..
make
```

### Ubuntu:

``` shell
apt-get install libsdl2-dev libsdl2-gfx-dev libsdl2-ttf-dev
mkdir build
cd build
cmake ..
make
```

### Arch:

``` shell
pacman -S sdl2 sdl2_gfx sdl2_ttf
mkdir build
cd build
cmake ..
make
```



---

## ZASADY:

### Cel:

Celem każdego gracza jest wyeliminowanie pozostałych przeciwników

### Przygotowanie:

Na początku wybierana jest ilość *"żywych"* graczy biorących udział w rozgrywce. Nad pozostałymi graczami z domyślnej puli kontrolę przejmuje komputer. Mapa wybierana jest losowo z gotowej puli map. Możliwe, że wraz z rozwojem projektu mapa będzie automatycznie generowana.

### Rozgrywka:

###### *Kolejność graczy jest losowa.*

**Początek:**

Na początku każdy gracz wybiera jedno z wolnych pól na planszy, które przejmuje. Pole to otrzymuje domyślną, podstawową liczbę siły (wartość ta potrzebna jest do atakowania innych pól lub obrony).

**Przebieg tury:**

Każda tura poza początkową składa się z fazy wzmocnienia i fazy ruchu.

**Faza wzmocnienia:**

Na początku swojej tury gracz otrzymuje liczbę siły do rozdysponowania, według podanego wzoru:

`siła = max(2, ilość_posiadanych_pól / 3)`

Gracz rozdziela ilość siły w dowolny sposób pomiędzy posiadanymi polami.

**Faza ruchu:**

W tej fazie gracz ma dwie akcje do wyboru. Może wzmocnić jedno ze swoich pól, albo zaatakowac jedno z pól przeciwnika.

**Wzmocnienie pola:**

Polega na dodaniu do jego siły domyslnej wartości lub wyliczeniu tego na podstawie sąsiadujących, przyjaznych pól.

**Atak:**

Siła ataku wyliczana jest jako połowa sumy sił przyjaznych pól graniczących z atakowanym polem. Wiąże się to z tym, że pola te tracą połowę swojej siły.

Siła obrony wynosi tyle ile siła atakowanego pola.

Atak symulowany jest na podstawie rzutów kośćmi. 

Ilość kości wyliczana jest na podstawie wzoru:

``` reStructuredText
ilosc_kosci_atakujacego = min(3, sila_atakujacego)
ilosc_kosci_broniacego = min(2, sila_broniacego)
```

Przeprowadza się symulacje rzutów, następnie sortuje wyniki każdego gracza. Porównuje się kolejno wyniki rzutów. Gracz z mniejsza liczbą oczek w danym porównaniu traci jedną jednostkę siły.

Wykonuje się tę operację dopóki któraś z sił się nie wyczerpie.

Jeżeli wygra atakujący to przejmuje podbite pole i ustawia na nim siłę równą pozostałeś sile ataku, a jezeli broniący to ustawia sile ataku równą pozostałej sile obrony.

**Koniec:**

Gra kończy się, gdy na planszy pozostanie jeden gracz

------

## INTERFEJS

Gra będzie wykorzystywać bibliotekę [SDL2](https://www.libsdl.org/index.php). Na początku wyświetlana będzie opcja z możliwościa wyboru ilości graczy biorących udział w rozgrywce. Następnie wyświetlana będzie plansza gry z miejscem na komunikaty pod nią. Plansza składać się będzie z sześciokątów pokolorowanych na kolor neutralny albo kolor gracza, do którego należy, i pokazaną ilościa siły. Podczas każdej tury, jeżeli gracz będzie mógł wykonać akcję na jakimś polu to będzie to pole graficznie zaznaczane. Dodatkowo podświetlane będzie pole pod kursorem gracza. Na końcu rozgrywki będzie wyswietlany komunikat o zwycięzcy.

------

## PROBLEMY DO IMPLEMENTACJI

- [x] rysowanie planszy
- [x] rozpoznawanie kliknietego pola
- [x] wyświetlanie napisów
- [x] zaznaczanie pól z możliwymi akcjami
- [x] podświetlanie pól
- [x] rozpoznawanie akcji użytkownika
- [x] zarządzanie turami
- [x] sztuczna inteligencja
- [x] i wiele, wiele więcej

------

## STRUKTURA PROGRAMU

- ai.c / ai.h - zarządzanie ruchami SI
- battle.c / battle.h - symulacja bitwy
- board.c / board.h - zarządzanie planszą
- defs.h - domyślne ustawienia
- game.c / game.h - główne zarządzanie rozgrywką
- generator.c / generator.h - generator planszy
- graphic.c / graphic.h - renderowanie obiektów
- input.c / input.h - zarządzanie zdarzeniami
- main.c / main.h - główna funkcja
- player.c / player.h - zarządzanie ruchami gracza
- utility.c / utility.h - pomocne funkcje, struktury

------

## BIBLIOTEKI

- SDL2
- SDL2_gfx
- SDL2_ttf
- inne (stdlib.h, stdbool.h, string.h, …)

------

## PRZYDATNE LINKI

- [http://www.redblobgames.com/grids/hexagons/](http://www.redblobgames.com/grids/hexagons/) - genialna strona o hexagonach
- [http://lazyfoo.net/tutorials/SDL/](http://lazyfoo.net/tutorials/SDL/) - tutorial SDL2
- [https://wiki.libsdl.org/FrontPage](https://wiki.libsdl.org/FrontPage) - dokumentacja SDL2
- [http://www.ferzkopp.net/Software/SDL2_gfx/Docs/html/index.html](http://www.ferzkopp.net/Software/SDL2_gfx/Docs/html/index.html) - dokumentacja SDL2_gfx
- [https://www.libsdl.org/projects/SDL_ttf/](https://www.libsdl.org/projects/SDL_ttf/) - dokumentacja SDL2_ttf

------

Tomasz Nanowski II Uwr