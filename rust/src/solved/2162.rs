use std::io;
use std::mem::swap;

#[derive(Clone, Copy, Debug)]
struct Point {
    x: i64,
    y: i64
}

impl Point {
    fn is_lower(&self, p: &Point) -> bool {
        self.x < p.x || (self.x == p.x && self.y <= p.y)
    }
    fn is_greater(&self, p: &Point) -> bool {
        self.x > p.x || (self.x == p.x && self.y > p.y)
    }
}

fn input_usize() -> usize {
    let mut s = String::new();
    io::stdin().read_line(&mut s).unwrap();

    let n = s.trim().parse().unwrap();

    n
}

fn input_points() -> Vec<Point> {
    let mut s = String::new();
    io::stdin().read_line(&mut s).unwrap();

    let p: Vec<i64> = s
        .split_ascii_whitespace()
        .take(4)
        .map(|s|s.parse().unwrap())
        .collect();

    vec![Point { x: p[0], y: p[1] }, Point { x: p[2], y: p[3] }]
}

fn ccw(a: &Point, b: &Point, c: &Point) -> i32 {
    let num = (b.x - a.x) * (c.y - a.y) - (c.x - a.x) * (b.y - a.y);

    match num {
        x if x > 0 => 1,
        x if x ==0 => 0,
        x if x < 0 => -1,

        _ => panic!("Error!")
    }
}

fn is_intersect(p1: Point, p2: Point, p3: Point, p4: Point) -> bool {
    
    let p1p2 = ccw(&p1, &p2, &p3) * ccw(&p1, &p2, &p4);
    let p3p4 = ccw(&p3, &p4, &p1) * ccw(&p3, &p4, &p2);

    if p1p2 == 0 && p3p4 == 0 {

        let (mut a1, mut a2) = (p1, p2);
        let (mut b1, mut b2) = (p3, p4);

        if a1.is_greater(&a2) {
            swap(&mut a1, &mut a2);
        }
        if b1.is_greater(&b2) {
            swap(&mut b1, &mut b2);
        }

        return a1.is_lower(&b2) && b1.is_lower(&a2);
    }

    p1p2 <= 0 && p3p4 <= 0
}

fn find_group(group: &mut Vec<usize>, x: usize) -> usize {
    if group[x] != x {
        group[x] = find_group(group, group[x]);
    }
    group[x]
}

fn union_group(group: &mut Vec<usize>, x: usize, y: usize) {
    let px = find_group(group, x);
    let py = find_group(group, y);

    if px != py {
        group[py] = px; 
    }
}

fn main() {
    let n = input_usize();

    let mut lines: Vec<Vec<Point>> = Vec::new();
    for _ in 0..n {
        lines.push(input_points());
    }

    let mut group: Vec<usize> = (0..n).collect();


    for i in 0..n {
        for j in i+1..n {
            if is_intersect(lines[i][0], lines[i][1], lines[j][0], lines[j][1]) {
                union_group(&mut group, i, j);
            }            
        }
    }

    let mut count_map = std::collections::HashMap::new();
    for i in 0..n {
        let root = find_group(&mut group, i);
        *count_map.entry(root).or_insert(0) += 1;
    }

    let group_count = count_map.len();
    let max_group_size = count_map.values().max().unwrap();
    
    println!("{group_count}\n{max_group_size}");
}