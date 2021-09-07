#include <ansi.h>
inherit NPC;
void create()
{
	set_name("������", ({ "yin susu", "yin", "susu" }) );
	set("long",
		  "ֻ�������������ӣ��������ɷ��\n");
	set("attitude", "peaceful");
	set("title", "��ӥ��");
	set("nickname", MAG "��΢������" NOR);
	set("gender","Ů��");
	set("age", 18);
	set("per", 38);
	set("combat_exp", 800000);

	set_skill("unarmed", 70+random(50));
	set_skill("parry", 70+random(50));
	set_skill("dodge", 70+random(50));

	setup();

	carry_object("/d/beijing/npc/obj/cloth4")->wear();
}

void init()
{
	add_action("do_yun","yun");
	add_action("do_yun","exert");
}

int do_yun(string arg)
{
	object obj;

	obj=this_object();
	if (arg == "roar" )
	{
		message_vision(CYN "\n�����غȵ������ӣ�Ҫ������ô������������ɲ����㣡"NOR"\n",obj);
		return 1;
	}
	return 0;

}

int accept_fight(object who)
{
	command("say �Ҳ�����ȣ��������Ź������ι۵ģ�");
	return 0;
}

int accept_hit(object who)
{
	command("say �Ҳ�����ȣ��������Ź������ι۵ģ�");
	return 0;
}

int accept_kill(object who)
{
	command("say ��ô��Ҫ����ô������������ɲ����㣡");
	return notify_fail("ɲ�Ǽ�����û��ǲ�Ҫ�������Ϊ�á�\n");
}

int accept_ansuan(object who)
{
	return notify_fail("����밵�㣬����ֻ���᳡���ѹѹ�ļ������ˣ��������������\n");
}

void receive_damage(string type, int n)
{
	return;
}

void receive_wound(string type, int n)
{
	return;
}

