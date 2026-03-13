/**
 * @file    hello.c
 * @author  Xiang
 * @date    12 Marzo 2026
 * @version 0.1
 * @brief   Modulo LKM introductorio para el seminario de PDIH.
 * Muestra mensajes en /var/log/kern.log al cargar y descargar.
*/

#include <linux/init.h>             // Macros para marcar funciones (__init, __exit)
#include <linux/module.h>           // Cabecera principal para LKMs
#include <linux/kernel.h>           // Tipos, macros y funciones del kernel

MODULE_LICENSE("GPL");              // Licencia obligatoria para evitar errores 
MODULE_AUTHOR("Xiang");       
MODULE_DESCRIPTION("Seminario LKM - Introduccion a modulos del kernel"); 
MODULE_VERSION("0.1");

static char *name = "usuario";      // Valor por defecto 
module_param(name, charp, S_IRUGO); // Definicion del parametro
MODULE_PARM_DESC(name, "Nombre que se mostrara en el log");

/** * Funcion de inicializacion (se ejecuta al hacer insmod)
 */
static int __init hello_init(void){
   printk(KERN_INFO "PDIH: Hola %s, bienvenido al kernel de Linux!\n", name);
   return 0;
}

/** * Funcion de limpieza (se ejecuta al hacer rmmod)
 */
static void __exit hello_exit(void){
   printk(KERN_INFO "PDIH: Adios %s, modulo descargado correctamente.\n", name);
}

// Registro de las funciones en el sistema
module_init(hello_init);
module_exit(hello_exit);
