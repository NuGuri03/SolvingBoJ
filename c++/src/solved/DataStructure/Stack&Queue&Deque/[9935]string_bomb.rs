// 문자열 폭발

use std::io;

fn input_string() -> String {
    let mut s = String::new();
    io::stdin().read_line(&mut s).unwrap();
    
    s.trim().to_string()
}

fn main() {
    let str = input_string();
    let bomb = input_string();

    let bomb_len = bomb.len();
    let bomb: Vec<char> = bomb.chars().collect();
    
    let mut stack: Vec<char> = Vec::new();    
    for ch in str.chars() {
        stack.push(ch);

        if stack.len() >= bomb_len {
            let sliced_str = &stack[stack.len() - bomb_len..];
            if sliced_str == bomb {
                for _ in 0..bomb_len {
                    stack.pop();
                }
            }
        }
    }

    if stack.is_empty() {
        println!("FRULA");
    } else {
        for ch in stack {
            print!("{ch}");
        }
        println!();
    }
}   