//Solution goes in Sources
struct Year{
    var calendarYear:Int16;
    var isLeapYear:Bool;
    init(calendarYear:Int16){
        self.calendarYear = calendarYear;
        isLeapYear = isLeap(year: calendarYear);
    }
}

func isLeap(year:Int16)->Bool {
    if year%4==0 {
        if year%100==0 {
            if year%400==0 {
                return true;
            }
            return false;
        }
        return true;
    }
    return false;
}

