import matplotlib.pyplot as plt

# Read the data from the text file
with open('times.txt', 'r') as file:
    lines = file.readlines()

# Parse the data
data = {}
for line in lines:
    key, value = line.strip().split(': ')
    data[key] = int(value)

# Define custom colors
colors = ['red', 'green', 'lightblue']

# Create a bar plot with custom colors

plt.figure(figsize=(10, 6))
bars = plt.bar(data.keys(), data.values(), color=colors)
plt.xlabel('Type of Policy', fontsize=16)  # Increase font size
plt.ylabel('Time', fontsize=16)  # Increase font size
plt.title('Process Distribution', fontsize=18)  # Increase font size

# Add labels to the bars
for bar in bars:
    yval = bar.get_height()
    plt.text(bar.get_x() + bar.get_width()/2.0, yval, round(yval, 2), va='bottom' if yval < 0 else 'top', ha='center', color='black', fontsize=30)

plt.xticks(fontsize=16)  
# Show the plot
plt.tight_layout()
plt.savefig("histogram1.png")
plt.show()
