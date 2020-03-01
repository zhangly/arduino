import hashlib
import os
print(os.getcwd())

f = open('git/pysha256.py', 'rb')

sh = hashlib.sha256()
sh.update(f.read())
print(sh.hexdigest())
print(sh.hexdigest() == 'e5d83e52841681387f1c9bec07d46f9d725b44092bf6de9374788144c99fdcb8')

f.close()
 