/*
 *  A simple physics simulator written in pure C for absolutely no reason.
 *  Using 8 spaces per tab for fun.
 */

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
struct Planet {
        float *position,
              *velocity,
              *force;
        float mass;
} typedef Planet;

struct SolarSystem {
        Planet **n_bodies;
        int n;
        int size;
} typedef SolarSystem;


void InitializePlanet(Planet *p) {
        p->position = (float *) malloc(sizeof(float) * 3);
        p->velocity = (float *) malloc(sizeof(float) * 3);
        p->force = (float *) malloc(sizeof(float) * 3);
        for (int i = 0; i < 3; ++i) {
                p->position[i] = 0;
                p->velocity[i] = 0;
                p->force[i] = 0;
        }
        p->mass = 1; // solar mass
}

void FreePlanet(Planet *p) {
        free(p->position);
        free(p->velocity);
        free(p->force);
}

void InitializeSolarSystem(SolarSystem *sol, int size) {
        sol->n_bodies = malloc(sizeof(Planet) * size);
        sol->n = 0;
        sol->size = size;
}

void FreeSolarSystem(SolarSystem *sol) {
        free(sol->n_bodies);
}

int AddPlanet(SolarSystem *sol, Planet *p) {
        sol->n_bodies[sol->n] = p;
        return sol->n++;
}

void Step(SolarSystem  *sol, float dt) {
        for (int i = 0; i < sol->n; ++i) {
                Planet *planet = sol->n_bodies[i];
                planet->force[2] += planet->mass * -9.8;
                planet->velocity[2] +=  planet->force[2] / planet->mass * dt;
                planet->position[2] += planet->velocity[2] * dt;
                planet->force[2] = 0;
                printf("%f %f %f\n", planet->position[0],
                                     planet->position[1],
                                     planet->position[2]);
        }
}

int main() {
        Planet *sun = (Planet *) malloc(sizeof(Planet));
        InitializePlanet(sun);

        SolarSystem *sol = (SolarSystem *) malloc(sizeof(SolarSystem));
        InitializeSolarSystem(sol, 1);
        AddPlanet(sol, sun);
        for (int i = 0; i < 10; ++i) {
               Step(sol, 1);
               sleep(1);
        }
        FreeSolarSystem(sol);
        FreePlanet(sun);
        return 0;
}
