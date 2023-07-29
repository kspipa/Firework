from multiprocessing import shared_memory
from copy import copy

class shm():
    def __init__(__self__, name: str, size: int):
        shm_a = shared_memory.SharedMemory(name=name, create=True, size=size)
        __self__.shm = shm_a
        __self__.previd = 0
    def get_ans_code(__self__):
        while __self__.shm.buf[0] == __self__.previd:
            continue
        ll = copy(__self__.shm.buf)
        __self__.previd = ll[0]
        return ll
    def send_ans_code(__self__,id: int, verdict: int):
        __self__.shm.buf[0] = id
        __self__.shm.buf[1] = verdict

def parsemem(memcell):
    packet = []
    p = memcell
    for i in range(p[1]):
        packet[i] = p[i+2]
    return (p[0], packet)
    
    
