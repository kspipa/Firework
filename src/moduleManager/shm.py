from multiprocessing import shared_memory
from copy import copy

class shm():
    def __init__(self, name: str, size: int):
        shm_a = shared_memory.SharedMemory(name=name, create=True, size=size)
        self.shm = shm_a
        self.previd = 0
    def get_ans_code(self):
        while self.shm.buf[0] == self.previd:
            continue
        ll = copy(self.shm.buf.tolist())
        self.previd = ll[0]
        return ll
    def send_ans_code(self ,id: int, verdict: int):
        self.shm.buf[0] = id
        self.shm.buf[1] = verdict

def parsemem(memcell):
    p = memcell
    packet = [0]*p[1]
    for i in range(p[1]):
        packet[i] = p[i+2]
    return (p[0], packet)
    
    
