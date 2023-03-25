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
    let payload = new_msg.get_payload_mut();
    println!("First source ip addr : {:?}", packethr::get_source_ip(payload));
    println!("First dest ip addr : {:?}", packethr::get_dest_ip(payload));
    packethr::set_source_ip(payload, [1,1,1,1]);
    packethr::set_dest_ip(payload, [1,1,1,1]);
    println!("Second source ip addr : {:?}", packethr::get_source_ip(payload));
    println!("Second dest ip addr : {:?}", packethr::get_dest_ip(payload));
    println!("Payload : {:?}", payload);
    let mut newpayload = payload.to_vec();
    new_msg.set_payload(newpayload);
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
fn _from_dec_to_hex(data: &[u8]) -> Vec<String>{
    let mut new_block:Vec<String> = vec![];
    let mut hex_str = String::from("0");
    for i in data.into_iter(){
        hex_str = format!("{:x}", &i);
        new_block.push(hex_str);
    }
    return new_block;
}