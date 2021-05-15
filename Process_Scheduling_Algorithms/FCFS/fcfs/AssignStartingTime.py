def get_starting_time_of_every_process(sorted_data:list):
	sorted_data[0].staring_time = sorted_data[0].arrival_time
	for i in range(1,len(sorted_data)):
		sorted_data[i].starting_time = sorted_data[i-1].starting_time + sorted_data[i-1].burst_time
	return sorted_data


