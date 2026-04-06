use std::fmt::{Display, Formatter, Debug};
use std::fmt;

#[derive(PartialEq,Debug)]
pub struct Clock {
    hrs:i32,
    min:i32
}

impl Clock {

    pub fn new(hours: i32, minutes: i32) -> Self {
        let mut_hrs = hours;
        let mut_min = minutes;

        let (mut_hrs,mut_min) = handle_invalid_time(mut_hrs,mut_min);

        return Clock{
            hrs:mut_hrs,
            min:mut_min
        }
    }

    pub fn add_minutes(self, minutes: i32) -> Self {
        let minute = self.min + minutes;
        return Clock::new(self.hrs,minute);
    }
}

fn handle_invalid_time(mut hr: i32, mut min: i32) -> (i32, i32) {
    if min < 0 {
        let subtract_hours = min.abs()/60 + 1;
        min = 60 + min%60;
        if hr > 0 {
            hr = hr - subtract_hours;
        }else{
            hr = 24 + hr - subtract_hours;
        }
    }
    if min>=60 {
        let addable_hours =  min/60;
        min = min%60;
        if hr >= 0 {
            hr = hr + addable_hours;
        }else {
            hr = 24 + hr + addable_hours;
        }
    }
    if hr < 0{
        hr = 24 + hr%24;
    }
    if hr >= 24 {
        hr = hr % 24;
    }
    (hr,min)
}

impl Display for Clock {
    fn fmt(&self, f: &mut Formatter) -> fmt::Result {
        write!(f,"{:0>2}:{:0>2}",self.hrs,self.min)
    }
}