#include <iostream>
#include "Maze.h"

using namespace std;

int main() {
    //////////////////////////// Scenariu de utilizare a claselor
    /// Creare labirint si plasarea jucatorului
    Maze labirint;
    labirint.create_maze();
    labirint.replace_player(3,1);
    cout << "Initializare labirint si jucator: \n";
    cout << labirint;
    cout << endl;
    ///Specificare iesire
    ///Plasare inamici
    labirint.place_enemy(1,7);
    labirint.place_enemy(3,4);
    cout<<"Plasam inamicii:\n";
    cout << labirint;
    ///Incepem jocul propriu zis
    while (labirint.checkGame()) {
        int alegere;
        cout<<"Alege dintre urmatoarele actiuni: "<<endl;
        cout<<"1 - Nord, 2 - Est, 3 - Sud, 4 - Vest, 5 - Plaseaza bomba\n";
        cin>>alegere;
        if (alegere >= 1 && alegere <= 4) {
            labirint.Move_Player(alegere);
        }
        else if (alegere == 5) {
            labirint.Player_Bomb();
        }
        cout << labirint;
    }
    return 0;
}
/* Legenda la maze:
 * - block
 o - block fals -> poate fi distrus
 P - player
 E - enemy
*/