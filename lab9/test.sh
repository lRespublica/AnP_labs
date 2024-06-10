direction="1 2"
amount="1 2 3 4 5 6 7"
sort_type="1 2 3"

for dir in $direction
do
    for am in $amount
    do
        for sort_val in $sort_type
        do
            printf "Amount: $am\n" >> "sort.log"
            printf "$dir\n$am\n$sort_val\n" | ./a.out | grep -e "We use" -e "It took" >> "sort.log"
            printf "\n\n" >> "sort.log"
        done
    done
done
