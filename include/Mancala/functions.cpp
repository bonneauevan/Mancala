#ifndef FUNCTIONS_CPP
#define FUNCTIONS_CPP
#include <vector>
#include <iostream>
#include <bin.h>

//-----------------------------------------------------------------------------
//calculates the sum of the bins on one side of the board excluding bank.
int rowSum(std::vector<bin*> a){
    int out = 0;
    for(int i=0; i<a.size(); i++){
        out += a[i]->getStones();
    }
    return out;
};
//-----------------------------------------------------------------------------
//moves all stones in the row to that players bank.
void bankAll(std::vector<bin*> a){
    for(int i=0; i<a.size(); i++){
        a[i]->toBank();
    }
};
//-----------------------------------------------------------------------------
//checks which player has more stones and prints a win message for whoever has more.
void calcWin(bin* p1, bin* p2){
    if(p1->getStones() > p2->getStones()){
        std::cout << "Player 1 wins" << std::endl;
    }else if(p1->getStones() > p2->getStones()){
        std::cout << "Player 2 wins" << std::endl;
    }else{
        std::cout << "The game ends in a tie" << std::endl;
    }
}
//-----------------------------------------------------------------------------
//initialize the initial board state, generate bins for each vector, connect all bin pointers.
void initBoard(std::vector<bin*> &p1, std::vector<bin*> &p2, bin* &p1_bank, bin* &p2_bank){
    //create new bin objects and connect them in order.
    //banks are connected to the start of the opposite players vector with the next pointer.
    for(int i=0; i<6; i++){
        p1.push_back(new bin(0));
        p1[i]->connectMyBank(p1_bank);
        p2.push_back(new bin(1));
        p2[i]->connectMyBank(p2_bank);
        if(i==0){
            p1_bank->connectNext(p2[0]);
            p2_bank->connectNext(p1[0]);
        }else{
            p1[i-1]->connectNext(p1[i]);
            p2[i-1]->connectNext(p2[i]);
        }
    }
    //end of the player vector is connected to the same players bank
    p1[5]->connectNext(p1_bank);
    p2[5]->connectNext(p2_bank);

    //the across pointers will connect to the bank physically across
    for(int i=0; i<6; i++){
        p1[i]->connectAcross(p2[5-i]);
        p2[i]->connectAcross(p1[5-i]);
    }
};
//-----------------------------------------------------------------------------
//gets a valid integer input from the user.
int getValidInput(int player, std::vector<bin*> p1, std::vector<bin*> p2){
    int move; 
    std::cin >> move;
    std::cout << move << std::endl;
    while(move < 0 || move > 5 || player==0 ? p1[move]->getStones()==0 : p2[move]->getStones()==0){
        std::cin.clear();
        std::cin.ignore();
        std::cout << "please enter a valid input: ";
        std::cin >> move;
        std::cout << std::endl;
    }
    return move;
}
//-----------------------------------------------------------------------------
//draws the board to cout based on the current state of the game.
void updateBoard(int player, std::vector<bin*> p1, std::vector<bin*> p2, bin* p1_bank, bin* p2_bank){
    printf("    |-------------------------------------------------|\n");
    if(player == 0){ //player 1
        printf("P2> |      |");
        for(int i=0; i<p2.size(); i++){
            printf("%*d  |", 3, p2[5-i]->getStones());
        }
        printf("      |\n");
        printf("    | %*d  |-----------------------------------", 3, p2_bank->getStones());
        printf("| %*d  |\n", 3, p1_bank->getStones());
        printf("P1> |      |");
        for(int i=0; i<p1.size(); i++){
            printf("%*d  |", 3, p1[i]->getStones());
        }
        printf("      |\n");
    }else{
        printf("P1> |      |");
        for(int i=0; i<p1.size(); i++){
            printf("%*d  |", 3, p1[5-i]->getStones());
        }
        printf("      |\n");
        printf("    | %*d  |-----------------------------------", 3, p1_bank->getStones());
        printf("| %*d  |\n", 3, p2_bank->getStones());
        printf("P2> |      |");
        for(int i=0; i<p2.size(); i++){
            printf("%*d  |", 3, p2[i]->getStones());
        }
        printf("      |\n");
    }
    printf("    |--------(0)---(1)---(2)---(3)---(4)---(5)--------|\n");
    
};
#endif  //FUNCTION_CPP