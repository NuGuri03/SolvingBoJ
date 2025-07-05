use std::io::{self, Write};

#[derive(PartialEq)]
enum Token {
    Plus,
    Minus,
    Multiply,
    Divide,
    Operand,
}

fn input_size() -> usize {
    let mut s = String::new();
    io::stdin().read_line(&mut s).unwrap();

    let n: usize = s.trim().parse().unwrap();

    n
}

fn input_expression() -> Vec<char> {
    let mut s = String::new();
    io::stdin().read_line(&mut s).unwrap();

    let postfix_expr: Vec<char> = s.trim().chars().collect();

    postfix_expr
}

fn input_operands(n: usize) -> Vec<f64> {
    let mut operands = Vec::with_capacity(n);

    for _ in 0..n {
        let mut s = String::new();
        io::stdin().read_line(&mut s).unwrap();

        let value: f64 = s.trim().parse().unwrap();
        operands.push(value);
    }

    operands
}

fn get_token(ch: char) -> Token {
    match ch {
        '+' => Token::Plus,
        '-' => Token::Minus,
        '*' => Token::Multiply,
        '/' => Token::Divide,
        _ => Token::Operand,
    }
}

fn main() {
    let mut stdout = io::stdout();

    let n = input_size();
    let postfix_expr = input_expression();
    let operand = input_operands(n);

    let mut stack: Vec<f64> = Vec::new();

    for ch in postfix_expr {
        let token = get_token(ch);

        if token == Token::Operand {
            let idx = (ch as u8 - b'A') as usize;
            stack.push(operand[idx]);
        } else {
            let op2 = stack.pop().unwrap();
            let op1 = stack.pop().unwrap();

            match token {
                Token::Plus => stack.push(op1 + op2),
                Token::Minus => stack.push(op1 - op2),
                Token::Multiply => stack.push(op1 * op2),
                Token::Divide => stack.push(op1 / op2),

                _ => panic!("Wrong!"),
            };
        }
    }

    writeln!(stdout, "{:.2}", stack.pop().unwrap()).unwrap();
}
