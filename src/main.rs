use nfq::{Queue, Verdict};
use fork::*;
fn main() -> std::io::Result<()> {
    let mut queue = Queue::open()?;
    queue.bind(0)?;
    loop{
        let mut new_msg = queue.recv()?;
        println!("{:?}", new_msg.get_payload());
        new_msg.set_verdict(Verdict::Accept);
        queue.verdict(new_msg)?;
    }
    Ok(())
}
fn start_daemons(){
    if let Ok(Fork::Child) = daemon(false, true) {
    }
}