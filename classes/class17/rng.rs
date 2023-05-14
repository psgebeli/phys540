struct Rng64 { // random # gen using LCG (see .txt)
    multiplier: u64,
    increment: u64,
    state: u64
}

#[allow(dead_code)]
impl Rng64 {
    fn knuth(seed: u64) -> Rng64 {
        Rng64 { multiplier: 6364136223846793005,
                increment:  1442695040888963407,
                state:      seed }
    }
    fn lcg64(seed: u64) -> Rng64 {
        Rng64 { multiplier: 2862933555777941757, 
                increment:  1013904243,
                state:      seed }
    }
    fn new(a: u64, c: u64, seed: u64) -> Rng64 {
        Rng64 { multiplier: a, increment: c, state: seed }
    }
    fn next(&mut self) -> u64 {
        // c++ : self.state = self.multiplier*self.state + self.increment;
        self.state = self.state.wrapping_mul(self.multiplier).wrapping_add(self.increment);
        self.state
    }
    // write this method in a second pass
    fn float(&mut self) -> f64 {
        // output a fp number drawn (pseudo-)randomly
        // from the uniform distribution on [0,1)
        let bitfield = self.next();
        // s eeeeeee mmmmmmmm
        // 0 011...1 xxxx...x
        // \_______/ \______/
        //  12 bits   52 bits
        let mask = 1023_u64 << 52;
        debug_assert_eq!(mask, 1.0_f64.to_bits());
        f64::from_bits((bitfield >> 12) | mask) - 1.0
    }
}

fn main() {
    let mut r = Rng64::lcg64(1975);

    for _ in 0..100 {
        //println!("{}", r.next());
        println!("{}", r.float());
    }
}
