import serial
#import mymodule
moduleName="led ON"
commandWords=["light","on"]

#str1=mymodule.str["name"]
def execute(command):
    #print(command)
    str1=command.split(';')

    ser=serial.Serial(str1[1],9600)
    ser.flush()
    ser.write("LED:ON;\n")

	#ser.write("LED:ON\n")
