def load_config(filname):
    with open(filname, 'r') as file:
        lines = file.readlines()
        
        for line in lines:
            data = line.split(' ')
            if data[0].lower() == 'window':
                print(data[1], data[2])
            elif data[0].lower() == 'Font':
                print(data[1], data[2], data[3], data[4], data[5])
            elif data[0].lower() == 'circle':
                print(data[0], data[1], data[2], data[3], data[4], data[5], data[6], data[7], data[8], data[9]) 
            elif data[0].lower() == 'rectangle':
                print(data[0], data[1], data[2], data[3], data[4], data[5], data[6], data[7], data[8], data[9], data[10]) 

load_config('config.txt')