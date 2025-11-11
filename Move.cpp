/*
 * Copyright 2023 University of Michigan EECS183
 *
 * Move.cpp
 * Project UID 848fee0125dbb5eb53ed294f20dbef81
 *
 * <#Names#>
 * <#Uniqnames#>
 *
 * Final Project - Elevators
 */
 
#include <cmath>
#include <sstream>
#include <stdio.h>      
#include <stdlib.h>
#include "Move.h"

using namespace std;

Move::Move(string commandString) : Move() {
	if (commandString.empty()) {
        isPass = true;
        return;
    }
    string upperCommandString = commandString;
    for (char &c : upperCommandString) {
        c = toupper(c);
    }    
    if (upperCommandString == "S") {
        isSave = true;
        return;
    }
    if (upperCommandString == "Q") {
        isQuit = true;
        return;
    }
	
	if (upperCommandString.length() >= 3 && upperCommandString[0] == 'E') {
        elevatorId = commandString[1] - '0';
        char moveType = upperCommandString[2];        
        if (moveType == 'F' && upperCommandString.length() >= 4) {
            targetFloor = commandString[3] - '0';     
        } 
		else if (moveType == 'P') {
            isPickup = true;
        }
    }
}

bool Move::isValidMove(Elevator elevators[NUM_ELEVATORS]) const {
	if (isPass || isSave || isQuit) {
        return true;
    }
	if (isPickup || (targetFloor != -1 && elevatorId != -1)) { 
        if (elevatorId < 0 || elevatorId >= NUM_ELEVATORS) {
            return false;
        }     
        if (elevators[elevatorId].isServicing()) {
            return false;
        }
        if (!isPickup) {
            if (targetFloor < 0 || targetFloor >= NUM_FLOORS) {
                return false;
            }            
            if (targetFloor == elevators[elevatorId].getCurrentFloor()) {
                return false;
            }
        }        
        return true;
    }    
    return false;
}


void Move::setPeopleToPickup(const string& pickupList, const int currentFloor, 
                             const Floor& pickupFloor) {
	numPeopleToPickup = 0;
    totalSatisfaction = 0;
	targetFloor = -1;
    int maxDistance = -1;
	for (char indexChar : pickupList) {
        int personIndex = indexChar - '0';        
        if (personIndex >= 0 && personIndex < pickupFloor.getNumPeople()) {
			Person p = pickupFloor.getPersonByIndex(personIndex);
			peopleToPickup[numPeopleToPickup] = personIndex;
			numPeopleToPickup++;
			totalSatisfaction += p.getAngerLevel();
			int personTargetFloor = p.getTargetFloor();
            int distance = abs(personTargetFloor - currentFloor);
            if (distance > maxDistance) {
                maxDistance = distance;
                targetFloor = personTargetFloor;
            }
        }
    }
}

//////////////////////////////////////////////////////
////// DO NOT MODIFY ANY CODE BENEATH THIS LINE //////
//////////////////////////////////////////////////////

Move::Move() {
    elevatorId = -1;
    targetFloor = -1;
    numPeopleToPickup = 0;
    totalSatisfaction = 0;
	isPass = false;
    isPickup = false;
    isSave = false;
    isQuit = false;
}

bool Move::isPickupMove() const {
    return isPickup;
}

bool Move::isPassMove() const {
	return isPass;
}

bool Move::isSaveMove() const {
	return isSave;
}

bool Move::isQuitMove() const {
	return isQuit;
}

int Move::getElevatorId() const {
    return elevatorId;
}

int Move::getTargetFloor() const {
    return targetFloor;
}

int Move::getNumPeopleToPickup() const {
    return numPeopleToPickup;
}

int Move::getTotalSatisfaction() const {
    return totalSatisfaction;
}

void Move::setTargetFloor(int inTargetFloor) {
    targetFloor = inTargetFloor;
}

void Move::copyListOfPeopleToPickup(int newList[MAX_PEOPLE_PER_FLOOR]) const {
    for (int i = 0; i < numPeopleToPickup; ++i) {
        newList[i] = peopleToPickup[i];
    }
}

