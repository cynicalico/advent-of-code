use aoc2022::common::read_lines;

fn main() {
    if let Ok(lines) = read_lines("res/p1.txt") {
        let mut v: Vec<i32> = lines.into_iter().fold(vec![0], |mut v, cals| {
            if let Ok(caln) = cals {
                if caln.is_empty() {
                    v.push(0);
                } else {
                    *v.last_mut().unwrap() += caln.parse::<i32>().unwrap();
                }
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
}
