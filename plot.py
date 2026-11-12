import matplotlib.pyplot as plt

# Charger les données du premier fichier
data1 = {'NumEntries': [], 'Time': []}
with open("tree-rn/debug/temps_insertion.txt", "r") as file1:
    next(file1)  # Ignorer l'en-tête
    for line in file1:
        num_entries, time = line.strip().split(' ')
        data1['NumEntries'].append(int(num_entries))
        data1['Time'].append(float(time))

# Charger les données du second fichier
data2 = {'NumEntries': [], 'Time': []}
with open("tree-avl/debug/insertion_times.txt", "r") as file2:
    next(file2)  # Ignorer l'en-tête
    for line in file2:
        num_entries, time = line.strip().split(',')
        data2['NumEntries'].append(int(num_entries))
        data2['Time'].append(float(time))

# Tracer les deux séries de données
plt.plot(data1['NumEntries'], data1['Time'], marker='o', label="Rouge et Noir", color='blue')
plt.plot(data2['NumEntries'], data2['Time'], marker='s', label="AVL", color='#378595')

# Ajouter les labels et le titre
plt.xlabel("Nombre d'entrées")
plt.ylabel("Temps d'exécution (secondes)")
plt.grid(True)

# Ajouter une légende pour identifier les courbes
plt.legend()

# Afficher le graphe
plt.show()

