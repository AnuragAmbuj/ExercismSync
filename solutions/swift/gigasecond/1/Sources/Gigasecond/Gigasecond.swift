import Foundation

public struct Gigasecond {
    let description:String?;
    init?(from:String){
       let formatter = DateFormatter();
        formatter.dateFormat = "yyyy-MM-dd'T'HH:mm:ss";
        var date = formatter.date(from: from);
        date?.addTimeInterval(TimeInterval(1000000000))
        description = formatter.string(from: date!)
    }
}