/*
“ест по основах ќќѕ в C++:

1.  лас в C++ Ч шаблон, €кий описуЇ властивост≥ та повед≥нку обТЇкт≥в.
2. ќбТЇкт класу Ч конкретний екземпл€р, створений на основ≥ класу.
3.  онструктор Ч спец≥альний метод, €кий викликаЇтьс€ при створенн≥ обТЇкта ≥ ≥н≥ц≥ал≥зуЇ його.
4. private Ч обмежуЇ доступ до член≥в класу лише всередин≥ класу.
5. public Ч дозвол€Ї доступ до член≥в класу ззовн≥.
6. Ќасл≥дуванн€ Ч механ≥зм створенн€ нового класу на основ≥ ≥снуючого.
7. class Warrior : public Character Ч Warrior насл≥дуЇ вс≥ public ≥ protected члени Character.
8. √еттери (наприклад getHealth()) Ч використовуютьс€ дл€ безпечного доступу до приватних даних.
9. ќператор -> Ч використовуЇтьс€ дл€ доступу до член≥в обТЇкта через вказ≥вник.
10. ≤нкапсул€ц≥€ Ч приховуванн€ внутр≥шньоњ реал≥зац≥њ класу та доступ до даних через методи.
11. this Ч вказ≥вник на поточний обТЇкт класу.
*/

#include <iostream>
#include <string>
using namespace std;

class character
{
    string name;
    float health;
    float max_health;
    bool is_dead;

    void UpdateIsDead() {
        this->is_dead = getHealth() <= 0;
        if (is_dead) {
            cout << this->name << " has died!" << endl;
        }
    }
public:
    character(string name, float health)
    {
        this->name = name;
        this->health = health;
        this->max_health = health;
        UpdateIsDead();
    }

    void getinfo()
    {
        cout << "Name: " << name << "; Health: " << health << "/" << max_health << ";\n";
    }

    float getHealth() { return health; }

    void setHealth(float health) {
        this->health = health;
        if (health < 0) this->health = 0;
        if (health > max_health) this->health = max_health;
        UpdateIsDead();
    }

    void heal(float heal) { setHealth(getHealth() + heal); }
    void damage(float damage) { setHealth(getHealth() - damage); }
    string getName() { return name; }
};

class warrior : public character
{
    float strength;
public:
    warrior(string name, float health, float strength) : character(name, health) {
        this->strength = strength;
    }

    void attack(character* victim) { victim->damage(strength); }
    float getDamage() { return strength; }

    void getinfo()
    {
        cout << "Name: " << getName() << "; Health: " << getHealth() << "; Strength: " << getDamage() << ";\n";
    }
};

class zealot : public character
{
    float mana;
public:
    zealot(string name, float health, float mana) : character(name, health) {
        this->mana = mana;
    }

    void heal(character* target, float heal)
    {
        if (heal > mana) {
            cout << "Not enough mana!" << endl;
            return;
        }
        target->heal(heal);
        this->mana -= heal;
    }

    float getMana() { return mana; }

    void getinfo()
    {
        cout << "Name: " << getName() << "; Health: " << getHealth() << "; Mana: " << getMana() << ";\n";
    }
};

class necromancer : public zealot
{
public:
    necromancer(string name, float health, float mana) : zealot(name, health, mana) {}

    void revive(character* target)
    {
        if (target->getHealth() <= 0) {
            cout << getName() << " resurrects " << target->getName() << "!" << endl;
            target->setHealth(20);
        }
        else {
            cout << target->getName() << " is still alive!" << endl;
        }
    }
};

class thief : public warrior
{
public:
    thief(string name, float health, float strength) : warrior(name, health, strength) {}

    void stealLife(character* target)
    {
        float dmg = getDamage() / 2;
        target->damage(dmg);
        this->heal(dmg / 2);
        cout << getName() << " steals life from " << target->getName() << "!" << endl;
    }
};

int main()
{
    warrior w1("uno", 100, 150);
    warrior w2("dos", 100, 30);
    zealot zealot1("tres", 100, 10);
    thief thief1("shadow", 80, 60);
    necromancer necro1("darklord", 90, 50);

    w1.getinfo();
    w2.getinfo();
    cout << "--------------------" << endl;

    thief1.stealLife(&w1);
    w1.getinfo();
    thief1.getinfo();

    cout << "--------------------" << endl;

    w1.damage(200);
    necro1.revive(&w1);
    w1.getinfo();

    cout << "--------------------" << endl;
    zealot1.getinfo();

    return 0;
}
