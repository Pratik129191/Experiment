import pkg

# operators list.........
operators=["^","*","/","+","-"]

# given expression........
expression=pkg.takeExpressionInput()

# initialising some variables.........
temp=0
output=[]

# doing calculation........
for fig in expression:
	if fig not in operators:
		output.append(fig)
	if fig in operators:
		if fig==operators[0]:
			temp=float(output[-2]) ** float(output[-1])
			del output[len(output)-2:len(output)]
			output.append(temp)
		if fig==operators[1]:
			temp=float(output[-2]) * float(output[-1])
			del output[len(output) - 2:len(output)]
			output.append(temp)
		if fig==operators[2]:
			temp=float(output[-2]) / float(output[-1])
			del output[len(output) - 2:len(output)]
			output.append(temp)
		if fig==operators[3]:
			temp=float(output[-2]) + float(output[-1])
			del output[len(output) - 2:len(output)]
			output.append(temp)
		if fig==operators[4]:
			temp=float(output[-2]) - float(output[-1])
			del output[len(output) - 2:len(output)]
			output.append(temp)


# printing output........
if len(output)==1:
	print(f"\nThe Value of Given Infix Expression is:- {output[0]}")
if len(output)!=1:
	print("\nInfix Expression is Incorrect.\n")
    
input("Press Enter To Exit.......")

