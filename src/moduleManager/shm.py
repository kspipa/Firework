from multiprocessing import shared_memory

class shm():
    def __init__(__self__, name: str):
        shm_a = shared_memory.SharedMemory(name=name, create=True, size=10)
        __self__.shm = shm_a
        print(list(shm_a.buf))
    def get_ans_code(__self__):
        while __self__.shm.buf[0] == 0:
            continue
        return 1
    def send_ans_code(__self__, verdict: int, id: int):
        __self__.shm.buf[0] = 2
        __self__.shm.buf[1] = id
        __self__.shm.buf[2] = verdict
    def parsemem(__self__):
        packet = []
        num = __self__.shm.buf[1]
        for i in range(num):
            packet[i] = __self__.shm.buf[i+2]
        return (packet, __self__.shm.buf[num + 1])
    
    
