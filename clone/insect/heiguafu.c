// heiguafu.c �ڹѸ�

#include <ansi.h>

inherit POISON_INSECT;

void create()
{
	set_name("�ڹѸ�", ({ "hei guafu" }) );
	set_weight(80);
	set("race", "Ұ��");
	set("age", 2);
	set("long", "һֻ���þ޴�ĳ�ª�ޱȵĴ�֩�롣\n");
	set("attitude", "peaceful");
	set("str", 20);
	set("con", 20);
	set("unit", "ֻ");
	set("limbs", ({ "ͷ��", "����", "��" }) );
	set("verbs", ({ "bite" }) );

	set("insect_poison", ([
		"level"  : 80,
		"maximum": 30,
	]));

	set("combat_exp", 100);

	setup();
}
