/*
 * Copyright 2023 University of Michigan EECS183
 *
 * AI.cpp
 * Project UID 848fee0125dbb5eb53ed294f20dbef81
 *
 * Ashley Liao, Yeeun Kim, Liming Ng, Jaeseong Koo
 * ashleyyl, kimyeeun, limingf, jaeseo
 *
 * Final Project - Elevators
 */

#include "AI.h"
#include <cassert>
#include <string>
#include <iostream>
#include <sstream>
#include <cmath>

using namespace std;

string getAIMoveString(const BuildingState& buildingState) {
    
    for (int i = 0; i < NUM_ELEVATORS; ++i) {
        if (!buildingState.elevators[i].isServicing) {
            int currentFloor = buildingState.elevators[i].currentFloor;
            
            if (buildingState.floors[currentFloor].numPeople > 0) {
                return "e" + to_string(i) + "p";
            }
        }
    }

    int maxAngerFound = -1;
    int targetFloor = -1;

    for (int f = 0; f < NUM_FLOORS; ++f) {
        if (buildingState.floors[f].numPeople > 0) {
            for (int p = 0; p < buildingState.floors[f].numPeople; ++p) {
                int currentAnger = buildingState.floors[f].people[p].angerLevel;
                if (currentAnger > maxAngerFound) {
                    maxAngerFound = currentAnger;
                    targetFloor = f;
                }
            }
        }
    }

    if (targetFloor == -1) {
        return "";
    }

    int bestElevatorId = -1;
    int minDistance = 100;

    for (int i = 0; i < NUM_ELEVATORS; ++i) {
        if (!buildingState.elevators[i].isServicing) {
            int dist = abs(buildingState.elevators[i].currentFloor - targetFloor);
            
            if (dist < minDistance) {
                minDistance = dist;
                bestElevatorId = i;
            }
        }
    }

    if (bestElevatorId != -1) {
        return "e" + to_string(bestElevatorId) + "f" + to_string(targetFloor);
    }

    return "";
}

string getAIPickupList(const Move& move, const BuildingState& buildingState,
                       const Floor& floorToPickup) {
    
    int elevatorId = move.getElevatorId();
    int currentFloor = buildingState.elevators[elevatorId].currentFloor;

    int upAngerSum = 0;
    int downAngerSum = 0;
    
    for (int i = 0; i < floorToPickup.getNumPeople(); ++i) {
        Person p = floorToPickup.getPersonByIndex(i);
        
        if (p.getTargetFloor() > currentFloor) {
            upAngerSum += p.getAngerLevel();
        } else if (p.getTargetFloor() < currentFloor) {
            downAngerSum += p.getAngerLevel();
        }
    }
    
    bool pickupUp = (upAngerSum >= downAngerSum);
    
    string indices = "";
    
    for (int i = 0; i < floorToPickup.getNumPeople(); ++i) {
        Person p = floorToPickup.getPersonByIndex(i);
        
        if (pickupUp) {
            if (p.getTargetFloor() > currentFloor) {
                indices += to_string(i);
            }
        } else {
            if (p.getTargetFloor() < currentFloor) {
                indices += to_string(i);
            }
        }
    }
    
    return indices;
}
