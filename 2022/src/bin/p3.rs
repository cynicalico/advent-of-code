use aoc2022::common::read_lines;
use std::collections::HashSet;

fn main() {
    let lines: Vec<String> = match read_lines("res/p3.txt") {
        Ok(v) => v.into_iter().filter_map(|e| e.ok()).collect(),
        Err(e) => panic!("Failed to read input file: {}", e),
    };

    let p1_ans = lines.iter().fold(0, |tot, items| {
        let (sack1, sack2) = items.split_at(items.len() / 2);

        let sack1_chars: HashSet<char> = sack1.chars().collect();
        let sack2_chars: HashSet<char> = sack2.chars().collect();
        let common_char = sack1_chars.intersection(&sack2_chars).next().unwrap();

        let ascii_val = *common_char as u32;
        let priority = if ascii_val >= 97 {
            ascii_val - 96
        } else {
            ascii_val - 38
        };

        tot + priority
    });

    let p2_ans = lines.chunks(3).fold(0, |tot, items| {
        let sack1_chars: HashSet<char> = items[0].chars().collect();
        let sack2_chars: HashSet<char> = items[1].chars().collect();
        let sack3_chars: HashSet<char> = items[2].chars().collect();

        let sets = vec![sack1_chars, sack2_chars, sack3_chars];
        // This is terrible agh
        let common_char = sets
            .iter()
            .skip(1)
            .fold(sets[0].clone(), |acc, hs| {
                acc.intersection(hs).cloned().collect()
            })
            .into_iter()
            .next()
            .unwrap();

        let ascii_val = common_char as u32;
        let priority = if ascii_val >= 97 {
            ascii_val - 96
        } else {
            ascii_val - 38
        };

        tot + priority
    });

    // P1: 7845
    // P2: 2790
    println!("P1: {}\nP2: {}", p1_ans, p2_ans);
}
