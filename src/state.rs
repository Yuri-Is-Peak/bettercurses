use crate::helpers::RgbCell;

#[derive(Default)]
struct ProgramFlags  {
    fullscreen: bool,
    partial: bool,
}

pub struct ProgramState  {
    pub(crate) buf: String,
    pub(crate) errbuf: String,
    pub(crate) flag: ProgramFlags,
}

impl ProgramState  {
    fn new() -> ProgramState  {
        ProgramState {
            buf: String::new(),
            flag: ProgramFlags::default(),
            errbuf: String::default(),
        }
    }

    pub fn initfullscr(&mut self) -> bool {
        if !self.flag.partial && !self.flag.fullscreen {
            self.addch(format!("{}[?1049h", ESC));
            true
        }
        else {false}
    }

    pub fn partialscr(&mut self) -> bool {
        if !self.flag.partial && !self.flag.fullscreen {
            
            true
        }
        else {false}
    }
    pub(crate) fn addch(&mut self, txt: String)  {
        self.buf += &txt;
    }

    pub fn addtxt(&mut self, x: u16, y: u16, txt: &str, col: Option<RgbCell>)  {
        if x+txt.len() as u16 <= self.maxx && x <= self.maxy {
            match col  {
                Some(col) => {
                    self.savescrsr();
                    self.movecrsr(x, y);
                    self.setcol(col);
                    self.addch(txt.to_string());

                }
                None => {
                    self.movecrsr(x, y);
                    self.addch(txt.to_string());
                }
            }
        }
        else  {
            crate::helpers::throw_err(self, "Out of bounds!");
        }
    }

    pub fn setcol(&mut self, col: RgbCell)  {
        if col.transbg  {
            self.addch(format!("{}[38;2;{};{};{}m",
                    ESC, col.f.red, col.f.green, col.f.blue));
        }
        else  {
            self.addch(format!("{}[38;2;{};{};{}m",
                ESC, col.f.red, col.f.green, col.f.blue));
            self.addch(format!("{}[48;2;{};{};{}m",
                ESC, col.b.red, col.b.green, col.b.blue));
        }
    }

    pub fn destroyscr(&mut self)  {
        if self.flag.fullscreen {
            self.addch(format!("{}[?1049l", ESC));
        }
    }

}

pub(crate) const ESC: &str = "\x1B";
