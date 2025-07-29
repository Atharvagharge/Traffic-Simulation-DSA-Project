// #ifndef SIMULATION_H
// #define SIMULATION_H

// #include "graph.h"

// // Function declarations:
// void updateTraffic(Graph G);
// void adjustSignals(Graph G);
// void simulationLoop(Graph G, int simulationDuration);  // simulationDuration in simulation time units

// #endif

#ifndef SIMULATION_H
#define SIMULATION_H

#include "graph.h"

// Function declarations:
void updateTraffic(Graph G);
void adjustSignals(Graph G);
void simulationLoop(Graph G, int simulationDuration);  // simulationDuration in simulation time units
void handleEmergencyVehicle(Graph G, int intersection);  // New function to prioritize emergency vehicles



#endif

