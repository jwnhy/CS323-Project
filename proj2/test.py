import os
for t in os.listdir('test'):
    if t.endswith("spl"):
        os.system(f'bin/splc test/{t} > test/{t[0:15]}.out')