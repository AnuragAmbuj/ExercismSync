//`Two-fer` or `2-fer` is short for two for one. One for you and
//one for me. Package contains method to display this.
package twofer

//Given a name, the method returns a string with the message:
//One for <name> and one for me.
//Fore an empty name it defaults name as 'you'
func ShareWith(name string) string {
	if name == "" {
		name = "you"
	}
	return "One for " + name + ", one for me."
}
