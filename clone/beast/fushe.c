//fushe.c

inherit SNAKE;
#include <ansi.h>

void create()
{
	set_name("����", ({ "fu she", "she" }));
	set("race", "Ұ��");
	set("age", random(10));
	set("long", "ֻ����ȫ��Ѫ�죬ͷ�����ǣ��������£��������졣\n");
	set("attitude", "peaceful");
	set("str", 20);
	set("con", 20);
	set("limbs", ({ "ͷ��", "����", "�ߴ�", "β��" }) );
	set("verbs", ({ "bite" }) );

	set("snake_poison", ([
		"level"  : 120,
		"perhit" : 10,
		"remain" : 20,
		"maximum": 20,
		"supply" : 1,
	]));

	set("combat_exp", 50000 + random(50000));

	set_temp("apply/attack", 20+random(10));
	set_temp("apply/damage", 10+random(10));
	set_temp("apply/armor",  15+random(10));
	set_temp("apply/defence",50+random(50));
	setup();
}

void die()
{
	object ob;
	message_vision("$N���ڵ��ϣ����ˣ�\n", this_object());
	ob = new("/clone/misc/shedan");
	ob->move(environment(this_object()));
	::die();
}
