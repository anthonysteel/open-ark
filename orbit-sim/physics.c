/*
 *  A simple physics simulator written in pure C for absolutely no reason.
 *  Using 8 spaces per tab for fun.
 *
 *  Ignores interplanetary interactions. Only calculates force of sun on each
 *  planet.
 *
 *  All units are in SI (kg, m, s)
 */

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// Indices for planets in Planet array
#define SUN 0
#define MERCURY 1
#define VENUS 2
#define EARTH 3
#define MARS 4
#define JUPITER 5
#define SATURN 6
#define URANUS 7
#define NEPTUNE 8
#define N 9

// Indices of X, Y, Z axes in position, velocity and force members of Planet
#define X 0
#define Y 1
#define Z 2

struct Planet {
        float *position,
              *velocity,
              *force;
        float mass;
} typedef Planet;

struct SolarSystem {
        Planet **n_bodies;
} typedef SolarSystem;


void InitializePlanets(Planet **p, const int n) {
        for (int i = 0; i < n; ++i) {
                p[i] = (Planet *) malloc(sizeof(Planet));
                p[i]->position = (float *) malloc(sizeof(float) * 3);
                p[i]->velocity = (float *) malloc(sizeof(float) * 3);
                p[i]->force = (float *) malloc(sizeof(float) * 3);
                for (int j = 0; j < 3; ++j) {
                        p[i]->position[j] = 0;
                        p[i]->velocity[j] = 0;
                        p[i]->force[j] = 0;
                }
                p[i]->mass = 0;
        }
}

void FreePlanets(Planet **p, const int n) {
        for (int i = 0; i < n; ++i) {
                free(p[i]->position);
                free(p[i]->velocity);
                free(p[i]->force);
        }
}

void InitializeSolarSystem(SolarSystem *sol, Planet **planets, int n) {
        planets[SUN]->mass = 1.989 * pow(10, 30);

        planets[MERCURY]->mass = 3.285 * pow(10, 23);
        planets[MERCURY]->position[X] = 5.79 * pow(10, 7);
        planets[MERCURY]->velocity[Y] = 4.7 * pow(10, 4);

        planets[VENUS]->mass = 4.867 * pow(10, 24);
        planets[VENUS]->position[X] = 1.08 * pow(10, 8);
        planets[VENUS]->velocity[Y] = 3.5 * pow(10, 4);

        planets[EARTH]->mass = 5.972 * pow(10, 24);
        planets[EARTH]->position[X] = 1.49 * pow(10, 8);
        planets[EARTH]->velocity[Y] =  2.98 * pow(10, 4);

        planets[MARS]->mass = 6.39 * pow(10, 23);
        planets[MARS]->position[X] = 2.28 * pow(10, 8);
        planets[MARS]->velocity[Y] = 2.4 * pow(10, 4);

        planets[JUPITER]->mass = 1.898 * pow(10, 27);
        planets[JUPITER]->position[X] = 7.78 * pow(10, 8);
        planets[JUPITER]->velocity[Y] = 1.31 * pow(10, 4);

        planets[SATURN]->mass = 5.683 * pow(10, 26);
        planets[SATURN]->position[X] = 1.43 * pow(10, 9);
        planets[SATURN]->velocity[Y] = 9.7 * pow(10, 3);

        planets[URANUS]->mass = 8.681 * pow(10, 25);
        planets[URANUS]->position[X] = 2.87 * pow(10, 9);
        planets[URANUS]->velocity[Y] = 6.8 * pow(10, 3);

        planets[NEPTUNE]->mass = 1.024 * pow(10, 26);
        planets[NEPTUNE]->position[X] = 4.50 * pow(10, 9);
        planets[NEPTUNE]->velocity[Y] = 5.4 * pow(10, 3);

        sol->n_bodies = planets;
}

void FreeSolarSystem(SolarSystem *sol) {
        free(sol->n_bodies);
}

double UniversalGravitation(const Planet* p1, const Planet* p2) {
        const float G = 6.67430 * pow(10, -11);
        const double m1 = p1->mass;
        const double m2 = p2->mass;
        const double r_squared = pow(p1->position[X], 2) + pow(p1->position[Y], 2);
        const double F = G * m1 * m2  / r_squared;
        return F;
}

void Step(SolarSystem  *sol, float dt) {
        for (int i = 0; i < N; ++i) {
                Planet *planet = sol->n_bodies[i];
                const double F = UniversalGravitation(planet, sol->n_bodies[SUN]);
                const double theta = atan(planet->position[Y]/planet->position[X]);
                planet->force[X] += F * cos(theta);
                planet->force[Y] += F * sin(theta);
                for (int j = 0; j < Y; ++j) {
                        planet->velocity[j] +=  planet->force[j] / planet->mass * dt;
                        planet->position[j] += planet->velocity[j] * dt;
                        planet->force[j] = 0;
                }
        }
        printf("%f %f\n\n", sol->n_bodies[MARS]->position[X],
                            sol->n_bodies[MARS]->position[Y]);
}

int main() {
        Planet **planets = (Planet **) malloc(sizeof(Planet*) * N);
        InitializePlanets(planets, N);

        SolarSystem *sol = (SolarSystem *) malloc(sizeof(SolarSystem));
        InitializeSolarSystem(sol, planets, N);

        for (int i = 0; i < 10; ++i) {
               Step(sol, 1);
               sleep(1);
        }

        FreePlanets(planets, N);
        FreeSolarSystem(sol);
        return 0;
}
