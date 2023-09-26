<?php
// Include the database connection file
require_once("dbConnection.php");

// Fetch data in descending order (lastest entry first)
$result = mysqli_query($mysqli, "SELECT * FROM users ORDER BY id DESC");
?>

<!DOCTYPE html>
<head>
<title>Mercadao</title>
<style>
table, th, td {
  border:1px solid black;
}
</style>
</head>

<body>
    <h1>Cadastro Usuario</h1>
    Nome:<input id="userNome"></input>
    <br>
    Email:<input id="userEmail"></input>
    <br>
    Senha:<input id="userSenha" type="password"></input>
    <br>
    <br>
    <table id="tbUser">
    </table>
    <br>
    <button id="btnAdd">Adicionar Contato</button>
    <button id="btnConfirma" style="display:none">Confirmar edicao</button>
    <script>
        var contatos = [
            {nome:"Jonas",email:"jonas@email.com",senha:"1234-1234"},
            {nome:"Maria",email:"maria@email.com",senha:"3562-2349"},
            {nome:"Linus Torvalds",email:"ltorvalds@email.com",senha:"2598-9781"},
            {nome:"Stallman",email:"richardstallman@fsf.com",senha:"9295-0838"},
            ];

        var tabela = document.getElementById("tbUser");

        var isEditing = false;
        var position;

        // The table is updated by removing all it's child elements(all rows), including the header
        // and then the array contato is updated, lastly the rows are created with the updated array
        function createTableHeader(){
            var headerRow = tabela.insertRow(0);

            // Create each column
            for(let i = 0;i < 4;i++){
                var headerCell = headerRow.insertCell(i);
                var headerTitle;

                switch(i){
                    case 0:
                        headerTitle="Nome";
                        break;
                    case 1:
                        headerTitle="Email";
                        break;
                    case 2:
                        headerTitle="Senha";
                        break;
                    case 3:
                        headerTitle="Acoes";
                        break;
                }
                headerCell.innerHTML = headerTitle;
                headerCell.style.fontWeight = "bold";
                headerCell.style.textAlign = "center";
            }
    }

        function createTable(){
            for(let i = 0;i < contatos.length;i++){

                var row = tabela.insertRow(i+1);
                var cell1 = row.insertCell(0);
                var cell2 = row.insertCell(1);
                var cell3 = row.insertCell(2);
                var cell4 = row.insertCell(3);

                cell1.innerHTML = contatos[i].nome
                cell2.innerHTML = contatos[i].email
                cell3.innerHTML = contatos[i].senha
                cell4.innerHTML = "<button class='btnEditar';>Editar</button><button class='btnExcluir';>Excluir</button>"
                // By using a class for the button, we are able to add an event listener for every button created here
            }
        }

        // Creating event listener to add a new person
        var btn_add = document.getElementById("btnAdd");
        btn_add.addEventListener("click",()=>{
            var nome = document.getElementById("userNome");
            var email = document.getElementById("userEmail");
            var senha = document.getElementById("userSenha");
            if(nome.value !== "" && email.value !== "" && senha.value !== ""){
                contatos.push({
                    nome: nome.value,
                    email: email.value,
                    senha: senha.value
                })
                nome.value = '';
                email.value = '';
                senha.value = '';
                // Only the array is updated, we need to refresh the table
                refreshTable();
            }
            else{
                alert("Preencha todos os campos")
            }
        })

        function refreshTable(){
            // Remove all child elements from our table tabela
            while(tabela.firstChild){
                tabela.removeChild(tabela.firstChild)
            }
            // Add everything updated
            createTableHeader();
            createTable();
            refreshButtons();
        }

        // Add and event listener to every button with the specified class
        // Those vars are arrays that contain each HTML button inside, we need to update them
        // everytime we remove and create new buttons when refreshing the table
        // Each of these buttons have their indexes fixed (i)
        function refreshButtons(){
            var btn_editar = document.getElementsByClassName("btnEditar");
            for(let i = 0;i < btn_editar.length;i++){
                btn_editar[i].addEventListener("click",()=>{
                    var nome = document.getElementById("userNome");
                    var email = document.getElementById("userEmail");
                    var senha = document.getElementById("userSenha");

                    nome.value = contatos[i].nome;
                    email.value = contatos[i].email;
                    senha.value = contatos[i].senha;

                    var btnConfirm = document.getElementById("btnConfirma");
                    btnConfirm.style.display="inline"

                    isEditing = true;
                    position = i;

                    refreshTable();
                    // The name is fixed, only the other cells are editable
                    // About the splice, we remove 1 element from index i, and in it's place we push a new element
                })
            }

            var btn_excluir = document.getElementsByClassName("btnExcluir");
            for(let i = 0; i < btn_excluir.length;i++){
                btn_excluir[i].addEventListener("click",()=>{
                    contatos.splice(i,1)
                    refreshTable();
                })
            }
        }

        var btnConfirm = document.getElementById("btnConfirma");
        btnConfirm.addEventListener("click",()=>{
            console.log("clicke")
            confirmar();
        });

        function confirmar(){
            var nome = document.getElementById("userNome");
            var email = document.getElementById("userEmail");
            var senha = document.getElementById("userSenha");

            if(isEditing && nome.value !== "" && email.value !== "" && senha.value !== ""){
                contatos.splice(position,1,{nome: nome.value, email: email.value, senha: senha.value});
                console.log(contatos);
                isEditing = false;
                console.log(isEditing,position)
                nome.value = '';
                email.value = '';
                senha.value = '';

                btnConfirm.style.display="none";
                refreshTable();
            }
            else{
                alert("Preencha todos os campos");
            }
        }

        // Call all these when opening the webpage
        createTableHeader();
        createTable();
        refreshButtons();
    </script>
</body>
</html>

