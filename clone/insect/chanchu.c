// chanchu.c ���

#include <ansi.h>

inherit POISON_INSECT;

void create()
{
	set_name("���", ({ "chan chu" }) );
	set_weight(350);
	set("race", "Ұ��");
	set("age", 2);
	set("long", "һֻ���ü�Ϊ���ĵ���󡡣\n");
	set("attitude", "peaceful");
	set("str", 20);
	set("con", 20);
	set("unit", "ֻ");
	set("limbs", ({ "ͷ��", "����", "����" }) );
	set("verbs", ({ "bite" }) );

	set("insect_poison", ([
		"level"  : 20,
		"maximum": 30,
	]));

	set("combat_exp", 100);

	setup();
}
