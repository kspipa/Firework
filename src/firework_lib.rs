use nfq::Message;
use shmem;



pub struct fifobuffer<'a>{
    buffer: Vec<&'a Message>
}
impl fifobuffer<'_>{
    pub fn new() -> Self{
        return fifobuffer {buffer : Vec::new()};
    }
    pub fn write(&mut self, data: &mut Message){
        self.buffer.push(data);
    }
    pub fn read(&self) -> Vec<&Message>{
        return self.buffer.clone();
    }
    pub fn getlen(&self) -> usize{
        return self.buffer.len()
    }
}
pub struct shmemCell{
    cell: shmem::Array<u8>,
    name: String
}
impl shmemCell{
    pub fn init(name: &str) -> shmemCell{
        let mut k: shmem::Array<u8> = shmem::array::open::<u8, _>(name).unwrap();
        return shmemCell::from(k, name.to_string());
    }
    fn from(arr: shmem::Array<u8>, name: String) -> Self{
        return shmemCell {cell: arr, name: name};
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
    pub fn readcode(&self) -> (u8, u8){
        return (self.cell[0], self.cell[1]);
    }

}

