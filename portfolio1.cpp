#include <iostream>
#include <cstdlib>
#include <ctime>
#include <limits>
#include <string>

struct GameData{
    int playerHP{100};
    int monsterHP{100};
    bool swordObtained{false};
    bool keyObtained{false};
    bool doorLocked{true};
};

namespace Rooms {
    const std::string mainRoom {
        R"(
          +--------------[ FRONT ]--------------+
          | . . . . . . . . . . . . . . . . . . |
          | . . . . . . . . . . . . . . . . . . |
        +-+                                     +-+
        | | . . . . . . . . @ . . . . . . . . . | |
        LEFT. . . . . . .(Player) . . . . . . .RIGHT
        | | . . . . . . . . . . . . . . . . . . | |
        +-+                                     +-+
          +-------------------------------------+
        )"
    };

    const std::string leftWithSword {
        R"(
        +-------------------------------------+
        | . . . . . . . . . . . . . . . . . . |
        | . . . . . . . . . . . . . . . . . . |
        |                                     +-+
        | . . . . . . .  /| . . . . . . . . . | |
        | . . . . . . . ( sword ) . . . . . .LEFT
        | . . . . . . . . . . . . . . . . . . | |
        |                                     +-+
        | . . . . . . . . . . . . . . . . . . |
        | . . . . . . . . . . . . . . . . . . |
        +-------------------------------------+
        )"
    };

    const std::string leftWithoutSword {
        R"(
        +-------------------------------------+
        | . . . . . . . . . . . . . . . . . . |
        | . . . . . . . . . . . . . . . . . . |
        |                                     +-+
        | . . . . . . . . . . . . . . . . . . | |
        | . . . . . . . . . . . . . . . . . .LEFT
        | . . . . . . . . . . . . . . . . . . | |
        |                                     +-+
        | . . . . . . . . . . . . . . . . . . |
        | . . . . . . . . . . . . . . . . . . |
        +-------------------------------------+
        )"
    };

    const std::string rightWithKey {
        R"(
          +-------------------------------------+
          | . . . . . . . . . . . . . . . . . . |
          | . . . . . . . . . . . . . . . . . . |
        +-+                                     |
        | | . . . . . . .  o- . . . . . . . . . |
       RIGHT. . . . . . .( key ) . . . . . . .  |
        | | . . . . . . . . . . . . . . . . . . |
        +-+                                     |
          | . . . . . . . . . . . . . . . . . . |
          | . . . . . . . . . . . . . . . . . . |
          +-------------------------------------+
        )"
    };

    const std::string rightWithoutKey {
        R"(
          +-------------------------------------+
          | . . . . . . . . . . . . . . . . . . |
          | . . . . . . . . . . . . . . . . . . |
        +-+                                     |
        | | . . . . . . . . . . . . . . . . . . |
       RIGHT. . . . . . . . . . . . . . . . . . |
        | | . . . . . . . . . . . . . . . . . . |
        +-+                                     |
          | . . . . . . . . . . . . . . . . . . |
          | . . . . . . . . . . . . . . . . . . |
          +-------------------------------------+
        )"
    };

    const std::string frontRoom {
        R"(
        +-------------------------------------+
        | . . . . . . . . . . . . . . . . . . |
        | . . . . . . . . . . . . . . . . . . |
        | . . . . . .   (O___O)   . . . . . . |
        | . . . . . .   /|_|_|\   . . . . . . |
        | . . . . . .  //| | |\\  . . . . . . |
        | . . . . . .  [X]   [X]  . . . . . . |
        | . . . . . . . . . . . . . . . . . . |
        | . . . . . . . . . . . . . . . . . . |
        +--------------[ FRONT ]--------------+
        )"
    };
}

void MainRoom(bool &doorLocked, bool &keyObtained, int &optionSelect);
void FrontRoom(bool &swordObtained, int &optionSelect, int &monsterHP, int &playerHP);
void LeftRoom(int &optionSelect, bool &swordObtained);
void RightRoom(int &optionSelect, bool &keyObtained);
bool VerifyInput (int &optionSelect, int maxOptions);

int main(){
    int optionSelect{};

    srand(time(NULL));

    GameData game{};

    do{
        std::cout<<"\nPlease input a number 1-2"
                    <<"\n\n1. Play"
                    <<"\n2. Quit\n\n";
        std::cin>>optionSelect;

        if(std::cin.fail() || (optionSelect!=1 && optionSelect!=2)){
            std::cout<<"\nInvalid input\n";

            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }

        switch(optionSelect){
            case 1:
                std::cout<<"\nYou enter a dungeon, what do you do?\n";
                break;
            case 2:
                std::cout<<"\nExiting\n";
                return 0;
            }
    }while(std::cin.fail() || (optionSelect!=1 && optionSelect!=2));

    while(true){

        MainRoom(game.doorLocked, game.keyObtained, optionSelect);

        if(optionSelect == 1){
            LeftRoom(optionSelect, game.swordObtained);
        }else if(optionSelect == 2){
            RightRoom(optionSelect, game.keyObtained);
        }else if(optionSelect == 3){
            FrontRoom(game.swordObtained, optionSelect, game.monsterHP, game.playerHP);

            if (game.playerHP <= 0 || game.monsterHP <= 0) {
                return 0;
            }
        }
    }
}

void MainRoom(bool &doorLocked, bool &keyObtained, int &optionSelect) {
    do {
        std::cout << Rooms::mainRoom << '\n'
                  << "\n1. Enter the left room"
                  << "\n2. Enter the right room"
                  << "\n3. Enter the front room\n";
        
        std::cin >> optionSelect;

        if (!VerifyInput(optionSelect, 3)) {
            continue;
        }

        if (optionSelect == 3 && !keyObtained) {
            std::cout << "\nThe door is locked\n";
            optionSelect = 0;
            continue; 
        }

        break;
    } while (true);

    if (optionSelect == 3 && keyObtained && doorLocked) {
        std::cout << "\nThe door unlocks\n";
    }
}

void FrontRoom(bool &swordObtained, int &optionSelect, int &monsterHP, int &playerHP){

    do {

        std::cout << Rooms::frontRoom << '\n'
                <<"\nA monster appears"
                << "\n1. Fight monster"
                << "\n2. Exit room\n";
        
        std::cin >> optionSelect;

        if (!VerifyInput(optionSelect, 2)) {
            continue;
        }

        if (optionSelect == 1) {

        srand(time(NULL));

        do {
        std::cout<<Rooms::frontRoom<<'\n'
            <<"Monster HP is "<<monsterHP<<" and player HP is "<<playerHP
            <<"\nWhat will you do?"
            <<"\n1. Attack"
            <<"\n2. Heal\n";
        std::cin>>optionSelect;

        if (!VerifyInput(optionSelect, 2)) {
            continue;
        }

        if(optionSelect == 1){

            int playerAttack{};

            if(swordObtained){
                playerAttack = rand()%10 + 10;
            }else{
                playerAttack = rand()%10 + 5;
            }

            monsterHP -= playerAttack;

            std::cout<<"\nYou attack the monster for "<<playerAttack<< " damage";

            if(monsterHP <= 0){
                break;
            }
        }else if(optionSelect == 2){
            int heal{rand()%15 + 10};
            playerHP += heal;
            std::cout<<"\nYou heal for "<<heal<<" HP";
        }

        int monsterAttack{rand()%15 + 5};
        playerHP -= monsterAttack;
        std::cout<<"\n\nThe monster attacks you for "<<monsterAttack<<" damage";

        } while (monsterHP > 0 && playerHP > 0);

        if (monsterHP <= 0) {
            std::cout<<"\n\nMonster has been defeated, you win.\n";
            return;
        } else if (playerHP <= 0) {
            std::cout<<"\n\nThe monster has defeated you, you lose.\n";
            return;
        }
        
    } else if (optionSelect == 2) {
        return;
    }

    } while (true);
}

void LeftRoom(int &optionSelect, bool &swordObtained){
    do {
        if (!swordObtained) {
            std::cout << Rooms::leftWithSword << '\n'
                    << "\n1. Exit room"
                    << "\n2. Grab sword\n";
            
            std::cin >> optionSelect;

            if (!VerifyInput(optionSelect, 2)) {
                continue;
            } 

            if (optionSelect == 2) {
                swordObtained = true;
            } else if (optionSelect == 1) {
                return;
            }
        } else if (swordObtained) {
            std::cout << Rooms::leftWithoutSword << '\n'
                    << "\n1. Exit room\n";
            
            std::cin >> optionSelect;

            if (!VerifyInput(optionSelect, 1)) {
                continue;
            } 

            if (optionSelect == 1) {
                return;
            }
        }
    } while (true);
}

void RightRoom(int &optionSelect, bool &keyObtained){
do {
        if (!keyObtained) {
            std::cout << Rooms::rightWithKey << '\n'
                    << "\n1. Exit room"
                    << "\n2. Grab key\n";
            
            std::cin >> optionSelect;

            if (!VerifyInput(optionSelect, 2)) {
                continue;
            } 

            if (optionSelect == 2) {
                keyObtained = true;
            } else if (optionSelect == 1) {
                return;
            }
        } else if (keyObtained) {
            std::cout << Rooms::rightWithoutKey << '\n'
                    << "\n1. Exit room\n";
            
            std::cin >> optionSelect;

            if (!VerifyInput(optionSelect, 1)) {
                continue;
            } 

            if (optionSelect == 1) {
                return;
            }
        }
    } while (true);
}

bool VerifyInput(int &optionSelect, int maxOptions) {
    if (std::cin.fail() || optionSelect < 1 || optionSelect > maxOptions) {
        std::cout << "\nInvalid input\n";
        
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        
        return false;
    } else {
        return true;
    }
}