use std::fs::File;
use std::io::{self, BufRead, BufReader};
use std::env;

fn main() -> io::Result<()> {
    let args: Vec<String> = env::args().collect();

    let mut file = File::open(args[1].clone())?;

    let reader = BufReader::new(file);

    for line in reader.lines() {
        let line = line?;
        println!("{}", line);
    }
    Ok(())
}
