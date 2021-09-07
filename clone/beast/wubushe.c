// wubushe.c

#include <ansi.h>

inherit SNAKE;

void create()
{
	set_name("�岽��", ({ "wubu she", "she" }));
	set("long", "�岽���Ǹ����ط����ߣ��ഫ�ж���·�岽���е��С�\n");

	set("race", "Ұ��");
	set("age", 3);
	set("attitude", "peaceful");

	set("max_ging", 180);
	set("max_qi", 300);

	set("str", 10);
	set("con", 50);

	set("limbs", ({ "ͷ��", "����", "β��" }) );
	set("verbs", ({ "bite" }) );

	set("snake_poison", ([
		"level"  : 50,
		"perhit" : 25,
		"remain" : 50,
		"maximum": 50,
		"supply" : 2,
	]));

	set_temp("apply/attack",  50);
	set_temp("apply/damage",  10);
	set_temp("apply/defense", 70);
	set_temp("apply/armor",   10);

	set("combat_exp", 6000);
	setup();
}
