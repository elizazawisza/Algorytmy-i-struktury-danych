package main

import (
    "./algorithms"
    "fmt"
    . "math/rand"
    "os"
    "strconv"
    "time"
)


func generateArray(size int) []int {

    array := make([]int, size)
    Seed(time.Now().UnixNano())
    for i := 0; i < size; i++ {
        array[i] = Intn(900) - Intn(900)
    }
    return array
}

func main() {

    sortOrder := "<="
    fileName := os.Args[2]
    k, _ := strconv.Atoi(os.Args[3])
    //fmt.Println(k, fileName, sortOrder)
    file, err := os.Create(fileName)
    if err != nil {
        fmt.Println("os.Create:", err)
        return
    }
    generateQuickStatistics(k, file, sortOrder)
    //arrayToSort := generateArray(20)

}

func generateQuickStatistics(k int, file *os.File, sortOrder string) {
    var comparisons = 0
    var swaps = 0
    var sortingTime float64 = 0
    for n := 100; n <= 10000; n += 100 {
        for i := 0; i < k; i++ {
            arrayToSort := generateArray(n)
            comparisons, swaps, sortingTime = algorithms.PrepareSortProgram("quick", sortOrder, arrayToSort)
            fmt.Fprintf(file, "%s, %d, %d, %d, %f\n", "quick", n, comparisons, swaps, sortingTime)
            comparisons, swaps, sortingTime = algorithms.PrepareSortProgram("dual", sortOrder, arrayToSort)
            fmt.Fprintf(file, "%s, %d, %d, %d, %f\n", "dual", n, comparisons, swaps, sortingTime)
        }
    }
}
