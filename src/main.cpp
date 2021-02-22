/* Planning 
 -bin class
 |_next ->
 |_across ->
 |_int stones
 >> select - remove stones and follow next pointers until stones is 0 adding a stone to each bin
 >> collectAcross - remove stones from this bin and across bin and deposit to end

 player array of bin
 - 7 elements, 6 normal and 1 bank
 - 6 normal bins connect across to 7-i bin of other player 

 board design 
    |-------------------------------------------------|
    |      |  x  |  x  |  x  |  x  |  x  |  x  |      |
    | bank |-----------------------------------| bank |
    |      |  x  |  x  |  x  |  x  |  x  |  x  |      |
    |---------0-----1-----2-----3-----4-----5---------|
*/
#include <bin.h>
#include <functions.cpp>

int main(int argc, char *argv[])
{
    //-----------------------------------------------------------------------------
    //Setup
    //instantiate banks and the player bin vectors
    bin* p1_bank = new bin(0, 0);
    bin* p2_bank = new bin(1, 0);
	std::vector<bin*> p1, p2;
    p1.reserve(6);
    p2.reserve(6);

    initBoard(p1, p2, p1_bank, p2_bank);

    int player = 0;
    int move;
    bool exTurn = false;

    //std::cout << p1[0]->whatsMyBank() << "  -  " << p1_bank << std::endl;
    

    
    //-----------------------------------------------------------------------------
    // main game loop
    while(true){
        updateBoard(player, p1, p2, p1_bank, p2_bank);
        std::cout << "Player " << player+1 << " make your move: ";
        move = getValidInput(player, p1, p2);
        std::cout << std::endl;

        if(player == 0){
            //perform move for player 1
            exTurn = p1[move]->activate();
            if(rowSum(p1) == 0){ //end of game condition
                updateBoard(player, p1, p2, p1_bank, p2_bank);
                bankAll(p2);
                calcWin(p1_bank, p2_bank);
                return 0;
            }
        }else{
            //perform move for player 2
            exTurn = p2[move]->activate();
            if(rowSum(p2) == 0){ //end of game condition
                updateBoard(player, p1, p2, p1_bank, p2_bank);
                bankAll(p1);
                calcWin(p1_bank, p2_bank);
                return 0;
            }
        }
        //add weird end game condition

        if(!exTurn)
            player = (player+1)%2;

    }
    return 0;
    
}