import tkinter as tk
from matplotlib.backends.backend_tkagg import FigureCanvasTkAgg
import matplotlib.pyplot as plt
import threading
import time
from WasteDisposalHandler import empty_container, resolve_temperature_problems, receive_temp, communication_routine

# Variabile globale per contenere i valori della temperatura
temperature_data = []

def update_graph(canvas, ax, line):
    """
    Aggiorna il grafico con i dati più recenti.
    """
    # Limiti della finestra scorrevole
    window_size = 50
    if len(temperature_data) > window_size:
        displayed_data = temperature_data[-window_size:]
    else:
        displayed_data = temperature_data

    # Aggiorna il grafico
    line.set_ydata(displayed_data)
    line.set_xdata(range(len(displayed_data)))
    ax.relim()
    ax.autoscale_view()

    # Fissa i limiti dell'asse Y tra 10 e 30
    ax.set_ylim(10, 30)

    # Aggiorna il canvas
    canvas.draw()

def message_loop(canvas, ax, line):
    """
    Ciclo infinito che aggiorna i dati della temperatura e il grafico.
    """
    global temperature_data
    while True:
        # Simula la ricezione della temperatura (sostituisci con dati reali se disponibili)
        new_temperature = receive_temp()
        # print(new_temperature)
        temperature_data.append(new_temperature)
        if len(temperature_data) > 500:  # Limita la lunghezza massima per evitare uso eccessivo di memoria
            temperature_data = temperature_data[-500:]

        # Aggiorna il grafico
        update_graph(canvas, ax, line)
        time.sleep(1)

def create_gui():
    # Creazione della finestra principale
    root = tk.Tk()
    root.title("Container Management")
    root.geometry("1200x800")  # Imposta una dimensione iniziale di 800x400 pixel

    # Centra la finestra sullo schermo
    root.update_idletasks()
    width = root.winfo_width()
    height = root.winfo_height()
    x = (root.winfo_screenwidth() // 2) - (width // 2)
    y = (root.winfo_screenheight() // 2) - (height // 2)
    root.geometry(f"{width}x{height}+{x}+{y}")

    # Creazione di un frame principale
    main_frame = tk.Frame(root)
    main_frame.pack(fill=tk.BOTH, expand=True)

    # Creazione di un frame per il grafico
    graph_frame = tk.Frame(main_frame, width=300, height=100)
    graph_frame.pack(side=tk.LEFT, fill=tk.BOTH, padx=10, pady=10)

    # Creazione del grafico
    fig, ax = plt.subplots(figsize=(5, 2))  # Dimensioni più compatte del grafico
    ax.set_title("Temperature Graphic")
    ax.set_xlabel("Time")
    ax.set_ylabel("Temperature")
    ax.set_ylim(10, 30)  # Range fisso per l'asse Y
    ax.grid(True)

    # Linea del grafico inizializzata con valori vuoti
    line, = ax.plot([], [], color='red', marker='o')

    # Aggiunta del grafico alla GUI
    canvas = FigureCanvasTkAgg(fig, master=graph_frame)
    canvas_widget = canvas.get_tk_widget()
    canvas_widget.pack(fill=tk.BOTH, expand=True)

    # Creazione di un frame per i pulsanti
    button_frame = tk.Frame(main_frame)
    button_frame.pack(side=tk.RIGHT, fill=tk.Y, padx=10, pady=10)

    # Creazione dei pulsanti
    btn_empty_container = tk.Button(button_frame, text="Empty Container", command=empty_container, width=20, height=2)
    btn_resolve_temp = tk.Button(button_frame, text="Resolve Temperature Problems", command=resolve_temperature_problems, width=20, height=2)

    # Posizionamento dei pulsanti
    btn_empty_container.pack(pady=20)
    btn_resolve_temp.pack(pady=20)

    # Avvio del thread per aggiornare i dati e il grafico
    threading.Thread(target=message_loop, args=(canvas, ax, line), daemon=True).start()


    # Avvio del loop principale della GUI
    root.mainloop()

if __name__ == "__main__":
    threading.Thread(target=communication_routine, daemon=True).start()
    create_gui()