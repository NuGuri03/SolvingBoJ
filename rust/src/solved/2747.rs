// 2747 피보나치 수

fn fibonacci(n: i32) -> i32 {
    let n = n as usize;
    let mut dp: Vec<i32> = vec![0; n + 1];

    dp[0] = 0;
    dp[1] = 1;
    for i in 2..=n {
        dp[i] = dp[i - 1] + dp[i - 2];
    }

    dp[n]
}

fn main() {
    let mut s = String::new();
    std::io::stdin().read_line(&mut s).unwrap();

    let n: i32 = s.trim().parse().unwrap();

    println!("{}", fibonacci(n));
}
