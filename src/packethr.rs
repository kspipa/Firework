pub fn get_dest_ip(packet: &[u8]) -> &[u8]{
    return &packet[16..20];
}
pub fn get_source_ip(packet: &[u8]) -> &[u8]{
    return &packet[12..16];
}
pub fn set_dest_ip(packet: &mut [u8], dest_ip: [u8; 4]){
    let mut t = 0;
    for i in 16..20{
        packet[i] = dest_ip[t];
        t += 1;
    }
}
pub fn set_source_ip(packet: &mut [u8], source_ip: [u8; 4]){
    let mut t = 0;
    for i in 12..16{
        packet[i] = source_ip[t];
        t += 1;
    }
}
pub fn get_ttl(packet: &[u8]) -> u8{
    return packet[8]
}
pub fn get_next_layer_proto(packet: &[u8]) -> u8{
    return packet[9];
}