use shmem;
pub fn init() -> shmem::Array<u8> {
    let mut k = shmem::array::open::<u8, _>("strongnigga").unwrap();
    return k
}
