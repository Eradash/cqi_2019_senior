from inputs import get_key
import time
import serial

keys = {}

ser = serial.Serial('/dev/tty.usbmodem14101', 9600, timeout=.1)

key_codes = {
    "KEY_Q": "q.",
    "KEY_E": "e.",
    "KEY_A": "a.",
    "KEY_RESERVED": "d.",
    "KEY_SPACE": "sp"
}


def send_event_to_arduino(event_code, event_state):
    if key_codes.__contains__(event_code):
        command = str(key_codes[event_code]) + str(event_state) + "\n"
        ser.write(bytes(command, 'utf-8'))
        print(command)


while 1:
    time.sleep(0.01)
    events = get_key()
    for event in events:
        if event.ev_type == "Key":
            if event.code in keys:
                if keys[event.code] != event.state:
                    send_event_to_arduino(event.code, event.state)
                    keys[event.code] = event.state
            else:
                keys[event.code] = event.state
                send_event_to_arduino(event.code, event.state)

