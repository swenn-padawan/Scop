use std::env;
use std::fs::File;
use std::io::{self, BufRead, BufReader};
use crate::parsing::Mesh;

fn v_fill(line: &str, mesh: &mut Mesh){
    let parts: Vec<&str> = line.split_whitespace().collect();
    if parts.len() >= 4 {
        let x: f32 = parts[1].parse().unwrap_or(0.0);
        let y: f32 = parts[2].parse().unwrap_or(0.0);
        let z: f32 = parts[3].parse().unwrap_or(0.0);
        mesh.vertex.push([x, y, z]);
        println!("Vertex added: {:?}", [x, y, z]);
    }
}

fn  f_fill(line: &str, mesh: &mut Mesh){
    let parts: Vec<&str> = line.split_whitespace().collect();
    if parts.len() >= 4 {
        let x: usize = parts[1].parse().unwrap_or(0);
        let y: usize = parts[2].parse().unwrap_or(0);
        let z: usize = parts[3].parse().unwrap_or(0);
        mesh.faces.push([x, y, z]);
        println!("Faces added: {:?}", [x, y, z]);
    }
}

fn vn_fill(line: &str, mesh: &mut Mesh){
    let parts: Vec<&str> = line.split_whitespace().collect();
    if parts.len() >= 4 {
        let x: f32 = parts[1].parse().unwrap_or(0.0);
        let y: f32 = parts[2].parse().unwrap_or(0.0);
        let z: f32 = parts[3].parse().unwrap_or(0.0);
        mesh.normales.push([x, y, z]);
        println!("Normales added: {:?}", [x, y, z]);
    }
}


fn fill_mesh(line: &str, mesh: &mut Mesh){
    if line.starts_with("v "){
        v_fill(line, mesh);
    }
    else if line.starts_with("f "){
        f_fill(line, mesh);
    }
    else if line.starts_with("vn "){
        vn_fill(line, mesh);
    }
    else{
        println!("Need to implement {}", line);
    }

}

pub fn obj_parsing() -> io::Result<Mesh> {
    let args: Vec<String> = env::args().collect();
    if args.len() != 2{
        panic!("No file provided")
    }

    let file = File::open(args[1].clone())?;

    let reader = BufReader::new(file);
    let mut mesh = Mesh::new();
    for line in reader.lines() {
        let line = line?;
        fill_mesh(&line, &mut mesh);
    }
    Ok(mesh)
}
