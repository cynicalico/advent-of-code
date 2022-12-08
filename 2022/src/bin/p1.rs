use aoc2022::common::read_lines;

fn main() {
    let lines: Vec<String> = match read_lines("res/p1.txt") {
        Ok(v) => v.into_iter().filter_map(|e| e.ok()).collect(),
        Err(e) => panic!("Failed to read input file: {}", e),
    };

    let mut v: Vec<i32> = lines.iter().fold(vec![0], |mut v, cals| {
        if cals.is_empty() {
            v.push(0);
        } else {
            *v.last_mut().unwrap() += cals.parse::<i32>().unwrap();
        }
        v
    });
    v.sort();

    let p1_ans = *v.last().unwrap();

    // Making an assumption that we have at least three elements
    let p2_ans = v[v.len()-3..].iter().sum::<i32>();

    // P1: 68442
    // P2: 204837
    println!("P1: {}\nP2: {}", p1_ans, p2_ans);
}
