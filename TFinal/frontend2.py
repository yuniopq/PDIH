import customtkinter as ctk
import backend 

# --- CONFIGURACIÓN DEL TEMA MODERNO ---
ctk.set_appearance_mode("Dark")
ctk.set_default_color_theme("blue")

# --- MEMORIA TEMPORAL DE LA INTERFAZ ---
memoria_app = {
    "motor_corrector": None,           # El algoritmo matemático inicializado
    "datos_codificados": None,         # El mensaje convertido a bytes + paridad
    "datos_con_ruido": None,           # El paquete después de pasar por el canal malo
    "cantidad_bytes_paridad": 0        # Cuántos bytes extra se añadieron para seguridad
}

# --- FUNCIONES PUENTE ---
def escribir_consola(mensaje_texto):
    """Escribe un mensaje en la caja de resultados y hace auto-scroll hacia abajo."""
    consola_resultados.insert("end", mensaje_texto)
    consola_resultados.see("end")

def actualizar_ruido(valor_deslizador):
    """Actualiza el texto del porcentaje al mover el deslizador."""
    etiqueta_porcentaje.configure(text=f"{int(valor_deslizador)}%")

def accion_codificar():
    texto_capacidad_t = caja_capacidad_t.get()
    mensaje_original = caja_mensaje_original.get("0.0", "end").strip()
    
    if not mensaje_original or not texto_capacidad_t.isdigit():
        escribir_consola("\n[ERROR] Faltan datos o la capacidad 't' no es un número válido.\n")
        return

    # LLAMAMOS AL BACKEND 
    motor_corrector, datos_codificados, cantidad_bytes_paridad = backend.codificar_mensaje(mensaje_original, int(texto_capacidad_t))
    
    # Guardamos los resultados en la memoria temporal
    memoria_app["motor_corrector"] = motor_corrector
    memoria_app["datos_codificados"] = datos_codificados
    memoria_app["cantidad_bytes_paridad"] = cantidad_bytes_paridad
    
    escribir_consola(f"\n[1. CODIFICADO] Paridad añadida: {cantidad_bytes_paridad} bytes.\n Paquete (Hex): {datos_codificados.hex()}\n")

def accion_ruido():
    if not memoria_app["datos_codificados"]:
        escribir_consola("\n[ERROR] Primero codifica un mensaje.\n")
        return

    porcentaje_ruido = deslizador_ruido.get()
    
    # LLAMAMOS AL BACKEND
    datos_con_ruido, cantidad_errores = backend.aplicar_ruido_canal(memoria_app["datos_codificados"], porcentaje_ruido)
    memoria_app["datos_con_ruido"] = datos_con_ruido
    
    # 1. Extraemos solo la parte del mensaje
    bytes_paridad = memoria_app["cantidad_bytes_paridad"]
    solo_mensaje_con_ruido = datos_con_ruido[:-bytes_paridad] if bytes_paridad > 0 else datos_con_ruido
    
    # 2. Intentamos leerlo como texto
    texto_dañado_visible = solo_mensaje_con_ruido.decode('utf-8', errors='replace')
    
    escribir_consola(f"\n[2. CANAL] Errores inyectados: {cantidad_errores}\n")
    escribir_consola(f"   Paquete recibido (Hex): {datos_con_ruido.hex()}\n")
    escribir_consola(f"   Texto dañado visible: {texto_dañado_visible}\n")

def accion_decodificar():
    if not memoria_app["motor_corrector"] or not memoria_app["datos_con_ruido"]:
        escribir_consola("\n[ERROR] No hay datos corruptos listos para decodificar.\n")
        return
        
    escribir_consola("\n[3. DECODIFICACIÓN]\n")
    
    # LLAMAMOS AL BACKEND
    decodificacion_exitosa, errores_reparados, mensaje_recuperado = backend.decodificar_mensaje(memoria_app["motor_corrector"], memoria_app["datos_con_ruido"])
    
    if decodificacion_exitosa:
        escribir_consola(f"   ¡Éxito! Errores detectados y reparados: {errores_reparados}\n")
        escribir_consola(f"   Mensaje original recuperado: {mensaje_recuperado}\n")
    else:
        escribir_consola("   [FALLO CRÍTICO] Demasiados errores. La capacidad 't' no fue suficiente para reparar el paquete.\n")

def accion_limpiar():
    """Borra todo el texto de la consola de resultados."""
    consola_resultados.delete("0.0", "end")


# --- DISEÑO DE LA INTERFAZ ---
ventana = ctk.CTk()
ventana.title("Simulador Códigos Correctores")
ventana.geometry("550x600")
ventana.configure(padx=20, pady=20)

# Fila 0
ctk.CTkLabel(ventana, text="Capacidad corrección (t):").grid(row=0, column=0, sticky="e")
caja_capacidad_t = ctk.CTkEntry(ventana, width=100)
caja_capacidad_t.grid(row=0, column=1, sticky="w")
caja_capacidad_t.insert(0, "3")

# Fila 1
ctk.CTkLabel(ventana, text="Mensaje a transmitir:").grid(row=1, column=0, sticky="ne", pady=10)
caja_mensaje_original = ctk.CTkTextbox(ventana, width=350, height=80)
caja_mensaje_original.grid(row=1, column=1, pady=10)

# Fila 2
ctk.CTkLabel(ventana, text="Ruido del Canal (%):").grid(row=2, column=0, sticky="e")

# Agrupamos el deslizador y el texto del porcentaje
frame_deslizador = ctk.CTkFrame(ventana, fg_color="transparent")
frame_deslizador.grid(row=2, column=1, sticky="w")

deslizador_ruido = ctk.CTkSlider(frame_deslizador, from_=0, to=100, command=actualizar_ruido)
deslizador_ruido.grid(row=0, column=0)
deslizador_ruido.set(0)

etiqueta_porcentaje = ctk.CTkLabel(frame_deslizador, text="0%")
etiqueta_porcentaje.grid(row=0, column=1, padx=10)

# Fila 3: Botones
frame_botones = ctk.CTkFrame(ventana, fg_color="transparent")
frame_botones.grid(row=3, column=0, columnspan=2, pady=20)

ctk.CTkButton(frame_botones, text="1. Codificar", command=accion_codificar).grid(row=0, column=0, padx=5)
ctk.CTkButton(frame_botones, text="2. Aplicar Ruido", command=accion_ruido).grid(row=0, column=1, padx=5)
ctk.CTkButton(frame_botones, text="3. Decodificar", command=accion_decodificar).grid(row=0, column=2, padx=5)
ctk.CTkButton(frame_botones, text="Limpiar", command=accion_limpiar, fg_color="#D32F2F", hover_color="#B71C1C").grid(row=0, column=3, padx=5)

# Fila 4: Consola
consola_resultados = ctk.CTkTextbox(ventana, width=500, height=200)
consola_resultados.grid(row=4, column=0, columnspan=2, pady=5)

ventana.mainloop()
