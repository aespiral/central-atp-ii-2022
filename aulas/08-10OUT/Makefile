padrao: recursao.c
	gcc -o recursao recursao.c

teste: recursao_testes.c
	gcc recursao_testes.c $$(pkg-config --cflags --libs cunit) -o recursao_testes
