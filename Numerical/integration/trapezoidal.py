from equation import utility
from common import functions, table, takeInput


def calculateValueAndFormulaFromTable(spacing: float, xfx_table: list[tuple[float, float]], decimal: int):
    value = 0
    formula = f"({spacing}/2) * [{xfx_table[0][1]} + "
    temp2 = "2("
    for t in xfx_table[1: -1]:
        value += (2 * t[1])
        temp2 += f"{t[1]} + "

    value += (xfx_table[0][1] + xfx_table[-1][1])
    value *= (spacing/2)
    temp2 += "\b\b\b)"
    formula += f"{temp2} + {xfx_table[-1][1]}]"
    return round(value, decimal), formula


eqtn, upper, lower, interval, spacing, decimal = takeInput.asEquation()
terms, operator = utility.splitAndReformatEveryTerm(eqtn)
points = functions.calculatePointsAccordingToSpacing(upper, lower, spacing, interval, decimal)
xfx_table = table.createXFxTable(terms, operator, points, decimal)
trapezoidal, formula = calculateValueAndFormulaFromTable(spacing, xfx_table, decimal)

print("""
The formula is :===>
h/2 * [Y0 + 2(Y1 + Y2 + Y3 + ... + Y{n-1}) + Yn]
""")

print("<===:  X-Fx Table  :===>")
for t in xfx_table:
    print(f"\t{t}")

print(f"\nThe Integration Value of the Given Function is: ==>\n"
      f"{formula}\n"
      f"= {trapezoidal}")


