// 13728 행렬식과 gcd

use std::io::{self, BufRead, BufWriter, Write};
const MOD: u64 = 10u64.pow(9) + 7;

fn get_gcd(mut a: usize, mut b: usize) -> usize {
    while b != 0 {
        let temp = a % b;
        a = b;
        b = temp;
    }
    a
}

fn main() {
    let stdin = io::stdin();
    let mut stdout = BufWriter::new(io::stdout());

    let mut fibo = vec![0; 100002];
    fibo[1] = 1;
    for i in 2..100002 {
        fibo[i] = (fibo[i - 1] + fibo[i - 2]) % MOD;
    }

    let mut s = String::new();
    stdin.lock().read_line(&mut s).unwrap();
    let mut n: usize = s.trim().parse().unwrap();
    n += 1;

    let mut sum = 0;
    for i in 2..=n {
        let gcd = get_gcd(i, n);
        sum = (sum + fibo[gcd]) % MOD;
    }

    writeln!(stdout, "{sum}").unwrap();
}
