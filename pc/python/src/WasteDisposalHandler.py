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
lastTemperature = 0.0

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
    global lastTemperature
    header = msg[:4]
    content = msg[5:]
    if header == "TEMP":
        lastTemperature = float(content)
        print(float(content))
    
def receive_temp():
        return lastTemperature