use std::env;
use std::process;

#[allow(non_upper_case_globals)]
const dt:f64 = 0.005;    // time step
const N:u64 = 40_000;    // number of time steps
#[allow(unused_variables)]
#[allow(dead_code)]
const T:f64 = (N as f64)*dt;  // total elapsed time

#[allow(non_snake_case)]
struct VanDerPol {
    x:f64,
    v:f64,
    a:f64,
    mu:f64,
    A:f64,
    w:f64
}

#[allow(unused_variables)]
impl VanDerPol {
    fn update_verlet(&mut self, n:u64) {
        // define new positions at the next time step
        let xx = self.x + self.v*dt + 0.5*self.a*dt*dt;
        let aa = -self.x + self.mu*(1.0-self.x*self.x)*self.v + self.A*(self.w*(n as f64)*dt).sin();
        let vv = self.v + 0.5*(self.a+aa)*dt;
        self.x = xx;
        self.v = vv;
        self.a = aa;
    }
}

#[allow(non_snake_case)]
fn main() {
    // parse the command line
    let args: Vec<String> = env::args().collect();
    if args.len() != 2 && args.len() != 4 {
        eprintln!("Usage: van-der-pol <damping> [<forcing ampl> <forcing freq>]");
        process::exit(1);
    }
    let mu:f64 = args[1].parse().expect("The 'mu' model parameter");
    let forced:bool = args.len() == 4;
    let A:f64 = if forced { args[2].parse().expect("The 'A' model parameter") } else { 0.0 };
    let w:f64 = if forced { args[3].parse().expect("The 'omega' model parameter") } else { 0.0 };
    // initialize the simulation
    let mut vdp = VanDerPol { x: 1.0, v: -2.0, a: 0.0, mu: mu, A: A, w: w };
    // run the intergrator loop
    println!("# mu = {}", mu);
    for n in 0..N {
        println!("{} {} {} {}", (n as f64)*dt, vdp.x, vdp.v, vdp.a);
        vdp.update_verlet(n);
    }
    println!("");
    println!("");
}

