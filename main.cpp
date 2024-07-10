#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Produto {
public:
    string marca, nome, codigo;
    int quantidade;
    double preco;

    Produto(string marca, string nome, int quantidade, string codigo, double preco)
        : marca(marca), nome(nome), quantidade(quantidade), codigo(codigo), preco(preco) {}

    void addCarrinho() {
        cout << "Produto " << nome << " adicionado ao carrinho." << endl;
    }

    void addFavoritos() {
        cout << "Produto " << nome << " adicionado aos favoritos." << endl;
    }

    void removerCarrinho() {
        cout << "Produto " << nome << " removido do carrinho." << endl;
    }
};

class Anuncio {
public:
    string data, titulo, descricao;
    Produto produto;

    Anuncio(string data, string titulo, string descricao, Produto produto)
        : data(data), titulo(titulo), descricao(descricao), produto(produto) {}

    void publicarAnuncio() {
        cout << "Anúncio '" << titulo << "' publicado." << endl;
    }

    void editarAnuncio(string novoTitulo, string novaDescricao) {
        titulo = novoTitulo;
        descricao = novaDescricao;
        cout << "Anúncio '" << titulo << "' editado." << endl;
    }

    void removerAnuncio() {
        cout << "Anúncio '" << titulo << "' removido." << endl;
    }
};

class Compra {
public:
    string data, codigo;
    int quantidade;
    double valorTotal;

    Compra(string data, int quantidade, string codigo, double valorTotal)
        : data(data), quantidade(quantidade), codigo(codigo), valorTotal(valorTotal) {}

    void finalizarCompra() {
        cout << "Compra finalizada. Valor total: R$ " << valorTotal << endl;
    }

    void cancelarCompra() {
        cout << "Compra cancelada." << endl;
    }
};

class Usuario {
public:
    string login,email, password, addr,phone, cpf;
    vector<Anuncio> favoritos;
    vector<Anuncio> anuncios;
    vector<Compra> compras;

    Usuario(string login, string email, string password, string addr, string phone, string cpf)
        : login(login), email(email), password(password), addr(addr), phone(phone), cpf(cpf) {}

    Anuncio criarAnuncio(Produto produto) {
        string data = "2024-07-07";
        Anuncio anuncio(data, produto.nome, produto.marca + " - " + produto.nome, produto);
        anuncios.push_back(anuncio);
        anuncio.publicarAnuncio();
        return anuncio;
    }

    Compra comprar(Anuncio anuncioCompra, int quantidade) {
        double valorTotal = anuncioCompra.produto.preco * quantidade;
        string data = "2024-07-07"; 
        Compra compra(data, quantidade, anuncioCompra.produto.codigo, valorTotal);
        compras.push_back(compra);
        compra.finalizarCompra();
        return compra;
    }

    bool cancelarCompra(string codigo) {
        for (auto it = compras.begin(); it != compras.end(); ++it) {
            if (it->codigo == codigo) {
                it->cancelarCompra();
                compras.erase(it);
                return true;
            }
        }
        return false;
    }

    bool deletarAnuncio(string titulo) {
        for (auto it = anuncios.begin(); it != anuncios.end(); ++it) {
            if (it->titulo == titulo) {
                it->removerAnuncio();
                anuncios.erase(it);
                return true;
            }
        }
        return false;
    }

    bool favoritar(string titulo) {
        for (const auto& anuncio : anuncios) {
            if (anuncio.titulo == titulo) {
                favoritos.push_back(anuncio);
                cout << "Anúncio '" << anuncio.titulo << "' adicionado aos favoritos." << endl;
                return true;
            }
        }
        return false;
    }
};

class Admin {
public:
    string nome, senha;

    Admin(string nome, string senha) : nome(nome), senha(senha) {}

    bool deletarUsuario(vector<Usuario>& usuarios, string login) {
        for (auto it = usuarios.begin(); it != usuarios.end(); ++it) {
            if (it->login == login) {
                usuarios.erase(it);
                cout << "Usuário " << login << " deletado com sucesso." << endl;
                return true;
            }
        }
        cout << "Usuário " << login << " não encontrado." << endl;
        return false;
    }

    Usuario criarUsuario() {
        string login, email, password, addr, phone, cpf;
        cout << "Digite o login: ";
        cin >> login;
        cout << "Digite o email: ";
        cin >> email;
        cout << "Digite a senha: ";
        cin >> password;
        cout << "Digite o endereço: ";
        cin >> addr;
        cout << "Digite o telefone: ";
        cin >> phone;
        cout << "Digite o CPF: ";
        cin >> cpf;

        Usuario novoUsuario(login, email, password, addr, phone, cpf);
        cout << "Usuário criado com sucesso." << endl;
        return novoUsuario;
    }

    Produto criarProduto() {
        string marca, nome, codigo;
        int quantidade;
        double preco;

        cout << "Digite a marca: ";
        cin >> marca;
        cout << "Digite o nome: ";
        cin >> nome;
        cout << "Digite a quantidade: ";
        cin >> quantidade;
        cout << "Digite o código: ";
        cin >> codigo;
        cout << "Digite o preço: ";
        cin >> preco;

        Produto novoProduto(marca, nome, quantidade, codigo, preco);
        cout << "Produto criado com sucesso." << endl;
        return novoProduto;
    }
};

int main() {
    vector<Usuario> usuarios;
    vector<Admin> admins;

    int userType;
    cout << "Cadastro de Usuário ou Admin:\n";
    cout << "1. Usuário\n";
    cout << "2. Admin\n";
    cout << "Escolha uma opção: ";
    cin >> userType;

    if (userType == 1) {
        Usuario novoUsuario = Admin("admin", "admin").criarUsuario();
        usuarios.push_back(novoUsuario);
    } else if (userType == 2) {
        string nome, senha;
        cout << "Digite o nome do admin: ";
        cin >> nome;
        cout << "Digite a senha do admin: ";
        cin >> senha;
        admins.push_back(Admin(nome, senha));
    } else {
        cout << "Opção inválida." << endl;
        return 1;
    }

    Usuario* usuarioLogado = nullptr;
    Admin* adminLogado = nullptr;

    int loginType;
    cout << "Login de Usuário ou Admin:\n";
    cout << "1. Usuário\n";
    cout << "2. Admin\n";
    cout << "Escolha uma opção: ";
    cin >> loginType;

    if (loginType == 1) {
        string login, senha;
        cout << "Digite o login: ";
        cin >> login;
        cout << "Digite a senha: ";
        cin >> senha;

        for (auto& usuario : usuarios) {
            if (usuario.login == login && usuario.password == senha) {
                usuarioLogado = &usuario;
                break;
            }
        }

        if (!usuarioLogado) {
            cout << "Login ou senha inválidos." << endl;
            return 1;
        }
    } else if (loginType == 2) {
        string nome, senha;
        cout << "Digite o nome do admin: ";
        cin >> nome;
        cout << "Digite a senha do admin: ";
        cin >> senha;

        for (auto& admin : admins) {
            if (admin.nome == nome && admin.senha == senha) {
                adminLogado = &admin;
                break;
            }
        }

        if (!adminLogado) {
            cout << "Nome ou senha inválidos." << endl;
            return 1;
        }
    } else {
        cout << "Opção inválida." << endl;
        return 1;
    }

    int choice;
    do {
        cout << "\nMenu de Opções:\n";
        if (usuarioLogado) {
            cout << "1. Criar Anúncio\n";
            cout << "2. Comprar Anúncio\n";
            cout << "3. Cancelar Compra\n";
            cout << "4. Deletar Anúncio\n";
            cout << "5. Favoritar Anúncio\n";
            cout << "6. Listar Anúncios\n";
            cout << "7. Listar Compras\n";
            cout << "8. Listar Favoritos\n";
            cout << "9. Sair\n";
        } else if (adminLogado) {
            cout << "1. Criar Usuário\n";
            cout << "2. Criar Produto\n";
            cout << "3. Deletar Usuário\n";
            cout << "9. Sair\n";
        }
        cout << "Escolha uma opção: ";
        cin >> choice;

        if (usuarioLogado) {
            switch (choice) {
                case 1: {
                    Produto produto = adminLogado->criarProduto();
                    Anuncio anuncio = usuarioLogado->criarAnuncio(produto);
                    break;
                }
                case 2: {
                    if (!usuarioLogado->anuncios.empty()) {
                        cout << "Escolha a quantidade para comprar: ";
                        int quantidade;
                        cin >> quantidade;
                        Compra compra = usuarioLogado->comprar(usuarioLogado->anuncios[0], quantidade);
                    } else {
                        cout << "Nenhum anúncio disponível para compra." << endl;
                    }
                    break;
                }
                case 3: {
                    if (!usuarioLogado->compras.empty()) {
                        cout << "Digite o código da compra a ser cancelada: ";
                        string codigo;
                        cin >> codigo;
                        bool result = usuarioLogado->cancelarCompra(codigo);
                        cout << (result ? "Compra cancelada com sucesso." : "Falha ao cancelar a compra.") << endl;
                    } else {
                        cout << "Nenhuma compra disponível para cancelamento." << endl;
                    }
                    break;
                }
                case 4: {
                    if (!usuarioLogado->anuncios.empty()) {
                        cout << "Digite o título do anúncio a ser deletado: ";
                        string titulo;
                        cin.ignore();
                        getline(cin, titulo);
                        bool result = usuarioLogado->deletarAnuncio(titulo);
                        cout << (result ? "Anúncio deletado com sucesso." : "Falha ao deletar o anúncio.") << endl;
                    } else {
                        cout << "Nenhum anúncio disponível para deletar." << endl;
                    }
                    break;
                }
                case 5: {
                    if (!usuarioLogado->anuncios.empty()) {
                        cout << "Digite o título do anúncio a ser favoritado: ";
                        string titulo;
                        cin.ignore();
                        getline(cin, titulo);
                        bool result = usuarioLogado->favoritar(titulo);
                        cout << (result ? "Anúncio favoritado com sucesso." : "Falha ao favoritar o anúncio.") << endl;
                    } else {
                        cout << "Nenhum anúncio disponível para favoritar." << endl;
                    }
                    break;
                }
                case 6: {
                    cout << "Anúncios:\n";
                    for (const auto& anuncio : usuarioLogado->anuncios) {
                        cout << "- " << anuncio.titulo << endl;
                    }
                    break;
                }
                case 7: {
                    cout << "Compras:\n";
                    for (const auto& compra : usuarioLogado->compras) {
                        cout << "- Compra de " << compra.quantidade << " unidade(s) do produto com código " << compra.codigo << endl;
                    }
                    break;
                }
                case 8: {
                    cout << "Favoritos:\n";
                    for (const auto& anuncio : usuarioLogado->favoritos) {
                        cout << "- " << anuncio.titulo << endl;
                    }
                    break;
                }
                case 9: {
                    cout << "Saindo..." << endl;
                    break;
                }
                default: {
                    cout << "Opção inválida. Tente novamente." << endl;
                    break;
                }
            }
        } else if (adminLogado) {
            switch (choice) {
                case 1: {
                    Usuario novoUsuario = adminLogado->criarUsuario();
                    usuarios.push_back(novoUsuario);
                    break;
                }
                case 2: {
                    Produto novoProduto = adminLogado->criarProduto();
                    break;
                }
                case 3: {
                    cout << "Digite o login do usuário a ser deletado: ";
                    string login;
                    cin >> login;
                    adminLogado->deletarUsuario(usuarios, login);
                    break;
                }
                case 9: {
                    cout << "Saindo" << endl;
                    break;
                }
                default: {
                    cout << "Opção inválida. Tente novamente." << endl;
                    break;
                }
            }
        }
    } while (choice != 9);

    return 0;
}