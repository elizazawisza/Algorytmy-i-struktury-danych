package main

import (
    "./algorithms"
    "fmt"
    "os"
    "regexp"
)

func checkCorrectnessOfCommandLineArguments(args string) bool {
    matchedRegex, _ := regexp.MatchString(`--type (insert|merge|quick) --comp (>=|<=)`, args)
    if matchedRegex == true {
        return true
    } else {
        return false
    }
}

func getProgramParameters() []int{
    var size int
    var array []int
    var element int
    fmt.Println("Enter size of array to sort")
    fmt.Scanln(&size)
    for i := 0; i < size; i++ {
        fmt.Scanln(&element)
        array = append(array, element)
    }
    return array
}

func main() {
    runProgram := checkCorrectnessOfCommandLineArguments(fmt.Sprint(os.Args[1:]))
    if runProgram {
        sortAlgorithm := os.Args[2]
        sortOrder := os.Args[4]
        arrayToSort := getProgramParameters()
        algorithms.PrepareSortProgram(sortAlgorithm, sortOrder, arrayToSort)
    } else {
        fmt.Println("Given command line arguments are not correct try one more time with pattern: --type " +
            "insert|merge|quick --comp >=|<=")
    }
}
