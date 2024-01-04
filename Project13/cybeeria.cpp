#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <thread>

using namespace std;

const int inventarysize = 5;

struct User {
    string username;
    string Class;
    int health;
    int XP;
    string inventory[inventarysize];
    int inventorySize;
};

struct Mission {
    string name;
    int difficulty;
};

User initializeUser() {
    User User;
    cout << "Enter your name: ";
    getline(cin, User.username);


    do {
        cout << "Enter your hero class (warrior/mage/rogue): ";
        cin >> User.Class;

        if (User.Class != "warrior" || User.Class != "mage" || User.Class != "rogue")
        {
            cout << "Please choose a valid class (warrior, mage, or rogue).\n";
        }

    } while (User.Class != "warrior" && User.Class != "mage" && User.Class != "rogue");
    User.health = 100;
    User.XP = 0;
    User.inventorySize = 0;
    return User;
}

void displayUserinfo(const User& player) {
    cout << "\nCharacter Information:\n";
    cout << "Name: " << player.username << "\n";
    cout << "Class: " << player.Class << "\n";
    cout << "Health: " << player.health << "\n";
    cout << "Experience: " << player.XP << "\n";
    cout << "Inventory:\n";
    for (int i = 0; i < player.inventorySize; i++) {
        cout << i + 1 << ". " << player.inventory[i] << "\n";
    }
}

Mission missionsinitialize(int missionNum) {
    switch (missionNum) {
    case 1:
        return { "CyberVanguard X1", 1 };
    case 2:
        return { "TechSniper Y3", 2 };
    case 3:
        return { "CyberDrake Alpha9", 3 };
    default:
        return { "Invalid Number.", 0 };
    }
}

void displayMissions() {
    cout << "\nAvailable Missions:\n";
    cout << "1. Operation ShadowNet Override (Difficulty: 1)\n";
    cout << "2. Project Binary Sentinel (Difficulty: 2)\n";
    cout << "3. Operation Neon Serpent Strike (Difficulty: 3)\n";
}

Mission missionSelection() {
    int MissionChoice;
    do {
        cout << "\nEnter the number of the Mission you want to play: ";
        if (!(cin >> MissionChoice)) {
            cout << "Invalid input. Please enter a number.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        if (MissionChoice == 1) {
            cout << "Mission 1. Operation ShadowNet Override (Difficulty: 1) is selected.\n";
        }
        else if (MissionChoice == 2) {
            cout << "Mission 2. Project Binary Sentinel (Difficulty: 2) is selected.\n";
        }
        else if (MissionChoice == 3) {
            cout << "Mission 3. Operation Neon Serpent Strike (Difficulty: 3) is selected.\n";
        }
        else {
            cout << "Please select between 1 and 3.\n";
        }
    } while (MissionChoice < 1 || MissionChoice > 3);

    return missionsinitialize(MissionChoice);
}

void Story(const Mission& Mission) {
    // Different stories for each quest
    if (Mission.name == "CyberVanguard X1") {
        cout << "In the dark corners of the digital realm, the notorious CyberVanguard X1 has emerged.\n";
        cout << "Their cybernetic minions are wreaking havoc, and it's up to you to stop their nefarious plans!\n";
        cout << "Your MISSION is to infiltrate their virtual lair and neutralize the threat!\n";
    }
    else if (Mission.name == "TechSniper Y3") {
        cout << "The elusive TechSniper Y3, a master of precision and stealth, has been targeting key technological assets.\n";
        cout << "Your MISSION is to track down and confront TechSniper Y3 before they can unleash chaos on the digital infrastructure!\n";
    }
    else if (Mission.name == "CyberDrake Alpha9") {
        cout << "A formidable entity known as CyberDrake Alpha9 has surfaced, bringing chaos to the interconnected world.\n";
        cout << "Your MISSION is to confront CyberDrake Alpha9 in the heart of the digital domain and restore order!\n";
    }
}

void war(User& user, const Mission& Mission) {
    srand(time(0)); // Simplified seed

    int enemyDifficulty = Mission.difficulty * 2;
    int enemyHealth = 30 + rand() % (enemyDifficulty * 10);

    Story(Mission);

    cout << "\nBattle Start! You are standing in front of a strong enemy!\n";

    while (user.health > 0 && enemyHealth > 0) {
        int userAttack = 1 + rand() % 10;
        enemyHealth -= userAttack;
        cout << "You dealt " << userAttack << " damage to the enemy ";

        int villainAttack = 1 + rand() % (enemyDifficulty * 2);
        user.health -= villainAttack;
        cout << "The enemy dealt " << villainAttack << " damage to you.\n ";

        cout << "Your Health: " << user.health << ", Enemy's Health: " << enemyHealth << "\n";
        system("pause");
    }

    if (user.health <= 0) {
        cout << "You are defeated in battle. Game Over!\n";
    }
    else {
        cout << "You defeated the enemy!\n";
        user.XP += Mission.difficulty * 10;

        char increaseHealthChoice;
        do {
            cout << "Caution: If you increase your health, experience points will be deducted.\n";
            system("pause");
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear the input buffer

            cout << "Do you want to increase your health? (y/n): ";
            cin >> increaseHealthChoice;

            if (cin.fail()) {
                cin.clear(); // Clear the error flag
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear the input buffer
                cout << "Invalid input. Please enter 'y' or 'n'.\n";
                continue; // Skip the rest of the loop and start over
            }

            if (increaseHealthChoice != 'y' && increaseHealthChoice != 'Y' && increaseHealthChoice != 'n' && increaseHealthChoice != 'N') {
                cout << "Invalid Choice. Please select 'y' or 'n'.\n";
            }
        } while (increaseHealthChoice != 'y' && increaseHealthChoice != 'Y' && increaseHealthChoice != 'n' && increaseHealthChoice != 'N');

        }

        if (Mission.name == "CyberVanguard X1") {
            cout << "Congratulations! You obtained a Cyber Sword. Added it to your inventory.\n";
            if (user.inventorySize < inventarysize) {
                user.inventory[user.inventorySize++] = "Cyber Sword";
            }
            else {
                cout << "Your inventory is full. Cannot add more items.\n";
            }
        }
        else if (Mission.name == "TechSniper Y3") {
            cout << "Congratulations! You obtained a Stealth Cloak. Added it to your inventory.\n";
            if (user.inventorySize < inventarysize) {
                user.inventory[user.inventorySize++] = "Stealth Cloak";
            }
            else {
                cout << "Your inventory is full. Cannot add more items.\n";
            }
        }
        else if (Mission.name == "CyberDrake Alpha9") {
            cout << "Congratulations! You obtained a Digital Shield. Added it to your inventory.\n";
            if (user.inventorySize < inventarysize) {
                user.inventory[user.inventorySize++] = "Digital Shield";
            }
            else {
                cout << "Your inventory is full. Cannot add more items.\n";
            }
        }
    }


void levelUp(User& player) {
    int requiredExperience = 50;
    if (player.XP >= requiredExperience) {
        cout << "\nLevel Up!\n";
        player.health += 30;
        player.XP = 0;
        cout << "Health increased. Your new health: " << player.health << "\n";
        cout << "Experience points deducted. Your new experience is: " << player.XP << endl;
    }
}

int main() {

    string message =
     "              .-. . . .-. .-. . . .-. .-. .   .-. .-.   .-. .-.\n"
     "              |   |-| |(  | | |\|  |  |   |   |-  `-.   | | |- \n"
     "              `-' ' ` ' ' `-' ' ` `-' `-' `-' `-' `-'   `-' '  \n"

     "        _______         ______  _______ _______ _________ _______   \n"
     "       (  ____ \\     /|  ___ \\(  ____ \\  ____ )\\__   __/(  ___  )  \n"
     "       | (    \\/ \\   / ) (   ) ) (    \\/ (    )|   ) (   | (   ) |_ \n"
     "       | |      \\ () /| (_/ /| (   | (____)|   | |   | (___) |_)\n"
     "       | |       \\   / |  __ ( |  __)  |     __)   | |   |  ___  |  \n"
     "       | |        ) (  | (  \\ \\| (     | (\\ (      | |   | (   ) |_ \n"
     "       | (____/\\  | |  | )___) ) (____/\\ ) \\ \\_____) (___| )   ( |_)\n"
     "       (_______/  \\_/  |/ \\___/(_______//   \\__/\\_______/|/     \\|  \n"
     "    \n"
     "    \n"
     "                            SERENITY OF ELDERS"
     "    \n"
     "    \n";

 for (char c : message) {
     cout << c;
     this_thread::sleep_for(std::chrono::milliseconds(0));


 }

    cout << "WELCOME to '  Serenity of Elders in the Cybernetic Era.'" << endl << endl << "In the year 2126, the world is under the oppressive rule of the SUPERIORS,\n who seek to assimilate humanity into a cybernetic regime. Join our heroes: \na warrior who escaped the clutches of the SUPERIORS, \na librarian turned mage preserving ancient wisdom, \nand a rogue mastering stealth in the face of high-tech tyranny.\n As you navigate this cybernetic era, your choices will shape \nthe destiny of a world torn between ancient mysticism and technological dominance. \nAre you ready to lead the rebellion and restore freedom? \n";



    User user = initializeUser();
    int questCount = 3;

    for (int i = 0; i < questCount; i++) {
        displayUserinfo(user);
        displayMissions();

        Mission selectedQuest = missionSelection();
        war(user, selectedQuest);

        if (user.health <= 0) {
            cout << "You DIED! Game Over!\n";
            break;
        }

        levelUp(user);

        char continueChoice;
        do {
            cout << "\nDo you want to continue? (y/n): ";
            cin >> continueChoice;

            if (cin.fail()) {
                cin.clear(); // Clear the error flag
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear the input buffer
                cout << "Invalid input. Please enter 'y' or 'n'.\n";
                continue; // Skip the rest of the loop and start over
            }

            if (continueChoice != 'y' && continueChoice != 'Y' && continueChoice != 'n' && continueChoice != 'N') {
                cout << "Invalid choice. Please enter 'y' to continue or 'n' to exit.\n";
            }
        } while (continueChoice != 'y' && continueChoice != 'Y' && continueChoice != 'n' && continueChoice != 'N');

        if (continueChoice != 'y' && continueChoice != 'Y') {
            cout << "\nExiting the game.\n";
            break;
        }
    }

    return 0;
}
