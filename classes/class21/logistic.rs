use std::env;
use std::process;

fn main() {
    let args: Vec<String> = env::args().collect();
    if args.len() != 3 {
        eprintln!("Usage: logistic <initial x0> <prefactor>");
        process::exit(1);
    }

    // starting value 0 < x0 < 1
    let mut x:f64 = args[1].parse().expect("The initial x0 value");
    let prefactor:f64 = args[2].parse()
        .expect("The constant prefactor of the logistic map");

    println!("{}", x);
    for _ in 0..1000
    {
        // x_{n+1} = prefactor * x_n * (1 - x_n)
        x = prefactor*x*(1.0-x);
        println!("{}", x);
    }
}
