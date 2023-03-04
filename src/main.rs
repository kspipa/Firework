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
    println!("Packet mark is : {}",new_msg.get_nfmark());
    let addr = get_hw_addr(&new_msg);
    println!("hook : {}", new_msg.get_hook());
    println!("Get hw addr : {:?}", addr);
    return new_msg;

}
fn get_hw_addr(msg: &nfq::Message) -> &[u8]{
    let option_addr = msg.get_hw_addr();
    let addr = match option_addr{
        Some(option_addr) => option_addr,
        None => &[0]
    };
    return addr;
}