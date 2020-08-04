'''
Calculate amount of hydrogen that is necessary to sustain psuedo-sun
'''

def main():
    # Hydrogen atom density in the interstellar medium
    p_h = 2.7 * 10 ** 6 # hydrogen atoms / m^3

    # Q value for hydrogen-hydrogen reaction
    Q_h = 6.7 * 10 ** -14 # J / hydrogen-hydrogen reaction

    p_E = 0.5 * p_h * Q_h # J / m^3

    print("Energy density in the interstellar medium:", p_E, "J/m^3")

    V_J = 1 / p_E # Volume required for 1 J

    print("Volume of space required to collect 1 J of energy:", V_J, "J")
    print("Or a cube of space with sides:", V_J ** (1 / 3), "m")

if __name__ == '__main__':
    main()
