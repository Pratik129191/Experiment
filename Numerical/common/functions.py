def factorial(x):
    if x == 0 or x == 1:
        return 1
    else:
        fact = 1
        for i in range(2, x+1):
            fact *= i
        return fact


def reformatPIs(k: str):
    loc = k.find('pi')
    k = list(k)
    if loc == 0:
        k.insert(0, '1')
    if "".join(k[-2:]) == 'pi':
        k.append("/1")

    k = "".join(k)
    return k


def convertToValues(k: str):
    part = k.split('/')
    return (float(part[0][:k.find('pi')]) * 180) / float(part[1])


def convertDividingValues(k: str):
    part = k.split('/')
    return float(part[0]) / float(part[1])


def getActualValues(upper: str, lower: str):
    val = []
    for i in [upper, lower]:
        if i.find('/') != -1 and i.find('pi') == -1:
            val.append(convertDividingValues(i))
        elif i.find('/') == -1 and i.find('pi') == -1:
            val.append(float(i))
        else:
            val.append(convertToValues(reformatPIs(i)))

    return val[0], val[1]


def calculatePointsAccordingToSpacing(upper: float, lower: float, spacing: float, interval: int, decimal: int):
    points = []

    for i in range(0, interval):
        points.append(round(lower, decimal))
        lower += spacing
    points.append(round(upper, decimal))
    # while lower <= upper:
    #     points.append(round(lower, 6))
    #     lower += spacing
    # points.append(round(lower, 6))
    return points







