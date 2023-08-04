use shmem;

pub struct shmemCell{
    cell: shmem::Array<u8>,
    name: String,
    last_id: u8
}
impl shmemCell{
    pub fn init(name: &str) -> shmemCell{
        let mut k: shmem::Array<u8> = shmem::array::open::<u8, _>(name).unwrap();
        return shmemCell::from(k, name.to_string());
    }
    fn from(arr: shmem::Array<u8>, name: String) -> Self{
        return shmemCell {cell: arr, name: name, last_id: 0};
    }
    pub fn setpack(&mut self, packet: &[u8],id : u8){
        self.setinfo([&[id], packet].join(&(packet.len() as u8)).as_slice());
        return;
    }
    pub fn setinfo(&mut self, info: &[u8]){
        let mut t = 0;
        for i in info{
            self.cell[t] = *i;
            t += 1;
        }
        return;
    }
    pub fn waitcode(&mut self) -> (u8, u8){
        loop{
            let val = self.readcode().clone();
            if  val.0 == self.last_id{}
            else {
                self.last_id = val.0;
                return val;
            }
        }
    }
    fn readcode(&self) -> (u8, u8){
        return (self.cell[0], self.cell[1]);
    }

}

