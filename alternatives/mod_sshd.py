#!/usr/bin/env python3
import re
import binascii

def asm(x):
    return binascii.unhexlify(x.replace(b" ",b""))

with open("sshd", "rb") as f:
    data = f.read()
    new_data = bytearray(data)

needle1 = re.findall(b".." + asm(b"c5 4e ec c4 4e ec c4"), data)
assert len(needle1) == 1

needle1 = needle1[0]
# 40 88 28        mov byte ptr ds:[rax],bpl
# 8A 55 00        mov dl,byte ptr ss:[rbp]
replace1  = asm(b"40 88 28 8A 55 00 90 90 90")

needle2  = asm(b"0f b6 54 14 0a")
# 8A 54 15 00     mov dl,byte ptr ss:[rbp+rdx]
replace2 = asm(b"8A 54 15 00 90")

offset = data.find(needle1)
assert offset != -1
print(f"Offset 1: {hex(offset)}")
new_data[offset:offset+len(needle1)] = replace1

offset = data.find(needle2, offset)
assert offset != -1
print(f"Offset 2: {hex(offset)}")
new_data[offset:offset+len(needle2)] = replace2

with open("sshd_patch", "wb") as f:
    f.write(new_data)

print("sshd_patch created successfully")