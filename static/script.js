const movimentos = [
    "DIREITA",
    "ESQUERDA",
    "CIMA",
    "BAIXO",
    "PARADO"
];
function atualizarSistema(){
    //movimento aleatorio
    const movimento = movimentos[Math.floor(Math.random() * movimentos.length)];
    document.getElementById("movimento").innerText = movimento;
    
    //intensidade aleatoria
    const intensidade = Math.floor(Math.random() * 100);
    document.getElementbyId("intensidade").innerText = intensidade + "%";
    
    //vibracao automatica
    if(intensidade > 70){
        document.getElementById("vibracao").innertext = "ATIVADO";
    }else{
        document.getElementById("vibracao").innertext = "DESATIVADO";
    }
    
    //criar log
    const logs = document.getElementbyId("log-list");
    const novoLog = document.createElement("li");
    novoLog.textContent = `movimento detectado: ${movimento}`;
    logs.prepend(novoLog);
    
    //limite de logs
    if(logs.children.length > 6){
        logs.removeChild(logs.lastChild);
    }
}

//atualiza a cada 2seg
setInterval(atualizarSistema, 2000);

function testeVibracao(){

    alert("Vibracall ativado!");

    const logs = document.getElementById("log-list");

    const novoLog = document.createElement("li");

    novoLog.textContent = "Teste manual de vibração executado.";

    logs.prepend(novoLog);
}

