from shm import shm

cell = shm("strongnigga")
cell.get_ans_code()
print(list(cell.shm.buf))
