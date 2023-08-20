from equation import utility
from common import functions, table, takeInput


def calculateValueAndFormulaFromTable(spacing: float, xfx_table: list[tuple[float, float]], decimal: int):
    value = 0
    formula = f"((3 * {spacing})/8) * [{xfx_table[0][1]} + "
    temp2 = "2("
    temp3 = "3("

    for i in range(1, len(xfx_table) - 1):
        if i % 3 == 0:
            value += (2 * xfx_table[i][1])
            temp2 += f"{xfx_table[i][1]} + "
        else:
            value += (3 * xfx_table[i][1])
            temp3 += f"{xfx_table[i][1]} + "

    value += (xfx_table[0][1] + xfx_table[-1][1])
    value *= ((3 * spacing)/8)
    temp2 += "\b\b\b)"
    temp3 += "\b\b\b)"
    formula += f"{temp2} + {temp3} + {xfx_table[-1][1]}]"
    return round(value, decimal), formula


eqtn, upper, lower, interval, spacing, decimal = takeInput.asEquation()
terms, operator = utility.splitAndReformatEveryTerm(eqtn)
points = functions.calculatePointsAccordingToSpacing(upper, lower, spacing, interval, decimal)
xfx_table = table.createXFxTable(terms, operator, points, decimal)
simpson_3_8, formula = calculateValueAndFormulaFromTable(spacing, xfx_table, decimal)

print("""
The formula is :===>
h/2 * [Y0 + 2(Y3 + Y6 + Y9 + ... + Y{n-3})
          + 3(Y1 + Y2 + Y4 + Y5 + ... + Y{n-1}) + Yn]
""")

print("<===:  X-Fx Table  :===>")
for t in xfx_table:
    print(f"\t{t}")

print(f"\nThe Integration Value of the Given Function is: ==>\n"
      f"{formula}\n"
      f"= {simpson_3_8}")

