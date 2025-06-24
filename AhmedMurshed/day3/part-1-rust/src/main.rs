use regex::Regex;
use std::fs;

fn main() {
    let re = Regex::new(r"mul\((?P<num1>\d{1,3}),(?P<num2>\d{1,3})\)").unwrap();

    let hay = fs::read_to_string(std::env::args().skip(1).next().unwrap()).unwrap();
    let sum = re
        .captures_iter(&hay)
        .map(|caps| {
            let num1 = caps["num1"].parse::<u32>().unwrap();
            let num2 = caps["num2"].parse::<u32>().unwrap();
            num1 * num2
        })
        .sum::<u32>();

    println!("{sum}");
}
