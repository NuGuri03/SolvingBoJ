use std::io::{self, BufWriter, Write};

fn get_eulers_totient_function(mut n: usize) -> i64 {
    
    let mut x = n as f64;
    let sqrt_n = (n as f64).sqrt() as usize;    
    for i in 2..=sqrt_n {
        if n % i == 0 {
            while n % i == 0 {
                n /= i;
            }
            x *= 1.0 - (1.0 / i as f64);
        }
    }
    if n != 1 {
        x *= 1.0 - (1.0 / n as f64);
    }

    x as i64
} 

fn main() {
    let (stdin, stdout) = (io::stdin(), io::stdout());
    let mut out = BufWriter::new(stdout.lock());

    let mut s = String::new();
    stdin.read_line(&mut s).unwrap();

    let n = s.trim().parse::<usize>().unwrap();

    writeln!(out, "{}", get_eulers_totient_function(n)).unwrap();
}