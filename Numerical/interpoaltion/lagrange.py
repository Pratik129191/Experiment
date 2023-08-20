import common.takeInput as tI


def LagrangeValue(x_obtain: float, x: list, subscript: int):
    upper = 1
    lower = 1
    for i in range(len(x)):
        if i == subscript:
            continue
        else:
            upper *= (x_obtain - x[i])
            lower *= (x[subscript] - x[i])
    return upper / lower


x, fx, x_obtain = tI.asValueTable()
y = 0
for i in range(len(x)):
    y += (LagrangeValue(x_obtain, x, subscript=i) * fx[i])

print(f"The Value is: {y}")


