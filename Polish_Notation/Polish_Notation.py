import pkg

# operator precedence list.......
high=["^"]
middle=["*","/"]
low=["+","-"]

# declaring opening & closing brackets........
opening=["(","{","["]
closing=[")","}","]"]

# given expression......
expression=pkg.takeExpressionInput()

# creating stack & output expression list.......
stk=[]
postfix=[]

# initialising some temporary checking variables........
operator=0
position=0
index=0

# doing calculation...........
for fig in expression:
	if fig in high+middle+low+opening:
		stk.append(fig)
		if len(stk)>1:
			operator=pkg.isLastTwoElementsAreOperator(stack_list=stk,operators_list=high+middle+low)
			if operator==1:
				position=pkg.isHigherOrderIsInLastPosition(stack_list=stk,high_priority=high,moderate_priority=middle,lowest_priority=low)
				if position==1:
					pass
				if position==0:
					postfix.append(stk[-2])
					del stk[-2]
	if fig in closing:
		stk.append(fig)
		index=pkg.lastAppearanceIndexOfOpeningBracketInStack(stk)
		temp=[]
		for i in stk[index+1:len(stk)-1]:
			temp.append(i)
		temp.reverse()
		for i in temp:
			postfix.append(i)
		del stk[index:len(stk)]
	if fig not in high+middle+low+opening+closing:
		postfix.append(fig)

print("\nConverted POSTFIX-NOTATION is.....\n")
for i in postfix:
	print(i,end="")
print("\n")

input("Press Enter To Exit........")
