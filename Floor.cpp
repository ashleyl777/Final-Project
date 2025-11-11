/*
 * Copyright 2023 University of Michigan EECS183
 *
 * Floor.cpp
 * Project UID 848fee0125dbb5eb53ed294f20dbef81
 *
 * Ashley Liao, Yeeun Kim, Liming Ng, Jaeseong Koo
 * ashleyyl, kimyeeun, limingf, jaeseo
 *
 * Final Project - Elevators
 */


#include "Floor.h"

using namespace std;

int Floor::tick(int currentTime) {
    int exploadedCount = 0;
    int indicesToRemove[MAX_PEOPLE_PER_FLOOR];
    int numPeopleToRemove = 0;

    for (int i = 0; i < numPeople; ++i) {
        people[i].tick(currentTime);
        
        if (people[i].getAngerLevel() >= MAX_ANGER) {
            indicesToRemove[numPeopleToRemove] = i;
            numPeopleToRemove++;
            exploadedCount++;
        }
    }
    if (0 < numPeopleToRemove) {
        removePeople(indicesToRemove, numPeopleToRemove);
    }
    return exploadedCount;
}

void Floor::addPerson(Person newPerson, int request) {
    if (numPeople < MAX_PEOPLE_PER_FLOOR) {
        people[numPeople] = newPerson;
        numPeople++;
    }
    
    if (request > 0) {
        hasUpRequest = true;
    }
    
    if (request < 0) {
        hasUpRequest = false;
    }
}

void Floor::removePeople(const int indicesToRemove[MAX_PEOPLE_PER_FLOOR],
                         int numPeopleToRemove) {
    if (numPeopleToRemove <= 0) {
        return;
    }

    int remove[MAX_PEOPLE_PER_FLOOR];
    for (int i = 0; i < numPeopleToRemove; i++) {
        remove[i] = indicesToRemove[i];
    }

    for (int i = 0; i < numPeopleToRemove - 1; i++) {
        for (int j = i + 1; j < numPeopleToRemove; j++) {
            if (remove[i] < remove[j]) {
                int temp = remove[i];
                remove[i] = remove[j];
                remove[j] = temp;
            }
        }
    }

    for (int i = 0; i < numPeopleToRemove; i++) {
        int index = remove[i];
        for (int j = index; j < numPeople - 1; j++) {
            people[j] = people[j + 1];
        }
        numPeople--;
    }     

    resetRequests();
}

void Floor::resetRequests() {
    hasUpRequest = false;
    hasDownRequest = false;

    for (int i = 0; i < numPeople; ++i) {

        if (people[i].getTargetFloor() < people[i].getCurrentFloor()) {
            hasDownRequest = true;
        }
        else if (people[i].getTargetFloor > people[i].getCurrentFloor()) {
            hasUpRequest = true;
        }
        if (hasUpRequest && hasDownRequest) {
            return;
        }
    }
}

//////////////////////////////////////////////////////
////// DO NOT MODIFY ANY CODE BENEATH THIS LINE //////
//////////////////////////////////////////////////////

Floor::Floor() {
    hasDownRequest = false;
    hasUpRequest = false;
    numPeople = 0;
}

void Floor::prettyPrintFloorLine1(ostream& outs) const {
    string up = "U";
    outs << (hasUpRequest ? up : " ") << " ";
    for (int i = 0; i < numPeople; ++i){
        outs << people[i].getAngerLevel();
        outs << ((people[i].getAngerLevel() < MAX_ANGER) ? "   " : "  ");
    }
    outs << endl;
}

void Floor::prettyPrintFloorLine2(ostream& outs) const {
    string down = "D";
    outs << (hasDownRequest ? down : " ") << " ";
    for (int i = 0; i < numPeople; ++i) {
        outs << "o   ";
    }
    outs << endl;
}

void Floor::printFloorPickupMenu(ostream& outs) const {
    cout << endl;
    outs << "Select People to Load by Index" << endl;
    outs << "All people must be going in same direction!";
    /*  O   O
    // -|- -|-
    //  |   |
    // / \ / \  */
    outs << endl << "              ";
    for (int i = 0; i < numPeople; ++i) {
        outs << " O   ";
    }
    outs << endl << "              ";
    for (int i = 0; i < numPeople; ++i) {
        outs << "-|-  ";
    }
    outs << endl << "              ";
    for (int i = 0; i < numPeople; ++i) {
        outs << " |   ";
    }
    outs << endl << "              ";
    for (int i = 0; i < numPeople; ++i) {
        outs << "/ \\  ";
    }
    outs << endl << "INDEX:        ";
    for (int i = 0; i < numPeople; ++i) {
        outs << " " << i << "   ";
    }
    outs << endl << "ANGER:        ";
    for (int i = 0; i < numPeople; ++i) {
        outs << " " << people[i].getAngerLevel() << "   ";
    }
    outs << endl << "TARGET FLOOR: ";
    for (int i = 0; i < numPeople; ++i) {
        outs << " " << people[i].getTargetFloor() << "   ";
    }
}

void Floor::setHasUpRequest(bool hasRequest) {
    hasUpRequest = hasRequest;
}

bool Floor::getHasUpRequest() const {
    return hasUpRequest;
}

void Floor::setHasDownRequest(bool hasRequest) {
    hasDownRequest = hasRequest;
}

bool Floor::getHasDownRequest() const {
    return hasDownRequest;
}

int Floor::getNumPeople() const {
    return numPeople;
}

Person Floor::getPersonByIndex(int index) const {
    return people[index];
}











