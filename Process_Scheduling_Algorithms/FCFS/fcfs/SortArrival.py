def sort_by_arrival_time(process_details:list):
	for i in range(0,len(process_details)-1):
		for j in range(0,len(process_details)-1-i):
			if	process_details[j].arrival_time > process_details[j+1].arrival_time:
				temp=process_details[j]
				process_details[j] = process_details[j+1]
				process_details[j+1] = temp
	return process_details
