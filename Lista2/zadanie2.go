package main

import (
    "./algorithms"
    "fmt"
    . "math/rand"
    "os"
    "regexp"
    "strconv"
    "time"
)

func checkCorrectnessOfCommandLineArguments2(args string) bool {
    matchedRegex, _ := regexp.MatchString(`--comp (>=|<=) --stat`, args)
    if matchedRegex == true {
        return true
    } else {
        return false
    }
}

func GenerateArray(size int) []int {

    array := make([]int, size)
    Seed(time.Now().UnixNano())
    for i := 0; i < size; i++ {
        array[i] = Intn(900) - Intn(900)
    }
    return array
}

func main() {
    runProgram := checkCorrectnessOfCommandLineArguments2(fmt.Sprint(os.Args[1:]))
    if runProgram {
        sortOrder := os.Args[2]
        fileName := os.Args[4]
        k, _ := strconv.Atoi(os.Args[5])
        //fmt.Println(k, fileName, sortOrder)
        file, err := os.Create(fileName)
        if err != nil {
           fmt.Println("os.Create:", err)
           return
        }
        generateStatistics(k, file, sortOrder)
        //arrayToSort := generateArray(20)
    } else {
        fmt.Println("Given command line arguments are not correct try one more time with pattern: --comp >=|<= " +
            "--stat fileName k")
    }
}

func generateStatistics(k int, file *os.File , sortOrder string) {
    var comparisons = 0
    var swaps = 0
    var sortingTime float64 = 0
    for n := 100; n <= 10000; n += 100 {
        for i := 0; i < k; i++ {
            arrayToSort := GenerateArray(n)
            arrayMerge := arrayToSort
            arrayInsert := arrayToSort
            arrayQuick := arrayToSort
            comparisons, swaps, sortingTime = algorithms.PrepareSortProgram("quick", sortOrder, arrayQuick)
            fmt.Fprintf(file, "%s, %d, %d, %d, %f\n", "quick",  n, comparisons, swaps, sortingTime)
            comparisons, swaps, sortingTime = algorithms.PrepareSortProgram("insert", sortOrder, arrayInsert)
            fmt.Fprintf(file, "%s, %d, %d, %d, %f\n", "insert",  n, comparisons, swaps, sortingTime)
            comparisons, swaps, sortingTime = algorithms.PrepareSortProgram("merge", sortOrder, arrayMerge)
            fmt.Fprintf(file, "%s, %d, %d, %d, %f\n", "merge",  n, comparisons, swaps, sortingTime)
        }
    }
}
