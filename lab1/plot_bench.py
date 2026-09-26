import matplotlib.pyplot as plt

# файл bench.txt: строки вида "потоков n интеграл время"
filename = "bench.txt"

threads = []
time = []

with open(filename, "r") as f:
  for line in f:
    line = line.strip()
    if not line:
      continue
    parts = line.split()
    t = int(parts[0])
    dt = float(parts[3])
    threads.append(t)
    time.append(dt)

# сортируем по числу потоков на случай, если строки шли не по порядку
pairs = sorted(zip(threads, time))
threads = [p[0] for p in pairs]
time = [p[1] for p in pairs]

plt.figure(figsize=(8, 5))
plt.plot(threads, time, marker="o")
plt.xlabel("число потоков")
plt.ylabel("время расчета, сек")
plt.title("Масштабируемость OpenMP-программы")
plt.grid(True)
plt.xticks(threads)


plt.show()

