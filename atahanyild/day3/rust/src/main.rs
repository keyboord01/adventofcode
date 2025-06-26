use std::fs::read_to_string;

use regex::Regex;

fn run_instructions(hs: &str) -> i32 {
    let re = Regex::new(r"mul\(([0-9]{1,3}),([0-9]{1,3})\)").unwrap();

    re.captures_iter(&hs)
        .map(|c| {
            let (_, [num1, num2]) = c.extract::<2>();
            let a: i32 = num1.parse().unwrap();
            let b: i32 = num2.parse().unwrap();
            a * b
        })
        .sum::<i32>()
}

fn run_enabled_instructions(hs: &str) -> i32 {
    let mut enabled = true;
    let mut sum: i32 = 0;

    let re = Regex::new(r"do\(\)|don't\(\)|mul\(([0-9]{1,3}),([0-9]{1,3})\)").unwrap();

    for ele in re.captures_iter(hs) {
        match ele.get(0).unwrap().as_str() {
            "do()" => enabled = true,
            "don't()" => enabled = false,
            _ => {
                if enabled {
                    sum += ele.get(1).unwrap().as_str().parse::<i32>().unwrap()
                        * ele.get(2).unwrap().as_str().parse::<i32>().unwrap()
                }
            }
        }
    }

    sum
}

fn main() {
    let hs = read_to_string("./input.txt").expect("Error reading the input");

    let sum = run_instructions(&hs);
    println!("Sum of all multiplications: {}", sum);

    let sum2: i32 = run_enabled_instructions(&hs);
    println!("Sum of all multiplications part 2: {}", sum2);
}

#[cfg(test)]
mod tests {
    use super::*;
    use crate::run_instructions;

    #[test]
    fn test_part1() {
        let hs = "xmul(2,4)%&mul[3,7]!@^do_not_mul(5,5)+mul(32,64]then(mul(11,8)mul(8,5))";
        assert_eq!(161, run_instructions(&hs));
    }

    #[test]
    fn test_part2() {
        let hs = "xmul(2,4)&mul[3,7]!^don't()_mul(5,5)+mul(32,64](mul(11,8)undo()?mul(8,5))";
        assert_eq!(48, run_enabled_instructions(&hs))
    }
}
