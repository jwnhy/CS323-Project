import os

for i in range(0, 12):
    os.system(f"./jp.out test/test_1_r{str(i+1).zfill(2)}.spl > out/{str(i+1).zfill(2)}.out")
    os.system(f"diff test/test_1_r{str(i+1).zfill(2)}.out out/{str(i+1).zfill(2)}.out")
