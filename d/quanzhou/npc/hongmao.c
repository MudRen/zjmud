// hongmao.c

#include <ansi.h>

inherit NPC;

void create()
{
	set_name("��ë��", ({ "hongmao gui", "gui"}));
	set("gender", "����");
	set("age", random(10) + 30);
	set("str", 25);
	set("dex", 16);
	set("long", "�������쳯����̨��ĺ�����ë�������϶���һ֧��ǹ��ǹ�ڻ�ð�����̡�\n");
	set("combat_exp", 25000);
	set("shen_type", 1);
	set("attitude", "peaceful");

	set_temp("apply/attack", 30);
	set_temp("apply/defense", 30);
	set_temp("apply/armor", 30);
	set_temp("apply/damage", 30);

	setup();
	carry_object(__DIR__"obj/huoqiang")->wield();
}

void init()
{
	object ob;

	::init();

	if (interactive(ob = this_player()) && ! is_fighting())
	{
		remove_call_out("greeting");
		call_out("greeting", 1, ob);
	}
}

void greeting(object ob)
{
	string startroom;

	if (! objectp(ob) || environment(ob) != environment()) return;

	if (stringp(startroom = query("startroom")) &&
	    find_object(startroom) == environment())
	{
		say("��ë��̧�־���һǹ�����顱��һ�Ż����ǹ�ڴܳ���\n");
		tell_object(ob, HIR "���ܲ�����ֻ�����˿�һʹ��"NOR"\n");
		ob->receive_wound("qi", 90);
	} else
		say("��ë������㣬���˰��졣\n");
}
