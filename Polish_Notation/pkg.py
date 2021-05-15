def takeExpressionInput():
	print("\n=:Conversion of INFIX-NOTATION into POSTFIX-NOTATION:=\n")
	str=input("Enter The Given Expression:- ")
	exp=[]
	for i in str:
		exp.append(i)
	exp.insert(0,"(")
	exp.append(")")
	return exp


def isLastTwoElementsAreOperator(stack_list,operators_list):
	if stack_list[-1] in operators_list and stack_list[-2] in operators_list:
		return 1
	else:
		return 0


def isHigherOrderIsInLastPosition(stack_list,high_priority,moderate_priority,lowest_priority):
	if stack_list[-1] in high_priority+moderate_priority and stack_list[-2] in lowest_priority:
		return 1
	if stack_list[-1] in high_priority and stack_list[-2] in moderate_priority+lowest_priority:
		return 1
	else:
		return 0


def lastAppearanceIndexOfOpeningBracketInStack(stack_list):
	item="("
	for i in range(len(stack_list)-1,-1,-1):
		if stack_list[i]==item:
			return i
