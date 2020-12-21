#You can import any required modules here
import serial
#This can be anything you want
#import sys
#import os
#sys.path.append(os.path.abspath('../path'))


#(sys.path)
moduleName = "templateModule"

#All of the words must be heard in order for this module to be executed
commandWords = ["yes"]
#str = mymodule.str["name"]

def execute(command):
    #Write anything you want to be executed when the commandWords are heard
    #The 'command' parameter is the command you speak
    str1=command.split(';')
    
    ser=serial.Serial(str1[1],9600)
    ser.flush()
    ser.write("LED:ON;\n")
    
    
