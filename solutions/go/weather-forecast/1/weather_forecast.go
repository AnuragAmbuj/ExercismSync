// Package weather provides tools to get the weather forecast
// for a location.
package weather

// CurrentCondition represents current weather condition in a location.
var CurrentCondition string

// CurrentLocation represents the current city.
var CurrentLocation string

// Forecast takes in city and its weather condition in as a string and returns
// them combined with '- current weather condition:' concatenated between the two.
func Forecast(city, condition string) string {
	CurrentLocation, CurrentCondition = city, condition
	return CurrentLocation + " - current weather condition: " + CurrentCondition
}
