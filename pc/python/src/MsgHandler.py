import serial
import time

class MsgHandler:
    
    # Initialise the class with the arduino port and baudrate
    def __init__(self, port, baudrate):
        self.port = port
        self.baudrate = baudrate
        self.msgAvailable = False
    
    # Start a connection on the serial port and waits 3 seconds for Arduino to connect
    def connectToSerialPort(self):
        self.arduino = serial.Serial(port=self.port, baudrate=self.baudrate, timeout=1)
        print("Connecting to arduino on port "+self.port+"...")
        time.sleep(3)
        self.msgAvailable = False
    
    # Receive a message from Arduino
    def recvMsg(self):
        self.msg = self.arduino.readall().decode('utf-8').strip()
        if self.msg != "" or self.msg != None:
            self.msgAvailable = True
    
    # Return a message if it is available, None otherwise
    def getMsg(self):
        if self.msgAvailable:
            self.msgAvailable = False
            return self.msg
        return None
    
    # Send a message to Arduino
    def sendMsg(self, msg):
        self.arduino.write(msg+"\n").encode('utf-8')
    
    # Close the connection with Arduino before the class is been deleted
    def __del__(self):
        self.arduino.close()
        
        
        