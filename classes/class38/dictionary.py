ResetFormatting = "\u001b[0m";
BoldText = "\u001b[1m";

BrightRed = "\u001b[31;1m";
BrightGreen = "\u001b[32;1m";
BrightYellow = "\u001b[33;1m";
BrightBlue = "\u001b[34;1m";
BrightMagenta = "\u001b[35;1m";

ansi = [ BrightRed, BrightGreen, BrightYellow, BrightBlue, BrightMagenta ]

#https://www.energy.gov/science/doe-explainsthe-standard-model-particle-physics

standard = { 
   'quarks': ['up', 'charm', 'top', 'down', 'strange', 'bottom'],
   'leptons': ['tau', 'muon', 'electron', 'tau neutrino', 'muon neutrino', 'electron neturino'],
   'bosons': ['photon', 'gluon', 'W', 'Z', 'Higgs']
}

#print("All the particle categories of the Standard Model:")
#for key in standard:
#    print(key)

c = len(standard)
p = sum(len(standard[key]) for key in standard)

print("The standard model has {} categories of particle".format(c))
print("and {} different particles".format(p))

print("\n\nAll the particles grouped by category:")
for particles in standard.values():
    print(particles)

print("\n\nAll the particles grouped by category and labelled:")
for key, particles in standard.items():
    print("{}: {}".format(key,particles))

print("\n\nAll the particles grouped by category, labelled, and formatted:")
for index, (key, particles) in enumerate(standard.items()):
    print(ansi[index]+"{}:".format(key))
    for particle in particles:
        print(" + {}".format(particle))
    print(ResetFormatting)

print("\n\nSame but with an alternative colour scheme:")
for key, particles in standard.items():
    print((BoldText+"{}:"+ResetFormatting).format(key))
    for index, particle in enumerate(particles):
        print(ansi[index%len(ansi)]+" + {}".format(particle))
    print(ResetFormatting)

