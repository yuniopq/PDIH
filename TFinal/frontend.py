import tkinter as tk
import backend 

estado = {
    "rs_obj": None,
    "paquete_codificado": None,
    "paquete_corrupto": None,
    "nsym": 0  
}

# --- FUNCIONES PUENTE ---
def escribir_consola(mensaje):
    """Escribe un mensaje en la caja de resultados y hace auto-scroll hacia abajo."""
    salida_resultados.insert(tk.END, mensaje)
    salida_resultados.see(tk.END)

def accion_codificar():
    t_str = entrada_t.get()
    texto = entrada_mensaje.get("1.0", tk.END).strip()
    
    if not texto or not t_str.isdigit():
        escribir_consola("\n[ERROR] Faltan datos o 't' no es válido.\n")
        return

    # LLAMAMOS AL BACKEND
    rs_obj, paquete, nsym = backend.codificar_mensaje(texto, int(t_str))
    
    # Guardamos los resultados en la memoria temporal
    estado["rs_obj"] = rs_obj
    estado["paquete_codificado"] = paquete
    estado["nsym"] = nsym
    
    escribir_consola(f"\n[1. CODIFICADO] Paridad: {nsym} bytes.\n Paquete (Hex): {paquete.hex()}\n")

def accion_ruido():
    if not estado["paquete_codificado"]:
        escribir_consola("\n[ERROR] Primero codifica un mensaje.\n")
        return

    porcentaje = slider_ruido.get()
    
    # LLAMAMOS AL BACKEND
    paquete_corr, num_errores = backend.aplicar_ruido_canal(estado["paquete_codificado"], porcentaje)
    estado["paquete_corrupto"] = paquete_corr
    
    # 1. Extraemos solo la parte de los datos (quitando la paridad del final)
    nsym = estado["nsym"]
    datos_corruptos = paquete_corr[:-nsym] if nsym > 0 else paquete_corr
    
    # 2. Intentamos leerlo como texto (usamos errors='replace' para que ponga un símbolo '' si el byte está totalmente roto)
    texto_roto = datos_corruptos.decode('utf-8', errors='replace')
    
    escribir_consola(f"\n[2. CANAL] Errores inyectados: {num_errores}\n")
    escribir_consola(f"   Paquete recibido (Hex): {paquete_corr.hex()}\n")
    escribir_consola(f"   Texto dañado visible: {texto_roto}\n")
def accion_decodificar():
    if not estado["rs_obj"] or not estado["paquete_corrupto"]:
        escribir_consola("\n[ERROR] No hay datos corruptos.\n")
        return
        
    escribir_consola("\n[3. DECODIFICACIÓN]\n")
    
    # LLAMAMOS AL BACKEND
    exito, num_errores_reparados, texto_final = backend.decodificar_mensaje(estado["rs_obj"], estado["paquete_corrupto"])
    
    if exito:
        escribir_consola(f"   ¡Éxito! Errores reparados: {num_errores_reparados}\n")
        escribir_consola(f"   Mensaje original: {texto_final}\n")
    else:
        escribir_consola("   [FALLO CRÍTICO] Demasiados errores para reparar.\n")

def accion_limpiar():
    """Borra todo el texto de la consola de resultados."""
    salida_resultados.delete("1.0", tk.END)


# --- DISEÑO DE LA INTERFAZ ---
ventana = tk.Tk()
ventana.title("Simulador Códigos Correctores")
ventana.geometry("550x600")
ventana.config(padx=20, pady=20)

# Fila 0
tk.Label(ventana, text="Capacidad corrección (t):").grid(row=0, column=0, sticky="e")
entrada_t = tk.Entry(ventana, width=10)
entrada_t.grid(row=0, column=1, sticky="w")
entrada_t.insert(0, "3")

# Fila 1
tk.Label(ventana, text="Mensaje a transmitir:").grid(row=1, column=0, sticky="ne", pady=10)
entrada_mensaje = tk.Text(ventana, width=35, height=4)
entrada_mensaje.grid(row=1, column=1, pady=10)

# Fila 2
tk.Label(ventana, text="Ruido del Canal (%):").grid(row=2, column=0, sticky="e")
slider_ruido = tk.Scale(ventana, from_=0, to=100, orient=tk.HORIZONTAL)
slider_ruido.grid(row=2, column=1, sticky="w")

# Fila 3: Botones (agrupados en un Frame)
frame_botones = tk.Frame(ventana)
frame_botones.grid(row=3, column=0, columnspan=2, pady=20)

tk.Button(frame_botones, text="1. Codificar", command=accion_codificar).grid(row=0, column=0, padx=5)
tk.Button(frame_botones, text="2. Aplicar Ruido", command=accion_ruido).grid(row=0, column=1, padx=5)
tk.Button(frame_botones, text="3. Decodificar", command=accion_decodificar).grid(row=0, column=2, padx=5)
tk.Button(frame_botones, text="Limpiar", command=accion_limpiar, bg="#ffcccc").grid(row=0, column=3, padx=5)

# Fila 4: Consola
salida_resultados = tk.Text(ventana, width=60, height=12, bg="#f0f0f0")
salida_resultados.grid(row=4, column=0, columnspan=2, pady=5)

ventana.mainloop()
