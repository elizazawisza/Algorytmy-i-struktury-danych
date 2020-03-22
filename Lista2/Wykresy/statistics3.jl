using Plots

k=1000

open("statistics_3_k$k.txt") do file
  quickTime = Any[]
  quickSwaps = Any[]
  quickComparisons = Any[]
  comparisonsQuotientQuick = Any[]
  swapsQuotientQuick = Any[]


  xValues = Any[]

  dualQuickTime = Any[]
  dualQuickSwaps = Any[]
  dualQuickComparisons = Any[]
  comparisonsQuotientDualQuick = Any[]
  swapsQuotientDualQuick = Any[]



  for (i, line) in enumerate(eachline(file))
  arr = split(line,", ")
    

  if arr[1]=="quick" 
    push!(quickTime, parse(Float64, arr[5]))
    push!(quickSwaps, parse(Int64,arr[4]))
    push!(quickComparisons, parse(Int64,arr[3]))

  else
    push!(dualQuickTime, parse(Float64,arr[5]))
    push!(dualQuickSwaps, parse(Int64,arr[4]))
    push!(dualQuickComparisons, parse(Int64,arr[3]))
  end
  

end

for i in 100: 100: 10000
  for j in 1:k
    push!(xValues, i)
  end
end
  for i = 1:length(dualQuickSwaps)
    push!(swapsQuotientDualQuick, dualQuickSwaps[i]/xValues[i])
  end

  for i = 1:length(quickSwaps)
    push!(swapsQuotientQuick, quickSwaps[i]/xValues[i])
  end

  for i = 1:length(dualQuickComparisons)
    push!(comparisonsQuotientDualQuick, dualQuickComparisons[i]/xValues[i])
  end

  for i = 1:length(quickComparisons)
    push!(comparisonsQuotientQuick, quickComparisons[i]/xValues[i])
  end


plot(xValues,[dualQuickTime, quickTime],title = "Time", label = ["dualQuick" "quick"], lw = 2, xlabel = "n")
file_name = string("time_k_$k.png")
savefig(file_name)

plot(xValues,[dualQuickComparisons, quickComparisons],title = "Comparisons Avg", label = ["dualQuick" "quick"], lw = 2, xlabel = "n")
file_name = string("comparisons_k_$k.png")
savefig(file_name)


plot(xValues,[dualQuickSwaps, quickSwaps],title = "Swaps Avg", label = ["dualQuick" "quick"], lw = 2, xlabel = "n")
file_name = string("swaps_k_$k.png")
savefig(file_name)

plot(xValues,[swapsQuotientDualQuick, swapsQuotientQuick],title = "c/n", label = ["dualQuick" "quick"], lw = 2, xlabel = "n")
file_name = string("c__n_k_$k.png")
savefig(file_name)

plot(xValues,[comparisonsQuotientDualQuick, comparisonsQuotientQuick],title = "Swaps Avg", label = ["dualQuick" "quick"], lw = 2, xlabel = "n")
file_name = string("s__n_k_$k.png")
savefig(file_name)


end

