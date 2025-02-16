// Deve-se estar nesta página antes de injetar o código
// https://certificados.iffarroupilha.edu.br/certificados/listaPublica

// Usado para limpar as strings de acentuações e caracteres não suportados (além de normalizar para lowercase)
// cleanse('Olá mundo') -> 'ola mundo'
function cleanse(str) {
    return str.normalize("NFD")
        .replace(/[\u0300-\u036f]/g, "")
        .toLowerCase()
        .trim()
}

// Extrai o código do certificado e retorna a url de download
function downloadCert(str) {
    const code = (str.split('/'))
        .slice(-1)[0]
    return `https://certificados.iffarroupilha.edu.br/emitir/${code}`
}


// Inicializa o dict GLOBAL
function genDict() {
    const elem = document.getElementsByName('txtEvento')[0]
    const dict = {};

    let i = 1;
    let opt = elem.options[i]
    while (typeof(opt) == 'object') {
        dict[opt.value] = opt.text.trim()
        i += 1
        opt = elem.options[i]
    }
    return dict
}
const dict = genDict()


// Método Post
async function request(eventID) {
    const fetchPromise = await fetch("https://certificados.iffarroupilha.edu.br/certificados/listaCertificadosPublicos", {
        "headers": {
            "accept-language": "en-US,en;q=0.9,pt-BR;q=0.8,pt;q=0.7",
            "cache-control": "max-age=0",
            "content-type": "application/x-www-form-urlencoded",
            "sec-fetch-dest": "document",
            "sec-fetch-mode": "navigate",
            "sec-fetch-site": "same-origin",
            "sec-fetch-user": "?1",
            "upgrade-insecure-requests": "1"
        },

        "referrer": "https://certificados.iffarroupilha.edu.br/certificados/listaPublica",
        "referrerPolicy": "no-referrer-when-downgrade",
        "body": `txtEvento=${eventID}`,
        "method": "POST",
        "mode": "cors",
        "credentials": "include"
    });
    return fetchPromise;
}


// Procura pelo nome no evento especifico
async function find(key, name) {
    try {
        const response = await request(key);
        const text = await response.text();
        const parser = new DOMParser();

        const doc = parser.parseFromString(text, "text/html")
        for (const rows of doc.getElementById("data_table")
                .rows) {
            if (rows.id) {
                let certUser = rows.cells[0].innerText
                if (cleanse(certUser)
                    .includes(cleanse(name))) {
                    let cert = rows.cells[1].innerText
                    let href = rows.cells[2].querySelector('a')
                        .getAttribute('href')
                    console.log(`=====[ ${cert} ]=====\nNome: ${certUser} \nDownload: ${downloadCert(href)}`)

                }
            }
        }
    } catch (e) {
        console.error(`>> Erro ao procurar certificado "${dict[key]}" | ${e}`);
    }
}




// Procura pelo nome em todos os eventos
async function findAll(name) {
    const allPromisses = []
    try {
        for (const [key, value] of Object.entries(dict)) {
            allPromisses.push(find(key, name))
        }
        await Promise.all(allPromisses)
        console.log(">> Todos certificados vasculhados.")
    } catch (e) {
        console.error(`>> Erro ao procurar certificado "${value}" | ${e}`);
    }
}


// Download de OBJ em forma de JSON
// Exemplo: downloadJSON(dict, "Lista Cód Eventos");
function downloadJSON(exportObj, exportName) {
    const dataStr = "data:text/json;charset=utf-8," + encodeURIComponent(JSON.stringify(exportObj, null, 4));
    const downloadAnchorNode = document.createElement('a');
    downloadAnchorNode.setAttribute("href", dataStr);
    downloadAnchorNode.setAttribute("download", exportName + ".json");
    document.body.appendChild(downloadAnchorNode);
    downloadAnchorNode.click();
    downloadAnchorNode.remove();
};
