// dushe

#include <ansi.h>

inherit SNAKE;

void create()
{
	set_name("����", ({ "du she", "she" }));
	set("long", "һ֧�������ŵĶ�������������ض����㡣\n");

	set("race", "Ұ��");
	set("age", 3);
	set("attitude", "peaceful");

	set("max_ging", 80);
	set("max_qi", 80);

	set("str", 10);
	set("con", 50);

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
