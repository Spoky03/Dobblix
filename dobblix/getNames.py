#making txt file of all names in pictures folder
import os
import math
import matplotlib.pyplot as plt

f = open("names.txt", "w")
i=0
for line in os.listdir("pictures"):
    f.write(line)
    f.write("\n")
    i+=1
f.close()
#circle visualisation
tuples = []
n=8
def circles(g):
    g_d_list = []  # graph data list
    lg = [g] * (n*g)
    ang = 360/len(lg)  # calculate the angle of each entry in circle list.
    ang_list = []
    for i in range(len(lg)+1):
        ang_list.append(ang*i)
    for i, c in enumerate(lg):
            # calculate the x and y axis points or each circle. in this instance
            # i'm expanding circles by multiples of ten but could be any number.
        x_axis = 0 + (800*g) * math.cos(math.radians(ang_list[i+1]))
        y_axis = 0 + (800*g) * math.sin(math.radians(ang_list[i+1]))
            # tuple structure ((axis tuple), circle size, circle colour)
        tuples.append((x_axis, y_axis))
        g_d_list.append(((x_axis, y_axis), 66, 'r'))

    fig, ax = plt.subplots()
    for c in range(len(g_d_list)):
        circle = plt.Circle(g_d_list[c][0], radius=g_d_list[c][1], fc=g_d_list[c][2])
        ax.add_patch(circle)
    plt.axis('scaled')
    plt.axis('off')  # optional if you don't want to show axis
    plt.show()
#writing tuples to file 
f = open("tuples.txt", "w")
for i in tuples:
    f.write(str(i))
    f.write("\n")
f.close()

circles(1)
