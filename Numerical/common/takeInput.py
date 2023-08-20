from common import functions


def asValueTable():
    count = int(input("How Many Values are Given:\t"))
    x = []
    fx = []
    for i in range(count):
        x.append(float(input(f"Value of X{i} is:\t")))
        fx.append(float(input(f"Value for F({x[i]}) is:\t")))

    x_obtain = float(input("F(x) should be obtained for which value of X:\t"))

    return x, fx, x_obtain


def asEquation():
    eqtn = input("Enter The Equation:\t").lower()
    lower_s = input("Enter The Lower Range:\t")
    upper_s = input("Enter The Upper Range:\t")
    decimal = int(input("Maximum Number of Decimal Points:\t"))
    upper, lower = functions.getActualValues(upper_s, lower_s)

    choice = int(input("\nIf Interval is Given Press 0\nIf Spacing is Given Press 1\nEnter Your Choice:\t"))
    if choice == 0:
        interval = int(input("Maximum Number of Allowable Intervals is:\t"))
        spacing = round((upper - lower) / interval, decimal)
        return eqtn, upper, lower, interval, spacing, decimal
    else:
        spacing = float(input("Enter The Given Spacing:\t"))
        interval = int(round((upper - lower) / spacing, decimal))
        return eqtn, upper, lower, interval, spacing, decimal


def asEquationForRomberg():
    eqtn = input("Enter The Equation:\t").lower()
    lower_s = input("Enter The Lower Range:\t")
    upper_s = input("Enter The Upper Range:\t")
    decimal = int(input("Maximum Number of Decimal Points:\t"))
    upper, lower = functions.getActualValues(upper_s, lower_s)
    interval = 2
    spacing = round((upper - lower) / interval, decimal)
    return eqtn, upper, lower, interval, spacing, decimal


