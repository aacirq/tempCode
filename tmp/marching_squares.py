import matplotlib.pyplot as plt
import math
import random
import time

from numpy import concatenate


NUM = 5
# centers = [[1.001, 1.001], [2.001, 2.001], [3.001, 3.001], [4.001, 4.001], [5.001, 5.001], [6.001, 6.001], [3.001, 5.001], [5.001, 3.001]]
# velocity = [[0, 0]] * NUM
centers = []
velocity = []
MAX_VELOCITY = 0.1

bias = 0.5

MAX_SIZE = 10
bound = [0, MAX_SIZE]
num_iter = 100
thres = 3

dt = 0.1

step = 0.5


def fun(point):
    x1, y1 = point[0], point[1]
    res = 0.0
    for i in range(NUM):
        x2, y2 = centers[i][0], centers[i][1]
        res += 1 / math.sqrt((x1 - x2)**2 + (y1 - y2)**2)
    return res


def init():
    for i in range(NUM):
        x = MAX_SIZE * random.random()
        y = MAX_SIZE * random.random()
        vx = 4*(random.random() - 0.5)
        vy = 4*(random.random() - 0.5)
        centers.append([x, y])
        velocity.append([vx, vy])


def updatePos():
    for i in range(NUM):
        centers[i][0] += velocity[i][0] * dt
        centers[i][1] += velocity[i][1] * dt


def linearInterpolation(p1, p2, v1, v2, thres):
    x1, y1 = p1[0], p1[1]
    x2, y2 = p2[0], p2[1]
    p = (thres - v1) / (v2 - v1)
    x = x1 + (x2 - x1) * p
    y = y1 + (y2 - y1) * p
    return x, y


def marching(v1, v2, v3, v4, p1, p2, p3, p4):
    n = (int(v1 >= thres) << 3) + (int(v2 >= thres) << 2) + \
        (int(v3 >= thres) << 1) + int(v4 >= thres)
    # if (n != 0):
    #     print(n)
    #     print(v1, v2, v3, v4)
    #     input("next:")
    if n == 0:
        return
    elif n == 1 or n == 14:
        x1, y1 = linearInterpolation(p1, p4, v1, v4, thres)
        x2, y2 = linearInterpolation(p3, p4, v3, v4, thres)
        plt.plot([x1, x2], [y1, y2], 'b-')
    elif n == 2 or n == 13:
        x1, y1 = linearInterpolation(p2, p3, v2, v3, thres)
        x2, y2 = linearInterpolation(p4, p3, v4, v3, thres)
        plt.plot([x1, x2], [y1, y2], 'b-')
    elif n == 3 or n == 12:
        x1, y1 = linearInterpolation(p2, p3, v2, v3, thres)
        x2, y2 = linearInterpolation(p4, p1, v4, v1, thres)
        plt.plot([x1, x2], [y1, y2], 'b-')
    elif n == 4 or n == 11:
        x1, y1 = linearInterpolation(p1, p2, v1, v2, thres)
        x2, y2 = linearInterpolation(p3, p2, v3, v2, thres)
        plt.plot([x1, x2], [y1, y2], 'b-')
    elif n == 5:
        x1, y1 = linearInterpolation(p1, p2, v1, v2, thres)
        x2, y2 = linearInterpolation(p3, p2, v3, v2, thres)
        plt.plot([x1, x2], [y1, y2], 'b-')
        x1, y1 = linearInterpolation(p1, p4, v1, v4, thres)
        x2, y2 = linearInterpolation(p3, p4, v3, v4, thres)
        plt.plot([x1, x2], [y1, y2], 'b-')
    elif n == 6 or n == 9:
        x1, y1 = linearInterpolation(p1, p2, v1, v2, thres)
        x2, y2 = linearInterpolation(p3, p4, v3, v4, thres)
        plt.plot([x1, x2], [y1, y2], 'b-')
    elif n == 7 or n == 8:
        x1, y1 = linearInterpolation(p1, p2, v1, v2, thres)
        x2, y2 = linearInterpolation(p1, p4, v1, v4, thres)
        plt.plot([x1, x2], [y1, y2], 'b-')
    elif n == 10:
        x1, y1 = linearInterpolation(p1, p2, v1, v2, thres)
        x2, y2 = linearInterpolation(p1, p4, v1, v4, thres)
        plt.plot([x1, x2], [y1, y2], 'b-')
        x1, y1 = linearInterpolation(p3, p2, v3, v2, thres)
        x2, y2 = linearInterpolation(p3, p4, v3, v4, thres)
        plt.plot([x1, x2], [y1, y2], 'b-')


if __name__ == "__main__":

    init()
    print("velocity:", velocity)

    fig = plt.figure()
    # plt.figure()
    ax = fig.add_subplot(111)
    ax.set_aspect('equal', adjustable='box')
    x_max = bound[1] + bias

    plt.ion()
    for _ in range(num_iter):
        print("centers", centers)
        plt.clf()
        x = bound[0]
        while x <= x_max:
            y = bound[0]
            while y <= bound[1]:
                # if fun((x, y)) >= thres:
                #     plt.scatter(x, y, marker='.', c='b')
                v1 = fun((x, y))
                v2 = fun((x, y+step))
                v3 = fun((x+step, y))
                v4 = fun((x+step, y+step))

                marching(v1, v2, v3, v4, (x, y), (x, y+step),
                         (x+step, y), (x+step, y+step))

                y += step
            x += step

        updatePos()
        plt.xlim(bound)
        plt.ylim(bound)
        plt.pause(0.1)
        # plt.ioff()
        # input("next:")

    plt.ioff()
    plt.show()
