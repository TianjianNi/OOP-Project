/*
 * Author: Tianjian Ni
 * Winter 2021 Tandon Bridge OOP Project
 * */

/*The goal for this project is to create a simple two-dimensional predator-prey simulation. In this simulation the prey are ants and the pred-ators are doodlebugs. These critters live in a world composed of a 20 x 20 grid of cells. Only one critter may occupy a cell at a time. The grid is enclosed, so a critter is not allowed to move off the edges of the world. Time is simulated in time steps. Each critter performs some action every time step.
The ants behave according to the following model: Move. Every time step, randomly try to move up, down, left, or right. If the neighboring cell in the selected direction is occupied or would move the ant off the grid, then the ant stays in the current cell.

Breed. If an ant survives for three time steps, then at the end of the time step (that is; after moving) the ant will breed. This is simulated by creat-ing a new ant in an adjacent (up, down, left, or right) cell that is empty. If there is no empty cell available, then no breeding occurs. Once an off-spring is produced, an ant cannot produce an offspring until three more time steps have elapsed.

The doodlebugs behave according to the following model: Move. Every time step, if there is an adjacent ant (up, down, left, or right), then the doodlebug will move to that cell and eat the ant. Otherwise, the doodlebug moves according to the same rules as the ant. Note that a doodlebug cannot eat other doodlebugs.

Breed. If a doodlebug survives for eight time steps, then at the end of the time step it will spawn off a new doodlebug in the same manner as the ant.

Starve. If a doodlebug has not eaten an ant within the last three time steps, then at the end of the third time step it will starve and die. The doodlebug should then be removed from the grid of cells.

During one turn, all the doodlebugs should move before the ants do.

Write a program to implement this simulation and draw the world using ASCII characters of "o" for an ant and "X" for a doodlebug or "-" for an empty space. Create a class named Organism that encapsulates basic data common to both ants and doodlebugs. This class should have a virtual function named move that is defined in the derived classes of Ant and Doodlebug. You may need additional data structures to keep track of which critters have moved.

Initialize the world with 5 doodlebugs and 100 ants. After each time step, prompt the user to press Enter to move to the next time step. You should see a cyclical pattern between the population of predators and prey, although random perturbations may lead to the elimination of one or both species.
*/

#include <iostream>
#include <vector>
#include <cstdlib>

using namespace std;

char coordinate[20][20];

void printBoard(){
    for (int i = 0; i < 20; i++) {
        for (int j = 0; j < 20; j++) {
            cout << coordinate[i][j] << "\t";
        }
        cout << endl;
    }
}

class Organism
{
public:
    virtual void move();

    Organism(int row, int column) {
        x = row;
        y = column;
    }
    int getY() const {
        return y;
    }
    int getX() const {
        return x;
    }
    void setX(int row) {
        x = row;
    }
    void setY(int column) {
        y = column;
    }
private:
    int x;
    int y;
};

void Organism::move() {

}

class Ant: public Organism
{
public:
    Ant(int row, int column) : Organism(row, column) {
        setX(row);
        setY(column);
        coordinate[getX()][getY()] = 'o';
        breedTurnCount = 0;
    }
    int getBreedTurnCount() const{
        return breedTurnCount;
    }
    void setBreedTurnCount(int turn){
        breedTurnCount = turn;
    }
    void move();
    void breed();
private:
    int breedTurnCount;
};

vector<Ant> ants;

void Ant::move() {

    int randomNum = rand() % 4;

    if (randomNum == 0){
        if (getX() - 1 >= 0){
            if (coordinate[getX() - 1][getY()] == '-'){
                coordinate[getX() - 1][getY()] = 'o';
                coordinate[getX()][getY()] = '-';
                setX(getX() - 1);
            }
        }
    }

    if (randomNum == 1){
        if (getX() + 1 <= 19){
            if (coordinate[getX() + 1][getY()] == '-'){
                coordinate[getX() + 1][getY()] = 'o';
                coordinate[getX()][getY()] = '-';
                setX(getX() + 1);
            }
        }
    }

    if (randomNum == 2){
        if (getY() - 1 >= 0){
            if (coordinate[getX()][getY() - 1] == '-'){
                coordinate[getX()][getY() - 1] = 'o';
                coordinate[getX()][getY()] = '-';
                setY(getY() - 1);
            }
        }
    }

    if (randomNum == 3){
        if (getY() + 1 <= 19){
            if (coordinate[getX()][getY() + 1] == '-'){
                coordinate[getX()][getY() + 1] = 'o';
                coordinate[getX()][getY()] = '-';
                setY(getY() + 1);
            }
        }
    }

}

void Ant::breed() {
    setBreedTurnCount(getBreedTurnCount() + 1);
    if (getBreedTurnCount() == 3){
        setBreedTurnCount(0);
        int x, y;
        if (coordinate[getX() - 1][getY()] == '-'){
            x = getX() - 1;
            y = getY();
            Ant ant(x, y);
            ants.push_back(ant);
        } else if (coordinate[getX() + 1][getY()] == '-'){
            x = getX() + 1;
            y = getY();
            Ant ant(x, y);
            ants.push_back(ant);
        } else if (coordinate[getX()][getY() - 1] == '-'){
            x = getX();
            y = getY() - 1;
            Ant ant(x, y);
            ants.push_back(ant);
        } else if (coordinate[getX()][getY() + 1] == '-'){
            x = getX();
            y = getY() + 1;
            Ant ant(x, y);
            ants.push_back(ant);
        }
    }
}

class Doodlebug: public Organism
{
public:
    Doodlebug (int row, int column) : Organism(row, column) {
        setX(row);
        setY(column);
        coordinate[row][column] = 'X';
        setBreedTurnCount(0);
        setStarveTurnCount(0);
    }
    int getBreedTurnCount() const{
        return breedTurnCount;
    }
    void setBreedTurnCount(int breedTurn){
        breedTurnCount = breedTurn;
    }
    int getStarveTurnCount() const{
        return starveTurnCount;
    }
    void setStarveTurnCount(int starveTurn){
        starveTurnCount = starveTurn;
    }
    void move();
    void breed();

private:
    int breedTurnCount;
    int starveTurnCount;
};

vector<Doodlebug> doodlebugs;

void Doodlebug::move() {

    setStarveTurnCount(getStarveTurnCount() + 1);

    bool eat = false;

    int x, y;
    if (coordinate[getX() - 1][getY()] == 'o'){
        eat = true;
        x = getX() - 1;
        y = getY();
        auto it = ants.begin();
        while(it != ants.end()){
            if (it->getX() == x && it->getY() == y) {
                coordinate[it->getX()][it->getY()] = 'X';
                it = ants.erase(it);
            }
            else {
                ++it;
            }
        }
        coordinate[getX()][getY()] = '-';
        setX(getX() - 1);
    } else if (coordinate[getX() + 1][getY()] == 'o'){
        eat = true;
        x = getX() + 1;
        y = getY();
        auto it = ants.begin();
        while(it != ants.end()){
            if (it->getX() == x && it->getY() == y) {
                coordinate[it->getX()][it->getY()] = 'X';
                it = ants.erase(it);
            }
            else {
                ++it;
            }
        }
        coordinate[getX()][getY()] = '-';
        setX(getX() + 1);
    } else if (coordinate[getX()][getY() - 1] == 'o'){
        eat = true;
        x = getX();
        y = getY() - 1;
        auto it = ants.begin();
        while(it != ants.end()){
            if (it->getX() == x && it->getY() == y) {
                coordinate[it->getX()][it->getY()] = 'X';
                it = ants.erase(it);
            }
            else {
                ++it;
            }
        }
        coordinate[getX()][getY()] = '-';
        setY(getY() - 1);
    } else if (coordinate[getX()][getY() + 1] == 'o'){
        eat = true;
        x = getX();
        y = getY() + 1;
        auto it = ants.begin();
        while(it != ants.end()){
            if (it->getX() == x && it->getY() == y) {
                coordinate[it->getX()][it->getY()] = 'X';
                it = ants.erase(it);
            }
            else {
                ++it;
            }
        }
        coordinate[getX()][getY()] = '-';
        setY(getY() + 1);
    }

    if (eat){
        setStarveTurnCount(0);
    } else {

        int randomNum = rand() % 4;

        if (randomNum == 0) {
            if (getX() - 1 >= 0) {
                if (coordinate[getX() - 1][getY()] == '-') {
                    coordinate[getX() - 1][getY()] = 'X';
                    coordinate[getX()][getY()] = '-';
                    setX(getX() - 1);
                }
            }
        }

        if (randomNum == 1) {
            if (getX() + 1 <= 19) {
                if (coordinate[getX() + 1][getY()] == '-') {
                    coordinate[getX() + 1][getY()] = 'X';
                    coordinate[getX()][getY()] = '-';
                    setX(getX() + 1);
                }
            }
        }

        if (randomNum == 2) {
            if (getY() - 1 >= 0) {
                if (coordinate[getX()][getY() - 1] == '-') {
                    coordinate[getX()][getY() - 1] = 'X';
                    coordinate[getX()][getY()] = '-';
                    setY(getY() - 1);
                }
            }
        }

        if (randomNum == 3) {
            if (getY() + 1 <= 19) {
                if (coordinate[getX()][getY() + 1] == '-') {
                    coordinate[getX()][getY() + 1] = 'X';
                    coordinate[getX()][getY()] = '-';
                    setY(getY() + 1);
                }
            }
        }
    }

}

void starve(){

    auto it = doodlebugs.begin();
    while(it != doodlebugs.end()){
        if (it->getStarveTurnCount() == 3) {
            coordinate[it->getX()][it->getY()] = '-';
            it = doodlebugs.erase(it);
        }
        else {
            ++it;
        }
    }
}

void Doodlebug::breed() {

    setBreedTurnCount(getBreedTurnCount() + 1);

    if (getBreedTurnCount() == 8){
        setBreedTurnCount(0);
        int x, y;
        if (coordinate[getX() - 1][getY()] == '-'){
            x = getX() - 1;
            y = getY();
            Doodlebug doodlebug(x, y);
            doodlebugs.push_back(doodlebug);
        } else if (coordinate[getX() + 1][getY()] == '-'){
            x = getX() + 1;
            y = getY();
            Doodlebug doodlebug(x, y);
            doodlebugs.push_back(doodlebug);
        } else if (coordinate[getX()][getY() - 1] == '-'){
            x = getX();
            y = getY() - 1;
            Doodlebug doodlebug(x, y);
            doodlebugs.push_back(doodlebug);
        } else if (coordinate[getX()][getY() + 1] == '-'){
            x = getX();
            y = getY() + 1;
            Doodlebug doodlebug(x, y);
            doodlebugs.push_back(doodlebug);
        }
    }
}



void initialize() {

    srand(time(NULL));

    for (int i = 0; i < 20; i++) {
        for (int j = 0; j < 20; j++) {
            coordinate[i][j] = '-';
        }
    }

    int randomNumX, randomNumY, count;
    count = 0;
    while (count < 100){
        randomNumX = random() % 20;
        randomNumY = random() % 20;
        if (coordinate[randomNumX][randomNumY] == '-'){
            Ant ant(randomNumX, randomNumY);
            ants.push_back(ant);
            count += 1;
        }
    }
    count = 0;
    while (count < 5){
        randomNumX = random() % 20;
        randomNumY = random() % 20;
        if (coordinate[randomNumX][randomNumY] == '-'){
            Doodlebug doodlebug(randomNumX, randomNumY);
            doodlebugs.push_back(doodlebug);
            count += 1;
        }
    }
    printBoard();
}

int main() {

    initialize();
    int turn, X, o;
    bool run;
    turn = 0;

    do {
        turn += 1;
        cout << endl;
        for (int i = 0; i < doodlebugs.size(); i++) {
            doodlebugs[i].move();
            doodlebugs[i].breed();
        }

        starve();
        for (int j = 0; j < ants.size(); j++) {
            ants[j].move();
            ants[j].breed();
        }
        printBoard();
        X = 0;
        o = 0;
        for (int i = 0; i < 20; ++i) {
            for (int j = 0; j < 20; ++j) {
                if (coordinate[i][j] == 'X'){
                    X += 1;
                } else if (coordinate[i][j] == 'o'){
                    o += 1;
                }
            }
        }
        cout << "After turn " << turn << " move, X number is " << X << ", o number is " << o << endl;
        cout << endl;
        cout << "Press enter to continue" << endl;

        run = false;
        if (cin.get() == '\n'){
            run = true;
        }
    } while (run);

    return 0;
}
