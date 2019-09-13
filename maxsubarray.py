def maxSubArray(nums, k):
	# write your code here
	#mustTheLast[i][j] repesent the number i of nums must be the last number in the j-th subarrays.
	#notTheLast[i][j] repesent the number i of nums can be the last number in the j-th subarrays or not.
	n = len(nums)
	mustTheLast = [[-1e9 for i in range(k+1)] for j in range(n+1)]
	notTheLast = [[-1e9 for i in range(k+1)] for j in range(n+1)]
	mustTheLast[0][0] = 0
	notTheLast[0][0] = 0
	for i in range(1, n+1):
	    mustTheLast[i][0] = 0
	    notTheLast[i][0] = 0
	    for j in range(1, k+1):
	        mustTheLast[i][j] = max(notTheLast[i-1][j-1] + nums[i-1], mustTheLast[i-1][j] + nums[i-1])
	        notTheLast[i][j] = max(mustTheLast[i][j], notTheLast[i-1][j])
	return notTheLast[n][k]


nk = input().split()
n, k = int(nk[0]), int(nk[1])
nums = [int(x) for x in input().split()]
print(maxSubArray(nums, k))