import paho.mqtt.client as mqtt
from tkinter import *
import random
import time

username= "Ravson"
password = "pass"




mqttc = mqtt.Client("Python Client")

mqttc.username_pw_set(username, password)
mqttc.connect(host="192.168.178.11", port=1883)


class Servo():
    def __init__(self, mqtt_client, client_name):
        self.mqtt= mqtt_client
        self.client_name = client_name

    def on(self):
        self.mqtt.publish(f"{self.client_name}/Movement", "ON")

    def off(self):
        self.mqtt.publish(f"{self.client_name}/Movement", "OFF")
    
    def pos(self, position : int):
        if position <= 180 and position >= 0: 
            self.mqtt.publish(f"{self.client_name}/Pos", position)


    def pos_Servo(self, position : int, Servo : str):
        if position <= 180 and position >= 0: 
            self.mqtt.publish(f"{self.client_name}/{Servo}/Pos", position)

    def move_right_eye(self):
            
        for i in range(0, 20):
            self.mqtt.publish(f"{self.client_name}/Servo1/Pos", random.randint(30,130))
            self.mqtt.publish(f"{self.client_name}/Servo2/Pos", random.randint(80,140))

            self.mqtt.publish(f"{self.client_name}/Servo3/Pos", random.randint(70,170))
            self.mqtt.publish(f"{self.client_name}/Servo4/Pos", random.randint(25,75))
            self.mqtt.publish(f"{self.client_name}/Servo5/Pos", random.randint(45,135))
            self.mqtt.publish(f"{self.client_name}/Servo6/Pos", random.randint(45,135))
            self.mqtt.publish(f"{self.client_name}/Servo7/Pos", random.randint(10,180))
            time.sleep(2)

        # for i in range(0, 10):
        #     self.mqtt.publish(f"{self.client_name}/Servo3/Pos", 0)
        #     self.mqtt.publish(f"{self.client_name}/Servo4/Pos", 30)
        #     time.sleep(0.5)
        #     self.mqtt.publish(f"{self.client_name}/Servo3/Pos", 50)
        #     self.mqtt.publish(f"{self.client_name}/Servo4/Pos", 180)
        #     time.sleep(0.5)


servo = Servo(mqtt_client=mqttc,client_name="Robo")


class MyFrame(Frame):
    def __init__(self, master=None):
        self.counter = 0
        #Frame erzeugen und anzeigen
        super().__init__(master) 
        self.grid()

        self.createWidgets()


    def createWidgets(self): 
        
        #Beispiel Button
        self.lbl_Servo = Label(self,text="Servo Control")
        self.lbl_Servo.grid(row=0,column=0,sticky=EW, columnspan=2, pady=5)

        self.btn_ON = Button(self,text="ON",command=servo.on,bg="#ffdddd")
        self.btn_ON.grid(row=1,column=0,sticky=EW)

        self.btn_OFF = Button(self,text="OFF",command=servo.off,bg="#ffdddd")
        self.btn_OFF.grid(row=1,column=1,sticky=EW)

        self.btn_move_right_eye = Button(self,text="Move Right Eye",command=servo.move_right_eye,bg="#ffdddd")
        self.btn_move_right_eye.grid(row=7,column=0,sticky=EW)
        
        self.lbl_Position_Servo_1 = Label(self,text="Position Servo 1:")
        self.lbl_Position_Servo_1.grid(row=2,column=0,sticky=EW, pady=5)
        
        self.lbl_Position_Servo_2 = Label(self,text="Position Servo 2:")
        self.lbl_Position_Servo_2.grid(row=3,column=0,sticky=EW, pady=5)
        
        self.lbl_Position_Servo_3 = Label(self,text="Position Servo 3:")
        self.lbl_Position_Servo_3.grid(row=4,column=0,sticky=EW, pady=5)
        
        self.lbl_Position_Servo_4 = Label(self,text="Position Servo 4:")
        self.lbl_Position_Servo_4.grid(row=5,column=0,sticky=EW, pady=5)
        

        self.Entry_publishVar_Servo_1 = StringVar()
        self.Entry_publish_Servo_1 = Entry(self, textvariable = self.Entry_publishVar_Servo_1)
        self.Entry_publish_Servo_1.grid(row=2,column=1,sticky=EW, columnspan=2, padx=1, pady=5)
        self.Entry_publish_Servo_1.bind('<Key>', self.publish_position_Servo_1)

        self.Entry_publishVar_Servo_2 = StringVar()
        self.Entry_publish_Servo_2 = Entry(self, textvariable = self.Entry_publishVar_Servo_2)
        self.Entry_publish_Servo_2.grid(row=3,column=1,sticky=EW, columnspan=2, padx=1, pady=5)
        self.Entry_publish_Servo_2.bind('<Key>', self.publish_position_Servo_2)

        self.Entry_publishVar_Servo_3 = StringVar()
        self.Entry_publish_Servo_3 = Entry(self, textvariable = self.Entry_publishVar_Servo_3)
        self.Entry_publish_Servo_3.grid(row=4,column=1,sticky=EW, columnspan=2, padx=1, pady=5)
        self.Entry_publish_Servo_3.bind('<Key>', self.publish_position_Servo_3)

        self.Entry_publishVar_Servo_4 = StringVar()
        self.Entry_publish_Servo_4 = Entry(self, textvariable = self.Entry_publishVar_Servo_4)
        self.Entry_publish_Servo_4.grid(row=5,column=1,sticky=EW, columnspan=2, padx=1, pady=5)
        self.Entry_publish_Servo_4.bind('<Key>', self.publish_position_Servo_4)



        self.Scale_Pos_Var = DoubleVar()
        self.Scale_Pos = Scale(self, variable=self.Scale_Pos_Var, from_=0, to_=180, orient= HORIZONTAL, length=200)
        self.Scale_Pos.grid(row=6,column=0,sticky=EW, columnspan=2, padx=1, pady=5)
        self.Scale_Pos.bind("<B1-Motion>", self.scale_motion)


    def publish_position_Servo_1(self, event):
        if event.keysym == "Return":
            position = int(self.Entry_publish_Servo_1.get())
            print(position)
            servo.pos_Servo(position, "Servo1")
            self.Entry_publishVar_Servo_1.set("")


    def publish_position_Servo_2(self, event):
        if event.keysym == "Return":
            position = int(self.Entry_publish_Servo_2.get())
            print(position)
            servo.pos_Servo(position, "Servo2")
            self.Entry_publishVar_Servo_2.set("")


    def publish_position_Servo_3(self, event):
        if event.keysym == "Return":
            position = int(self.Entry_publish_Servo_3.get())
            print(position)
            servo.pos_Servo(position, "Servo3")
            self.Entry_publishVar_Servo_3.set("")


    def publish_position_Servo_4(self, event):
        if event.keysym == "Return":
            position = int(self.Entry_publish_Servo_4.get())
            print(position)
            servo.pos_Servo(position, "Servo4")
            self.Entry_publishVar_Servo_4.set("")


    def scale_motion(self, event):
        servo.pos(int(self.Scale_Pos.get()))
        



#Fenster erzeugen           
root = Tk()
root.title("Servo")
  

#MyFrame erzeugen
rahmen = MyFrame(root)       
root.mainloop()
