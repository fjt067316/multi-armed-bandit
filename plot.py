import matplotlib.pyplot as plt
import csv

x_data = []
y_data = []

with open('data.csv') as csvfile:
    reader = csv.reader(csvfile)
    next(reader)  # skip the header row
    for row in reader:
        x_data.append(float(row[0]))
        y_data.append(float(row[1]))

plt.plot(x_data, y_data)
plt.xscale('log')  # set the x-axis scale to logarithmic
plt.xlabel('x')
plt.ylabel('y')
plt.show()
