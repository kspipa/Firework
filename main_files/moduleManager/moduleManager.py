from shm import shm, parsemem

cell = shm("strongnigga", 2000)
seccell = shm("strongnigga2", 2)

def module(packid: int, packet):
    return (packid, 1)

while True:
    (packid, packet) = parsemem(cell.get_ans_code())
    ver = module(packid, packet)
    seccell.send_ans_code(ver[0], ver[1])
