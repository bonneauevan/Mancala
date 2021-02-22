#include <bin.h>
#include <iostream>
void bin::toBank(){
    my_bank->stones += this->stones;
    this->stones = 0;
}

bool bin::activate(){
    int tmp = stones;
    bin* next_bin = this->next;
    stones=0;
    while(tmp>0){
        if(tmp == 1 && next_bin == this->whatsMyBank()){
            std::cout << "bank extra turn" << std::endl;
            next_bin->stones++;
            return true;            
        }else if(tmp == 1 && next_bin->stones == 0 && next_bin != this->whatsMyBank() && this->owner == next_bin->whatsMyOwner()){
            //take the stones across and move to score bin
            std::cout << "stone steal" << std::endl;
            int acc = next_bin->across->stones;
            next_bin->across->stones = 0;
            this->my_bank->stones += (acc + 1);
            return false;
        }
        next_bin->stones++;
        next_bin = next_bin->next;
        tmp--;
    }
    return false;
}

