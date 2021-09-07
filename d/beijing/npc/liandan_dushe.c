#include <ansi.h>

inherit SNAKE;

void create()
{
	set_name("����", ({ "du she", "du", "she"}));
	set("long",     "һ֧�������ŵĶ��ߣ�����������ض����㡣\n");
	set("race", "Ұ��");
	set("age", 3);
	set("attitude", "peaceful");
	set("max_ging", 40);
	set("max_qi", 40);
	set("str", 10);
	set("cor", 30);
	set("limbs", ({ "ͷ��", "����", "β��" }) );
	set("verbs", ({ "bite" }) );

	set("snake_poison", ([
		"level"   : 80,
		"remain"  : 20,
		"maximum" : 20,
		"perhit"  : 10,
		"supply"  : 1,
	]));

	set_temp("apply/attack", 10);
	set_temp("apply/damage", 10);
	set_temp("apply/armor", 10);

	set("combat_exp", 8000);

	setup();
}

void init()
{
	object ob;

	::init();

	if (interactive(ob = this_player()))
	{
		remove_call_out("kill_ob");
		call_out("kill_ob", 1, ob); 
	}
}
