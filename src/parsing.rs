pub mod obj;

pub struct Mesh{
    pub vertex: Vec<[f32; 3]>,
    pub faces: Vec<[usize; 3]>,
}

impl Mesh {
    pub fn new() -> Self {
        Mesh {
            vertex: Vec::new(),
            faces: Vec::new(),
        }
    }
}
