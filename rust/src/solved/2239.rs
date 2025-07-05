use std::io;

static BOARD_SIZE: usize = 9;
static mut FOUND: bool = false;

fn create_board() -> Vec<Vec<u8>> {
    let mut board: Vec<Vec<u8>> = vec![vec![0u8; BOARD_SIZE]; BOARD_SIZE];

    for i in 0..BOARD_SIZE {
        let mut s = String::new();
        io::stdin().read_line(&mut s).unwrap();
        let s = s.trim();

        for (j, ch) in s.chars().enumerate() {
            let num = ch.to_digit(10).unwrap() as u8;
            board[i][j] = num;
        }
    }

    board
}

fn is_full(b: &Vec<Vec<u8>>) -> bool {
    for i in 0..BOARD_SIZE {
        for j in 0..BOARD_SIZE {
            if b[i][j] == 0 {
                return false;
            }
        }
    }
    true
}

fn solve_sudoku(b: &mut Vec<Vec<u8>>) {
    unsafe {
        if FOUND {
            return;
        }
    }

    if is_full(b) {
        unsafe {
            FOUND = true;
        }
        return;
    }

    for i in 0..BOARD_SIZE {
        for j in 0..BOARD_SIZE {
            if b[i][j] != 0 {
                continue;
            }

            let mut marked_number = vec![false; 10];

            // check row
            for k in 0..BOARD_SIZE {
                let val = b[i][k];
                if val != 0 {
                    marked_number[val as usize] = true;
                }
            }

            // check col
            for k in 0..BOARD_SIZE {
                let val = b[k][j];
                if val != 0 {
                    marked_number[val as usize] = true;
                }
            }

            // check rect
            let start_i = i - i % 3;
            let start_j = j - j % 3;
            for di in 0..3 {
                for dj in 0..3 {
                    let val = b[start_i + di][start_j + dj];
                    if val != 0 {
                        marked_number[val as usize] = true;
                    }
                }
            }

            // back tracking
            for num in 1..=9 {
                if !marked_number[num] {
                    b[i][j] = num as u8;

                    solve_sudoku(b);

                    unsafe {
                        if FOUND {
                            return;
                        }
                    }

                    b[i][j] = 0;
                }
            }

            return;
        }
    }
}

fn main() {
    let mut board = create_board();

    solve_sudoku(&mut board);

    for row in &board {
        for ele in row {
            print!("{ele}");
        }
        println!();
    }
}
