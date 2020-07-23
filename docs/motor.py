import matplotlib.pyplot as plt
import numpy as np

with open('motor_out.csv', encoding='utf-8') as f:
    csv = f.read()

lines = csv.split("\n")

xs_1 = []
ys_1 = []

xs_2 = []
ys_2 = []

for i, line in enumerate(lines):
    if not line.strip():
        continue
    y_1, y_2 = [int(x) for x in line.split(",")]

    xs_1.append(i)
    xs_2.append(i)
    ys_1.append(y_1)
    ys_2.append(y_2)
    if y_1 == 1:
        xs_1.append(i+1)
        ys_1.append(1)
    if y_2 == 1:
        xs_2.append(i+1)
        ys_2.append(1)

# plt.imshow(data.T)

plt.subplot(211)
plt.xlim(0, 50)
plt.plot(xs_1, ys_1)

plt.subplot(212)
plt.xlim(0, 50)
plt.plot(xs_2, ys_2)
plt.show()
