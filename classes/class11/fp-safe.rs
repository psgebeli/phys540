// dots make rust interpret as float
// eg 1. is 1 but a float, not an int

fn norm_unsafe(x:f64, y:f64) -> f64
{
    (x*x + y*y).sqrt()
}

fn norm(x:f64, y:f64) -> f64
{
    let xx = x.abs();
    let yy = y.abs();
    if xx > yy
    {
	let r = yy/xx;
	let one_r2 = 1. + r*r;
	xx*one_r2.sqrt()
    }else{
	let r = xx/yy;
	let one_r2 = 1. + r*r;
	yy*one_r2.sqrt()
    }
}

fn quadratic_roots_unsafe(a:f64, b:f64, c:f64) -> (f64, f64)
{
    let x = (b*b-4.*a*c).sqrt();
    let x1 = (-b+x)/(2.*a);
    let x2 = (-b-x)/(2.*a);
    (x1,x2)
}

fn quadratic_roots(a:f64, b:f64, c:f64) -> (f64, f64)
{
    let x = (b*b-4.*a*c).sqrt();
    let y = if b > 0.0 { -b-x } else { -b+x };
    let x1 = 2.*c/y;
    let x2 = y/(2.*a);
    (x1,x2)
}

fn sinc_unsafe(x:f64) -> f64
{
    x.sin()/x
}

fn sinc(x:f64) -> f64
{
    // write it as a power series
    // sinc(x) = sin(x)/x = (x-x^3/3! + x^5/5! - ...)/x = 1-x^2/6 + x^4/120 + .
    //  horner                 1-(1/6)*x^2*(1-(1/20)*x^2*(1-(1/42(*x^2))))

    let x2 = x*x;
    if x.abs() < 1.0e-6
    {
	1. - (1./6.)*x2*(1.-(1./20.)*x2*(1.-(1./42.)*x2))
    } else {
	x.sin()/x
    }
}

fn main()
{
    println!("Norm of a 2-vector:");
    for &(x,y) in [(1.0,2.0), (2.0,3.0), (3.0,4.0), (1.5e-2, 4.75e3),
		   (-1386., 29.12), (3.1e12, 4.8e13), (3.1e14, 4.8e15)].iter()
    {
	println!("|({}, {})| = ", x, y);
	println!("     {:+.16e}", norm(x,y));
	println!(" cf. {:+.16e}", norm_unsafe(x,y));
	println!("");
    }

    println!("roots of a quadratic polynomial:");
    for &(a,b,c) in [(2., -24., 70.),
		     (0.25, 258.2, 5.3),
		     (0.1, 1.177e4, 2.3e-3)].iter()
    {
	println!("{}x^2 + {}x + {} = 0", a, b, c);
	{
	    let (x1, x2) = quadratic_roots(a,b,c);
	    println!("       x1 = {}; x2 = {}", x1, x2);
	}
	{
	    
	    let (x1, x2) = quadratic_roots_unsafe(a,b,c);
            println!(" cf.   x1 = {}; x2 = {}", x1, x2);
	}
    }
    println!("Behavior of the ratio sinc(x) = sin(x)/x:");
    for &x in [0., 1.0e-12, 1.0e-6].iter()
    {
	println!("sinc({}) = ", x);
	println!("     {}", sinc(x));
	println!(" cf. {}", sinc_unsafe(x));
    }
}
