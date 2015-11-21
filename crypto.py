import random

def stypr_encrypt(d):
	try:
		k = random.randint(1, 1024)
		n = 0
		f = ""
		for i in range(len(d)):
			n += 1
			c = (n * n) ^ 0x3E
			f += ("00000" + hex(int(oct(ord(d[i]) ^ (k ^ 0xAFE43 ^ 0x399AA3 ^ c))))[2:])[-6:]
		f = (("000" + hex(k ^ 0xA9F ^ 0xE77E)[2:])[-4:] + f)[::-1].upper()
		return f
	except:
		return -1

def stypr_decrypt(d):
	try:
		e = d[::-1]
		k = int(e[:4], 16) ^ 0xA9F ^ 0xE77E
		t = e[4:]
		f = ""
		n = 0
		for i in range(0, len(t), 6):
			n += 1
			c = (n * n) ^ 0x3E
			# $tmp = $tmp . chr(octdec(hexdec(substr($Temps, $i, 6))) ^ ($MyKey ^ hexdec("AFE43") ^ hexdec("399AA3") ^ $cal));
			f += chr(int(str(int(t[i:i+6], 16)), 8) ^ (k ^ 0xAFE43 ^ 0x399AA3 ^ c))
		return f
	except:
		return -1

print(stypr_encrypt(__import__("sys").argv[1]))
