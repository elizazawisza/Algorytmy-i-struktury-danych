using Plots

k = 1000

open("statistics_k$k.txt") do file


  quickTime = Any[]
  quickSwaps = Any[]
  quickComparisons = Any[]

  insertTime = Any[]
  insertSwaps = Any[]
  insertComparisons = Any[]

  mergeTime = Any[]
  mergeSwaps = Any[]
  mergeComparisons = Any[]

  xValues = Any[]
  swapsQuotientMerge = Any[]
  swapsQuotientInsert = Any[]
  swapsQuotientQuick = Any[]

  comparisonsQuotientMerge = Any[]
  comparisonsQuotientInsert = Any[]
  comparisonsQuotientQuick = Any[]

  for (i, line) in enumerate(eachline(file))
  arr = split(line,", ")
    

  if arr[1]=="insert" 
    push!(insertTime, parse(Float64, arr[5]))
    push!(insertSwaps, parse(Int64,arr[4]))
    push!(insertComparisons, parse(Int64,arr[3]))

  elseif arr[1]=="quick" 
    push!(quickTime, parse(Float64,arr[5]))
    push!(quickSwaps, parse(Int64, arr[4]))
    push!(quickComparisons, parse(Int64,arr[3]))
  else
    push!(mergeTime, parse(Float64,arr[5]))
    push!(mergeSwaps, parse(Int64,arr[4]))
    push!(mergeComparisons, parse(Int64,arr[3]))
  end
  

end


  for i in 100: 100: 10000
    for j in 1:k
      push!(xValues, i)
    end
  end


  for i = 1:length(mergeSwaps)
    push!(swapsQuotientMerge, mergeSwaps[i]/xValues[i])
  end

  for i = 1:length(insertSwaps)
    push!(swapsQuotientInsert, insertSwaps[i]/xValues[i])
  end

  for i = 1:length(quickSwaps)
    push!(swapsQuotientQuick, quickSwaps[i]/xValues[i])
  end


  for i = 1:length(mergeComparisons)
    push!(comparisonsQuotientMerge, mergeComparisons[i]/xValues[i])
  end

  for i = 1:length(insertComparisons)
    push!(comparisonsQuotientInsert, insertComparisons[i]/xValues[i])
  end

  for i = 1:length(quickComparisons)
    push!(comparisonsQuotientQuick, quickComparisons[i]/xValues[i])
  end


plot(xValues,[mergeTime, insertTime, quickTime],title = "Time", label = ["merge" "insert" "quick"], lw = 2, xlabel = "n")
file_name = string("time_k_$k.png")
savefig(file_name)

plot(xValues,[mergeComparisons, insertComparisons, quickComparisons],title = "Comparisons Avg", label = ["merge" "insert" "quick"], lw = 2, xlabel = "n")
file_name = string("comparisons_k_$k.png")
savefig(file_name)


plot(xValues,[mergeSwaps, insertSwaps, quickSwaps],title = "Swaps Avg", label = ["merge" "insert" "quick"], lw = 2, xlabel = "n")
file_name = string("swaps_k_$k.png")
savefig(file_name)

plot(xValues,[swapsQuotientMerge, swapsQuotientInsert, swapsQuotientQuick],title = "s/n", label = ["merge" "insert" "quick"], lw = 2, xlabel = "n")
file_name = string("s__n_k_$k.png")
savefig(file_name)

plot(xValues,[comparisonsQuotientMerge, comparisonsQuotientInsert, comparisonsQuotientQuick],title = "c/n", label = ["merge" "insert" "quick"], lw = 2, xlabel = "n")
file_name = string("c__n_k_$k.png")
savefig(file_name)


end

