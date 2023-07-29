from shm import shm, parsemem
from threading import *

cell = shm("strongnigga", 100)
seccell = shm("strongnigga2", 2)

def module(packid: int, packet):
    return (packid, 1)

while True:
    (packid, packet) = parsemem(cell.get_ans_code())
    seccell.send_ans_code(module(packid, packet))
    print(list(cell.shm.buf))
