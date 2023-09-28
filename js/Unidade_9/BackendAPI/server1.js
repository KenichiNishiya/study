// Importando bibliotecas
const express = require("express");
const cors = require("cors");

// Criacao do servidor express
const app = express();
const port = 3000;

// Configuracao do express
app.use(express.json());

// Configuracao do cors
app.use(cors());

let produtos = [
    {id: 1, nome: "Produto A"},
    {id: 2, nome: "Produto B"},
];

// Rota para listar todos os produtos
app.get("/produtos", (req,res) =>{
    console.log("get");
    // Retorna uma lista de produtos
    res.json(produtos);
})

//Rota para obter um produto por ID
app.get("/produtos/:id", (req,res) =>{
    // Obtem o ID
    const id = parseInt(req.params.id);
    // Procura o produto no array
    const produto = produtos.find((produto) => produto.id === id);
    // Retorna o produto encontrado ou um erro
    if(produto){
        res.json(produto);
    }
    else{
        res.status(404).json({message: "Produto nao encontrado"});
    }
});

// Rota para adicionar um novo produto
app.post("/produtos", (req,res) =>{
    // Obtem os dados do produto
    const newproduto = req.body;
    // Adiciona o produto ao array
    produtos.push(newproduto);
    // Retorna o novo produto
    res.status(201).json(newproduto);
});

// Rota para atualizar um produto
app.put("/produtos/:id",(req,res)=> {
    // Obtem o ID do produto
    const id = parseInt(req.params.id);
    // Obtem os dados do produto
    const updatedproduto = req.body;
    // Procura o produto no array
    const index = produtos.findIndex((produto)=>produto.id === id);
    // Atualiza o produto encontrado ou retorna um erro
    if (index !== -1){
        produtos[index] = { ...produtos[index], ...updatedproduto};
        res.json(produtos[index]);
    }
    else{
        res.status(404).json({message:"Produto nao encontrado"});
    }
});
// Rota para remover um produto
app.delete("/produtos/:id", (req,res) =>{
    // Obtem o ID do produto
    const id = parseInt(req.params.id);
    // Procura o produto no array
    const index = produtos.findIndex((produto) => produto.id === id);
    // Remove o produto encontrado ou retorna um erro
    if(index !== -1){
        const removedproduto = produtos.splice(index,1);
        res.json(removedproduto[0]);
    }
    else{
        res.status(404).json({message: "Produto nao encontrado"});
    }
});

// Inicia o servidor
app.listen(port,() => {
    console.log(`Servidor iniciado na porta ${port}`);
})
