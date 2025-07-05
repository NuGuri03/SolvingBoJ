use std::io;

fn input_integers(count: usize) -> Vec<usize> {
    let mut s = String::new();
    io::stdin().read_line(&mut s).unwrap();

    let integers = s
        .split_ascii_whitespace()
        .take(count)
        .map(|s| s.parse().unwrap())
        .collect();

    integers
}

fn main() {
    let n = input_integers(1)[0];

    let arr = input_integers(n);

    let mut monotonic_stack: Vec<(usize, usize)> = Vec::new();
    let mut nge: Vec<usize> = Vec::new();

    for i in (0..n).rev() {
        while !monotonic_stack.is_empty() && monotonic_stack[monotonic_stack.len() - 1].0 <= arr[i]
        {
            monotonic_stack.pop();
        }

        if monotonic_stack.is_empty() {
            monotonic_stack.push((arr[i], i));
            nge.push(i);
        } else {
            nge.push(monotonic_stack[monotonic_stack.len() - 1].1);
            monotonic_stack.push((arr[i], i));
        }
    }

    nge.reverse();
    for i in 0..n {
        if nge[i] == i {
            print!("-1 ");
        } else {
            print!("{} ", arr[nge[i]]);
        }
    }
    println!();
}
