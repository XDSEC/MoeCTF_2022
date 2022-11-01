// gcc ret2text.c -fno-stack-protector -no-pie -o pwn
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

void abandon() { system("echo \"abandon is a CET-4 word^_^\""); }
void aboard() { system("echo \"aboard is a CET-4 word^_^\""); }
void absolute() { system("echo \"absolute is a CET-4 word^_^\""); }
void absolutely() { system("echo \"absolutely is a CET-4 word^_^\""); }
void absorb() { system("echo \"absorb is a CET-4 word^_^\""); }
void abstract() { system("echo \"abstract is a CET-4 word^_^\""); }
void abundant() { system("echo \"abundant is a CET-4 word^_^\""); }
void abuse() { system("echo \"abuse is a CET-4 word^_^\""); }
void academic() { system("echo \"academic is a CET-4 word^_^\""); }
void accelerate() { system("echo \"accelerate is a CET-4 word^_^\""); }
void accidental() { system("echo \"accidental is a CET-4 word^_^\""); }
void accommodate() { system("echo \"accommodate is a CET-4 word^_^\""); }
void accommodation() { system("echo \"accommodation is a CET-4 word^_^\""); }
void accompany() { system("echo \"accompany is a CET-4 word^_^\""); }
void accomplish() { system("echo \"accomplish is a CET-4 word^_^\""); }
void accordance() { system("echo \"accordance is a CET-4 word^_^\""); }
void accordingly() { system("echo \"accordingly is a CET-4 word^_^\""); }
void account() { system("echo \"account is a CET-4 word^_^\""); }
void accumulate() { system("echo \"accumulate is a CET-4 word^_^\""); }
void accuracy() { system("echo \"accuracy is a CET-4 word^_^\""); }
void accurate() { system("echo \"accurate is a CET-4 word^_^\""); }
void accustomed() { system("echo \"accustomed is a CET-4 word^_^\""); }
void acid() { system("echo \"acid is a CET-4 word^_^\""); }
void acquaintance() { system("echo \"acquaintance is a CET-4 word^_^\""); }
void acquire() { system("echo \"acquire is a CET-4 word^_^\""); }
void acre() { system("echo \"acre is a CET-4 word^_^\""); }
void action() { system("/bin/sh"); }
void adapt() { system("echo \"adapt is a CET-4 word^_^\""); }
void addition() { system("echo \"addition is a CET-4 word^_^\""); }
void additional() { system("echo \"additional is a CET-4 word^_^\""); }
void addres() { system("echo \"addres is a CET-4 word^_^\""); }
void adequate() { system("echo \"adequate is a CET-4 word^_^\""); }
void adjust() { system("echo \"adjust is a CET-4 word^_^\""); }
void administration() { system("echo \"administration is a CET-4 word^_^\""); }
void admission() { system("echo \"admission is a CET-4 word^_^\""); }
void admit() { system("echo \"admit is a CET-4 word^_^\""); }
void advance() { system("echo \"advance is a CET-4 word^_^\""); }
void advanced() { system("echo \"advanced is a CET-4 word^_^\""); }
void adventure() { system("echo \"adventure is a CET-4 word^_^\""); }
void advisable() { system("echo \"advisable is a CET-4 word^_^\""); }
void affair() { system("echo \"affair is a CET-4 word^_^\""); }
void affect() { system("echo \"affect is a CET-4 word^_^\""); }
void affection() { system("echo \"affection is a CET-4 word^_^\""); }
void afford() { system("echo \"afford is a CET-4 word^_^\""); }
void afterward() { system("echo \"afterward is a CET-4 word^_^\""); }
void age() { system("echo \"age is a CET-4 word^_^\""); }
void aggressive() { system("echo \"aggressive is a CET-4 word^_^\""); }
void aircraft() { system("echo \"aircraft is a CET-4 word^_^\""); }
void alcohol() { system("echo \"alcohol is a CET-4 word^_^\""); }
void alike() { system("echo \"alike is a CET-4 word^_^\""); }
void alloy() { system("echo \"alloy is a CET-4 word^_^\""); }
void alphabet() { system("echo \"alphabet is a CET-4 word^_^\""); }
void alter() { system("echo \"alter is a CET-4 word^_^\""); }
void alternative() { system("echo \"alternative is a CET-4 word^_^\""); }
void altitude() { system("echo \"altitude is a CET-4 word^_^\""); }
void aluminium() { system("echo \"aluminium is a CET-4 word^_^\""); }
void amaze() { system("echo \"amaze is a CET-4 word^_^\""); }
void ambulance() { system("echo \"ambulance is a CET-4 word^_^\""); }
void amongst() { system("echo \"amongst is a CET-4 word^_^\""); }
void amuse() { system("echo \"amuse is a CET-4 word^_^\""); }
void analyse() { system("echo \"analyse is a CET-4 word^_^\""); }
void analysis() { system("echo \"analysis is a CET-4 word^_^\""); }
void ancestor() { system("echo \"ancestor is a CET-4 word^_^\""); }
void anchor() { system("echo \"anchor is a CET-4 word^_^\""); }
void ancient() { system("echo \"ancient is a CET-4 word^_^\""); }
void ankle() { system("echo \"ankle is a CET-4 word^_^\""); }
void announce() { system("echo \"announce is a CET-4 word^_^\""); }
void annoy() { system("echo \"annoy is a CET-4 word^_^\""); }
void annual() { system("echo \"annual is a CET-4 word^_^\""); }
void anticipate() { system("echo \"anticipate is a CET-4 word^_^\""); }
void anxiety() { system("echo \"anxiety is a CET-4 word^_^\""); }
void anxious() { system("echo \"anxious is a CET-4 word^_^\""); }
void apart() { system("echo \"apart is a CET-4 word^_^\""); }
void apologize() { system("echo \"apologize is a CET-4 word^_^\""); }
void apparatus() { system("echo \"apparatus is a CET-4 word^_^\""); }
void appeal() { system("echo \"appeal is a CET-4 word^_^\""); }
void appetite() { system("echo \"appetite is a CET-4 word^_^\""); }
void appliance() { system("echo \"appliance is a CET-4 word^_^\""); }
void applicable() { system("echo \"applicable is a CET-4 word^_^\""); }
void application() { system("echo \"application is a CET-4 word^_^\""); }
void appoint() { system("echo \"appoint is a CET-4 word^_^\""); }
void appreciate() { system("echo \"appreciate is a CET-4 word^_^\""); }
void approval() { system("echo \"approval is a CET-4 word^_^\""); }
void approve() { system("echo \"approve is a CET-4 word^_^\""); }
void approximate() { system("echo \"approximate is a CET-4 word^_^\""); }
void arbitrary() { system("echo \"arbitrary is a CET-4 word^_^\""); }
void architecture() { system("echo \"architecture is a CET-4 word^_^\""); }
void argue() { system("echo \"argue is a CET-4 word^_^\""); }
void argument() { system("echo \"argument is a CET-4 word^_^\""); }
void arise() { system("echo \"arise is a CET-4 word^_^\""); }
void arithmetic() { system("echo \"arithmetic is a CET-4 word^_^\""); }
void arouse() { system("echo \"arouse is a CET-4 word^_^\""); }
void article() { system("echo \"article is a CET-4 word^_^\""); }
void artificial() { system("echo \"artificial is a CET-4 word^_^\""); }
void artistic() { system("echo \"artistic is a CET-4 word^_^\""); }
void ash() { system("echo \"ash is a CET-4 word^_^\""); }
void ashamed() { system("echo \"ashamed is a CET-4 word^_^\""); }
void aspect() { system("echo \"aspect is a CET-4 word^_^\""); }
void assemble() { system("echo \"assemble is a CET-4 word^_^\""); }
void assembly() { system("echo \"assembly is a CET-4 word^_^\""); }
void assess() { system("echo \"assess is a CET-4 word^_^\""); }

void (*learn[])() = {
    abandon,      aboard,      absolute,       absolutely,   absorb,
    abstract,     abundant,    abuse,          academic,     accelerate,
    accidental,   accommodate, accommodation,  accompany,    accomplish,
    accordance,   accordingly, account,        accumulate,   accuracy,
    accurate,     accustomed,  acid,           acquaintance, acquire,
    acre,         adapt,       addition,       additional,   addres,
    adequate,     adjust,      administration, admission,    admit,
    advance,      advanced,    adventure,      advisable,    affair,
    affect,       affection,   afford,         afterward,    age,
    aggressive,   aircraft,    alcohol,        alike,        alloy,
    alphabet,     alter,       alternative,    altitude,     aluminium,
    amaze,        ambulance,   amongst,        amuse,        analyse,
    analysis,     ancestor,    anchor,         ancient,      ankle,
    announce,     annoy,       annual,         anticipate,   anxiety,
    anxious,      apart,       apologize,      apparatus,    appeal,
    appetite,     appliance,   applicable,     application,  appoint,
    appreciate,   approval,    approve,        approximate,  arbitrary,
    architecture, argue,       argument,       arise,        arithmetic,
    arouse,       article,     artificial,     artistic,     ash,
    ashamed,      aspect,      assemble,       assembly,     assess};

int main() {
    char wish[64];

    printf(
        "I've prepared a gift for you, if you don't want to keep learning "
        "CET-4 words, "
        "find it out!\n");

    srand(time(NULL));
    learn[rand() % 100]();

    printf("Make a wish: ");
    read(0, wish, 0x64);

    return 0;
}

__attribute__((constructor)) void unbuffer() {
    setbuf(stdin, NULL);
    setbuf(stdout, NULL);
    setbuf(stderr, NULL);
}
