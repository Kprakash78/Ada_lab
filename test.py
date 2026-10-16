import sys

# Read input safely in case the terminal has no data
values = sys.stdin.read().strip().split()

if not values:
    print("No input provided.")
    sys.exit(0)

n = int(values[0])
arr = list(map(int, values[1:1 + n]))

if len(arr) < n:
    arr.extend([0] * (n - len(arr)))

# Print the array
for i in range(n):
    print(arr[i], end=" ")

low = 0
high = n - 1
first_one = n

# Binary search: find the first index where the value is 1
while low <= high:
    mid = (low + high) // 2

    if arr[mid] == 1:
        first_one = mid
        high = mid - 1
    else:
        low = mid + 1

ones = n - first_one
zeros = first_one

print("\nTotal 1s found:", ones)
print("Total 0s found:", zeros)