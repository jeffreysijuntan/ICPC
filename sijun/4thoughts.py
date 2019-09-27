
import math

def main():
	table = {}
	for op1 in "+-*/":
		for op2 in "+-*/":
			for op3 in "+-*/":
				if int(op1 == '/') + int(op2 == '/') + int(op3 == '/') > 1:
					continue
				expr = "4 {} 4 {} 4 {} 4".format(op1, op2, op3)
				res = int(eval(expr))
				table[res] = expr + ' = {}'.format(res)

	for op in '+-*/':
		expr1 = '0 {} 4'.format(op)
		res1 = int(eval(expr1))
		table[res1] = '4 / 4 / 4 {} 4'.format(op) + ' = {}'.format(res1)

	print(table)

	arr = []
	num = int(input())
	
	for i in range(num):
		s = input()
		s = int(s)
		arr.append(s)

	
	for i in arr:
		if i in table:
			print(table[i])
		else:
			print('no solution')



if __name__ == "__main__":
	main()