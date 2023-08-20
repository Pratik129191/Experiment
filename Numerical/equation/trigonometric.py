def isAnyTrigonometricTerm(t: str):
    constants = ["sin", "cosec", "tan", "cot", "cos", "sec"]
    for c in constants:
        if t.find(c) != -1:
            return True
    return False


def formatXPart(t):
    t = list(t)
    del t[0], t[-1]

    if t[0] == 'x':
        t.insert(0, '1')
    if '^' not in t:
        t.append("^1")
    return '(' + "".join(t) + ')'


def getConstantDetails(t: str):
    constants = ["sin", "cosec", "tan", "cot", "cos", "sec"]
    locs = 0
    const = ""
    for c in constants:
        locs = t.find(c)
        if locs != -1:
            const = c
            break

    loce = len(const) + locs
    return locs, loce, const


def reformatTrigonometricTerms(t: str):
    locs, loce, const = getConstantDetails(t)
    t = list(t)
    if locs == 0:
        t.insert(0, '1')
        locs += 1
        loce = len(const) + locs
    if t[loce] != '(' and t[loce] != '^':
        t.insert(loce, '(')
        t.append(')')
    if t[loce] != '^':
        t.insert(loce, "^1")

    t[t.index('('):] = formatXPart("".join(t[t.index('('):]))
    return "".join(t)


def calculateTrigonometricTerm(t: str, x_value: float):
    locs, loce, const = getConstantDetails(t)
    t_coef = float(t[:locs])
    t_expo = float(t[loce+1: t.find('(')])
    x_coef = float(t[t.find('(')+1: t.find('x')])
    x_expo = float(t[t.find('x')+2: t.find(')')])

    import math
    if const == 'sin':
        return t_coef * pow(math.sin(math.radians(x_coef * pow(x_value, x_expo))), t_expo)
    elif const == 'cos':
        return t_coef * pow(math.cos(math.radians(x_coef * pow(x_value, x_expo))), t_expo)
    elif const == 'tan':
        return t_coef * pow(math.tan(math.radians(x_coef * pow(x_value, x_expo))), t_expo)
    elif const == 'cosec':
        return t_coef * pow((1 / math.sin(math.radians(x_coef * pow(x_value, x_expo)))), t_expo)
    elif const == 'sec':
        return t_coef * pow((1 / math.cos(math.radians(x_coef * pow(x_value, x_expo)))), t_expo)
    else:
        return t_coef * pow((1 / math.tan(math.radians(x_coef * pow(x_value, x_expo)))), t_expo)

