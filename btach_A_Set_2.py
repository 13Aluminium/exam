def test(nums):
    s = sorted(set(nums))
    return min([[a, b] for a, b in zip(s, s[1:])], key=lambda x: x[1] - x[0])
   
nums = [1.3, 5.24, 0.89, 21.0, 5.27, 1.3]
print("List of numbers:",nums)
print("Two closest distinct numbers in the said list of numbers:")
print(test(nums))
nums = [12.02, 20.3, 15.0, 19.0, 11.0, 14.99, 17.0, 17.0, 14.4, 16.8] 
print("\nList of numbers:",nums)
print("Two closest distinct numbers in the said list of numbers:")
print(test(nums))


#que 2


def test(strs):
     return [*map(len, strs)]
strs =  ['cat', 'car', 'fear', 'center']
print("Original strings:")
print(strs)
print("Lengths of the said list of non-empty strings:")
print(test(strs))
strs =  ['cat', 'dog', 'shatter', 'donut', 'at', 'todo', '']
print("\nOriginal strings:")
print(strs)
print("Lengths of the said list of non-empty strings:")
print(test(strs))
