from equation import utility
from common import functions, table, takeInput


def calculateValueAndFormulaFromTable(spacing: float, xfx_table: list[tuple[float, float]], decimal: int):
    value = 0
    formula = f"((3 * {spacing}) / 10) * [{xfx_table[0][1]} + "

    two, ti = "2 * (", 6
    six, si = "6 * (", 3
    five1, f1i = "5 * (", 1
    five2, f2i = "5 * (", 5
    two_start, tsi = "(", 2
    four_start, fsi = "(", 4

    for i in range(1, len(xfx_table)-1):
        if i == f1i:
            value += xfx_table[i][1]
            five1 += f"{xfx_table[i][1]} + "
            f1i += 6
        elif i == tsi:
            value += xfx_table[i][1]
            two_start += f"{xfx_table[i][1]} + "
            tsi += 6
        elif i == si:
            value += xfx_table[i][1]
            six += f"{xfx_table[i][1]} + "
            si += 6
        elif i == fsi:
            value += xfx_table[i][1]
            four_start += f"{xfx_table[i][1]} + "
            fsi += 6
        elif i == f2i:
            value += xfx_table[i][1]
            five2 += f"{xfx_table[i][1]} + "
            f2i += 6
        elif i == ti:
            value += xfx_table[i][1]
            two += f"{xfx_table[i][1]} + "
            ti += 6

    value += (xfx_table[0][1] + xfx_table[-1][1])
    value *= ((3 * spacing) / 10)
    two += "\b\b\b)"
    six += "\b\b\b)"
    five1 += "\b\b\b)"
    five2 += "\b\b\b)"
    two_start += "\b\b\b)"
    four_start += "\b\b\b)"

    formula += f"{two} + {six} + {five1} + {five2} + {two_start} + {four_start} + {xfx_table[-1][1]}]"
    return round(value, decimal), formula


eqtn, upper, lower, interval, spacing, decimal = takeInput.asEquation()
terms, operator = utility.splitAndReformatEveryTerm(eqtn)
points = functions.calculatePointsAccordingToSpacing(upper, lower, spacing, interval, decimal)
xfx_table = table.createXFxTable(terms, operator, points, decimal)
weddle, formula = calculateValueAndFormulaFromTable(spacing, xfx_table, decimal)

print("<===:  X-Fx Table  :===>")
for t in xfx_table:
    print(f"\t{t}")

print(f"\nThe Integration Value of the Given Function is: ==>\n"
      f"{formula}\n"
      f"= {weddle}")



