import matplotlib.pyplot as plt
import numpy as np

with open('lcd_out.csv', encoding='utf-8') as f:
    csv = f.read()

lines = csv.split("\n")
data = np.zeros((128, 128))

for line in lines:
    if not line.strip():
        continue
    x, y, color = [float(x) for x in line.split(",")]
    if color == 0:
        color = 0.5
    else:
        color = 1
    data[int(x), int(y)] = color

plt.imshow(data.T)
plt.show()
