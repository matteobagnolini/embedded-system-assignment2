import tkinter as tk
import time
import threading
from WasteDisposalHandler import empty_container, resolve_temperature_problems, communication_routine

def create_gui():
    # Creazione della finestra principale
    root = tk.Tk()
    root.title("Container Management")
    root.geometry("600x300")  # Imposta una dimensione iniziale di 600x300 pixel

    # Centra la finestra sullo schermo
    root.update_idletasks()
    width = root.winfo_width()
    height = root.winfo_height()
    x = (root.winfo_screenwidth() // 2) - (width // 2)
    y = (root.winfo_screenheight() // 2) - (height // 2)
    root.geometry(f"{width}x{height}+{x}+{y}")

    # Creazione di un frame per centrare i pulsanti
    frame = tk.Frame(root)
    frame.place(relx=0.5, rely=0.5, anchor=tk.CENTER)

    # Creazione dei pulsanti
    btn_empty_container = tk.Button(frame, text="Empty Container", command=empty_container, width=20, height=2)
    btn_resolve_temp = tk.Button(frame, text="Resolve Temperature Problems", command=resolve_temperature_problems, width=20, height=2)

    # Posizionamento dei pulsanti uno di fianco all'altro
    btn_empty_container.grid(row=0, column=0, padx=10, pady=10)
    btn_resolve_temp.grid(row=0, column=1, padx=10, pady=10)

    # Avvio del loop principale della GUI
    root.mainloop()

if __name__ == "__main__":
    threading.Thread(target=communication_routine, daemon=True).start()
    create_gui()
