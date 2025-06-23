use itertools::Itertools;
use std::fs::read_to_string;

fn is_valid(levels: &[i32]) -> bool {
    let is_increasing: bool = if levels[1] - levels[0] > 0 {
        true
    } else {
        false
    };

    for i in 0..levels.len() - 1 {
        let diff: i32 = levels[i + 1] - levels[i];
        if is_increasing && (diff < 1 || diff > 3) {
            return false;
        } else if !is_increasing && (diff < -3 || diff > -1) {
            return false;
        }
    }

    return true;
}

fn is_safe_part_1(levels: &[i32]) -> i32 {
    is_valid(levels) as i32
}

fn is_safe_part_2(levels: &[i32]) -> i32 {
    if is_valid(levels) {
        return 1;
    }

    levels
        .iter()
        .cloned()
        .combinations(levels.len() - 1)
        .any(|comb| is_valid(&comb)) as i32
}

fn main() {
    let reports: Vec<Vec<i32>> = read_to_string("./input.txt")
        .expect("Can not read the file")
        .lines()
        .map(|line| {
            line.split(" ")
                .map(|n| n.parse::<i32>().expect("Can not parse"))
                .collect()
        })
        .collect();

    let mut safe = reports
        .iter()
        .map(|r| is_safe_part_1(r))
        .sum::<i32>();

    print!("Part1 Safe amount: {}\n", safe);

    safe = reports
        .iter()
        .map(|r| is_safe_part_2(r))
        .sum::<i32>();

    print!("Part2 Safe amount: {}", safe);
}
