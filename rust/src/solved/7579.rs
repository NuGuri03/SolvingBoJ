// 7579 앱

use std::io;
use std::cmp::max;

struct Memory {
    byte: usize,
    cost: usize
}

fn input_integers() -> (usize, usize) {
    let mut s = String::new();
    io::stdin().read_line(&mut s).unwrap();
    let mut nums = s
        .split_ascii_whitespace()
        .map(|s|s.parse::<usize>().unwrap());
    
    let n = nums.next().unwrap();
    let m = nums.next().unwrap();

    (n, m)
}

fn create_vector(size: usize) -> Vec<usize> {
    let mut s = String::new();
    io::stdin().read_line(&mut s).unwrap();

    let v = s
        .split_ascii_whitespace()
        .take(size)
        .map(|s|s.parse().unwrap())
        .collect();
    
    v
}

fn get_minimum_cost(apps: &Vec<Memory>, m: usize) -> usize {
    let n = apps.len();
    let mut max_cost = 0;
    for app in apps {
        max_cost += app.cost;
    }

    let mut dp = vec![vec![0; max_cost + 1]; n + 1];

    for i in 1..=n {
        for j in 0..=max_cost {
            dp[i][j] = dp[i-1][j];
            if j >= apps[i - 1].cost {
                dp[i][j] = max(dp[i][j], dp[i-1][j-apps[i-1].cost] + apps[i - 1].byte);
            }
        }
    }

    let mut result = max_cost;
    for (cost, byte) in dp[n].iter().enumerate() {
        if *byte >= m && cost < result {
            result = cost;
        }
    }

    result
}
fn main() {
    let (n, m) = input_integers();

    let a = create_vector(n);
    let c = create_vector(n);

    let mut apps: Vec<Memory> = Vec::with_capacity(n);
    for i in 0..n {
        apps.push(Memory {byte: a[i], cost: c[i]});
    }

    println!("{}", get_minimum_cost(&apps, m));
}