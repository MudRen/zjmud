// gongsun.c

inherit NPC;

#include <ansi.h>

void create()
{
	set_name("�������", ({ "gongsun daniang", "daniang" }) );
	set("gender", "Ů��" );
	set("age", 32);
	set("str", 30);
	set("per", 40);
	set("long", @LONG
һ����װ��Ů��ü���͸��һ�����ڲ�ͬ�����ʡ�
LONG);
	set("combat_exp", 10000);
	set("attitude", "friendly");

	set_skill("art-cognize", 500);
	set_skill("wujian-shu", 500);

	setup();
	carry_object(__DIR__"obj/skirt")->wear();
	carry_object("/clone/weapon/changjian")->wield();
}

int recognize_apprentice(object ob, string skill)
{
	object me;

	me = this_object();
	if (ob->query("gender") == "����")
	{
		message_vision("$N����$nһ�ۣ�������ü��û˵ʲô��\n",
			       me, ob);
		return -1;
	}

	if (ob->query("gender") == "����" &&
	    ob->query("weiwang") < 10000)
	{
		message_vision("$N���俴��$nһ�ۣ�����������"
			       "ʲô�ˣ��Ҳ�������֮������\n",
			       me, ob);
		return -1;
	}

	return 1;
}
