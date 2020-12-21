import serial
#import mymodule
moduleName="play SNAKE"
commandWords=["play","snake"]

#str1=mymodule.str["name"]
def execute(command):
    #print(command)
    str1=command.split(';')

    ser=serial.Serial(str1[1],9600)
    ser.flush()
    ser.write("play:SNAKE;\n")


