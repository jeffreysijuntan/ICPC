
'''
def gcd(a, b):
	a, b = int(a), int(b)
	if b > a:
		b, a = a, b
	r = a % b
	if r == 0:
		return b
	return gcd(b, r)
'''
def gcd(a, b):
	if a == 0 or b == 0:
		return a + b
	return gcd(b, a%b)

def main():
	f, k = [x for x in input().split()]
	num_digits = len(f.split('.')[-1])
	f = float(f)
	k = int(k)

	diff = num_digits - k
	n1 = f * pow(10, diff)
	n2 = f * pow(10, num_digits)

	a = int(n2) - int(n1)
	b = pow(10,num_digits) - pow(10,diff)

	divisor = gcd(int(a), int(b))

	print('{}/{}'.format(a//divisor, b//divisor))

main()