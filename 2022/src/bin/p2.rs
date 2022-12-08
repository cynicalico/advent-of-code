use aoc2022::common::read_lines;
use std::collections::HashMap;

fn main() {
    let lines: Vec<String> = match read_lines("res/p2.txt") {
        Ok(v) => v.into_iter().filter_map(|e| e.ok()).collect(),
        Err(e) => panic!("Failed to read input file: {}", e),
    };

    let rock_points = HashMap::from([("A", 3), ("B", 0), ("C", 6)]);
    let paper_points = HashMap::from([("A", 6), ("B", 3), ("C", 0)]);
    let scissors_points = HashMap::from([("A", 0), ("B", 6), ("C", 3)]);

    let win_points = HashMap::from([("A", 2), ("B", 3), ("C", 1)]);
    let draw_points = HashMap::from([("A", 1), ("B", 2), ("C", 3)]);
    let lose_points = HashMap::from([("A", 3), ("B", 1), ("C", 2)]);

    let (p1_ans, p2_ans) = lines.iter().fold((0, 0), |(p1_tot, p2_tot), round| {
        let v: Vec<&str> = round.split_ascii_whitespace().collect();
        if let [opponent, you] = v.as_slice() {
            (
                match *you {
                    "X" => p1_tot + 1 + rock_points[opponent],
                    "Y" => p1_tot + 2 + paper_points[opponent],
                    "Z" => p1_tot + 3 + scissors_points[opponent],
                    _ => unreachable!(),
                },
                match *you {
                    "X" => p2_tot + 0 + lose_points[opponent],
                    "Y" => p2_tot + 3 + draw_points[opponent],
                    "Z" => p2_tot + 6 + win_points[opponent],
                    _ => unreachable!(),
                },
            )
        } else {
            panic!("Line is in wrong format: '{}'", round)
        }
    });

    // P1: 15523
    // P2: 15702
    println!("P1: {}\nP2: {}", p1_ans, p2_ans);
}
