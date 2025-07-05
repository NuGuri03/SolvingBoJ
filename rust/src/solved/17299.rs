use std::{io, str};
use io::Write;
use std::collections::HashMap;

pub struct UnsafeScanner<R> {
    reader: R,
    buf_str: Vec<u8>,
    buf_iter: str::SplitAsciiWhitespace<'static>,
}

impl<R: io::BufRead> UnsafeScanner<R> {
    pub fn new(reader: R) -> Self {
        Self {
            reader,
            buf_str: vec![],
            buf_iter: "".split_ascii_whitespace(),
        }
    }

    pub fn token<T: str::FromStr>(&mut self) -> T {
        loop {
            if let Some(token) = self.buf_iter.next() {
                return token.parse().ok().expect("Failed parse");
            }
            self.buf_str.clear();
            self.reader
                .read_until(b'\n', &mut self.buf_str)
                .expect("Failed read");
            self.buf_iter = unsafe {
                let slice = str::from_utf8_unchecked(&self.buf_str);
                std::mem::transmute(slice.split_ascii_whitespace())
            }
        }
    }

    pub fn line(&mut self) -> String {
        let mut input = String::new();
        self.reader.read_line(&mut input).expect("Failed read");
        input
    }
}

fn main() {
    let (stdin, stdout) = (io::stdin(), io::stdout());
    let mut scan = UnsafeScanner::new(stdin.lock());
    let mut out = io::BufWriter::new(stdout.lock());

    let n = scan.token::<usize>();

    let mut arr: Vec<usize> = vec![0; n];
    let mut map: HashMap<usize, usize> = HashMap::new();

    for element in arr.iter_mut() {
        *element = scan.token::<usize>();
        *map.entry(*element).or_insert(1) += 1;
    }

    let mut stack: Vec<(usize, usize)> = Vec::new();
    let mut ngf: Vec<usize> = Vec::new();

    for i in (0..n).rev() {
        while !stack.is_empty() && 
            map[&(stack[stack.len() - 1].0)] <= map[&arr[i]] {
            stack.pop();
        }

        if stack.is_empty() {
            stack.push((arr[i], i));
            ngf.push(i);
        } else {
            ngf.push(stack[stack.len() - 1].1);
            stack.push((arr[i], i));
        }
    }

    ngf.reverse();

    for i in 0..n {
        write!(
            out,
            "{} ", 
            if arr[i] == arr[ngf[i]] {
                -1 as i32
            } else {
                arr[ngf[i]] as i32
            }
        ).unwrap();
    }
    writeln!(out).unwrap();

}