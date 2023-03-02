use nfq::{Queue, Verdict};

fn main() -> std::io::Result<()> {
    let mut queue = Queue::open()?;
    queue.bind(0)?;
    loop {
        let new_msg = parse(queue.recv()?);
        queue.verdict(new_msg)?;
    }
    Ok(())
}
fn parse(msg: nfq::Message) -> nfq::Message{
    let mut new_msg = msg;
    let proto_num = new_msg.get_hw_protocol();
    if proto_num != 2048{
        new_msg.set_verdict(Verdict::Drop);
        println!("Packet has been drop. Its proto num is: {}", proto_num);
    }
    else{
        println!("Packet has been send. Its proto num is: {}", proto_num);
    }
    return new_msg;

}