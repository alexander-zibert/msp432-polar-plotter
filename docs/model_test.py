import matplotlib.pyplot as plt
import numpy as np

with open('model_out.csv', encoding='utf-8') as f:
    csv = f.read()

lines = csv.split("\n")

xs = []
ys = []

for line in lines:
    if not line.strip():
        continue
    x, y = [float(x) for x in line.split(",")]

    xs.append(x)
    ys.append(y)

# plt.imshow(data.T)
plt.plot(xs, ys, ',')
plt.show()
