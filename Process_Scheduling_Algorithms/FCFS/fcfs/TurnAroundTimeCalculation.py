def calculate_turn_around_time_of_every_process(sorted_data:list):
	for i in range(0,len(sorted_data)):
		sorted_data[i].turn_around_time = sorted_data[i].waiting_time + sorted_data[i].burst_time
	return sorted_data