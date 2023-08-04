use nfq::{Queue, Verdict};
fn main() -> std::io::Result<()>{
    let mut queue = Queue::open()?;
    queue.bind(0)?;
    let mut new_msg: nfq::Message;
    loop{
        new_msg = queue.recv()?;
        new_msg.set_verdict(Verdict::Accept);
        queue.verdict(new_msg);
    }
    Ok(())
}