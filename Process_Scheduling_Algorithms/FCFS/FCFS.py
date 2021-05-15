import fcfs.TakeInput as ti
import fcfs.SortArrival as sa
import fcfs.AssignStaringTime as ast
import fcfs.WaitingTimeCalculation as wtc
import fcfs.TurnAroundTimeCalculation as tatc
import fcfs.ResponseTimeCalculation as rtc
import fcfs.RelativeDelayCalculation as rdc


# taking the given question as input......
data=ti.takeInput()

# sorting all processes as per the arrival time.......
data=sa.sort_by_arrival_time(data)

# getting the staring time of every processes.........
data=ast.get_starting_time_of_every_process(data)

# individual waiting time.........
data=wtc.calculate_waiting_time_of_every_process(data)

# individual turn around time........
data=tatc.calculate_turn_around_time_of_every_process(data)

# individual response time.......
data=rtc.calculate_response_time_of_every_process(data)

# individual relative delay.........
data=rdc.calculate_relative_delay_of_every_process(data)

print("\n<==:Required Result is Below:==>\n")

# average waiting time....
avg_wt=0
for i in range(0,len(data)):
	avg_wt=avg_wt+data[i].waiting_time
avg_wt=avg_wt/len(data)
print(f"Average Waiting Time is:- {avg_wt} unit.")

# average turn around time.....
avg_tat=0
for i in range(0,len(data)):
	avg_tat=avg_tat+data[i].turn_around_time
avg_tat=avg_tat/len(data)
print(f"Average Turn Around Time is:- {avg_tat} unit.")

# average response time....
avg_rt=0
for i in range(0,len(data)):
	avg_rt=avg_rt+data[i].response_time
avg_rt=avg_rt/len(data)
print(f"Average Response Time is:- {avg_rt} unit.")

# average relative delay....
avg_rd=0
for i in range(0,len(data)):
	avg_rd=avg_rd+data[i].relative_delay
avg_rd=avg_rd/len(data)
print(f"Average Relative Delay is:- {avg_rd} unit.")
