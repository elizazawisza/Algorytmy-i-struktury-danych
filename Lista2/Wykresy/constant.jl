using Plots

k=10
f(n)=n*log2(n)

open("statistics_3_k$k.txt") do file


  xValues = Any[]
  functionValues_2 = Any[]
  functionValues_1 = Any[]
  functionValues_12 = Any[]
  functionValues_15 = Any[]
  functionValues_13 = Any[]
  functionValues_14 = Any[]
  functionValues_135 = Any[]
  dualQuickComparisons = Any[]


  for (i, line) in enumerate(eachline(file))
    arr = split(line,", ")
    

    if arr[1]=="dual" 
      push!(dualQuickComparisons, parse(Int64,arr[3]))
    end
  end



for i in 100: 100: 10000
  for j in 1:k
    push!(xValues, i)
  end
end
  

for i in 100: 100: 10000
  for j in 1:k
    push!(functionValues_135, 1.35*f(i))
    push!(functionValues_1, 1*f(i))
    push!(functionValues_12, 1.2*f(i))
    push!(functionValues_13, 1.3*f(i))
    push!(functionValues_14, 1.4*f(i))
    push!(functionValues_15, 1.5*f(i))
    push!(functionValues_2, 2*f(i))
  end
end
  

plot(xValues,[dualQuickComparisons, functionValues_1, functionValues_12, functionValues_13, functionValues_135, functionValues_14, functionValues_15, functionValues_2],title = "Different constants", label = ["dualQuick" "1*n ln(n)" "1.2*n ln(n)" "1.3*n ln(n)" "1.35*n ln(n)" "1.4*n ln(n)" "1.5*n ln(n)" "2*n ln(n)"], lw = 1.5, xlabel = "n")
file_name = string("constant_k=$k.png")
savefig(file_name)


end

