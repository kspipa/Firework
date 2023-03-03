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
    match check_proto(&mut new_msg){
        Some(t) => println!("Packet has been drop. Its proto num is : {}", t),
        None => println!("Packet has been send. Its proto num is ipv4 proto")
    };
    println!("Packet mark is : {}",new_msg.get_nfmark());
    let addr = get_hw_addr(&new_msg);
    new_msg.get_payload();
    println!("Get hw addr : {:?}", addr);
    return new_msg;

}
fn get_hw_addr(msg: &nfq::Message) -> &[u8]{
    let option_addr = msg.get_hw_addr();
    let addr = match option_addr{
        Some(option_addr) => option_addr,
        None => panic!("Cant get hw address")
    };
    return addr;
}
fn check_proto(msg: &mut nfq::Message) -> Option<u16>{
    let proto_num = msg.get_hw_protocol();
    if proto_num != 2048{
        msg.set_verdict(Verdict::Drop);
        return Some(proto_num);
    }
    else{
        return None;
    }
}