#ifndef ALFABETO_H
#define ALFABETO_H
#include <vector>
#include <map>
#include <string>

using namespace std;

// -- ALFABETO -- 
map<string, string> alfabeto = {
    // <Proteina>
    {"pollo_asado", "PROTEINA"},
    {"pechuga_a_la_plancha", "PROTEINA"},
    {"bistec_asado", "PROTEINA"},
    {"carne_deshebrada", "PROTEINA"},
    {"picadillo", "PROTEINA"},
    {"pescado_empapelado", "PROTEINA"},
    {"atun", "PROTEINA"},
    {"huevo_a_la_mexicana", "PROTEINA"},
    {"tinga_de_pollo", "PROTEINA"},
    {"fajitas_de_pollo", "PROTEINA"},

    // <Bebida>
    {"agua_natural", "BEBIDA"},
    {"agua_de_jamaica", "BEBIDA"},
    {"agua_de_limon", "BEBIDA"},
    {"agua_de_horchata", "BEBIDA"},
    {"agua_de_tamarindo", "BEBIDA"},
    {"agua_de_pepino", "BEBIDA"},
    {"agua_de_pina", "BEBIDA"},
    {"agua_mineral", "BEBIDA"},
    {"te_de_manzanilla", "BEBIDA"},
    {"limonada", "BEBIDA"},

    // <Guarnicion1>
    {"arroz_rojo", "GUARN1"},
    {"arroz_blanco", "GUARN1"},
    {"arroz_integral", "GUARN1"},
    {"frijoles_de_la_olla", "GUARN1"},
    {"frijoles_refritos", "GUARN1"},
    {"lentejas", "GUARN1"},
    {"tortilla_de_maiz", "GUARN1"},
    {"papa_cocida", "GUARN1"},
    {"elote_cocido", "GUARN1"},
    {"papa_al_horno", "GUARN1"},

    // <Guarnicion2>
    {"ensalada_verde", "GUARN2"},
    {"ensalada_de_nopales", "GUARN2"},
    {"calabacitas", "GUARN2"},
    {"brocoli_al_vapor", "GUARN2"},
    {"zanahorias_cocidas", "GUARN2"},
    {"chayote_cocido", "GUARN2"},
    {"espinacas", "GUARN2"},
    {"verduras_al_vapor", "GUARN2"},
    {"nopales_asados", "GUARN2"},
    {"pico_de_gallo", "GUARN2"},

    // <EntradaLigera>
    {"guacamole", "ENTRADA"},
    {"ensalada_de_aguacate", "ENTRADA"},
    {"ensalada_de_pepino", "ENTRADA"},
    {"jicama_con_limon", "ENTRADA"},
    {"pepinos_con_limon", "ENTRADA"},
    {"ensalada_de_betabel", "ENTRADA"},
    {"tostada_de_nopal", "ENTRADA"},
    {"verduras_con_limon", "ENTRADA"},
    {"ensalada_de_jitomate", "ENTRADA"},
    {"champinones_asados", "ENTRADA"},

    // <Sopa>
    {"sopa_de_verduras", "SOPA"},
    {"sopa_de_fideo", "SOPA"},
    {"sopa_de_arroz", "SOPA"},
    {"sopa_de_tortilla", "SOPA"},
    {"sopa_de_lentejas", "SOPA"},
    {"caldo_de_pollo", "SOPA"},
    {"caldo_de_res", "SOPA"},
    {"caldo_tlalpeno", "SOPA"},
    {"crema_de_calabaza", "SOPA"},
    {"crema_de_elote", "SOPA"},

    // <Postre>
    {"pay_de_manzana", "POSTRE"},
    {"flan", "POSTRE"},
    {"arroz_con_leche", "POSTRE"},
    {"pastel_de_chocolate", "POSTRE"},
    {"pastel_tres_leches", "POSTRE"},
    {"helado_de_vainilla", "POSTRE"},
    {"churros", "POSTRE"},
    {"capirotada", "POSTRE"},
    {"pay_de_limon", "POSTRE"},
    {"gelatina", "POSTRE"},

    // Especiales
    {"+", "Y"},
    {"$", "FIN"}};


    #endif