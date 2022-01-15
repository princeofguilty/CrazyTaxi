import math

import cv2
import numpy as np
import random

canvas = np.zeros((1000, 1000, 3), np.uint8)
target_pos = [[300, 300], [400, 400]]
car_pos = 0


def car_init():
    global car_pos
    x_pos_rand = random.randint(0, 900)
    y_pos_rand = random.randint(0, 900)
    x1_y1 = (x_pos_rand, y_pos_rand)
    x2_y2 = (x_pos_rand + 100, y_pos_rand + 100)
    car_pos = (x1_y1, x2_y2)


def get_car_distance(cp, tg):
    center_car = (int((cp[0][0] + cp[1][0]) / 2), int((cp[0][1] + cp[1][1]) / 2))
    center_target = (int((tg[0][0] + tg[1][0]) / 2), int((tg[0][1] + tg[1][1]) / 2))
    distance = int(math.sqrt((center_target[0] - center_car[0])**2 + (center_target[1] - center_car[1])**2))

    return distance, center_car, center_target


def car_mov(msg):
    global car_pos
    global canvas

    while True:
        x_y_adjust = [0, 0]

        if msg == 0:  # forward
            x_y_adjust = 0, 1
        elif msg == 1:  # backward
            x_y_adjust = 0, -1
        elif msg == 2:  # right forward
            x_y_adjust = 1, 1
        elif msg == 3:  # left forward
            x_y_adjust = -1, 1
        elif msg == 4:  # right backward
            x_y_adjust = 1, -1
        elif msg == 5:  # left backward
            x_y_adjust = -1, -1
        elif msg == 6:  # stop
            x_y_adjust = 0, 0

        updated_x_y_1 = car_pos[0][0] + x_y_adjust[0], car_pos[0][1] + x_y_adjust[1]
        updated_x_y_2 = car_pos[1][0] + x_y_adjust[0], car_pos[1][1] + x_y_adjust[1]

        car_pos = (updated_x_y_1, updated_x_y_2)

        canvas = np.zeros((1000, 1000, 3), np.uint8)
        canvas = cv2.rectangle(canvas, target_pos[0], target_pos[1], (0, 0, 255), -1)
        canvas = cv2.rectangle(canvas, car_pos[0], car_pos[1], (0, 255, 0))

        distance, car_center, target_center = get_car_distance(car_pos, target_pos)

        cv2.circle(canvas, car_center, 10, (0, 255, 255), -1)
        cv2.circle(canvas, target_center, 10, (0, 255, 255), -1)
        cv2.line(canvas, car_center, target_center, (255, 255, 0), thickness=5)
        cv2.putText(canvas, 'dis: ' + str(distance), (30, 30), cv2.FONT_HERSHEY_SIMPLEX, 1, (255, 255, 50), 2, cv2.LINE_AA)
        cv2.imshow('img', canvas)

        if cv2.waitKey(100) == ord('e'):
            break


car_init()
car_mov(0)
cv2.destroyAllWindows()
