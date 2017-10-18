import subprocess
import re
import datetime
from matplotlib import pyplot as PLT

result_file = open('result.txt', 'w')

# n_array = ['50', '100', '200', '400', '800', '1000', '2000', '4000', '8000', '16000', '32000', '64000', '128000']
n_array = ['50', '100', '200', '400', '800', '1000']

# vs = {
#     'a': ['1', '2', '4', '8', '16', '2', '1', '1', '1', '8'],
#     'b': ['2', '2', '2', '2', '4', '1', '1', '1', '4', '4'],
#     'c': ['0', '0', '0', '0', '0', '1', '1', '1', '0', '0'],
#     'd': ['0', '0', '0', '0', '0', '0', '0', '1', '1', '8'],
#     'e': ['1', '1', '1', '1', '1', '1', '1', '1', '2', '2'],
#     'f': ['0', '0', '0', '0', '0', '0', '0', '2', '0', '0'],
# }
vs = {
    'a': ['1','2','4','8','16','2','1','1','1','8'],
    'b': ['2','2','2','2','4','1','1','1','4','4'],
    'c': ['0','0','0','0','0','1','1','1','0','0'],
    'd': ['0','0','0','0','0','0','0','1','1','8'],
    'e': ['1','1','1','1','1','1','1','1','2','2'],
    'f': ['0','0','0','0','0','0','0','2','0','0'],
}

g_array = ['0', '1', '2', '3']
# g_array = ['0', '1']

total_time_exec = []

# fig = PLT.figure()
labels = []
colors = ['red', 'blue', 'green', 'orange']

for i in range(0, 9):
    title = ['a:', vs['a'][i], 'b:', vs['b'][i], 'c:',vs['c'][i],
            'd:',vs['d'][i], 'e:',vs['e'][i], 'f:',vs['f'][i]]
    name = "-".join(title)
    title = " ".join(title)

    for g in g_array:
        # lets take advantage of g value can be a array index too
        total_time_exec.append([])

        for n in n_array:
            d = datetime.datetime.now()
            print(d)
            print("running g = " + g + " and n = " + n)
            print(title)
            print()

            # if g == 3 and n in ['2000', '4000', '8000', '16000', '32000', '64000', '128000']:
            if g == 3 and n in n_array:
                resp = "-0.1\n".encode('utf-8')
            else:
                try:
                    resp = subprocess.check_output(["./trabalho4", n, vs['a'][i], vs['b'][i], vs['c'][i], vs['d'][i], vs['e'][i], vs['f'][i], g], timeout=360)
                except:
                    resp = "-0.1\n".encode('utf-8')

            resp = resp.decode("utf-8").split("\n")
            print(resp)
            total_time_exec[int(g)].append(float(resp[0]))

        PLT.plot(n_array, total_time_exec[int(g)], 'ro', color=colors[int(g)])
        labels.append('g = ' + g)
        PLT.xlabel('N')
        PLT.ylabel('Tempo de execução (ms)')
        PLT.title(title)

    PLT.legend(labels, loc='upper left')
    PLT.xticks(range(len(total_time_exec[1])), n_array)
    # PLT.show()
    PLT.savefig(name, bbox_inches='tight')
    total_time_exec = []
    PLT.gcf().clear()

            # resp = ";".join(resp)

            # print
            # result_file.write(n + ";")
            # result_file.write(vs['a'][i] + ";" + vs['b'][i] + ";" + vs['c'][i] + ";" + vs['d'][i] + ";")
            # result_file.write(vs['e'][i] + ";" + vs['f'][i] + ";" + g + ";")
            # result_file.write(resp)
            # result_file.write("\n")
            # print(datetime.datetime.now())
            # print("\n")
            # print(resp)
