import java.io.FileWriter;
import java.io.IOException;
import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;
import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;

/*
 * Juego de Damas Inglesas - damas.java
 *
 * Reglas principales:
 * - Tablero de 8x8.
 * - Las fichas solo se mueven por las casillas oscuras.
 * - Las fichas normales avanzan hacia el lado contrario.
 * - Se puede capturar saltando una ficha rival.
 * - Al llegar al extremo contrario, una ficha se convierte en dama.
 * - Las damas pueden moverse en ambas direcciones.
 *
 * La estructura de datos ArrayList<Movimiento> guarda:
 * - Fecha y hora del movimiento.
 * - Jugador.
 * - Ficha que se movio.
 * - Casilla de origen.
 * - Casilla de destino.
 *
 * Al terminar, se puede guardar toda la partida en "partida_damas.txt".
 */

public class damas {

    static final int TAM = 8;
    static final char VACIO = '.';
    static final char BLANCA = 'b';
    static final char NEGRA = 'n';
    static final char DAMA_BLANCA = 'B';
    static final char DAMA_NEGRA = 'N';

    static char[][] tablero = new char[TAM][TAM];

    // Estructura de datos para guardar el historial de movimientos.
    static List<Movimiento> historial = new ArrayList<>();

    static Scanner scanner = new Scanner(System.in);

    static class Movimiento {
        LocalDateTime tiempo;
        String jugador;
        char ficha;
        int filaOrigen, columnaOrigen;
        int filaDestino, columnaDestino;

        Movimiento(String jugador, char ficha, int fo, int co, int fd, int cd) {
            this.tiempo = LocalDateTime.now();
            this.jugador = jugador;
            this.ficha = ficha;
            this.filaOrigen = fo;
            this.columnaOrigen = co;
            this.filaDestino = fd;
            this.columnaDestino = cd;
        }

        String texto() {
            DateTimeFormatter formato = DateTimeFormatter.ofPattern("yyyy-MM-dd HH:mm:ss");
            return String.format(
                "%s | %s | Ficha: %c | %s -> %s",
                tiempo.format(formato),
                jugador,
                ficha,
                casilla(filaOrigen, columnaOrigen),
                casilla(filaDestino, columnaDestino)
            );
        }
    }

    public static void main(String[] args) {
        inicializarTablero();

        String jugadorActual = "Negras";
        boolean jugando = true;

        System.out.println("=================================");
        System.out.println("       JUEGO DE DAMAS INGLESAS");
        System.out.println("=================================");
        System.out.println("Escribe los movimientos como: a3 b4");
        System.out.println("Para guardar la partida escribe: guardar");
        System.out.println("Para salir escribe: salir");
        System.out.println();

        while (jugando) {
            mostrarTablero();

            if (!tieneMovimientos(jugadorActual)) {
                String ganador = jugadorActual.equals("Negras") ? "Blancas" : "Negras";
                System.out.println("No hay movimientos disponibles.");
                System.out.println("¡Ganaron las " + ganador + "!");
                break;
            }

            System.out.println("Turno de: " + jugadorActual);
            System.out.print("Movimiento: ");

            String entrada = scanner.nextLine().trim();

            if (entrada.equalsIgnoreCase("salir")) {
                System.out.println("Partida terminada.");
                break;
            }

            if (entrada.equalsIgnoreCase("guardar")) {
                guardarPartida();
                continue;
            }

            String[] partes = entrada.split("\\s+");

            if (partes.length != 2) {
                System.out.println("Formato incorrecto. Ejemplo: a3 b4");
                continue;
            }

            int[] origen = convertirCasilla(partes[0]);
            int[] destino = convertirCasilla(partes[1]);

            if (origen == null || destino == null) {
                System.out.println("Casilla inválida. Usa desde a1 hasta h8.");
                continue;
            }

            char ficha = tablero[origen[0]][origen[1]];

            if (!esFichaDelJugador(ficha, jugadorActual)) {
                System.out.println("Esa ficha no pertenece a las " + jugadorActual + ".");
                continue;
            }

            if (!movimientoValido(origen[0], origen[1], destino[0], destino[1], jugadorActual)) {
                System.out.println("Movimiento inválido.");
                continue;
            }

            realizarMovimiento(origen[0], origen[1], destino[0], destino[1], jugadorActual);

            if (jugadorActual.equals("Negras")) {
                jugadorActual = "Blancas";
            } else {
                jugadorActual = "Negras";
            }
        }

        scanner.close();
    }

    static void inicializarTablero() {
        for (int f = 0; f < TAM; f++) {
            for (int c = 0; c < TAM; c++) {
                tablero[f][c] = VACIO;
            }
        }

        // Negras empiezan arriba.
        for (int f = 0; f < 3; f++) {
            for (int c = 0; c < TAM; c++) {
                if ((f + c) % 2 == 1) {
                    tablero[f][c] = NEGRA;
                }
            }
        }

        // Blancas empiezan abajo.
        for (int f = 5; f < 8; f++) {
            for (int c = 0; c < TAM; c++) {
                if ((f + c) % 2 == 1) {
                    tablero[f][c] = BLANCA;
                }
            }
        }
    }

    static void mostrarTablero() {
        System.out.println();
        System.out.println("    a b c d e f g h");
        System.out.println("   -----------------");

        for (int f = 0; f < TAM; f++) {
            System.out.print((8 - f) + " | ");

            for (int c = 0; c < TAM; c++) {
                System.out.print(tablero[f][c] + " ");
            }

            System.out.println("| " + (8 - f));
        }

        System.out.println("   -----------------");
        System.out.println("    a b c d e f g h");
        System.out.println("b/n = ficha normal | B/N = dama");
        System.out.println();
    }

    static boolean movimientoValido(int fo, int co, int fd, int cd, String jugador) {

    // La casilla destino debe estar vacía
    if (tablero[fd][cd] != VACIO) {
        return false;
    }

    int df = fd - fo;
    int dc = cd - co;

    // El movimiento debe ser diagonal
    if (Math.abs(df) != Math.abs(dc)) {
        return false;
    }

    char ficha = tablero[fo][co];

    boolean esDama = ficha == DAMA_BLANCA || ficha == DAMA_NEGRA;

    // ==========================================
    // MOVIMIENTO DE UNA FICHA NORMAL
    // ==========================================
    if (!esDama && Math.abs(df) == 1) {

        if (jugador.equals("Negras")) {
            return df == 1;
        }

        if (jugador.equals("Blancas")) {
            return df == -1;
        }

        return false;
    }

    // ==========================================
    // MOVIMIENTO DE UNA DAMA
    // ==========================================
    if (esDama && Math.abs(df) == 1) {
        return true;
    }

    // ==========================================
    // CAPTURA DE UNA FICHA
    // ==========================================
    if (Math.abs(df) == 2) {

        int filaMedio = (fo + fd) / 2;
        int columnaMedio = (co + cd) / 2;

        char fichaMedio = tablero[filaMedio][columnaMedio];

        return esFichaRival(fichaMedio, jugador);
    }

    return false;
}

    static void realizarMovimiento(int fo, int co, int fd, int cd, String jugador) {
        char ficha = tablero[fo][co];

        // Si salta una ficha rival, la elimina.
        if (Math.abs(fd - fo) == 2) {
            int fm = (fo + fd) / 2;
            int cm = (co + cd) / 2;
            tablero[fm][cm] = VACIO;
        }

        tablero[fd][cd] = ficha;
        tablero[fo][co] = VACIO;

        // Coronación.
        if (ficha == BLANCA && fd == 0) {
            tablero[fd][cd] = DAMA_BLANCA;
            System.out.println("¡La ficha blanca se convirtió en dama!");
        } else if (ficha == NEGRA && fd == 7) {
            tablero[fd][cd] = DAMA_NEGRA;
            System.out.println("¡La ficha negra se convirtió en dama!");
        }

        // Guardar el movimiento en la estructura de datos.
        historial.add(new Movimiento(
            jugador,
            ficha,
            fo, co,
            fd, cd
        ));

        System.out.println("Movimiento realizado correctamente.");
        System.out.println("Movimientos guardados: " + historial.size());
    }

    static boolean tieneMovimientos(String jugador) {
        for (int f = 0; f < TAM; f++) {
            for (int c = 0; c < TAM; c++) {
                if (esFichaDelJugador(tablero[f][c], jugador)) {
                    for (int df = -2; df <= 2; df++) {
                        for (int dc = -2; dc <= 2; dc++) {
                            int nf = f + df;
                            int nc = c + dc;

                            if (nf >= 0 && nf < TAM && nc >= 0 && nc < TAM) {
                                if (movimientoValido(f, c, nf, nc, jugador)) {
                                    return true;
                                }
                            }
                        }
                    }
                }
            }
        }
        return false;
    }

    static boolean esFichaDelJugador(char ficha, String jugador) {
        if (jugador.equals("Negras")) {
            return ficha == NEGRA || ficha == DAMA_NEGRA;
        }

        return ficha == BLANCA || ficha == DAMA_BLANCA;
    }

    static boolean esFichaRival(char ficha, String jugador) {
        if (jugador.equals("Negras")) {
            return ficha == BLANCA || ficha == DAMA_BLANCA;
        }

        return ficha == NEGRA || ficha == DAMA_NEGRA;
    }

    static int[] convertirCasilla(String texto) {
        if (texto.length() != 2) {
            return null;
        }

        char columna = Character.toLowerCase(texto.charAt(0));
        char filaChar = texto.charAt(1);

        if (columna < 'a' || columna > 'h' || filaChar < '1' || filaChar > '8') {
            return null;
        }

        int columnaNumero = columna - 'a';
        int filaNumero = 8 - (filaChar - '0');

        return new int[]{filaNumero, columnaNumero};
    }

    static String casilla(int fila, int columna) {
        char letra = (char) ('a' + columna);
        int numero = 8 - fila;
        return "" + letra + numero;
    }

    static void guardarPartida() {
        String archivo = "partida_damas.txt";

        try (FileWriter escritor = new FileWriter(archivo)) {
            escritor.write("========================================\n");
            escritor.write("       PARTIDA DE DAMAS INGLESAS\n");
            escritor.write("========================================\n\n");

            if (historial.isEmpty()) {
                escritor.write("No hay movimientos registrados.\n");
            } else {
                for (int i = 0; i < historial.size(); i++) {
                    escritor.write((i + 1) + ". " + historial.get(i).texto() + "\n");
                }
            }

            escritor.write("\nTotal de movimientos: " + historial.size() + "\n");

            System.out.println("Partida guardada correctamente en: " + archivo);
        } catch (IOException e) {
            System.out.println("Error al guardar la partida: " + e.getMessage());
        }
    }
}

