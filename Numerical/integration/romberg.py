from equation import utility
from common import functions, table, takeInput


def calculateValueFromTable(spacing: float, xfx_table: list[tuple[float, float]], decimal: int):
    value = 0
    for t in xfx_table[1: -1]:
        value += (2 * t[1])

    value += (xfx_table[0][1] + xfx_table[-1][1])
    value *= (spacing/2)
    return round(value, decimal)


def calculateInitialTableValuesFromTrapezoidalRule(terms, operator, upper, lower, spacing, interval, decimal, initial_set=4):
    values = []
    for i in range(0, initial_set):
        points = functions.calculatePointsAccordingToSpacing(upper, lower, (spacing/pow(2, i)), interval, decimal)
        xfx_table = table.createXFxTable(terms, operator, points, decimal)
        trapezoidal = calculateValueFromTable((spacing/pow(2, i)), xfx_table, decimal)
        values.append(trapezoidal)
    return values


def createRombergTable(initial_values: list, decimal: int):
    table = [initial_values]
    while len(table[-1]) != 1:
        temp = []
        for i in range(1, len(table[-1])):
            temp.append(round((table[-1][i] + ((table[-1][i] - table[-1][i-1])/3)), decimal))
        table.append(temp)
    return table


eqtn, upper, lower, interval, spacing, decimal = takeInput.asEquationForRomberg()
initial_set = int(input("Initially start with How Many set of values (> 4):\t"))
if initial_set < 4:
    initial_set = 4
terms, operator = utility.splitAndReformatEveryTerm(eqtn)
initial_values = calculateInitialTableValuesFromTrapezoidalRule(terms, operator, upper, lower, spacing, interval, decimal, initial_set)
table = createRombergTable(initial_values, decimal)
print(table)

print(f"The Integration Value of the Given Function is:\t{table[-1][0]}")

