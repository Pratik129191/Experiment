from equation import utility
from common import functions, table, takeInput


def calculateValueAndFormulaFromTable(spacing: float, xfx_table: list[tuple[float, float]], decimal: int):
    value = 0
    formula = f"({spacing}/3) * [{xfx_table[0][1]} + "
    temp2 = "2("
    temp4 = "4("

    for i in range(1, len(xfx_table)-1):
        if i % 2 == 0:
            value += (2 * xfx_table[i][1])
            temp2 += f"{xfx_table[i][1]} + "
        else:
            value += (4 * xfx_table[i][1])
            temp4 += f"{xfx_table[i][1]} + "

    value += (xfx_table[0][1] + xfx_table[-1][1])
    value *= (spacing / 3)
    temp2 += "\b\b\b)"
    temp4 += "\b\b\b)"
    formula += f"{temp2} + {temp4} + {xfx_table[-1][1]}]"
    return round(value, decimal), formula


eqtn, upper, lower, interval, spacing, decimal = takeInput.asEquation()
terms, operator = utility.splitAndReformatEveryTerm(eqtn)
points = functions.calculatePointsAccordingToSpacing(upper, lower, spacing, interval, decimal)
xfx_table = table.createXFxTable(terms, operator, points, decimal)
simpson_1_3, formula = calculateValueAndFormulaFromTable(spacing, xfx_table, decimal)

print("""
The formula is :===>
h/2 * [Y0 + 2(Y2 + Y4 + Y6 + ... + Y{n-2})
          + 4(Y1 + Y3 + Y5 + ... + Y{n-1}) + Yn]
""")

print("<===:  X-Fx Table  :===>")
for t in xfx_table:
    print(f"\t{t}")

print(f"\nThe Integration Value of the Given Function is: ==>\n"
      f"{formula}\n"
      f"= {simpson_1_3}")

