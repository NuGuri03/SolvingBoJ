use std::io::{self, Write};

#[derive(Copy, Clone)]
struct Point {
    x: f64,
    y: f64
}

fn input_points() -> Vec<Point> {
    let mut s = String::new();
    io::stdin().read_line(&mut s).unwrap();

    let p: Vec<f64> = s
        .split_ascii_whitespace()
        .take(4)
        .map(|s| s.parse().unwrap())
        .collect();

    let v = vec![
        Point { x: p[0], y: p[1] },
        Point { x: p[2], y: p[3] },
    ];
    
    v
}

fn ccw(p1: &Point, p2: &Point, p3: &Point) -> i32 {
    let mut s = p1.x * p2.y + p2.x * p3.y + p3.x * p1.y;
    s -= p1.y * p2.x + p2.y * p3.x + p3.y * p1.x;

    if s.abs() < 1e-9 {
        return 0;
    } else if s > 0.0 {
        return 1;
    } else {
        return -1;
    }
}

fn is_intersect(v: Vec<Vec<Point>>) -> bool {
    let p1 = v[0][0].clone();
    let p2 = v[0][1].clone();
    let p3 = v[1][0].clone();
    let p4 = v[1][1].clone();

    let c1c2 = ccw(&p1, &p2, &p3) * ccw(&p1, &p2, &p4);
    let c3c4 = ccw(&p3, &p4, &p1) * ccw(&p3, &p4, &p2);

    c1c2 <= 0 && c3c4 <= 0 
}

fn main() {
    let mut stdout = io::stdout();

    let mut line_segements: Vec<Vec<Point>> = Vec::new();
    for _ in 0..2 {
        line_segements.push(input_points());
    }
    
    let ans = match is_intersect(line_segements) {
        true => 1,
        false => 0   
    };

    writeln!(stdout, "{}", ans).unwrap();
}