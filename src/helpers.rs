use crate::state::ProgramState;

pub struct RgbCell  {
    pub f: Rgb,
    pub b: Rgb,
    pub transbg: bool,
}

struct Rgb  {
    pub red: u8,
    pub green: u8,
    pub blue: u8,
}

pub (crate) fn throw_err(state: &mut ProgramState, txt: &str)  {
    state.errbuf += &format!("{}\n", txt);
}


