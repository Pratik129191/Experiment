from equation import solve


def dividedDifference(fx: list):
    delfx = [fx]
    while len(delfx[-1]) != 1:
        temp = []
        for i in range(1, len(delfx[-1])):
            temp.append(delfx[-1][i] - delfx[-1][i-1])
        delfx.append(temp)
    return delfx


def createXFxTable(terms: list[str], operators: list[str], points: list[float], decimal: int):
    table = []
    for p in points:
        temp = (p, round(solve.compute(terms, operators, p), decimal))
        table.append(temp)
    return table


class CentralDifference:
    pass





