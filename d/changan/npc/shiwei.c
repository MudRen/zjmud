//shiwei.c

#include <ansi.h>

inherit NPC;

string *first_name = ({ "��","Ǯ","��","��","��","��","֣","��","��","��","ף","κ","��","��",
			"��","��", "��","��","��","��","ŷ��","˾��","Ľ��","���" });
string *name_words = ({ "˳","��","��","��","��","��","��","��","־","��","Т","��","��","��",
			"��","��","��","ʢ","ʤ","��","��","��","ͬ","��","��","��","��","¡",
			"��","��","��","��","��","˼","��","��","��","ƽ","��","��","ά","��",
			"��","Ϫ","��","��","ɽ","��","��","Ȫ","��","ѷ", });
	
void create()
{
	string name;
	name = first_name[random(sizeof(first_name))];
	name += name_words[random(sizeof(name_words))];
	if (random(10) > 2) name += name_words[random(sizeof(name_words))];
	set_name(name, ({"shi wei","shi","wei"}));
	set("long",
		"����λ�ػ��ʹ��Ĵ�������������װ���ֳָ�"
		"������˫Ŀ���⾼���������Ѳ�������ܵ����Ρ�\n");
	set("title", HIR"��Ʒ��������"NOR);
	set("age", 25);
	set("combat_exp", 200000);
	set("attitude", "heroism");
	set("str", 25);
	set("max_qi", 1000);
	set("max_jing", 1000);
	set("neili", 500);
	set("max_neili", 500);
	set("jiali", 30);
	set_skill("blade", 100);
	set_skill("unarmed", 100);
	set_skill("parry", 100);
	set_skill("dodge", 100);
	set_skill("force", 100);
	setup();

	carry_object(__DIR__"obj/blade")->wield();
	carry_object(__DIR__"obj/jinzhuang")->wear();
}
