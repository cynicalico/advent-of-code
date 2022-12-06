use aoc2022::common::read_lines;
use std::collections::HashMap;

fn main() {
    // let base_points = HashMap::from([("X", 1), ("Y", 2), ("Z", 3)]);
    let rock_points = HashMap::from([("A", 3), ("B", 0), ("C", 6)]);
    let paper_points = HashMap::from([("A", 6), ("B", 3), ("C", 0)]);
    let scissors_points = HashMap::from([("A", 0), ("B", 6), ("C", 3)]);

    let Ok(lines) = read_lines("res/p2.txt") else { return };
    let p1_ans = lines
        .into_iter()
        .filter_map(|e| e.ok())
        .fold(0, |tot, round| {
            let v: Vec<&str> = round.split_ascii_whitespace().collect();
            if let [opponent, you] = v.as_slice() {
                match *you {
                    "X" => tot + 1 + rock_points[opponent],
                    "Y" => tot + 2 + paper_points[opponent],
                    "Z" => tot + 3 + scissors_points[opponent],
                    _ => unreachable!()
                }
            } else {
                panic!("Line is in wrong format: '{}'", round)
            }
        });

    // P1:
    println!("P1: {}", p1_ans);
}
