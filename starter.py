import os
import keyboard
import time

cmd = os.system("start")
time.sleep(1)
keyboard.write("env\\Scripts\\activate.bat")
keyboard.press("enter")

keyboard.write("cd gramogram")
keyboard.press("enter")

keyboard.write("python manage.py runserver")
keyboard.press("enter")