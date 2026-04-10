import random
import csv

first_names = ['Alice','Bob','Carol','David','Eve','Frank','Grace','Heidi','Ivan','Judy',
               'Karl','Laura','Mallory','Niaj','Olivia','Peggy','Quentin','Rupert','Sybil','Trent',
               'Uma','Victor','Wendy','Xander','Yvonne','Zach','Aaron','Beth','Carlos','Diana',
               'Ethan','Fiona','George','Hannah','Ian','Jasmine','Kevin','Linda','Mike','Nancy', 'Sky',
               'Linus','Ada','Alan','Grace','Tim','Bill','Steve','Mark','Elon','Jeff']

last_names  = ['Smith','Johnson','Williams','Brown','Jones','Garcia','Miller','Davis','Wilson','Moore',
               'Taylor','Anderson','Thomas','Jackson','White','Harris','Martin','Thompson','Lee','Walker',
               'Hall','Allen','Young','Hernandez','King','Wright','Lopez','Hill','Scott','Green',
               'Adams','Baker','Gonzalez','Nelson','Carter','Mitchell','Perez','Roberts','Turner','Phillips', 
               'Miles', 'Lewis', 'Jobs', 'Ross', 'Gates', 'Musk', 'Zuckerberg', 'Turing', 'Lovelace',
               'Poe']

levels = ['Low','Medium','High','Urgent']

rows = []
for i in range(1, 1001):
    id = i + 10000
    name = random.choice(first_names) + ' ' + random.choice(last_names)
    level = random.choice(levels)
    month = random.randint(1, 12)
    day   = random.randint(1, 28)
    year  = random.randint(2023, 2026)
    res_time = random.randint(1, 365)   # days to resolve
    rows.append([id, name, level, month, day, year, res_time])

with open('tickets.csv', 'w', newline='') as f:
    w = csv.writer(f)
    w.writerow(['id','customerName','level','month','day','year','resTime'])
    w.writerows(rows)

print('done')
