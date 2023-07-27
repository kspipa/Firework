import os
import random
import time
s = "1234567890asdfghjklqwertyuiopzxcvbnm"
e = ""
for i in range(16):
    e += random.choice(list(s))
who = os.getlogin()
os.system(f"sudo useradd firework -p {e} --home-dir /home/{who}/.firework")
os.environ['FRWK_PATH'] = f'/home/{who}/.firework'