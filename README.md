
**CyberNight** to prosta gra platformowa stworzona jako projekt na zajęcia z C++ podczas studiów. Gra została zbudowana z wykorzystaniem frameworka [raylib](https://www.raylib.com/).

## Rozpoczęcie pracy

Aby uruchomić projekt lokalnie, wykonaj poniższe kroki:

1. **Klonowanie repozytorium**: Sklonuj repozytorium na swój lokalny komputer:
   ```bash
   git clone https://github.com/K3ster/CyberNight.git
   ```

2. **Przygotowanie środowiska**:
   - Upewnij się, że masz zainstalowany kompilator zgodny z C++.
   - Pobierz i zainstaluj [raylib](https://www.raylib.com/) zgodnie z instrukcjami dla Twojego systemu operacyjnego.

3. **Kompilacja projektu**:
   - Projekt zawiera skrypty `premake5` do generowania plików projektowych dla różnych środowisk. Wybierz odpowiedni dla Twojego systemu:
     - Dla Visual Studio: `premake-VisualStudio.bat`
     - Dla MinGW: `premake-mingw.bat`
   - Uruchom odpowiedni skrypt, aby wygenerować pliki projektowe.
   - Otwórz wygenerowany projekt w swoim IDE i skompiluj go.

## Struktura projektu

- `game/src/raylib_game.cpp`: Główny plik źródłowy gry.
- `_build`: Katalog zawierający pliki obiektowe, tekstury i inne zasoby niezbędne do działania gry.

## Wymagania

- Kompilator zgodny z C++.
- Zainstalowany framework [raylib](https://www.raylib.com/).

## Licencja

Ten projekt jest licencjonowany na podstawie licencji Zlib. Szczegółowe informacje znajdują się w pliku `LICENSE` w repozytorium.



