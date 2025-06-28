use std::fs::read_to_string;

const PATTERN: &[u8] = b"XMAS";
const DIRS: &[(isize, isize); 8] = &[
    (0, 1),   //E
    (0, -1),  //W
    (1, 0),   //N
    (-1, 0),  //S
    (1, 1),   //NE
    (1, -1),  //NW
    (-1, 1),  //SE
    (-1, -1), //SW
];

fn count_xmas(board: &[Vec<u8>]) -> u32 {
    let n = board.len() as isize;
    let mut sum = 0;

    for ci in 0..n {
        for ri in 0..n {
            if board[ri as usize][ci as usize] != PATTERN[0] {
                continue;
            }

            for (dr, dc) in DIRS {
                if PATTERN.iter().enumerate().all(|(i, &ch)| {
                    let rr = ri + dr * i as isize;
                    let cc = ci + dc * i as isize;

                    rr >= 0 && cc >= 0 && rr < n && cc < n && board[rr as usize][cc as usize] == ch
                }) {
                    sum += 1;
                }
            }
        }
    }

    sum
}

fn count_mas(board: &[Vec<u8>]) -> u32 {
    let n = board.len();
    let mut sum = 0;
    const MAS_PATTERN: &[u8] = b"MAS";

    for ci in 1..(n - 1) {
        for ri in 1..(n - 1) {
            if board[ri][ci] != MAS_PATTERN[1] {
                continue;
            }

            //it is a bs, but it works.
            if ((board[ri - 1][ci - 1] == MAS_PATTERN[0]
                && board[ri + 1][ci + 1] == MAS_PATTERN[2])
                || (board[ri + 1][ci + 1] == MAS_PATTERN[0]
                    && board[ri - 1][ci - 1] == MAS_PATTERN[2]))
                && ((board[ri - 1][ci + 1] == MAS_PATTERN[0]
                    && board[ri + 1][ci - 1] == MAS_PATTERN[2])
                    || (board[ri + 1][ci - 1] == MAS_PATTERN[0]
                        && board[ri - 1][ci + 1] == MAS_PATTERN[2]))
            {
                sum += 1;
            }
        }
    }

    sum
}
fn main() {
    let board: Vec<Vec<u8>> = read_to_string("./input.txt")
        .expect("Can not read input")
        .trim()
        .lines()
        .map(|l| l.bytes().collect())
        .collect();

    let res = count_xmas(&board);
    let res2 = count_mas(&board);
    print!("Part 1:{res}");
    print!("Part 2:{res2}");
}
