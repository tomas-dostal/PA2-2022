import random

commands = []
for i in range(42):
    x = random.randint(10, 590)
    y = random.randint(10, 390)
    diameter = random.randint(10, 50)

    if i % 10 == 0:

        color = random.choice([
            "BLUE__FUN_FOR_A_WEEKEND",
            "MAGENTA__BRAIN_OVERFLOW",
            "RED__COMPILED_WITH_ERRORS",
            "WHITE__LOADING",
            "YELLOW__FIT"
        ])
        commands.append(f"set color byname {color}")
    commands.append(f"draw star {x} {y} {diameter}")

commands.append(f"save svg stars.svg y")
#commands.append(f"save bmp stars.bmp y")

with open("skyofstars.tspaint", "w") as file:
    file.write("\n".join(commands))

