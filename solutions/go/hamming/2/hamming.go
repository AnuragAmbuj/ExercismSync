package hamming

import (
	"errors"
	"strings"
)

func Distance(a, b string) (int, error) {
	var distance = 0
	if len(a) != len(b) {
		return 0, errors.New("invalid")
	} else if strings.TrimSpace(a) == "" || strings.TrimSpace(b) == "" {
		if strings.TrimSpace(a) == "" && strings.TrimSpace(b) == "" {
			return 0, nil
		}
		return 0, errors.New("invalid")
	}
	for i := range a {
		if a[i] == b[i] {
			continue
		} else {
			distance = distance + 1
		}
	}
	return distance, nil
}
