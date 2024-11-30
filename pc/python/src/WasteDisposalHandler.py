from MsgHandler import MsgHandler

port = "/dev/cu.usbserial-14320"
baudRate = 9600

CONTAINER_FULL_TYPE = "CNTF"
DO_EMPTY_CONTAINER_TYPE = "CNTE"
SLEEP_MODE_TYPE = "SLPM"
TEMP_PROBLEM_DETECT_TYPE = "TMPP"
TEMPERATURE_TYPE = "TEMP"
FILLING_PERC_TYPE = "FILL"


isContainerFull = False
doEmptyContainer = False
sleepMode = False
tempProblemDetected = False
lastTemperature = None
lastFillingPerc = 0.0

msgHandler = MsgHandler(port, baudRate)

def communication_routine():
    msgHandler.connectToSerialPort()
    while True:
        msgHandler.recvMsg()
        msg = msgHandler.getMsg()
        if msg != None:
            handle_message(msg)

def empty_container():
    msg = 'CNTE:true'
    msgHandler.sendMsg(msg)
    print("Emptying the container...")
    

def resolve_temperature_problems():
    msg = 'TMPP:false'
    msgHandler.sendMsg(msg)
    print("Resolving temperature problems...")

def handle_message(msg):
    global lastTemperature, lastFillingPerc, isContainerFull, tempProblemDetected
    header = msg[:4]
    content = msg[5:]
    print(msg)
    if header == TEMPERATURE_TYPE:
        lastTemperature = float(content)
        return
    if header == FILLING_PERC_TYPE:
        lastFillingPerc = float(content)
        return
    if header == CONTAINER_FULL_TYPE:
        if content == "true":
            isContainerFull = True
        else:
            isContainerFull = False
        return
    if header == TEMP_PROBLEM_DETECT_TYPE:
        if content == "true":
            tempProblemDetected = True
        else:
            tempProblemDetected = False
        return
    
def receive_temp():
        return lastTemperature
def get_filling_perc():
    return lastFillingPerc
def get_container_full():
    return isContainerFull
def get_temp_problem_detected():
    return tempProblemDetected