from common import functions, table, takeInput


x, fx, x_obtain = takeInput.asValueTable()
h = x[1] - x[0]
s = (x_obtain - x[0]) / h
delfx = table.dividedDifference(fx)

result = delfx[0][0]
for i in range(1, len(delfx)):
    temp = 1
    for j in range(0, i):
        temp *= (s - j)
    temp *= delfx[i][0] / functions.factorial(i)
    result += temp

print(f"The Answer is:\tF({x_obtain}) = {result}")



