use std::fs;
use std::io::{self, Read};

fn main() {
    let text = fs::read_to_string("triangle.txt");

    let numbers: Vec<i32> = text
        .unwrap()
        .split_whitespace()
        .map(|s| s.parse::<i32>().expect("invalid integer")) // panic on bad data
        .collect();

    for num in numbers.iter() {
        println!("{num}");
    }
}
