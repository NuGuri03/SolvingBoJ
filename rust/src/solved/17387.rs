use std::io::{self, Write};
use std::mem::swap;

#[derive(Clone)]
struct Point {
    x: i64,
    y: i64,
}

fn input_points() -> Vec<Point> {
    let mut s = String::new();
    io::stdin().read_line(&mut s).unwrap();

    let p: Vec<i64> = s
        .split_ascii_whitespace()
        .take(4)
        .map(|s| s.parse().unwrap())
        .collect();

    vec![Point { x: p[0], y: p[1] }, Point { x: p[2], y: p[3] }]
}

fn ccw(a: &Point, b: &Point, c: &Point) -> i64 {
    let num = (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);

    match num {
        x if x > 0 => 1,  // 반시계
        x if x < 0 => -1, // 시계
        _ => 0,           // 일직선
    }
}

fn is_intersect(line: &Vec<Vec<Point>>) -> bool {
    let mut p1 = line[0][0].clone();
    let mut p2 = line[0][1].clone();
    let mut p3 = line[1][0].clone();
    let mut p4 = line[1][1].clone();

    let c1c2 = ccw(&p1, &p2, &p3) * ccw(&p1, &p2, &p4);
    let c3c4 = ccw(&p3, &p4, &p1) * ccw(&p3, &p4, &p2);

    if c1c2 == 0 && c3c4 == 0 {
        if p1.x > p2.x || (p1.x == p2.x && p1.y > p2.y) {
            swap(&mut p1, &mut p2);
        }

        if p3.x > p4.x || (p3.x == p4.x && p3.y > p4.y) {
            swap(&mut p3, &mut p4);
        }

        let p1p4 = p1.x < p4.x || (p1.x == p4.x && p1.y <= p4.y);
        let p2p3 = p2.x > p3.x || (p2.x == p3.x && p2.y >= p3.y);

        return p1p4 && p2p3;
    }

    c1c2 <= 0 && c3c4 <= 0
}

fn main() {
    let mut stdout = io::stdout();

    let mut line_segments: Vec<Vec<Point>> = Vec::new();
    for _ in 0..2 {
        line_segments.push(input_points());
    }

    let ans = match is_intersect(&line_segments) {
        true => 1,
        false => 0,
    };

    writeln!(stdout, "{}", ans).unwrap();
}
