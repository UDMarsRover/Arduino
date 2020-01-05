import smbus
import time
#Functions

class SetupError(Exception):
    pass

class PowerControlError(Exception):
    pass

class i2cCom(object):
    
    #This class sets up the i2c communications systems for a single device. The only shared variable
    #between object instances is the "bus" variable which will not chnage
    #
    #
    #Public Functions
    # . command(): this will send a command to the i2c device and return a value
    # . testConnection(): this will test the connection of the device and return a True if good and a False if bad
    # . on(): This will set up the connection. This must be run before communications start.
    #
    #Private Functions
    # . __writeByte(): this functions will write a single byte to the i2c bus
    # . __readByte(): this function will read a single byte form the i2c bus
    # . __readData(): this will read a string of data between [] up to 30 characters and return the
    # .               string.

    bus = smbus.SMBus(1) #This starts the i2c bus on the RPi

    def __writeByte(self, adress, command):
        # Parameter definitions:
        #  . adress: an integer representation of the i2c device address
        #  . command: and integer representation of a command to the ic2 device
        try:
            self.bus.write_byte(adress, command)
        except OSError:
            self.__errorInfo = 0xfffe
            self.__error = True
        
    def __readByte(self, adress):
        # Parameter definitions:
        #  . adress: an integer representation of the i2c device address
        try:
            data=self.bus.read_byte(adress)
        except OSError:
            self.__errorInfo = 0xfffd
            self.__error = True
            return None
        return data
    
    def command(self, command):
        # Parameter definitions:
        #  . command: an integer representation fo a command to send to the i2c device
        if self.testConnection:
            self.__writeByte(self.adress, command)
            return self.__readData()
        else:
            return "XXXXXXXX"

    
    def __readData(self):
        bytesIn = self.bus.read_i2c_block_data(self.adress,0,32) #adress,offset,bytes
        #print(bytesIn)
        start = False
        stop = False
        dataIn = []
        for i in range(len(bytesIn)):
            byteIn = bytesIn[i]
            if byteIn==255:
                bytesIn[i] = 32
        dataIn = "".join(map(chr,bytesIn))
        return dataIn
    
    def testConnection(self):
        
        self.__writeByte(self.adress, self.__testCommand)
        data = self.__readByte(self.adress)
        
        if not self.__error:
            if data != self.__testCommand:
                self.__errorInfo = 0xfffc
                return False
            else:
                return True
        else:
            return False
    
    def __init__(self, adress, powerPin = 140):
        # This is the setup function
        #
        # Function Parameters
        #  . adress: the address for the i2c device
        #  . powerPin: optional input intended to be used to restart device. No use yet
        self.__error = False
        self.__powerPin = powerPin
        self.__errorInfo=""
        self.__testCommand = 0x40
        self.adress = adress
        self.__setUp = False
        
    def on(self):
        if self.testConnection():
            self.__setUp = True
        else:
            raise SetupError("A critical systems set up error has occured: "+ hex(self.__errorInfo))
