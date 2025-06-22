use std::fs::read_to_string;

fn find_similarity(left_array: &Vec<u32>, right_array: &Vec<u32>) -> u32 {
    let mut similarity: u32 = 0;
    left_array.clone().into_iter().for_each(|l| {
        right_array.clone().into_iter().for_each(|r| {
            if l == r {
                similarity += l
            }
        })
    });

    return similarity;
}

fn bubble_sort(array: &mut Vec<u32>) {
    for i in 0..array.len() {
        for j in i..array.len() {
            if array[i] > array[j] {
                let temp = array[i];
                array[i] = array[j];
                array[j] = temp;
            }
        }
    }
}

fn calculate_difference(arr1: &Vec<u32>, arr2: &Vec<u32>) -> u32 {
    let mut diff: u32 = 0;
    arr1.into_iter()
        .zip(arr2.into_iter())
        .for_each(|(n1, n2)| diff += n1.abs_diff(*n2));

    return diff;
}

fn main() {
    let mut left_array = Vec::<u32>::new();
    let mut right_array = Vec::<u32>::new();

    for line in read_to_string("input.txt").unwrap().lines() {
        line.split("   ").enumerate().for_each(|(i, el)| {
            if i == 0 {
                left_array.push(el.parse::<u32>().unwrap())
            } else {
                right_array.push(el.parse::<u32>().unwrap())
            }
        });
    }

    let similarity = find_similarity(&left_array, &right_array);
    print!("Similarity: {}\n", similarity);

    bubble_sort(&mut left_array);
    bubble_sort(&mut right_array);

    let diff = calculate_difference(&left_array, &right_array);
    print!("Difference: {}", diff);
}
