stn = input()

words = stn.split(' ')

code = ''

for w in words:
	# print(w)
	error = False
	buffer = ''
	for c in w:
		if c != 'u' and c != 'm':
			if c.isalpha(): 
				error = True
				break
		else:
			buffer += ('1' if c == 'u' else '0')

	if not error: 
		code += buffer

# print(code)
res = ''
for i in range( len(code)//7 ):
	# print( code[i*7:(i+1)*7] )
	val = int( code[i*7:(i+1)*7], 2) #- 97
	n = chr(val)#binascii.b2a_uu( val.to_bytes(7, 'big' ) )
	res += n
print(res)