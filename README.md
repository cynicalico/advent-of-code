# advent-of-code

My solutions to [Advent of Code](https://adventofcode.com/), provided as a command line runner and input/puzzle download
tool.

## TODO

- [ ] Add support for downloading puzzle text
- [ ] Add support for submitting puzzle answers

## Usage

See `runner --help`

## Session token

You need to create a session token on the website to use the download features. This is read from the environment
variable `AOC_SESSION`. If placed in an .env file, it will be automatically loaded.

## Automation notes

This repo follows the automation guidelines on the r/adventofcode
community [wiki](https://www.reddit.com/r/adventofcode/wiki/faqs/automation]). Specifically:

- Outbound calls are throttled to every 3 minutes in `should_throttle_dl()`
- Once inputs are downloaded, they are saved to disk. An attempt to download them again will be skipped, unless
  `--force` is specified.
- The `User-Agent` header is set to `github.com/cynicalico/advent-of-code by cynicalico@pm.me`, since I'm the maintainer
  of this repo
