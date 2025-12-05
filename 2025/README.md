# AoC 2025

I decided to AoC in C++ this year, because despite it being my primary programming language, I haven't really used it
for AoC at all.

## Problem Status

- [x] Day 1 — straightforward solution, no special tricks
- [x] Day 2 — regex too powerful (kind of slow from all the int→string conversions, but it can't be helped)
    - [Original solution](https://github.com/cynicalico/advent-of-code/blob/f8fcb9512a4e39faaa0343894717cc9f7bd9d8ea/2025/solutions/day02.cpp)
      with regex rewritten to instead generate numbers instead of brute force validating.
- [x] Day 3 — first, you select the *most* significant digit, then the *second* most, then the *third* most...
- [x] Day 4 — parsed input to a grid of count of adjacent rolls, did naive loop for part 2, but it's fast enough
- [x] Day 5 — combined ranges as much as possible, then just checked every range; could do binary search but N is small
  here so it doesn't matter
- [ ] Day 6 — not released
- [ ] Day 7 — not released
- [ ] Day 8 — not released
- [ ] Day 9 — not released
- [ ] Day 10 — not released
- [ ] Day 11 — not released
- [ ] Day 12 — not released

## Thoughts

If I have any particular thoughts about any of the problems, I'll put them here.
