import serial
import keyboard

# Establish a connection to the Arduino
arduino = serial.Serial('/dev/tty.usbmodem21201', 9600)  # Change 'COM3' to your Arduino's port

def send_signal(signal):
    arduino.write(signal.encode())

# Assign functions to arrow keys
keyboard.on_press_key("up", lambda _: send_signal("U"))
keyboard.on_press_key("down", lambda _: send_signal("D"))
keyboard.on_press_key("left", lambda _: send_signal("R"))
keyboard.wait()  # Keep the program running

