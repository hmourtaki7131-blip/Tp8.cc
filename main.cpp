
#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <sstream>
using namespace std;

// Fonction pour remplacer un mot
void remplacer(string& texte, string ancien, string nouveau) {
    size_t pos = 0;

    while ((pos = texte.find(ancien, pos)) != string::npos) {
        texte.replace(pos, ancien.length(), nouveau);
        pos += nouveau.length();
    }
}

// Classe abstraite Plugin
class Plugin {
public:
    virtual string nom() const = 0;
    virtual string traiter(const string& texte) = 0;

    virtual ~Plugin() {}

    static unique_ptr<Plugin> creerPlugin(const string& type);
};

// Plugin correcteur
class CorrecteurOrthographique : public Plugin {
public:
    string nom() const override {
        return "Correcteur Orthographique";
    }

    string traiter(const string& texte) override {
        string resultat = texte;

        remplacer(resultat, "bonjor", "bonjour");
        remplacer(resultat, "salu", "salut");
        remplacer(resultat, "mercie", "merci");

        return resultat;
    }
};

// Plugin traducteur
class TraducteurAnglais : public Plugin {
public:
    string nom() const override {
        return "Traducteur Anglais";
    }

    string traiter(const string& texte) override {
        string resultat = texte;

        remplacer(resultat, "bonjour", "hello");
        remplacer(resultat, "merci", "thank you");
        remplacer(resultat, "chat", "cat");
        remplacer(resultat, "maison", "house");

        return resultat;
    }
};

// Plugin analyseur de style
class AnalyseurStyle : public Plugin {
public:
    string nom() const override {
        return "Analyseur de Style";
    }

    string traiter(const string& texte) override {
        string resultat = texte;
        int compteur = 0;
        string phrase;

        stringstream ss(texte);

        while (getline(ss, phrase, '.')) {
            stringstream mots(phrase);
            string mot;
            int nombre = 0;

            while (mots >> mot) {
                nombre++;
            }

            if (nombre > 10) {
                compteur++;
            }
        }

        if (compteur > 0) {
            resultat += "\nAttention : ";
            resultat += to_string(compteur);
            resultat += " phrase(s) trop longue(s).";
        }
        else {
            resultat += "\nStyle correct : aucune phrase trop longue.";
        }

        return resultat;
    }
};

// Factory
unique_ptr<Plugin> Plugin::creerPlugin(const string& type) {

    if (type == "correcteur")
        return make_unique<CorrecteurOrthographique>();

    if (type == "traducteur")
        return make_unique<TraducteurAnglais>();

    if (type == "analyseur")
        return make_unique<AnalyseurStyle>();

    return nullptr;
}

int main() {

    vector<unique_ptr<Plugin>> plugins;

    // Chargement des plugins
    plugins.push_back(Plugin::creerPlugin("correcteur"));
    plugins.push_back(Plugin::creerPlugin("traducteur"));
    plugins.push_back(Plugin::creerPlugin("analyseur"));

    string texte;

    cout << "Entrez votre texte : ";
    getline(cin, texte);

    // Application des plugins
    for (auto& plugin : plugins) {

        texte = plugin->traiter(texte);

        cout << "\nPlugin applique : "
             << plugin->nom() << endl;

        cout << "Texte transforme : "
             << texte << endl;
    }

    return 0;
}


