pub fn reverse(input: &str) -> String {
    let mut new_input = String::from("");
    for (_i,ch) in input.chars().rev().enumerate(){
        new_input.push(ch);
    }
    return new_input;
}
