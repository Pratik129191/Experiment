class ProcessDetails:
	def __init__(self,name,arr_time,bur_time,start_time:int,wt:int,tat:int,rt:int,rd:float):
		self.process_name=name
		self.arrival_time=arr_time
		self.burst_time=bur_time
		self.starting_time=start_time
		self.waiting_time=wt
		self.turn_around_time=tat
		self.response_time=rt
		self.relative_delay=rd


def takeInput():
	number=int(input("Enter How Many Processes Are There:- "))
	detail=[]
	for i in range(0,number):
		y=ProcessDetails("a","b","c",0,0,0,0,0.0)
		print("Enter Data for Process ",i+1,"........")
		y.process_name=input("Enter The Process Name:- ")
		y.arrival_time=int(input("Enter The Arrival Time:- "))
		y.burst_time=int(input("Enter The Burst Time:- "))
		detail.append(y)
	return detail
