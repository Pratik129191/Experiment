from equation import utility, solve


x = "(sinx+2x^2)/(12sin^2(x)+2+3x)"
# x = "1/(1+x^2)"
# x = "x^2 + 2x + 32 = 0"
terms, operator = utility.splitAndReformatEveryTerm(x)
print(solve.compute(terms, operator, 1))


