import serial
import time

ser = serial.Serial('/dev/ttyACM0',9600, timeout=1)
ser.reset_input_buffer()
time.sleep(0)
serss = serial.Serial('/dev/ttyACM0',9600, timeout=1)
time.sleep(0)
serss.reset_input_buffer()

ser.flush()
serss.flush()
    
    
    
def light():
 try:
    while True:
    
    
   
     if ser.in_waiting > 0:
            line = ser.readline().decode('utf-8').rstrip()
            print(line)
            
            
        
            #dark levels = Red Led
            if float(line) <= 50 and float(line) <=20:
                ser.write(b"red\n")
               
          #normal levels = green led
            elif float(line) > 50 and float(line) <= 200:
                ser.write(b"green\n")
            #bright level = yellow led
            elif float(line) > 201 and float(line) <= 500:
                ser.write(b"yellow\n")
                
            #too bright =  orange Led
            elif float(line) > 500:
                ser.write(b"orange\n")
                
             #too dark = Blue led   
            elif float(line) < 20:
                ser.write(b"blue\n")
               
            else:
                ser.write(b"ponto\n")
                
 except KeyboardInterrupt:
            ser.close()
def motion():
 try:
    while True:
    
    
   
     if serss.in_waiting > 0:
            lines = ser.readline().decode('utf-8').rstrip()
            print(lines)
            
            
        
            #correct length
            if lines <= 74 and lines >= 40: 
                serss.write(b"black\n")
                
            #too close
            elif lines <=39 and lines <= 73:
                
                serss.write(b"white\n")
               
              #too far  
            elif lines >=74:
                
                serss.write(b"silver\n")
                
 except KeyboardInterrupt:
            serss .close()                
           
                
if __name__ == '__main__':
    
    light()
    motion()
            