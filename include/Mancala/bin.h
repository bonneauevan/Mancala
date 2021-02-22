#ifndef BIN_H
#define BIN_H

class bin{
    private:
        int stones;
        int owner;
        bin* next = nullptr;
        bin* across = nullptr;
        bin* opp_bank = nullptr;
        bin* my_bank = nullptr;
    
    public: 
        bin(int player, int n=4): owner(player), stones(n) {}
        void connectAcross(bin* a){ this->across = a; }
        void connectNext(bin* a){ this->next = a; }
        void connectMyBank(bin* a){ this->my_bank = a; }
        int getStones(){ return this->stones; }
        bin* whatsMyBank(){ return this->my_bank; }
        int whatsMyOwner(){ return this->owner; }
        void toBank();
        bool activate();
};

#endif  //BIN_H