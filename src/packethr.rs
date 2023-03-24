
pub fn get_dest_ip(packet: &[u8]) -> &[u8]{
    return &packet[16..20];
}

pub fn get_source_ip(packet: &[u8]) -> &[u8]{
    return &packet[12..16];
}