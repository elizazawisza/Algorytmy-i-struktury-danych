package algorithms

import (
    "fmt"
    "time"
)

var comparisons int
var swaps int

func checkCorrectness(array []int, descending bool, duration float64) (int, int, float64) {
    var isError bool
    if descending {
        for i := 0; i < len(array)-1; i++ {
            if array[i] < array[i+1] {
                isError = true
            }
        }
    } else {
        for i := 0; i < len(array)-1; i++ {
            if array[i] > array[i+1] {
                isError = true
            }
        }
    }
    if !isError {
        fmt.Print("Sorted array: ")
        fmt.Println(array)
        fmt.Print("Size of elements: ")
        fmt.Println(len(array))
    }
    return comparisons, swaps, duration
}

func PrepareSortProgram(sortAlgorithm string, sortOrder string, array []int) (int, int, float64) {
    comparisons = 0
    swaps = 0
    var start time.Time
    var end time.Time
    var descendingOrder bool
    var sortedArray []int
    switch sortOrder {
    case "<=":
        descendingOrder = true
    case ">=":
        descendingOrder = false
    }
    switch sortAlgorithm {
    case "insert":
        start = time.Now()
        sortedArray = insertionSort(array, descendingOrder)
        end = time.Now()
    case "merge":
        start = time.Now()
        sortedArray = mergeSort(array, descendingOrder)
        end = time.Now()
    case "quick":
        start = time.Now()
        sortedArray = quickSort(array, 0, len(array)-1, descendingOrder)
        end = time.Now()
    case "dual":
        start = time.Now()
        dualQuickSort(array, 0, len(array)-1)
        sortedArray = array
        end = time.Now()
    }
    duration := end.Sub(start).Seconds()
    return checkCorrectness(sortedArray, descendingOrder, duration)
}

func insertionSort(array []int, descending bool) []int {
    n := len(array)
    for i := 1; i < n; i++ {
        j := i
        for j > 0 {
            if descending {
                comparisons++
                //fmt.Fprintln(os.Stderr, array[j-1], "<", array[j], "?")
                if array[j-1] < array[j] {
                    //fmt.Fprintln(os.Stderr, "swap ", array[j-1], " ", array[j])
                    array[j-1], array[j] = array[j], array[j-1]
                    swaps++
                }
            } else {
                comparisons++
                //fmt.Fprintln(os.Stderr, array[j-1], ">", array[j], "?")
                if array[j-1] > array[j] {
                    //fmt.Fprintln(os.Stderr, "swap ", array[j-1], " ", array[j])
                    array[j-1], array[j] = array[j], array[j-1]
                    swaps++
                }
            }
            j--
        }
    }
    return array
}

func mergeSort(array []int, descending bool) []int {
    size := len(array)

    if size == 1 {
        return array
    }

    middle := int(size / 2)
    left := make([]int, middle)
    right := make([]int, size-middle)
    copy(left, array[:middle])
    copy(right, array[middle:])
    return merge(mergeSort(left, descending), mergeSort(right, descending), descending)
}

func merge(left, right []int, descendingOrder bool) []int {
    result := make([]int, len(left)+len(right))
    index := 0
    for len(left) > 0 && len(right) > 0 {
        if descendingOrder {
            comparisons++
            //fmt.Fprintln(os.Stderr, left[0], ">", right[0], "?")
            if left[0] > right[0] {
                result[index] = left[0]
                left = left[1:]
            } else {
                result[index] = right[0]
                right = right[1:]
            }

        } else {
            comparisons++
            //fmt.Fprintln(os.Stderr, left[0], "<", right[0], "?")
            if left[0] < right[0] {
                result[index] = left[0]
                left = left[1:]
            } else {
                result[index] = right[0]
                right = right[1:]
            }
        }
        swaps++
        index++
    }
    for j := 0; j < len(left); j++ {
        result[index] = left[j]
        swaps++
        index++
    }
    for j := 0; j < len(right); j++ {
        result[index] = right[j]
        swaps++
        index++
    }
    return result
}

func partition(array []int, low int, high int, descending bool) int {
    pivot := array[high]
    i := low - 1
    for j := low; j < high; j++ {
        if descending {
            comparisons++
            //fmt.Fprintln(os.Stderr, array[j], ">", pivot, "?")
            if array[j] > pivot {
                i++
                swaps++
                //fmt.Fprintln(os.Stderr, "swap ", array[i], " ", array[j])
                array[i], array[j] = array[j], array[i]
            }
        } else {
            comparisons++
            //fmt.Fprintln(os.Stderr, array[j], "<", pivot, "?")
            if array[j] < pivot {
                i++
                swaps++
                //fmt.Fprintln(os.Stderr, "swap ", array[i], " ", array[j])
                array[i], array[j] = array[j], array[i]
            }
        }

    }
    swaps++
    array[i+1], array[high] = array[high], array[i+1]

    return i + 1
}

func quickSort(array []int, low int, high int, descending bool) []int {
    if low < high {
        q := partition(array, low, high, descending)
        quickSort(array, low, q-1, descending)
        quickSort(array, q+1, high, descending)
    }
    return array
}

func dualQuickSort(array []int, left int, right int) {
    p, q := 0, 0
    if right <= left {
        return
    }
    if array[right] < array[left] {
        p = array[right]
        q = array[left]
        comparisons++
    } else {
        p = array[left]
        q = array[right]
        comparisons++
    }
    i := left + 1
    k := right - 1
    j := i
    d := 0

    for j <= k {
        if d >= 0 {
            if array[j] < p{
                comparisons++
                array[i], array[j] = array[j], array[i]
                swaps++
                i += 1
                j += 1
                d += 1
            }else{
                if array[j] < q{
                    comparisons++
                    j += 1
                }else{
                    array[j], array[k] = array[k], array[j]
                    comparisons++
                    swaps++
                    k -= 1
                    d -= 1
                }
            }
        }else {
            if array[k] > q{
                comparisons++
                k -= 1
                d -= 1
            }else{
                if array[k] < p{
                    temp := array[k]
                    array[k] = array[j]
                    array[j] = array[i]
                    array[i] = temp
                    i += 1
                    d += 1
                    swaps++
                    comparisons++
                }else{
                    array[j], array[k] = array[k], array[j]
                    comparisons++
                    swaps++
                }
            }
            j += 1
        }
    }

    array[left] = array[i - 1]
    array[i - 1] = p
    array[right] = array[k + 1]
    array[k + 1] = q

    dualQuickSort(array, left, i - 2)
    dualQuickSort(array, i, k)
    dualQuickSort(array, k + 2, right)
}
