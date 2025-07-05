use std::io::{self, BufWriter, Write};
use std::f64::consts::PI;

#[derive(Clone, Copy)]
struct Circle {
    x: f64,
    y: f64,
    r: f64
}

fn get_distance(c1: &Circle, c2: &Circle) -> f64 {
    ((c1.x - c2.x).powi(2) + (c1.y - c2.y).powi(2)).sqrt()
}

fn get_theta(c1: &Circle, c2: &Circle) -> f64 {
    let d = get_distance(&c1, &c2);
    
    let cos_theta = (c1.r.powi(2) - c2.r.powi(2) + d.powi(2))
        / (2 as f64 * c1.r * d);

    cos_theta.acos()
}


fn get_overlap_area(c1: Circle, c2: Circle) -> f64 {
    let d = get_distance(&c1, &c2);
    
    if d >= c1.r + c2.r {
        // 외접 or 겹침 x
        0.0
    } else if d <= c1.r - c2.r {
        // 내접 or 포함
        c2.r.powf(2.0) * PI
    } else {
        // 부분 겹침
        let alpha = get_theta(&c1, &c2);
        let beta = get_theta(&c2, &c1);

        let area1 = c1.r.powi(2) * (alpha - alpha.sin() * alpha.cos());
        let area2 = c2.r.powi(2) * (beta - beta.sin() * beta.cos());
        
        area1 + area2
    } 

}

fn main() {
    let stdout = io::stdout().lock();
    let mut out = BufWriter::new(stdout);

    let mut s = String::new();
    io::stdin().read_line(&mut s).unwrap();

    let input: Vec<f64> = s
        .split_ascii_whitespace().take(6)
        .map(|s|s.parse::<f64>().unwrap())
        .collect();

    let mut c1 =  Circle {
        x: input[0],
        y: input[1],
        r: input[2]
    };

    let mut c2 =  Circle {
        x: input[3],
        y: input[4],
        r: input[5]
    };

    if c1.r < c2.r {
        std::mem::swap(&mut c1, &mut c2);
    }

    writeln!(out, "{:.3}", get_overlap_area(c1, c2)).unwrap();
}