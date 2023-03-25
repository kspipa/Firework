use nfq::{Queue, Verdict};

mod packethr;
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
    let payload = new_msg.get_payload();
    println!("{}",new_msg.get_indev());
    println!("{}", new_msg.get_outdev());
    println!("Payload: {:?}", payload);
    println!("Source ip addr : {:?}", packethr::get_source_ip(payload));
    println!("Dest ip addr : {:?}", packethr::get_dest_ip(payload));
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
fn _from_dec_to_hex_payload(payload: &[u8]) -> Vec<String>{
    let mut new_block:Vec<String> = vec![];
    let mut hex_str = String::from("0");
    for i in payload.into_iter(){
        hex_str = format!("{:x}", &i);
        new_block.push(hex_str);
    }
    return new_block;
}