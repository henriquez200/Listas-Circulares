#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "playlist.h"

int main() {
    Playlist* playlist = criar_playlist();
    int opcao;
    char titulo[100], artista[100];
    int duracao;

    do {
        printf("\n=== PLAYLIST ===\n");
        printf("1. Adicionar musica\n");
        printf("2. Remover musica\n");
        printf("3. Próxima musica\n");
        printf("4. Musica anterior\n");
        printf("5. Alternar modo repeticao\n");
        printf("6. Listar musicas\n");
        printf("7. Buscar musica\n");
        printf("8. Exibir musica atual\n");
        printf("0. Sair\n");
        scanf("%d", &opcao);
        getchar(); // Limpa o '\n' do buffer

        if (opcao == 1) {
            printf("Titulo: ");
            fgets(titulo, sizeof(titulo), stdin);
            titulo[strcspn(titulo, "\n")] = '\0';

            printf("Artista: ");
            fgets(artista, sizeof(artista), stdin);
            artista[strcspn(artista, "\n")] = '\0';

            printf("Duracaoo (segundos): ");
            scanf("%d", &duracao);
            getchar();

            adicionar_musica(playlist, titulo, artista, duracao);

        } else if (opcao == 2) {
            printf("Titulo da musica: ");
            fgets(titulo, sizeof(titulo), stdin);
            titulo[strcspn(titulo, "\n")] = '\0';

            remover_musica(playlist, titulo);

        } else if (opcao == 3) {
            proxima_musica(playlist);

        } else if (opcao == 4) {
            musica_anterior(playlist);

        } else if (opcao == 5) {
            alternar_modo_repeticao(playlist);

        } else if (opcao == 6) {
            listar_musicas(playlist);

        } else if (opcao == 7) {
            printf("Titulo da musica : ");
            fgets(titulo, sizeof(titulo), stdin);
            titulo[strcspn(titulo, "\n")] = '\0';

            buscar_musica(playlist, titulo);

        } else if (opcao == 8) {
            exibir_musica_atual(playlist);

        } else if (opcao == 0) {
            liberar_playlist(playlist);
            printf("Saindo...\n");

        } else {
            printf("Opcao invalida.\n");
        }

    } while (opcao != 0);

    return 0;
}
