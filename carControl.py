import time
import serial

serialComm = 0
is_inited = False


# start by using this function
def init_comm(port="COM3"):
    global serialComm
    global is_inited
    try:
        serialComm = serial.Serial("COM3", 9600, timeout=1)
        time.sleep(2)
        is_inited = True
    except:
        print("couldn't init")
        is_inited = False


# this would be used to communicate with the car   
def car_go(msg, show_response=False):
    global serialComm
    global is_inited

    if not is_inited:
        print("init communication!")
        return

    if isinstance(msg, int):
        msg = str(msg)

    serialComm.write(msg.encode())
    time.sleep(0.1)
    if show_response:
        print(serialComm.readline().decode('ascii'))


# execute this at end of the program
def end_comm():
    global serialComm
    global is_inited
    if not is_inited:
        print("init communication!")
        return
    serialComm.close()
    is_inited = False

#########################################
# read those test cases to              #
# under stand the module a bit more     #
# Thanks                                #
#########################################

def test0__():
    init_comm()
    car_go(6)
    end_comm()

test0__()

# def test1__():
#     init_comm()
#     while True:
#         mm = input("enter msg: ")
#         car_go(mm) # ex : mm = "b"
#         if mm == "end":
#             break
#     end_comm()

# test1__()
