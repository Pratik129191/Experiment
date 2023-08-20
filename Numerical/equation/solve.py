from equation import trigonometric as tri


def splitInTerms(part: str):
    part = list(part)
    if part[0] == '(' and part[-1] == ')':
        del part[0], part[-1]
    part = "".join(part)

    sections = []
    operator = []
    temp = ""
    for p in part:
        if p == '+' or p == '-':
            sections.append(temp)
            operator.append(p)
            temp = ""
        else:
            temp += p
    sections.append(temp)
    return sections, operator


def calculate(t: str, x_value: float):
    if t.find('x') != -1 and t.find('/') == -1:  # normal x terms
        coef = float(t[:t.find('x')])
        expo = float(t[t.find('^') + 1:])
        return coef * pow(x_value, expo)
    if t.find('x') == -1 and t.find('/') == -1:  # for normal constants
        return float(t)
    if t.find('x') == -1 and t.find('/') != -1:  # for dividing constants
        parts = t.split('/')
        return float(parts[0]) / float(parts[1])


def applyMainOperators(values: list[float], operators: list[str]):
    final = values[0]
    for i in range(len(operators)):
        if operators[i] == '+':
            final += values[i + 1]
        if operators[i] == '-':
            final -= values[i + 1]
    return final


def termWise(terms: list[str], x_value: float):
    values = []
    for t in terms:
        if t.find('x') != -1 and t.find('/') != -1:
            div = []
            for part in t.split('/'):
                sections, operator = splitInTerms(part)
                val = []
                for s in sections:
                    if tri.isAnyTrigonometricTerm(s):
                        val.append(tri.calculateTrigonometricTerm(s, x_value))
                    else:
                        val.append(calculate(s, x_value))
                div.append(applyMainOperators(val, operator))
            values.append(div[0] / div[1])
        elif tri.isAnyTrigonometricTerm(t):
            values.append(tri.calculateTrigonometricTerm(t, x_value))
        else:
            values.append(calculate(t, x_value))
    return values


def compute(terms: list[str], operators: list[str], x_value: float):
    values = termWise(terms, x_value)
    return applyMainOperators(values, operators)

