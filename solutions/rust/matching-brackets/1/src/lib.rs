pub fn brackets_are_balanced(string: &str) -> bool {
    let mut vec:Vec<char> = Vec::new();
    for c in string.chars() {
        match c {
            '[' | '{' | '(' => vec.push(c),
            ']' => {
                let char_popped = vec.pop();
                if char_popped.is_none() || char_popped.unwrap()!='['{
                    return false;
                }
            },
            '}' => {
                let char_popped = vec.pop();
                if char_popped.is_none() || char_popped.unwrap()!='{'{
                    return false;
                }
            }
            ')' => {
                let char_popped = vec.pop();
                if char_popped.is_none() || char_popped.unwrap()!='('{
                    return false;
                }
            }
            _ => {}
        }
    }
    return vec.is_empty();
}
