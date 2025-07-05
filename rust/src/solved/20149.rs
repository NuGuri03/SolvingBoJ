use std::io::{self, Write};
use std::mem::swap;

#[derive(Clone, Copy, Debug)]
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
        x if x > 0 => 1,
        x if x == 0 => 0,
        x if x < 0 => -1,

        _ => panic!("Error!"),
    }
}

fn is_lower(a: &Point, b: &Point) -> bool {
    a.x < b.x || (a.x == b.x && a.y <= b.y)
}
fn is_greater(a: &Point, b: &Point) -> bool {
    a.x > b.x || (a.x == b.x && a.y > b.y)
}
fn is_same(a: &Point, b: &Point) -> bool {
    a.x == b.x && a.y == b.y
}

fn is_intersect(lines: &Vec<Vec<Point>>) {
    let mut p1 = lines[0][0];
    let mut p2 = lines[0][1];
    let mut p3 = lines[1][0];
    let mut p4 = lines[1][1];

    let p1p2 = ccw(&p1, &p2, &p3) * ccw(&p1, &p2, &p4);
    let p3p4 = ccw(&p3, &p4, &p1) * ccw(&p3, &p4, &p2);

    if p1p2 == 0 && p3p4 == 0 {
        if is_greater(&p1, &p2) {
            swap(&mut p1, &mut p2);
        }
        if is_greater(&p3, &p4) {
            swap(&mut p3, &mut p4);
        }

        if is_lower(&p1, &p4) && is_lower(&p3, &p2) {
            // println!("{:?} {:?} {:?} {:?}", p1, p2, p3, p4);
            print_state(1);
            get_intersect_point(lines);
        } else {
            print_state(0);
        }
    } else {
        if p1p2 <= 0 && p3p4 <= 0 {
            print_state(1);
            get_intersect_point(lines);
        } else {
            print_state(0);
        }
    }
}

fn get_intersect_point(lines: &Vec<Vec<Point>>){
    let mut p1 
    = lines[0][0];
    let mut p2 = lines[0][1];
    let mut p3 = lines[1][0];
    let mut p4 = lines[1][1];

    if is_greater(&p1, &p2) {
        swap(&mut p1, &mut p2);
    }
    if is_greater(&p3, &p4) {
        swap(&mut p3, &mut p4);
    }

    let a1 = (p1.y - p2.y) as f64;
    let b1 = (p2.x - p1.x) as f64;
    let c1 = a1 * p1.x as f64 + b1 * p1.y as f64;

    let a2 = (p3.y - p4.y) as f64;
    let b2 = (p4.x - p3.x) as f64;
    let c2 = a2 * p3.x as f64 + b2 * p3.y as f64;

    let det = a1 * b2 - b1 * a2;

    if det.abs() < 1e-9 {
        if is_same(&p2, &p3) && is_lower(&p1, &p3){
            print_point(p2);

        } else if is_same(&p1, &p4) && is_lower(&p3, &p1) {
            print_point(p1);
        }
    } else {
        let x = (b2 * c1 - b1 * c2) / det;
        let y = (a1 * c2 - a2 * c1) / det;

        writeln!(io::stdout(), "{} {}", x, y).unwrap();
    }

}

fn print_state(result: u8) {
    writeln!(io::stdout(), "{result}").unwrap();
}

fn print_point(p: Point) {
    writeln!(io::stdout(), "{} {}", p.x, p.y).unwrap();
}

fn main() {
    let mut segment_lines: Vec<Vec<Point>> = Vec::new();

    segment_lines.push(input_points());
    segment_lines.push(input_points());

    is_intersect(&segment_lines);
}
