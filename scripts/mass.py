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
    print("Mass of Ark: ", m_ark, " with ", r_outer/km , " km outer radius ",\
            w/km, " km width and ", r_outer-r_inner/km, " km depth.")
    print("Percentage of m_ark/m_asteroid_belt", m_ark * 100, "%")

if __name__ == '__main__':
    main()
