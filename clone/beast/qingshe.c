//qingshe.c

#include <ansi.h>

inherit SNAKE;

void create()
{
	set_name("��Ҷ����", ({ "qing she", "she" }));
	set("race", "Ұ��");
	set("age", 2);
	set("long", "һֻ���˿�����Ƥ������Ҷ���ߡ�\n");
	set("attitude", "peaceful");
	set("str", 20);
	set("con", 20);
	set("limbs", ({ "ͷ��", "����", "�ߴ�", "β��" }) );
	set("verbs", ({ "bite" }) );

	set("snake_poison", ([
		"level"  : 40,
		"perhit" : 20,
		"remain" : 40,
		"maximum": 40,
		"supply" : 2,
	]));

	set("combat_exp", 5000 + random(4000));

	set_temp("apply/attack", 18);
	set_temp("apply/damage", 15);
	set_temp("apply/armor", 12);
	set_temp("apply/defence",16);

	setup();
}

void die()
{
	object ob;
	message_vision("$N���ڵ��ϣ����ˣ�\n", this_object());
	ob = new("/d/baituo/npc/obj/qingdan");
	ob->move(environment(this_object()));
	::die();
}
