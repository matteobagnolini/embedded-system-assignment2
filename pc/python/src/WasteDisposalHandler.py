from MsgHandler import MsgHandler

port = "/dev/cu.usbserial-14320"
baudRate = 9600

CONTAINER_FULL_TYPE = "CNTF"
DO_EMPTY_CONTAINER_TYPE = "CNTE"
SLEEP_MODE_TYPE = "SLPM"
TEMP_PROBLEM_DETECT_TYPE = "TMPP"
TEMPERATURE_TYPE = "TEMP"

isContainerFull = False
doEmptyContainer = False
sleepMode = False
tempProblemDetected = False
temperature = 0.0

msgHandler = MsgHandler(port, baudRate)

def communication_routine():
    msgHandler.connectToSerialPort()
    while True:
        msgHandler.recvMsg()
        msg = msgHandler.getMsg()
        if msg != None:
            handle_message(msg)

def empty_container():
    msg = ""
    MsgHandler.sendMsg(msg)
    print("Emptying the container...")
    

def resolve_temperature_problems():
    print("Resolving temperature problems...")

def handle_message(msg):
    print(msg)