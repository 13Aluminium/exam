
odd

t = int(input())

for i in range(t):
    n, m = map(int, input().split())
    topics = list(map(int, input().split()))

    unique_topics = set(topics)  # get the unique topics among the researchers

    if len(unique_topics) == m:  # if all topics are unique, Chef can win the prize
        print("Yes")
    else:
        print("No")

        
 

