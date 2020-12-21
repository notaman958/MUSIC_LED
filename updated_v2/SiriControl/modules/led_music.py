import serial
#import mymodule
moduleName="play MUSIC"
commandWords=["play","music"]

def execute(command):
    #print(command)
    str1=command.split(';')

    ser=serial.Serial(str1[1],9600)
    ser.flush()
    ser.write("led:MUSIC;\n")


