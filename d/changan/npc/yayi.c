//yayi.c

#include <ansi.h>

inherit NPC;

string *first_name = ({ "��","Ǯ","��","��","��","��","֣","��","��","��",
			"��","��" });
string *name_words = ({ "˳","��","��","��","��","��","��","��","־","��",
			"Т","��","��","��","��","��","��","ʢ","ʤ","��",
			"��","��","ͬ","��","��","��","��","¡","��","��",
			"��","��","��" });

varargs void drool(string msg, string who);

void create()
{
	string name, id;
	name = first_name[random(sizeof(first_name))];
	name += name_words[random(sizeof(name_words))];
	name += name_words[random(sizeof(name_words))];
	set_name(name, ({"yayi"}));
	set("title", "����");
	set("gender", "����");
	set("str", 25+random(10));
	set("age", 20+random(10));
	set("attitude", "peaceful");
	set("combat_exp", 40000);
	set_skill("unarmed", 50);
	set_skill("dodge", 50);
	set_skill("parry", 40);
	set_skill("staff", 40);
	set("max_qi", 500);
	set("max_jing", 500);
	set("max_neili", 300);
	set("neili", 300);
	set("jiali", 10);
	set("max_jingli", 300);
	set("jingli", 300);

	setup();
	carry_object(__DIR__"obj/yayifu")->wear();
	carry_object(__DIR__"obj/shawei")->wield();
}

int accept_fight(object me)
{
	command("say �ߣ���������Ҳ�������£�����\n");
	return 1;
}
