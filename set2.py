
even

# taking input for the number of test cases
t = int(input())

for _ in range(t):
    # taking input for the number of people and the minimum percentage of vaccinated people
    n, p = map(int, input().split())
    
    # taking input for the ages of the people
    ages = list(map(int, input().split()))
    
    # variables to keep track of the count of vaccinated and unvaccinated people
    vaccinated = 0
    unvaccinated = 0
    
    # calculating the count of vaccinated and unvaccinated people
    for age in ages:
        if age >= 80 or age <= 9:
            vaccinated += 1
        else:
            unvaccinated += 1
            
    # calculating the minimum number of days required to vaccinate minimum percentage of people
    min_days = (vaccinated // p) + (1 if vaccinated % p != 0 else 0)
    min_days += (unvaccinated // p) + (1 if unvaccinated % p != 0 else 0)
    
    # printing the result
    print(min_days)
