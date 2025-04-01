// 1697 숨바꼭질

use std::io;
use std::collections::VecDeque;

fn get_fastest_second(n: usize, m: usize) -> usize {
    let mut distance: Vec<i32> = vec![-1; 100_001];
    let mut queue: VecDeque<usize> = VecDeque::new();
    
    queue.push_back(n);
    distance[n] = 0;
    while !queue.is_empty() {
        let node = queue.pop_front().unwrap();

        if 1 <= node && distance[node-1] == -1 {
            distance[node-1] = distance[node] + 1;
            queue.push_back(node-1);
        } 
        if node + 1 <= 100_000 && distance[node+1] == -1 {
            distance[node+1] = distance[node] + 1;
            queue.push_back(node+1);
        }
        if node * 2 <= 100_000 && distance[node*2] == -1 {
            distance[node*2] = distance[node] + 1;
            queue.push_back(node*2);
        }
    }

    let min = distance[m] as usize;
    
    min
}

fn main() {
    let mut s = String::new();
    io::stdin().read_line(&mut s).unwrap();

    let nums: Vec<usize> = s
        .split_ascii_whitespace()
        .take(2)
        .map(|s|s.parse().unwrap())
        .collect();

    let n = nums[0];
    let m = nums[1];

    let result = get_fastest_second(n, m);
    println!("{result}");
}