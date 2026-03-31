use crate::state::ESC;
use crate::state::ProgramState;


impl ProgramState {

    pub fn savescrsr(&mut self) {
        self.addch(format!("{} 7", ESC));
    }

    pub fn restorecrsr(&mut self)  {
        self.addch(format!("{} 8", ESC));
    }


    pub fn movecrsr(&mut self, x: u16, y: u16)  {
        self.addch(format!("{}[{};{}H", ESC, y, x));
    }
    
}
