use std::io;
use io::Write;
use std::collections::VecDeque;

fn input_numbers(count: usize) -> Vec<i32> {
    let mut s = String::new();
    io::stdin().read_line(&mut s).unwrap();

    s.split_ascii_whitespace().take(count).map(|s|s.parse().unwrap()).collect()
}

fn bfs(b: &mut Vec<Vec<i32>>, n: usize, m: usize) -> i32 {
    let move_dir = vec![
        (-1, 0),
        (1, 0),
        (0, 1),
        (0, -1),
    ];
    
    let mut q: VecDeque::<(usize, usize, usize)> = VecDeque::new();
    let mut target = 0;
    
    for i in 1..=n {
        for j in 1..=m {
            if b[i][j] == 1 {
                q.push_back((i, j, 0));
            } else if b[i][j] == 0 {
                target += 1;
            }
        }
    }

    while !q.is_empty(){
        if target == 0 {
            let mut result = q.pop_front().unwrap().2;
            while !q.is_empty() {
                result = q.pop_front().unwrap().2;
            }

            return result as i32;
        }
        let idx = q.pop_front().unwrap();

        for (i, j) in &move_dir {
            let di = (i + idx.0 as i32) as usize;
            let dj = (j + idx.1 as i32) as usize;
            let count = idx.2 + 1;

            if b[di][dj] == 0 {
                target -= 1;
                
                q.push_back((di, dj, count));
                b[di][dj] = 1;
            }
        }
    }

    return -1;
}

fn main() {
    let stdout = io::stdout();
    let mut out = stdout.lock();

    let size = input_numbers(2);
    let m = size[0] as usize;
    let n = size[1] as usize;

    let mut tomato_box = vec![vec![-1; m + 2]; n + 2];
    for i in 1..=n {
        let row = input_numbers(m);
        for j in 1..=m {
            tomato_box[i][j] = row[j-1];
        }
    }

    let count = bfs(&mut tomato_box, n, m);
    writeln!(out, "{count}").unwrap();
}