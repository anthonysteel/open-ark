'''
Caclulate the mass of the Ark and the ratio of that mass to the total mass of
the asteroid belt.

    The calculation right now uses the formula for the volume of a cylinder but
    the volume of a torus would be more accurate.

    TODO:
        Break down the density into different materials, instead of just dirt,
        such as:
            - Atmosphere
            - Metal
            - People
'''
import math
def main():
    km = 1000 # m
    r_outer = 1000 * km # m
    r_inner =  r_outer - 2 * km # m
    w = 100 * km # m
    V = math.pi * (r_outer ** 2 - r_inner ** 2) * w # volume of a cylinder
    p_soil = 2000 # kg / m^3

    m_ark = V * p_soil # kg
    m_asteroid_belt = 3.6 * 10 ** 21
    print("Mass of Ark: ", m_ark)
    print(" with ", r_outer/km , " km outer radius, ",\
            w/km, " km width and ", r_outer-r_inner/km, " km depth.")
    print("Percentage of m_ark/m_asteroid_belt", m_ark / m_asteroid_belt * 100, "%")

    # Distance to Alpha Centauri ~ 4.2 light years
    d_ac = 4.0 * 10 ** 16 # m (4.2 light years)
    travel_time = 1.6 * 10 ** 11 # s
    c = 3.0 * 10 ** 9 # m/s
    v_ark = d_ac / travel_time # s
    print("Ratio of speed of light to get to AC in 5000 years ", v_ark / c * 100, "%")
    E_k = 0.5 * m_ark * v_ark ** 2
    print("Energy required for voyage: ", 2 * E_k, "J")

if __name__ == '__main__':
    main()
