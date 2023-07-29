mod firework_lib;
use firework_lib::*;
use nfq::{Queue, Verdict};
use fork::*;
fn main() -> std::io::Result<()>{
    let mut k = shmemCell::init("strongnigga");
    let seccell = shmemCell::init("strongnigga2");
    let mut buffer = fifobuffer::new();
    let mut queue = Queue::open()?;
    queue.bind(0)?;
    let mut new_msg: nfq::Message;
    loop{
        if let Ok(Fork::Child) = daemon(false, true) {
            loop{
                buffer.write(&mut queue.recv().unwrap());
            }
        }
    }
    Ok(())
}
fn getpack(){
 
}