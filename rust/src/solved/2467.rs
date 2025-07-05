use std::io;

fn input_number() -> Vec<i32> {
    let mut s = String::new();
    io::stdin().read_line(&mut s).unwrap();

    s.split_ascii_whitespace()
        .map(|s| s.parse().unwrap())
        .collect()
}

fn solve(ph: &Vec<i32>, n: usize) -> Vec<i32> {
    let mut numbers = vec![0; 2];
    let mut sum: Option<i32> = None;

    let mut left = 0;
    let mut right = n - 1;
    while left < right {
        let current_sum = (ph[left] + ph[right]) as i32;

        if let Some(value) = sum {
            if value.abs() > current_sum.abs() {
                sum = Some(current_sum);
                numbers[0] = ph[left];
                numbers[1] = ph[right];
            }
        } else {
            sum = Some(current_sum);
            numbers[0] = ph[left];
            numbers[1] = ph[right];
        }

        if current_sum < 0 {
            left += 1;
        } else if current_sum > 0 {
            right -= 1;
        } else {
            break;
        }
    }
    numbers
}

fn main() {
    let n = input_number()[0] as usize;

    let ph = input_number();

    let result = solve(&ph, n);
    for n in result {
        print!("{n} ");
    }
    println!();
}
