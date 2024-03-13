#include <iostream>
#include <iomanip>
#include <cstring>
using namespace std;


/*
Struct Name: Block
This structure stores the dice type: glass, wood, recycle, stone
It also stores the value assigned to it
*/

struct Block
{
    char type; // Type of block as a character, block does not exist, it is an X
    int number; // Value of the block, if block does not exist, it is a -1
};

void empty_building(Block building[][3]);
void fill_building(Block building[][3]);
int glass(Block building[][3]);
int recycled(Block building[][3]);
int stone(Block building[][3]);
int wood(Block building[][3]);
void print_building(Block building[][3]);
void print_score(int glass, int recycle, int stone, int wood);

int main() {
    int glass_points, stone_points,
    recycled_points, wood_points;

    Block building[6][3];

    empty_building(building);
    fill_building(building);

    glass_points = glass(building);
    recycled_points = recycled(building);
    stone_points = stone(building);
    wood_points = wood(building);

    cout << endl;

    print_building(building);

    cout << endl;

    print_score(glass_points, recycled_points,
                stone_points, wood_points);

    return 0;
}

/*

Function Name: print_score()

Purpose: To print out the score of the building

Details: Takes in all the points from the main program and prints it out
         in an organized fashion using setw from iomanip

Inputs: glass - The glass points
        recycle - The recycled points
        stone -   The stone points
        wood -    The wood points

*/


void print_score(int glass, int recycle, int stone, int wood){

    int total = glass + recycle + stone + wood;

    cout << "+----------+----+" << endl;
    cout << "|" << setw(10) << left << " glass" << "| " << setw(3) << glass << "|" << endl;
    cout << "|" << setw(10) << left << " recycled" << "| " << setw(3) << recycle << "|" << endl;
    cout << "|" << setw(10) << left << " stone" << "| " << setw(3) << stone << "|" << endl;
    cout << "|" << setw(10) << left << " wood" << "| " << setw(3) << wood << "|" << endl;
    cout << "+==========+====+" << endl;
    cout << "|" << setw(10) << left << " total" << "| " << setw(3) << total << "|" << endl;
    cout << "+----------+----+" << endl;

    return;
}

/*

Function Name: print_building()

Purpose: Prints out the appearance of the building given the format
         from the assignment

Details: Uses a for loop to iterate through each layer of the building
         Once it reaches a block, create a point to save where it rests and exit loop
         Use a for loop again to iterate through each layer starting from the saved point
         If there exists an 'X' in a column, print out "--"
         If not, print out the Block type and number

Inputs: building - The array of the building

*/

void print_building(Block building[][3]){

    int setpoint = -1;

    for (int i = 0; i < 6; i++){ //iterates through rows

        for (int j = 0; j < 3; j++){ //iterates through columns

            if (building[i][j].type != 'X'){ //Once it reaches a block break the loop and make a setpoint

                setpoint = i;
                break;
            }
        }

        if (setpoint != -1) break; // Break the outer loop if a valid setpoint has been found
    }

    if (setpoint != -1) { // Check if a valid setpoint has been found


        for (int i = setpoint; i < 6; i++) { //iterating through each row until the end

            for (int j = 0; j < 3; j++){

                if (j < 2){

                    if (building[i][j].type != 'X'){

                        cout << building[i][j].type << building[i][j].number << "|";

                    } else {

                        cout << "--|";
                    }

                } else {

                    if (building[i][j].type != 'X'){

                        cout << building[i][j].type << building[i][j].number << endl;

                    } else {

                        cout << "--" << endl;
                    }

                }
            }
        }
    }

    return;
}

/*

Function Name: wood()

Purpose: To count the points of any wood blocks in the building

Details: Iterates through each layer of the building tp check if there
                  exists a 'W' as the Block type
                  If so, check above, below, right, and left if there are
                  any blocks adjacent, if so add 2 points

Inputs: building - The array of the building

*/

int wood(Block building[][3]) {
    int wood_score = 0;

    for (int i = 5; i > -1; i--) { // Iterates through rows
        for(int j = 0; j < 3; j++) { // Iterates through columns
            if (building[i][j].type == 'W') {
                // Checks if there is a block on the right
                if (!((j + 1) > 2) && (building[i][j + 1].type != 'X')) {
                    wood_score += 2;
                }
                // Checks if there is a block on the left
                if(!((j - 1) < 0) && (building[i][j - 1].type != 'X')) {
                    wood_score += 2;
                }
                // Checks if there is a block on the bottom
                if (!((i + 1) > 5) && (building[i + 1][j].type != 'X')) {
                    wood_score += 2;
                }
                // Checks if there is a block on the top
                if (!((i - 1) < 0) && (building[i - 1][j].type != 'X')) {
                    wood_score += 2;
                }
            } else {
                wood_score += 0;
            }
        }
    }

    return wood_score;
}

/*

Function Name: stone()

Purpose: To count the points of any stone blocks in the building

Details: Iterates through each layer of the building to check if a Block type
        is an 'S'
        if so, find where it exists in the layer and distribute the
        respective points for the layer

Inputs: building - The array of the building

*/

int stone(Block building[][3]){
    int stone_score = 0;

    for (int i = 5; i > -1; i--){ // Iterates through rows

        for(int j = 0; j < 3; j++){ // Iterates through columns

            if(i == 5){

                if (building[i][j].type == 'S'){
                    stone_score += 2;
                }

            } else if ( i == 4){

                if (building[i][j].type == 'S'){
                    stone_score += 3;
                }
            } else if ( i == 3){

                if (building[i][j].type == 'S'){
                    stone_score += 5;
                }
            } else if ( i == 2){

                if (building[i][j].type == 'S'){
                    stone_score += 8;
                }
            } else {

                if (building[i][j].type == 'S'){
                    stone_score += 8;
                }

            }

        }

    }


    return stone_score;
}

/*

Function Name: recycled()

Purpose: To count the points of any recycled blocks in the building

Details: Iterates through each layer of the building and if there exists
         an 'R', then store the amount of them and distribute the
         respective points based on their amount

Inputs:  bulding - The array of the building


*/

int recycled(Block building[][3]){
    int recycled_amount = 0;
    int recycled_score;

    for (int i = 0; i < 6; i++){ // Iterates through rows

        for(int j = 0; j < 3; j++){ // Iterates through columns

            if (building[i][j].type == 'R'){
                recycled_amount++;
            }
        }
    }

    if (recycled_amount == 0)
    {
        recycled_score = 0;

    } else if (recycled_amount == 1)
    {
        recycled_score = 2;

    } else if (recycled_amount == 2)
    {
        recycled_score = 5;

    } else if (recycled_amount == 3)
    {
        recycled_score = 10;

    } else if (recycled_amount == 4)
    {
        recycled_score = 15;

    } else if (recycled_amount == 5)
    {
        recycled_score = 20;

    } else
    {
        recycled_score = 30;
    }

    return recycled_score;
}

/*

Function Name: glass()

Purpose: To count the points of any glass blocks in the building

Details: Iterates through each layer of the building and if the
         Block type is an 'G', add the number assigned to it to the
         score counter

Inputs: building - The array of the building

*/


int glass(Block building[][3]){
    int glass_amount = 0;

    for (int i = 0; i < 6; i++){ // Iterates through rows

        for(int j = 0; j < 3; j++){ // Iterates through columns

            if (building[i][j].type == 'G'){
                glass_amount += building[i][j].number;
            }

        }
    }
    return glass_amount;
}

/*

Function Name: fill_building()

Purpose: To read the building file and implement the dice to their
         given coordinates in a list

Details: Until it reads the end of the file, it will read
         the row position, column position, then the die and place
         them in their respective coordinates

Inputs: building - The array of the building

*/

void fill_building(Block building[][3]){
    int row, column;
    char dice[2];

    cin >> row >> column >> dice[0] >> dice[1];
    while(!cin.eof()){

        building[row][column].type = dice[0];
        building[row][column].number = dice[1] - 48;

        cin >> row >> column >> dice[0] >> dice[1];
    }


    return;
}

/*

Function Name: empty_building()

Purpose: Fills a building array with X's with the value -1

Details: Iterates through each layer of the building and fills
         it with X's and -1's

Inputs - building - The array of the building

*/


void empty_building(Block building[][3]){

    for (int i = 0; i < 6; i++) // Iterates through Rows
    {
        for (int j = 0; j < 3; j++) // Iterates through columns
        {
            building[i][j].type = 'X';
            building[i][j].number = -1;
        }

    }

    return;
}
