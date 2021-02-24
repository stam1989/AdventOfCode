//============================================================================
// Name        : Adventofcode.cpp
// Author      : Stamatis Chiotis
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================


#include "Day25.h"
#include "Timer.h"

#include <string>


int64_t Day25::Transform(const int64_t& publicKey, const int64_t& subjectNumber) {
    int64_t divider = 20201227;
    int64_t value = 1;
    int64_t loopSize = 0;
    while(true) {
        loopSize++;
        value *= subjectNumber;
        value = value % divider;
        if (value == publicKey) {
            return loopSize;
        }
    }
}


int64_t Day25::GetEncryptionKey(const int64_t& subjectNumber, const int64_t& loopSize) {
    int64_t encryptionKey = 1;
    int64_t divider = 20201227;
    for(int64_t i = 0; i < loopSize; i++) {
        encryptionKey *= subjectNumber;
        encryptionKey = encryptionKey % divider;
    }

    return encryptionKey;
}



int main() {
    Day25 d;

    std::string input_cardPublicKey("2084668");
    std::string input_doorPublicKey("3704642");
    int64_t card_publicKey = stol(input_cardPublicKey);
    int64_t door_publicKey = stol(input_doorPublicKey);
    int64_t subjectNumber = 7;


    {
        Timer t;
        auto card_loopSize = d.Transform(card_publicKey, subjectNumber);
        std::cout << "Card's loop size is: " << card_loopSize << "!\n";
        auto door_loopSize = d.Transform(door_publicKey, subjectNumber);
        std::cout << "Door's loop size is: " << door_loopSize << "!\n";
        auto card_encryptionKey = d.GetEncryptionKey(door_publicKey, card_loopSize);
    
        std::cout << "Encryption key is " <<  card_encryptionKey << "!\n";
    }

    {
        Timer t;

    }
    
    return 0;
}