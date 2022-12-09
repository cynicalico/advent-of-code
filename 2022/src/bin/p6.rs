use aoc2022::common::read_lines;

fn main() {
    let lines: Vec<String> = match read_lines("res/p6.txt") {
        Ok(v) => v.into_iter().filter_map(|e| e.ok()).collect(),
        Err(e) => panic!("Failed to read input file: {}", e),
    };
    let signal: Vec<char> = lines[0].chars().collect();

    let p1_ans = find_unique_character_seq(&signal, 4);
    let p2_ans = find_unique_character_seq(&signal, 14);

    // P1: 1920
    // P2: 2334
    println!("P1: {}\nP2: {}", p1_ans, p2_ans);
}

fn find_unique_character_seq(s: &Vec<char>, seq_len: usize) -> usize {
    for i in 0..s.len() - seq_len {
        if !has_duplicates(&s[i..i + seq_len]) {
            return i + seq_len;
        }
    }
    unreachable!()
}

fn has_duplicates(s: &[char]) -> bool {
    (1..s.len()).any(|i| s[i..].contains(&s[i - 1]))
}
