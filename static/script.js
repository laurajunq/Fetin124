const movimentos = [
    "DIREITA",
    "ESQUERDA",
    "CIMA",
    "BAIXO",
    "PARADO"
];

function atualizarSistema(){

    // Movimento aleatório
    const movimento =
        movimentos[
            Math.floor(Math.random() * movimentos.length)
        ];

    document.getElementById("movimento").innerText =
        movimento;

    // Intensidade aleatória
    const intensidade =
        Math.floor(Math.random() * 100);

    document.getElementById("intensidade").innerText =
        intensidade + "%";

    // Vibração automática
    if(intensidade > 70){

        document.getElementById("vibracao").innerText =
            "ATIVADO";

    }else{

        document.getElementById("vibracao").innerText =
            "DESATIVADO";
    }

    // Criar log
    const logs =
        document.getElementById("log-list");

    const novoLog =
        document.createElement("li");

    novoLog.textContent =
        `Movimento detectado: ${movimento}`;

    logs.prepend(novoLog);

    // Limite de logs
    if(logs.children.length > 6){

        logs.removeChild(logs.lastChild);
    }
}

// Atualiza a cada 2 segundos
setInterval(atualizarSistema, 2000);

function testeVibracao(){

    alert("Vibracall ativado!");

    const logs =
        document.getElementById("log-list");

    const novoLog =
        document.createElement("li");

    novoLog.textContent =
        "Teste manual de vibração executado.";

    logs.prepend(novoLog);
}