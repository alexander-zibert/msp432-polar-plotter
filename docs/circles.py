import matplotlib.pyplot as plt
import numpy as np


def semi_circle1(a, b, r):
    t = np.linspace(-np.pi / 2, 0)
    x = a + r * np.cos(t)
    y = b + r * np.sin(t)
    return [x, y]


def semi_circle2(a, b, r):
    t = np.linspace(-np.pi, -np.pi / 2)
    x = a + r * np.cos(t)
    y = b + r * np.sin(t)
    return [x, y]


def paper_filter(points):
    xs = []
    ys = []
    for x, y in points:
        if x >= 0 and x <= 500 and y >= 0 and y <= 470:
            xs.append(x)
            ys.append(y)
    return [xs, ys]


for r in range(10, 800, 25):
    x, y = semi_circle1(0, 470, r)
    x, y = paper_filter(zip(x, y))
    plt.plot(x, y, "b", alpha=0.5)

for r in range(10, 800, 25):
    x, y = semi_circle2(500, 470, r)
    x, y = paper_filter(zip(x, y))
    plt.plot(x, y, "b", alpha=0.5)

plt.scatter([0, 500], [470, 470])
plt.gca().set_aspect('equal', adjustable='box')

plt.tight_layout()
plt.rcParams.update({'font.size': 28})
plt.savefig("circles.png", dpi=600)
