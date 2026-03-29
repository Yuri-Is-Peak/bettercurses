struct RGB  {
    red: u8,
    green: u8,
    blue: u8,
}

impl RGB  {
    fn new() -> RGB  {
        let x = RGB {
            red: 0,
            green: 0,
            blue: 0,
        }
        x
    }
}

struct RGBCell  {
    f: RGB,
    b: RGB,
}

impl RGBCell  {
    fn new() -> RGBCell {
        let x = RGBCell  {
            f: RGB::new(),
            b: RGB::new(),
        }
        x
    }
}

struct Screens  {
    real: Vec<RGBCell>,
    buf: Vec<RGBCell>,
}

impl Screens  {
    fn new() -> Screens {
        let x = Screens  {
            real: Vec::new(),
            buf: Vec::new(),
        }
        x
    }
}

struct Dimensions  {
    maxx: u16,   
    maxy: u16,   
}

impl Dimensions  {
    fn new() -> Dimensions {
        let x = Dimensions {
            maxx,
            maxy,
        }
        x
    }
}

pub struct GlobalState  {
    scr: Screens,
    dim: Dimensions,
}

impl GlobalState  {
    fn new() -> GlobalState {
        let x = GlobalState  {
            scr: Screens::new(),
            dim: Dimensions::new(),
        }
        x
    }

    fn refresh(&mut self)  {
        
    }

    fn addtxt(&mut self, x: u8, y: u8, txt: &str, &RGBCell)  {
        let mut i=0;
        while i < txt.len()  {
            // todo
 //           if self.scr.real[x*]
        }
    }

}


fn main()  {
    let mut x = GlobalState::new();
}
