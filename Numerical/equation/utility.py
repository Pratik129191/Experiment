from equation import trigonometric as tri


def reformatCompositeTerms(p: str):
    p = list(p)
    if p[0] == '(' and p[-1] == ')':
        del p[0], p[-1]
    p = "".join(p)

    terms = []
    operators = []
    temp = ""
    for k in p:
        if k == '+' or k == '-':
            terms.append(temp)
            operators.append(k)
            temp = ""
        else:
            temp += k
    terms.append(temp)

    for t in terms:
        loc = terms.index(t)
        if tri.isAnyTrigonometricTerm(t):
            del terms[loc]
            terms.insert(loc, tri.reformatTrigonometricTerms(t))
        else:
            t = list(t)
            if 'x' in t:
                if t[0] == 'x':
                    t.insert(0, '1')
                if '^' not in t:
                    t.append("^1")
            del terms[loc]
            terms.insert(loc, "".join(t))

    final = "(" + terms[0]
    for i in range(len(operators)):
        final += operators[i]
        final += terms[i+1]
    final += ")"
    return final


def reformatTerms(terms: list[str]):
    for t in terms:
        loct = terms.index(t)
        if t.find('/') == -1 and t.find('x') != -1:  # for normal x terms ...
            if tri.isAnyTrigonometricTerm(t):
                del terms[loct]
                terms.insert(loct, tri.reformatTrigonometricTerms(t))
            else:
                t = list(t)
                if t[0] == 'x':
                    t.insert(0, '1')
                if '^' not in t:
                    t.append("^1")
                del terms[loct]
                terms.insert(loct, "".join(t))
        elif t.find('/') != -1 and t.find('x') != -1:  # for dividing x terms ...
            parts = t.split('/')
            for p in parts:
                locp = parts.index(p)
                if p.find('x') != -1:
                    if p[0] == '(' and p[-1] == ')':
                        del parts[locp]
                        parts.insert(locp, reformatCompositeTerms(p))
                    else:
                        if tri.isAnyTrigonometricTerm(p):
                            del parts[locp]
                            parts.insert(locp, tri.reformatTrigonometricTerms(p))
                        else:
                            p = list(p)
                            if p[0] == 'x':
                                p.insert(0, '1')
                            if '^' not in p:
                                p.append("^1")
                            del parts[locp]
                            parts.insert(locp, "".join(p))
            del terms[loct]
            terms.insert(loct, (parts[0] + '/' + parts[1]))
    return terms


def splitAndReformatEveryTerm(eqtn: str):
    terms = []
    operator = []
    x = ""
    for i in range(len(eqtn)):
        if eqtn[i] == '=':
            break
        elif eqtn[i] == '+' or eqtn[i] == '-':
            if eqtn[i - 1] == ' ' and eqtn[i + 1] == ' ':
                terms.append(x)
                operator.append(eqtn[i])
                x = ""
            else:
                x += eqtn[i]
        elif eqtn[i] == ' ':
            continue
        else:
            x += eqtn[i]
    terms.append(x)
    terms = reformatTerms(terms)
    return terms, operator


