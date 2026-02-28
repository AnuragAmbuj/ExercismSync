use std::collections::HashSet;
use std::str::Chars;

pub fn anagrams_for<'a>(word: &str, possible_anagrams: &[&'a str]) -> HashSet<&'a str> {
    let mut anagram_set = HashSet::new();
    let char_sum_word = sum_characters(word.to_lowercase().chars());
    let indexed_sum_word = find_indexed_sum(word.to_lowercase().as_str());
    for any_word in possible_anagrams {
        let char_sum_anagram = sum_characters(any_word.to_lowercase().chars());
        let indexed_sum_anagram = find_indexed_sum(any_word.to_lowercase().as_str());
        if char_sum_word == char_sum_anagram && indexed_sum_word != indexed_sum_anagram {
            anagram_set.insert(any_word.chars().as_str());
        }
    }
    return anagram_set;
}

fn find_indexed_sum(word: &str) -> usize {
    let mut indexed_char_sum = 0;

    for (i,c) in word.chars().enumerate() {
        let product = i*c as usize;
        indexed_char_sum = indexed_char_sum + product;
    }

    return indexed_char_sum;

}

fn sum_characters(ch_iter: Chars) -> usize {
    let mut char_sum = 0;
    ch_iter.for_each(|c| char_sum = char_sum + c as usize);
    char_sum
}
