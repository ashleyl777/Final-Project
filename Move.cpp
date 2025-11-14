/*
 * Copyright 2023 University of Michigan EECS183
 *
 * Move.cpp
 * Project UID 848fee0125dbb5eb53ed294f20dbef81
 *
 * Ashley Liao, Yeeun Kim, Liming Ng, Jaeseong Koo
 * ashleyyl, kimyeeun, limingf, jaeseo
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
    }

	else if (commandString == "S" || commandString == "s") { 
		isSave = true; 
	}

	else if (commandString == "Q" || commandString == "q") {
		isQuit = true; 
	}

	else if (commandString.size() == 4) { 
		elevatorId = commandString.at(1) - '0';
		targetFloor = commandString.at(3) - '0';
	}

	else {
		elevatorId = commandString.at(1) - '0';
		isPickup = true; 
	}
}

bool Move::isValidMove(Elevator elevators[NUM_ELEVATORS]) const {
	if (isPass || isSave || isQuit) {
        return true;
    }

   else if (isPickup) {
        if (elevatorId >= 0 && elevatorId < NUM_ELEVATORS && 
            !elevators[elevatorId].isServicing()) {
            return true;
        }
    }

    else if (targetFloor != -1) {
        if (elevatorId >= 0 && elevatorId < NUM_ELEVATORS &&
            !elevators[elevatorId].isServicing() && targetFloor >= 0 &&
            targetFloor < NUM_FLOORS && targetFloor != elevators[elevatorId].getCurrentFloor()) {
            return true;
        }
    }

    else {
        return false;
    }
    return false;
}

void Move::setPeopleToPickup(const string& pickupList, const int currentFloor, 
                             const Floor& pickupFloor) {
    numPeopleToPickup = 0;
    totalSatisfaction = 0;
    
    int mostExtreme = -1;
    int maxDiff = -1;

    for (int i = 0; i < pickupList.size(); i++) {
        int indice = pickupList.at(i) - '0';
		peopleToPickup[numPeopleToPickup] = indice;
        numPeopleToPickup++;

        Person p = pickupFloor.getPersonByIndex(indice);
        totalSatisfaction = totalSatisfaction + (MAX_ANGER - p.getAngerLevel());

        int diff = abs(currentFloor - p.getTargetFloor());
        if (diff > maxDiff) {
            maxDiff = diff;
            mostExtreme = p.getTargetFloor();
        }
    }

    targetFloor = mostExtreme;
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









