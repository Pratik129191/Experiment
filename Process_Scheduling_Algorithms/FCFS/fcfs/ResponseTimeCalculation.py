def calculate_response_time_of_every_process(sorted_data:list):
	for i in range(0,len(sorted_data)):
		sorted_data[i].response_time = sorted_data[i].starting_time - sorted_data[i].arrival_time
	return sorted_data
