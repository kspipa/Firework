mod firework_lib;
use firework_lib::*;
use nfq::{Queue, Verdict};
fn main() -> std::io::Result<()>{
    let mut k = shmemCell::init("strongnigga");
    let mut seccell = shmemCell::init("strongnigga2");
    let mut queue = Queue::open()?;
    queue.bind(0)?;
    let mut new_msg: nfq::Message;
    loop{
        new_msg = queue.recv()?;
        k.setpack(new_msg.get_payload(), (new_msg.get_packet_id() as u8));
        let res = seccell.waitcode();
        if res.1 == 0{
            new_msg.set_verdict(Verdict::Drop)
        }
        else {
            new_msg.set_verdict(Verdict::Accept)
        }
        queue.verdict(new_msg);
    }
    Ok(())
}