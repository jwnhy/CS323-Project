import os
for t in os.listdir('test-ex'):
    if t.endswith("spl"):
        os.system(f'bin/splc test-ex/{t}')
